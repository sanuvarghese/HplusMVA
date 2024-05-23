#!/bin/bash

# Loop over mass points from 40 to 160 GeV with a step of 10, plus 155
for mass in $(seq 40 10 160) 155; do
    # Adjust the mass format to match your requirements (e.g., M040 for 40 GeV)
    formatted_mass=$(printf "M%03d" $mass)

    # Run the script for each mass point
    ./runRDataFrame.sh Hplus${formatted_mass} base base ele A
done

echo "All jobs have been submitted."
