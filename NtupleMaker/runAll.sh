#!/bin/bash

# List of processes
processes=("TTbarP" "DY" "Wjets" "ST" "VV" "HplusM80" "HplusM90" "HplusM100" "HplusM110" "HplusM120" "HplusM140" "HplusM150" "HplusM160")

# List of filename scenarios
filename_scenarios=("base" "iso20" "cp5up" "cp5down" "hdampup" "hdampdown" "jecup" "jecdown" "jerup" "jerdown" "metup" "metdown")

# List of argument scenarios
argument_scenarios=("base" "PUWeight_do" "PUWeight_up" "prefire_up" "prefire_do"
                    "muEff_do" "muEff_up" "bc_stat_up" "bc_lhemuf_do" "bc_lhemuf_up" "lhemur_up"
                    "lhemur_do" "isr_up" "isr_do" "fsr_up" "fsr_do" "xdy_up" "xdy_do" "xdyc_up"
                    "xdyc_do" "intp_up" "intp_do" "extp_up" "extp_do" "xwj_up" "bfrag_do" "bfrag_Up"
                    "pdf_Up" "pdf_Do" "JEC_up" "JEC_do")  # Include "JEC_up" and "JEC_do"

# Channel and region options
channel="mu"
region="A"

# Loop over processes, filename scenarios, and argument scenarios
for process in "${processes[@]}"
do
    for filename_scenario in "${filename_scenarios[@]}"
    do
        for argument_scenario in "${argument_scenarios[@]}"
        do
            if [[ "$filename_scenario" == "iso20" || "$filename_scenario" == "cp5up" || "$filename_scenario" == "cp5down" || "$filename_scenario" == "hdampup" || "$filename_scenario" == "hdampdown" || "$filename_scenario" == "metup" || "$filename_scenario" == "metdown" ]]; then
                # Include "base" argument scenario only for specific filename scenarios
                if [[ "$argument_scenario" == "base" ]]; then
                    file_name="all_${process}_${filename_scenario}"
                    echo "Running script for file: $file_name with argument scenario: $argument_scenario"
                    python3 RDataFrame.py $file_name $argument_scenario --channel $channel --region $region
                    echo "$file_name with argument scenario: $argument_scenario done"
                fi
            elif [[ "$filename_scenario" == "jecup" || "$filename_scenario" == "jecdown" ]]; then
                # Include "JEC_up" and "JEC_do" only when filename scenario is "jecup" or "jecdown"
                if [[ "$argument_scenario" == "JEC_up" || "$argument_scenario" == "JEC_do" ]]; then
                    file_name="all_${process}_${filename_scenario}"
                    echo "Running script for file: $file_name with argument scenario: $argument_scenario"
                    python3 RDataFrame.py $file_name $argument_scenario --channel $channel --region $region
                    echo "$file_name with argument scenario: $argument_scenario done"
                fi
            else
                # For other filename scenarios, include all argument scenarios as before
                file_name="all_${process}_${filename_scenario}"
                echo "Running script for file: $file_name with argument scenario: $argument_scenario"
                python3 RDataFrame.py $file_name $argument_scenario --channel $channel --region $region
                echo "$file_name with argument scenario: $argument_scenario done"
            fi
        done
    done
done
