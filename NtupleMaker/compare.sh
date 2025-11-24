#!/bin/bash

# Directories containing the ROOT files
dir1="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/pre/pre_all"
dir2="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/post/post_all"

# Temporary files to hold the list of filenames (without path)
tmp1=$(mktemp)
tmp2=$(mktemp)

# Extract filenames without paths
ls "$dir1" > "$tmp1"
ls "$dir2" > "$tmp2"

# Identify files in dir1 not in dir2 and vice versa
missingInDir2=$(comm -23 <(sort "$tmp1") <(sort "$tmp2"))
missingInDir1=$(comm -13 <(sort "$tmp1") <(sort "$tmp2"))

echo "Files in $dir1 not in $dir2:"
echo "$missingInDir2"

echo ""
echo "Files in $dir2 not in $dir1:"
echo "$missingInDir1"

# Clean up temporary files
rm "$tmp1" "$tmp2"
