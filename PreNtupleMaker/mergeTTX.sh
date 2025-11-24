#!/bin/bash

# Define the base directory and output directory
base_dir="/afs/cern.ch/work/s/savarghe/private/HplusMVA/CMSSW_13_0_10/src/HplusMVA/PreNtupleMaker/root_files/QCDRBI/2016"
output_dir="${base_dir}"

# Define the required output files and corresponding input files to hadd
declare -A hadd_files=(
    ["IsoMET_QCD_TTW_2016.root"]="IsoMET_QCD_TTWJetsToLNu_2016.root IsoMET_QCD_TTWJetsToQQ_2016.root"
    ["IsoMET_QCD_TTZ_2016.root"]="IsoMET_QCD_TTZToLLNuNu_2016.root IsoMET_QCD_TTZToQQ_2016.root"
    ["IsoMET_QCD_TTG_2016.root"]="IsoMET_QCD_TTGToLL_2016.root IsoMET_QCD_TTGToLNu_2016.root IsoMET_QCD_TTGToQQ_2016.root"
    ["IsoMET_QCD_TTH_2016.root"]="IsoMET_QCD_TTHToGG_2016.root IsoMET_QCD_TTHToNonbb_2016.root IsoMET_QCD_TTHTobb_2016.root"
)

# Loop through the dictionary and hadd files
for output_file in "${!hadd_files[@]}"; do
    # Construct the full paths of the input files
    input_files=""
    for file in ${hadd_files[$output_file]}; do
        input_files+="${base_dir}/${file} "
    done

    # Run hadd command
    echo "Creating ${output_file} by combining: ${input_files}"
    hadd -f "${output_dir}/${output_file}" ${input_files}
done

echo "All required files have been created."
