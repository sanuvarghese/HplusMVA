#!/bin/bash

# Directories containing ROOT files
DIR1="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/pre/pre_all"
DIR2="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/post/post_all"

# Loop over ROOT files in the first directory
for FILE1 in $DIR1/*.root; do
    # Extract filename for comparison
    FILENAME=$(basename "$FILE1")
    
    # Check if this file exists in the second directory
    if [ -f "$DIR2/$FILENAME" ]; then
        # Get file sizes
        SIZE1=$(stat -c%s "$FILE1")
        SIZE2=$(stat -c%s "$DIR2/$FILENAME")
        
        # Calculate the ratio of the sizes
        # Assuming SIZE1 is the larger size to avoid division by zero
        if [ $SIZE1 -gt $SIZE2 ]; then
            RATIO=$(echo "$SIZE1 / $SIZE2" | bc -l)
        else
            RATIO=$(echo "$SIZE2 / $SIZE1" | bc -l)
        fi
        
        # Check if the ratio is 2 or more
        IS_DOUBLE=$(echo "$RATIO >= 2" | bc)
        if [ "$IS_DOUBLE" -eq 1 ]; then
            echo "The size of $FILENAME differs by a factor of 2 or more between directories."
            echo "Size in $DIR1: $SIZE1 bytes"
            echo "Size in $DIR2: $SIZE2 bytes"
        fi
    else
        echo "File $FILENAME does not exist in $DIR2"
    fi
done
