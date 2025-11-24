#!/bin/bash

# Directories for 2016, 2017, and 2018
years=("2016" "2017" "2018")

# Base path where the directories are located
base_path="/eos/cms/store/group/phys_b2g/savarghe/NewJEC"

# Loop over each year
for year in "${years[@]}"; do
    echo "Processing year: $year"
    
    # Paths to mu directory for each year
    mu_path="$base_path/$year/Full_Ntuples/training_base/mu/A"
    
    # Merge all HplusM* files
    echo "Merging HplusM files for $year..."
    hadd -f "$mu_path/all_HplusM_base_$year_mu.root" $mu_path/all_HplusM*_base_${year}_mu.root
    
    # Merge all TTbar files
    echo "Merging TTbar files for $year..."
    hadd -f "$mu_path/all_TTbar_base_$year_mu.root" "$mu_path/all_TTbar_base_${year}_mu.root"
    
    echo "Finished processing for $year."
done

# Combine all years into a single file for HplusM and TTbar
combined_path="/eos/cms/store/group/phys_b2g/savarghe/NewJEC/combined"

# Create the combined directory if it doesn't exist
mkdir -p "$combined_path"

echo "Merging all years' HplusM files..."
hadd -f "$combined_path/all_HplusM_base_combined_mu.root" \
    "$base_path/2016/Full_Ntuples/training_base/mu/A/all_HplusM_base_2016_mu.root" \
    "$base_path/2017/Full_Ntuples/training_base/mu/A/all_HplusM_base_2017_mu.root" \
    "$base_path/2018/Full_Ntuples/training_base/mu/A/all_HplusM_base_2018_mu.root"

echo "Merging all years' TTbar files..."
hadd -f "$combined_path/all_TTbar_base_combined_mu.root" \
    "$base_path/2016/Full_Ntuples/training_base/mu/A/all_TTbar_base_2016_mu.root" \
    "$base_path/2017/Full_Ntuples/training_base/mu/A/all_TTbar_base_2017_mu.root" \
    "$base_path/2018/Full_Ntuples/training_base/mu/A/all_TTbar_base_2018_mu.root"

echo "All files have been merged successfully!"
