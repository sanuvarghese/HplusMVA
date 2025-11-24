#!/bin/bash
rm -rf *.dag*

# Directory containing error files
error_dir="/afs/cern.ch/work/s/savarghe/NewJEC/2018/ele/A/LowMass/ExcTight/log"

# Directory containing JDL files
jdl_dir="./condor2018_lowmass"


# New DAG file for resubmitting failed jobs
resubmit_dag_file="resubmit_jobs1.dag"

# Log file to record the status of error checks and resubmission
log_file="resubmit_log.txt"

# Start fresh with the DAG and log file
> "$resubmit_dag_file"
> "$log_file"

# Function to add a job to the DAG file
add_job_to_dag() {
    job_name=$1
    jdl_path=$2
    echo "JOB $job_name $jdl_path" >> "$resubmit_dag_file"
}
# Loop through all error files in the directory
for err_file in "$error_dir"/*.err; do
    if [ ! -s "$err_file" ]; then
        echo "Success: $err_file is empty." >> "$log_file"
    else
        # Extract the job name from the error file name
        job_name=$(basename "$err_file" .err)

        # Skip DataMu, DataEle jobs, HplusM040 to HplusM070 jobs, specific patterns,
        # and jobs with names containing "TTWJetsToLNu", "TTHTobb", "TTHToNonbb"
        if [[ "$job_name" == *"DataMu"* ]] || 
#           [[ "$job_name" == *"DataEle"* ]] || 
#           [[ "$job_name" == HplusM0[4-7]0* ]] || 
           [[ "$job_name" == *"jerup"* ]] || 
           [[ "$job_name" == *"jerdown"* ]] || 
           [[ "$job_name" == *"metup"* ]] || 
           [[ "$job_name" == *"metdown"* ]] || 
 #          [[ "$job_name" == MCQCD* ]] || 
           # [[ "$job_name" == *"TTWJetsToLNu"* ]] || 
           # [[ "$job_name" == *"TTHTobb"* ]] || 
           # [[ "$job_name" == *"TTHToNonbb"* ]]; then
            echo "Skipping job: $job_name" >> "$log_file"
            continue
        fi

        echo "Failed: $err_file contains errors. Preparing for resubmission." >> "$log_file"

        # Construct the path to the corresponding JDL file
        jdl_file_path="$jdl_dir/${job_name}.jdl"

        if [ -f "$jdl_file_path" ]; then
            echo "Adding $job_name to resubmission DAG." >> "$log_file"
            add_job_to_dag "$job_name" "$jdl_file_path"
        else
            echo "Error: JDL file does not exist for $job_name" >> "$log_file"
        fi
    fi
done


# Check if there are any jobs to resubmit
if [ -s "$resubmit_dag_file" ]; then
    echo "Submitting resubmission DAG." >> "$log_file"
    condor_submit_dag "$resubmit_dag_file"
    echo "All failed jobs have been resubmitted. Check $log_file for details."
else
    echo "No failed jobs to resubmit. Check $log_file for details."
fi
