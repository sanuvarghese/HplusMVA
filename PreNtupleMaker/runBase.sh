#!/bin/bash

# List of processes
processes=(
  "HplusM040" "HplusM050" "HplusM060" "HplusM070" "HplusM080" "HplusM090" "HplusM100"
  "HplusM110" "HplusM120" 
  "HplusM130" "HplusM140" "HplusM150" "HplusM155" "HplusM160"
   "singleTop" "Wjets" "DYjets" "VBFusion" "MCQCDMu" "MCQCDEle"
   "TTGToLL" "TTGToLNu" "TTGToQQ" "TTHToNonbb" "TTHTobb" "TTHToGG"
   "TTWJetsToLNu" "TTWJetsToQQ" "TTZToLLNuNu" "TTZToQQ" "TTbar" "DataMu" "DataEle"
)

# List of filename scenarios
filename_scenarios=(
  "base"
)

# List of argument scenarios
argument_scenarios=("base")  # Include other scenarios as needed

# Channels and region options
channels="mu"  # Assuming you want to keep the channel constant; modify as needed
regions=("A" "B" "C" "D")  # List of all regions

# Function to run the script
run_script() {
    local process=$1
    local filename_scenario=$2
    local argument_scenario=$3
    local region=$4  # Added region as a parameter

    local file_name="all_${process}_${filename_scenario}"
    echo "Running script for file: $file_name with argument scenario: $argument_scenario and region: $region"
    python3 RDataFrame.py "$file_name" "$argument_scenario" --channel $channels --region $region
    echo "$file_name with argument scenario: $argument_scenario and region: $region done"
}

# Loop over processes, filename scenarios, and regions
for process in "${processes[@]}"; do
    for filename_scenario in "${filename_scenarios[@]}"; do
        for region in "${regions[@]}"; do  # Added loop over regions
            if [[ "$filename_scenario" == "base" ]]; then
                # For the "base" filename scenario, run all argument scenarios except "base"
                for argument_scenario in "${argument_scenarios[@]}"; do
                    run_script "$process" "$filename_scenario" "$argument_scenario" "$region"
                done
            else
                # For other filename scenarios, just run the "base" argument scenario
                run_script "$process" "$filename_scenario" "base" "$region"
            fi
        done
    done
done
