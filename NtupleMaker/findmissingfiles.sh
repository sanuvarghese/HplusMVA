#!/bin/bash

# Directories to compare
dir1="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/pre/pre_all"
dir2="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/post/post_all"

# Create temporary files to hold the sorted list of filenames (without paths)
temp1=$(mktemp)
temp2=$(mktemp)

# Populate temporary files with sorted, basename-only filenames
find "$dir1" -type f -exec basename {} \; | sort > "$temp1"
find "$dir2" -type f -exec basename {} \; | sort > "$temp2"

# Use 'comm' to compare the files
# -3 suppresses lines that appear in both files, leaving only unique lines
# Output sections are separated for clarity
echo "Files unique to $dir1:"
comm -23 "$temp1" "$temp2"

echo ""
echo "Files unique to $dir2:"
comm -13 "$temp1" "$temp2"

# Clean up temporary files
rm "$temp1" "$temp2"
