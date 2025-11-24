#!/bin/bash

# Define the array of mass values including special case 155
masses=(40 50 60 70 80 90 100 110 120 130 140 150 155 160)

# Define the list of background files (without the mass-specific Hplus files)
# Add or remove file names as per your actual background file names
background_files=(
  "hist_DYjets_2018_mu.root"
  "hist_DataEle_2018_mu.root"
  "hist_NewDataMu_2018_mu.root"
  "hist_UltimDataMu_2018_mu.root"
  "hist_UltimDataMu1_2018_mu.root"
  "hist_DataMu_2018_mu.root"
  "QCD_dd_2018.root"
  "hist_MCQCDMu_2018_mu.root"
  "hist_TTG_2018_mu.root"
  "hist_TTH_2018_mu.root"
  "hist_TTW_2018_mu.root"
  "hist_TTZ_2018_mu.root"
  "hist_TTbar_2018_mu.root"
  "hist_VBFusion_2018_mu.root"
  "hist_Wjets_2018_mu.root"
  "hist_singleTop_2018_mu.root"
)

# Merge TTG, TTH, TTW, and TTZ files
echo "Merging TTG, TTH, TTW, and TTZ files..."

# TTG
hadd -f -k hist_TTG_2018_mu.root hist_TTGToLL_2018_mu.root hist_TTGToLNu_2018_mu.root hist_TTGToQQ_2018_mu.root

# TTH
hadd -f -k hist_TTH_2018_mu.root hist_TTHToGG_2018_mu.root hist_TTHToNonbb_2018_mu.root hist_TTHTobb_2018_mu.root

# TTW
hadd -f -k hist_TTW_2018_mu.root hist_TTWJetsToLNu_2018_mu.root hist_TTWJetsToQQ_2018_mu.root

# TTZ
hadd -f -k hist_TTZ_2018_mu.root hist_TTZToLLNuNu_2018_mu.root hist_TTZToQQ_2018_mu.root

for mass in "${masses[@]}"
do
    # Create the mass directory if it doesn't exist
    mkdir -p "mass$mass"

    # Copy all background files to the mass directory
    for file in "${background_files[@]}"
    do
        cp -v "$file" "mass$mass/"
    done

    # Copy the specific Hplus mass file to the mass directory
    hplus_file="hist_HplusM${mass}_2018_mu.root"
    if [ -f "$hplus_file" ]; then
        cp -v "$hplus_file" "mass$mass/"
    else
        echo "Warning: $hplus_file does not exist."
    fi
done

echo "All files have been copied to their respective mass directories."
