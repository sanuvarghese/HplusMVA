#!/bin/bash

# Path to the directory containing your DAG and related files
JDL_DIRECTORY="./condor_muA"
DAG_FILE_NAME="submit_jobs.dag"

# Full path to the DAG file
DAG_FILE_PATH="${JDL_DIRECTORY}/${DAG_FILE_NAME}"

# Check if DAG-related files exist and remove them
if [ -f "${DAG_FILE_PATH}.condor.sub" ]; then
    echo "Removing existing DAG submit file."
    rm "${DAG_FILE_PATH}.condor.sub"
fi

if [ -f "${DAG_FILE_PATH}.lib.out" ]; then
    echo "Removing existing DAG lib out file."
    rm "${DAG_FILE_PATH}.lib.out"
fi

if [ -f "${DAG_FILE_PATH}.lib.err" ]; then
    echo "Removing existing DAG lib err file."
    rm "${DAG_FILE_PATH}.lib.err"
fi

if [ -f "${DAG_FILE_PATH}.dagman.out" ]; then
    echo "Removing existing DAGMan output file."
    rm "${DAG_FILE_PATH}.dagman.out"
fi

if [ -f "${DAG_FILE_PATH}.dagman.log" ]; then
    echo "Removing existing DAGMan log file."
    rm "${DAG_FILE_PATH}.dagman.log"
fi

# Submit the DAG job
echo "Submitting DAG job: ${DAG_FILE_PATH}"
condor_submit_dag -f "${DAG_FILE_PATH}"
