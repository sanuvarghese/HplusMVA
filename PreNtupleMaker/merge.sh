#!/bin/bash

# Directories containing the ROOT files
dir1="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2016/pre/pre_all"
dir2="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2016/post/post_all"

# Output directory for merged ROOT files
outputDir="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2016/pre/Combined_all"

# Check if output directory exists, if not create it
if [ ! -d "$outputDir" ]; then
    mkdir -p "$outputDir"
fi

# Loop through ROOT files in the first directory
for file1 in "$dir1"/*.root; do
    # Extract the filename without the path
    filename=$(basename "$file1")
    
    # Check if the file with the same name exists in the second directory
    file2="$dir2/$filename"
    if [ -f "$file2" ]; then
        # File exists in both directories, merge them
        outputFile="$outputDir/$filename"
        echo "Merging $file1 and $file2 into $outputFile"
        hadd -f "$outputFile" "$file1" "$file2"
    else
        echo "File $file2 does not exist. Skipping."
    fi
done
