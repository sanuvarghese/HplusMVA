#!/bin/bash

# Directories containing the ROOT files to merge
dir1="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2016/pre/pre_all"
dir2="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2016/post/post_all"

# Output directory for merged ROOT files
outputDir="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2016/pre/test2"

# File containing the list of ROOT files to re-merge
listFile="failed_verifications.txt"

# Ensure the output directory exists
mkdir -p "$outputDir"

# Read each filename from the list and perform the merge
while read -r filename; do
    # Construct the full paths for source files and the output file
    file1="$dir1/$filename"
    file2="$dir2/$filename"
    outputFile="$outputDir/$filename"
    
    # Check if source files exist before attempting to merge
    if [[ -f "$file1" && -f "$file2" ]]; then
        echo "Merging $filename into $outputFile"
        hadd -f "$outputFile" "$file1" "$file2"
    else
        echo "Skipping $filename as one or both source files do not exist."
    fi
done < "$listFile"
