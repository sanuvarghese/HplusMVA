#!/bin/bash

# Define the directory where the ROOT files are located
input_dir="/afs/cern.ch/work/s/savarghe/NewJEC/2018/mu/A/ExcControl" # Adjust this path to your directory containing the ROOT files

# Define the output directory for merged files
output_dir="/afs/cern.ch/work/s/savarghe/NewJEC/2018/mu/A/mergedHistos/LowMass/ExcControl" # Adjust this as needed

# Ensure output directory exists
mkdir -p "$output_dir"

# List of processes to merge
processes=(
  "TTbar" "DataMu" "DataEle"
  "HplusM040" "HplusM050" "HplusM060" "HplusM070" 
 "HplusM080" "HplusM090" "HplusM100"
 "HplusM110" "HplusM120"
 "HplusM130" "HplusM140" "HplusM150" "HplusM155" "HplusM160"
#  Uncomment if needed
 # "HminusM040" "HminusM050" "HminusM060" "HminusM070" "HminusM080" "HminusM090" "HminusM100"
 # "HminusM110" "HminusM120" "HminusM130" "HminusM140" "HminusM150" "HminusM155" "HminusM160"
  "singleTop" "Wjets" "DYjets" "VBFusion" "MCQCDMu" "MCQCDEle"
  "TTGToLL" "TTGToLNu" "TTGToQQ" "TTHToNonbb" "TTHTobb" "TTHToGG"
  "TTWJetsToLNu" "TTWJetsToQQ" "TTZToLLNuNu" "TTZToQQ"
)

# Loop through each process and merge its files
for process in "${processes[@]}"; do
    echo "Merging files for process: $process"
    
    # Define the output file name
    output_file="${output_dir}/hist_${process}_2018_mu.root"
    
    # Find and merge files for the current process
    find "${input_dir}" -name "bdt_${process}_*.root" -exec echo {} \; | xargs hadd -f "${output_file}"
    
    echo "Merged files into ${output_file}"
done

echo "All merging operations completed."
