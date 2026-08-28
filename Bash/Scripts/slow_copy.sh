#!/bin/bash

ORIGIN="/mnt/wd_black/Videos/Movies"
DESTINY="/mnt/red/Videos/Movies"

# TIME LIMIT PER FILE (ex: 120 seconds)
# Skips if it takes more than 120 seconds.
TIME_LIMIT="120s"

# Finds all files under the ORIGIN directory
find "$ORIGIN" -type f | while read -r file; do
    
    # Converts to the full file path for destiny
    relative_path="${file#$ORIGIN/}"
    absolute_path="$DESTINY/$relative_path"
    
    # Creates the needed directory if missing
    mkdir -p "$(dirname "$absolute_path")"
    
    echo "Processing: $relative_path"
    
    # Executes the rsync for a single file with a timeout
    timeout "$TIME_LIMIT" rsync -avh --progress --append-verify --partial "$file" "$absolute_path"
    
    # Checks if there was any interruption (Exit code 124 for timeout)
    if [ $? -eq 124 ]; then
        echo "⚠️ ALERT: file transfer too slow! Jumping..."
        # Records jumped files
        echo "$file" >> "$DESTINY/jumped_files.txt"
    fi
done

echo "🎉 Concluded!"
