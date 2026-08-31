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
