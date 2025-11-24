#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /afs/cern.ch/work/s/savarghe/private/HplusMVA/CMSSW_13_0_10/src/HplusMVA/NtupleMaker
eval `scramv1 runtime -sh`
# Run the Python script
# Construct the file name based on arguments
file_name="all_${1}_${2}"

echo "Running script for file: $file_name with argument scenario: $3"

# Now, run RDataFrame.py with all passed arguments
python3 RDataFrame.py "$file_name" "$3" --channel "$4" --region "$5"

echo "$file_name with argument scenario: $3 done"
