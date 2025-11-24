#!/bin/bash

# Directory to search
SEARCH_DIR="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/pre/pre_all/"

# Find files with size less than 15K and loop through them
find "$SEARCH_DIR" -type f -size -15k | while read filename; do
    # Check if the filename contains "Hminus"
    if [[ "$filename" == *"Hminus"* ]]; then
        # Skip this file
        continue
    fi

    # Extract the file details with ls -lh
    file_details=$(ls -lh "$filename")
    
    # Deduce the process name and systematic
    base_filename=$(basename "$filename")
    processName=${base_filename#all_}   # Remove 'all_' prefix
    processName=${processName%_*}       # Remove '_<systematic>.root' suffix
    sysName=${base_filename##*_}        # Remove everything up to the last underscore to isolate the systematic name
    sysName=${sysName%.root}            # Remove '.root' extension    
    #root -l -b -q PreAna_sys.C'(\"$processName\",\"$sysName\")'
    #root -l -b -q PreAna_sys.C'("'$processName'","'$sysName'")'
    root -l -b -q PreAna_sys.C'("'$processName'","'$sysName'")'
    # Print the file details, process name, and systematic name
    # echo "$file_details"
#     echo "Process Name: $processName"
#     echo "Systematic Name: $sysName"
#     echo ""  # Add a newline for better readability
done
