#!/bin/bash

# Check if the build folder exists
if [ -d "build" ]; then
    echo "Build folder exists. Changing directory to it..."
else
    # echo "cuild folder does not exist. Please create it first with 'mkdir build'..."
    echo "Build folder does not exist. Creating it..."
    mkdir build
fi

# Run cmake commands
cd build
cmake ..
make
cd ..
echo "Files that will be considered in the next git commit..."
git ls-files --others --exclude-standard

# Install linux cmake needed build-essential if cmake outputs errors:
# sudo apt install build-essential
