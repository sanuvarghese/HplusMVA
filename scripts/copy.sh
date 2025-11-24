#!/bin/bash

# Navigate to the directory containing the files and mass directories
#cd /path/to/ExcMedium

# Loop over files matching the pattern "HplusM0X0_2017_mu.root"
for file in hist_HplusM0[0-9][0]_2018_mu.root; do
  if [[ -f "$file" ]]; then
    # Construct the new file name by removing the extra zero after 'M'
    newfile=$(echo "$file" | sed 's/HplusM0/HplusM/g')

    # Extract the mass number from the file name for directory targeting
    mass=$(echo "$newfile" | grep -o 'M[0-9]\+' | sed 's/M//g')

    # Check if the mass directory exists, then copy the file to the corresponding directory
    if [[ -d "mass$mass" ]]; then
      echo "Copying $file to mass$mass/$newfile"
      cp "$file" "mass$mass/$newfile"
    else
      echo "Directory mass$mass does not exist for $file"
    fi
  fi
done
