#!/bin/bash

# Directory containing your JDL files
JDL_DIRECTORY="condor2018mu_topPt_low"

# Batch name for grouping jobs
BATCH_NAME="ExcTight2018TopPtmu_low"

# Loop through each JDL file in the directory and submit it
for jdl_file in "$JDL_DIRECTORY"/*.jdl; do
    echo "Submitting $jdl_file under batch name $BATCH_NAME"
    condor_submit -batch-name "$BATCH_NAME" "$jdl_file"
done

echo "All jobs submitted under the batch name $BATCH_NAME."
