# Scripts Examples
## Timeout copies
```sh
#!/bin/bash

ORIGIN="/mnt/wd_black/Videos/Series"
DESTINY="/mnt/red/Videos/Series"

# TIME LIMIT PER FILE (120 seconds)
# Skips if it takes more than 120 seconds.
TIME_LIMIT="120s"

# Finds all files under the ORIGIN directory
find "$ORIGIN" -type f | while read -r file; do
    
    # Converts to the full file path for destiny
    relative_path="${file#$ORIGIN/}"
    absolute_path="$DESTINY/$relative_path"
    
    # Creates the needed directory if missing
    mkdir -p "$(dirname "$absolute_path")"

    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "🎬 Processing: $relative_path"
    
    # Executes native rsync with real-time speed and progress visibility
    timeout "$TIME_LIMIT" rsync -a --append-verify --partial --info=progress2 "$file" "$absolute_path"
        
    status=$?
    
    # Checks if there was any interruption (Exit code 124 for timeout)
    if [ $status -eq 124 ]; then
        echo -e "\n⚠️ ALERT: file transfer too slow! Jumping..."
        echo "$file" >> "$DESTINY/jumped_files.txt"
    elif [ $status -eq 0 ]; then
        echo -e "\n✅ [OK] Finished or already up to date."
    fi
done

echo "🎉 Concluded!"
```

## Repeated movie files
To search for movies that are repated based only on the first word in their name
```sh
#!/bin/bash

video_extensions="mp4|mkv|avi|mov|flv|wmv|webm|mpeg|mpg"

# Step 1: Count occurrences of each first word
declare -A word_count

while IFS= read -r -d '' file; do
    filename=$(basename "$file")
    if [[ "$filename" =~ \.($video_extensions)$ ]]; then
        # Get first word (case-insensitive)
        first_word=$(echo "${filename%.*}" | awk -F'[ ._-]' '{print tolower($1)}')
        
        # Initialize if not exists, then increment
        if [[ -z "${word_count[$first_word]}" ]]; then
            word_count[$first_word]=1
        else
            ((word_count[$first_word]++))
        fi
    fi
done < <(find . -type f -print0 2>/dev/null)

# Step 2: For each word with count > 1, find all matching files
first_group=1

for word in "${!word_count[@]}"; do
    # Only process if count > 1
    if [ ${word_count["$word"]} -gt 1 ]; then
        # Find all files matching this word
        matches=()
        
        while IFS= read -r -d '' file; do
            filename=$(basename "$file")
            if [[ "$filename" =~ \.($video_extensions)$ ]]; then
                file_word=$(echo "${filename%.*}" | awk -F'[ ._-]' '{print tolower($1)}')
                if [ "$file_word" == "$word" ]; then
                    matches+=("$file")
                fi
            fi
        done < <(find . -type f -print0 2>/dev/null)
        
        # Print the group
        if [ $first_group -eq 0 ]; then
            echo ""
        fi
        
        echo "=== Group: $word (${word_count[$word]} files) ==="
        for file in "${matches[@]}"; do
            echo "$file"
        done
        
        first_group=0
    fi
done
```

