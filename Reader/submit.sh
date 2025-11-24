#!/bin/bash

# Loop over mass points from 40 to 160 GeV with a step of 10, plus 155
for mass in $(seq 40 10 160) 155; do
    # Adjust the mass format to match your requirements (e.g., HplusM040 for 40 GeV)
    formatted_mass=$(printf "HplusM%03d" $mass)

    # Run the script for each mass point
    ./runReader.sh ${formatted_mass} base 2018 ele /afs/cern.ch/work/s/savarghe/NewJEC/2018/ele/A/outputHistos
done

echo "All jobs have been submitted."
