#!/bin/bash

# Directory containing error files
error_dir="/afs/cern.ch/work/s/savarghe/private/NewJEC/Ntuple/error"

# Directory containing JDL files
jdl_dir="./condor"

# Log file to record the status of error checks and resubmission
log_file="./resubmit_log.txt"

# Batch name for all resubmitted jobs
batch_name="ResubmittedJobsBatch"

# Start fresh with the log file
> "$log_file"

# Function to submit a job individually with a batch name
submit_job() {
    jdl_path=$1
    echo "Submitting job: $jdl_path under batch name $batch_name" >> "$log_file"
    condor_submit -batch-name "$batch_name" "$jdl_path"
}

# Loop through all error files in the directory
for err_file in "$error_dir"/*.err; do
    if [ ! -s "$err_file" ]; then
        echo "Success: $err_file is empty." >> "$log_file"
    else
        # Extract the job name from the error file name
        job_name=$(basename "$err_file" .err)

        # Apply your skipping criteria as before
        if [[ "$job_name" == *"DataMu"* ]] || 
           [[ "$job_name" == *"DataEle"* ]] || 
           [[ "$job_name" == HplusM0[4-7]0* ]] || 
           [[ "$job_name" == *"jerup"* ]] || 
           [[ "$job_name" == *"jerdown"* ]] || 
           [[ "$job_name" == *"metup"* ]] || 
           [[ "$job_name" == *"metdown"* ]] ||
           [[ "$job_name" == *"iso20"* ]] || 
           [[ "$job_name" == MCQCD* ]] || 
           [[ "$job_name" == *"TTWJetsToLNu"* ]] || 
           [[ "$job_name" == *"TTHTobb"* ]] || 
           [[ "$job_name" == *"TTHToNonbb"* ]] ||
	   { [[ "$job_name" != *"TTbar"* ]] && 
             ([[ "$job_name" == *"cp5up"* ]] || 
              [[ "$job_name" == *"cp5down"* ]] || 
              [[ "$job_name" == *"hdampup"* ]] || 
              [[ "$job_name" == *"hdampdown"* ]] || 
              [[ "$job_name" == *"mtopup"* ]] || 
              [[ "$job_name" == *"mtopdown"* ]]); }; then
            echo "Skipping job: $job_name" >> "$log_file"
            continue
        fi

        echo "Failed: $err_file contains errors. Preparing for resubmission." >> "$log_file"

        # Construct the path to the corresponding JDL file
        jdl_file_path="$jdl_dir/${job_name}.jdl"

        if [ -f "$jdl_file_path" ]; then
            echo "Resubmitting $job_name." >> "$log_file"
            submit_job "$jdl_file_path"
        else
            echo "Error: JDL file does not exist for $job_name" >> "$log_file"
        fi
    fi
done

echo "Check $log_file for submission details and any errors."
