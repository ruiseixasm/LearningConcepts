#!/bin/bash

# Check if Firefox is running
if pgrep firefox >/dev/null; then
    # If Firefox is running, kill all instances
    echo "Firefox is running. Killing..."
    killall firefox
    if pgrep firefox >/dev/null; then
        echo "Firefox NOT killed."
    else
        echo "Firefox killed."
    fi
else
    echo "Firefox is not running."
fi

# Check if Firefox is running
if pgrep firefox >/dev/null; then
    # If Firefox is running, kill all instances
    echo "Firefox is running. Killing..."
    pkill firefox
    if pgrep firefox >/dev/null; then
        echo "Firefox NOT killed."
    else
        echo "Firefox killed."
    fi
else
    echo "Firefox is not running."
fi
