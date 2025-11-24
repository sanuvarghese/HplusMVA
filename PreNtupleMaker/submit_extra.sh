#!/bin/bash

# Directory containing your JDL files
JDL_DIRECTORY="./jdl"

# Batch name for grouping jobs
BATCH_NAME="PreNtupleMaker"

# Specific systematics for TTbar
TTBAR_SYSTEMATICS=("cp5up" "cp5down" "hdampup" "hdampdown" "mtopdown" "mtopup")

# Loop through each JDL file in the directory
for jdl_file in "$JDL_DIRECTORY"/*.jdl; do
    # Check if file name matches any of the TTbar systematics
    for syst in "${TTBAR_SYSTEMATICS[@]}"; do
        if [[ "$jdl_file" == *"$syst"* ]]; then
            echo "Submitting $jdl_file under batch name $BATCH_NAME for TTbar systematic $syst"
            condor_submit -batch-name "$BATCH_NAME" "$jdl_file"
        fi
    done
done

echo "All TTbar systematic jobs submitted under the batch name $BATCH_NAME."
