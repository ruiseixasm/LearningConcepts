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