## Tagged Backups
To keep a backup copy of folders that are tagged as such with one of these tags:
```
backup.blue
backup.black
```
So, the scrip becomes:
```sh
#!/bin/bash

###############################################################################
# backup.sh
#
# Tag-based rsync backup system
#
# SOURCE:
#   /mnt/red
#
# TARGETS:
#   /mnt/black
#   /mnt/blue
#
# A directory is selected for backup by placing a tag file inside it:
#
#   backup.black
#   backup.blue
#
# The name after "backup." identifies the target drive under /mnt.
#
# Example:
#
#   /mnt/red/Documents/backup.blue
#
# means:
#
#   /mnt/red/Documents/
#           ↓
#   /mnt/blue/Documents/
#
# The entire directory is copied.
#
# If a directory contains a backup tag, that directory is considered a
# complete backup unit. The recursive scan DOES NOT continue inside it.
#
###############################################################################


############################
# CONFIGURATION
############################

SOURCE="/mnt/red"

# All drives that are allowed to be backup targets.
TARGETS=(
    "/mnt/black"
    "/mnt/blue"
)

TAG_PREFIX="backup."


############################
# CHECK SOURCE
############################

# The source drive is a global precondition.
#
# If it isn't mounted, nothing can safely be done.
# In particular, REMOVE must never run without the source available.
#
# -d only checks that the directory exists, so additionally verify that
# SOURCE is actually a mount point.

if ! mountpoint -q "$SOURCE"; then
    echo "ERROR: Source drive is not mounted: $SOURCE"
    echo "Backup aborted."
    exit 1
fi

echo "Source mounted: $SOURCE"


############################
# FIND MOUNTED TARGETS
############################

# PROCESSABLE_TARGETS contains only targets that:
#
#   1. Are configured above
#   2. Are actually mounted
#
# This set is established ONCE at the beginning.
#
# Both COPY and REMOVE use this set.
#
# Therefore, if /mnt/blue isn't mounted, there is no point in processing
# backup.blue at all.

declare -A PROCESSABLE_TARGETS

SOURCE_NAME="${SOURCE##*/}"

for target in "${TARGETS[@]}"; do

    target_name="${target##*/}"

    # Never allow the source drive to be a backup target.
    if [[ "$target_name" == "$SOURCE_NAME" ]]; then
        echo "ERROR: Target is the source drive: $target"
        echo "Ignoring it."
        continue
    fi

    if mountpoint -q "$target"; then
        PROCESSABLE_TARGETS["$target_name"]="$target"
        echo "Target mounted: $target"
    else
        echo "Target NOT mounted: $target"
    fi

done


############################
# CHECK THAT AT LEAST ONE
# TARGET IS AVAILABLE
############################

if [ "${#PROCESSABLE_TARGETS[@]}" -eq 0 ]; then

    echo
    echo "ERROR: No target drives are mounted."
    echo "Backup aborted."

    exit 1

fi

echo
echo "Processable targets:"

for name in "${!PROCESSABLE_TARGETS[@]}"; do
    echo "  $name -> ${PROCESSABLE_TARGETS[$name]}"
done


###############################################################################
# COPY
###############################################################################

echo
echo "========================================"
echo "COPY"
echo "========================================"


###############################################################################
# process_directory
#
# Arguments:
#
#   $1 = directory currently being scanned
#
# This function recursively scans the source.
#
# If it finds:
#
#   backup.blue
#
# inside the current directory, the ENTIRE current directory is copied to:
#
#   /mnt/blue/<relative path>
#
# and the function returns immediately.
#
# This is the important pruning behaviour:
#
# Once a directory has a backup tag, we DO NOT scan anything below it.
###############################################################################

process_directory()
{
    local directory="$1"

    local tag
    local target_name
    local target
    local relative_path
    local destination


    ###########################################################################
    # LOOK FOR BACKUP TAGS IN THIS DIRECTORY
    ###########################################################################

    for tag in "$directory"/${TAG_PREFIX}*; do

        # If the glob didn't match anything, skip it.
        [ -e "$tag" ] || continue

        # Only regular files are considered tags.
        [ -f "$tag" ] || continue


        #######################################################################
        # Extract target name
        #
        # Example:
        #
        #   /mnt/red/Documents/backup.blue
        #
        # basename -> backup.blue
        # remove prefix -> blue
        #######################################################################

        target_name="$(basename "$tag")"
        target_name="${target_name#"$TAG_PREFIX"}"


        #######################################################################
        # Check whether this target is in the processable set.
        #
        # If /mnt/blue wasn't mounted, blue won't exist in this associative
        # array and the tag is ignored.
        #######################################################################

        if [[ -z "${PROCESSABLE_TARGETS[$target_name]+_}" ]]; then

            echo
            echo "Skipping:"
            echo "  $directory"
            echo "  Tag: $target_name"
            echo "  Target is not processable."

            continue

        fi


        target="${PROCESSABLE_TARGETS[$target_name]}"


        #######################################################################
        # Calculate path relative to SOURCE
        #
        # Example:
        #
        #   directory = /mnt/red/Documents/Projects
        #
        #   relative_path = Documents/Projects
        #######################################################################

        relative_path="${directory#"$SOURCE"/}"


        #######################################################################
        # Build destination
        #
        #   /mnt/blue/Documents/Projects
        #######################################################################

        destination="$target/$relative_path"


        #######################################################################
        # COPY THE ENTIRE DIRECTORY
        #######################################################################

        echo
        echo "BACKUP:"
        echo "  Source:      $directory"
        echo "  Tag:         $target_name"
        echo "  Destination: $destination"
        echo

        mkdir -p "$destination"


        #######################################################################
        # rsync
        #
        # -a = archive mode
        #
        # The trailing slash on the source means:
        #
        #   copy the CONTENTS of directory
        #
        # into the already-created destination directory.
        #######################################################################

        rsync -a \
            "$directory/" \
            "$destination/"


        #######################################################################
        # IMPORTANT:
        #
        # Do NOT recurse into this directory.
        #
        # The tag means the entire directory has already been selected as a
        # backup unit.
        #######################################################################

        return

    done


    ###########################################################################
    # NO BACKUP TAG FOUND
    #
    # Therefore this directory itself isn't a backup unit.
    #
    # Continue scanning its subdirectories.
    ###########################################################################

    local child

    for child in "$directory"/*; do

        [ -d "$child" ] || continue

        process_directory "$child"

    done
}


###############################################################################
# Start recursive COPY scan
###############################################################################

process_directory "$SOURCE"


###############################################################################
# REMOVE
###############################################################################

echo
echo "========================================"
echo "REMOVE"
echo "========================================"


###############################################################################
# REMOVE works from the TARGET side.
#
# For every backup-tagged directory found on a processable target:
#
#   1. Determine its corresponding source directory.
#   2. If that source directory does NOT exist:
#          SKIP
#   3. If the source directory exists:
#          check for the corresponding tag.
#   4. If the tag no longer exists:
#          remove the entire target directory.
#
# The source-mounted condition was already checked globally at the beginning.
#
# Therefore there is deliberately NO second "is SOURCE mounted?" check here.
###############################################################################


remove_obsolete()
{
    local target_name="$1"
    local target="$2"

    local tag
    local tag_name
    local directory
    local relative_path
    local source_directory
    local source_tag


    ###########################################################################
    # Find all backup tags belonging to this target.
    #
    # Example:
    #
    #   /mnt/blue/Documents/backup.blue
    #
    ###########################################################################

    while IFS= read -r -d '' tag; do


        #######################################################################
        # Extract the directory containing the tag.
        #######################################################################

        directory="$(dirname "$tag")"


        #######################################################################
        # Calculate its path relative to the target drive.
        #
        # Example:
        #
        #   /mnt/blue/Documents
        #
        # becomes:
        #
        #   Documents
        #######################################################################

        relative_path="${directory#"$target"/}"


        #######################################################################
        # Corresponding source directory
        #
        #   /mnt/red/Documents
        #######################################################################

        source_directory="$SOURCE/$relative_path"


        #######################################################################
        # SAFETY CONDITION
        #
        # If the corresponding source directory doesn't exist,
        # DO NOT DELETE anything.
        #
        # This handles situations such as a directory having been removed
        # from the source.
        #######################################################################

        if [ ! -d "$source_directory" ]; then

            echo
            echo "REMOVE SKIPPED:"
            echo "  Target directory: $directory"
            echo "  Source directory does not exist:"
            echo "    $source_directory"

            continue

        fi


        #######################################################################
        # Determine the corresponding source tag.
        #
        # Since this function is processing target_name, the expected tag is:
        #
        #   backup.blue
        #
        # or:
        #
        #   backup.black
        #######################################################################

        source_tag="$source_directory/${TAG_PREFIX}${target_name}"


        #######################################################################
        # If the source tag still exists, the target directory is still
        # supposed to be backed up.
        #######################################################################

        if [ -f "$source_tag" ]; then

            echo
            echo "KEEP:"
            echo "  $directory"
            echo "  Source tag exists."

            continue

        fi


        #######################################################################
        # The source directory exists, but its backup tag no longer exists.
        #
        # Therefore this entire directory is no longer selected for this
        # target and can be removed from the target.
        #######################################################################

        echo
        echo "REMOVE:"
        echo "  $directory"
        echo "  Source exists:"
        echo "    $source_directory"
        echo "  Source tag missing:"
        echo "    $source_tag"


        rm -rf -- "$directory"


        #######################################################################
        # IMPORTANT:
        #
        # The target directory is removed entirely.
        #
        # We do not simply remove the tag or synchronize it with rsync.
        #######################################################################

    done < <(
        find "$target" \
            -type f \
            -name "${TAG_PREFIX}${target_name}" \
            -print0
    )
}


###############################################################################
# Process every mounted target
###############################################################################

for target_name in "${!PROCESSABLE_TARGETS[@]}"; do

    target="${PROCESSABLE_TARGETS[$target_name]}"

    echo
    echo "Checking obsolete backups on:"
    echo "  $target"

    remove_obsolete "$target_name" "$target"

done


###############################################################################
# DONE
###############################################################################

echo
echo "========================================"
echo "BACKUP COMPLETE"
echo "========================================"
```

