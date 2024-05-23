#!/bin/bash

# List of processes
#processes=("TTbarP" "DY" "Wjets" "ST" "VV" "HplusM80" "HplusM90" "HplusM100" "HplusM110" "HplusM120" "HplusM140" "HplusM150" "HplusM160")
processes=(
#  "TTbar" "DataMu" "DataEle"
  "HplusM040" "HplusM050" "HplusM060" "HplusM070" "HplusM080" "HplusM090" "HplusM100"
  "HplusM110" "HplusM120" 
  # "HplusM130" "HplusM140" "HplusM150" "HplusM155" "HplusM160"
  # "HminusM040" "HminusM050" "HminusM060" "HminusM070" "HminusM080" "HminusM090" "HminusM100"
  # "HminusM110" "HminusM120" "HminusM130" "HminusM140" "HminusM150" "HminusM155" "HminusM160"
  # "singleTop" "Wjets" "DYjets" "VBFusion" "MCQCDMu" "MCQCDEle"
  # "TTGToLL" "TTGToLNu" "TTGToQQ" "TTHToNonbb" "TTHTobb" "TTHToGG"
  # "TTWJetsToLNu" "TTWJetsToQQ" "TTZToLLNuNu" "TTZToQQ"
)


# List of filename scenarios
#filename_scenarios=("base" "iso20" "cp5up" "cp5down" "hdampup" "hdampdown" "jecup" "jecdown" "jerup" "jerdown" "metup" "metdown")

filename_scenarios=(
  "base" "iso20" "metup" "metdown" "cp5up" "cp5down" "hdampup" "hdampdown" "mtopup" "mtopdown"
  "absmpfbup" "abssclup" "absstatup"
  "flavorqcdup" "fragup" "timeptetaup"
  "pudatamcup" "puptbbup" "puptec1up" "puptec2up" "pupthfup" "puptrefup"
  "relfsrup" "relbalup" "relsampleup"
  "reljerec1up" "reljerec2up" "reljerhfup"
  "relptbbup" "relptec1up" "relptec2up" "relpthfup"
  "relstatecup" "relstatfsrup" "relstathfup"
  "singpiecalup" "singpihcalup"
  "absmpfbdown" "absscldown" "absstatdown"
  "flavorqcddown" "fragdown" "timeptetadown"
  "pudatamcdown" "puptbbdown" "puptec1down" "puptec2down" "pupthfdown" "puptrefdown"
  "relfsrdown" "relbaldown" "relsampledown"
  "reljerec1down" "reljerec2down" "reljerhfdown"
  "relptbbdown" "relptec1down" "relptec2down" "relpthfdown"
  "relstatecdown" "relstatfsrdown" "relstathfdown"
  "singpiecaldown" "singpihcaldown"
)

# List of argument scenarios
argument_scenarios=("base" "PUWeight_do" "PUWeight_up" "prefire_up" "prefire_do"
                    "muEff_do" "muEff_up" "bc_stat_up" "bc_lhemuf_do" "bc_lhemuf_up" "lhemur_up"
                    "lhemur_do" "isr_up" "isr_do" "fsr_up" "fsr_do" "xdyb_up" "xdyb_do" "xdyc_up"
                    "xdyc_do" "intp_up" "intp_do" "extp_up" "extp_do" "xwj_up" "bfrag_do" "bfrag_Up"
                    "pdf_Up" "pdf_Do" "JEC_up" "JEC_do")  # Include "JEC_up" and "JEC_do"

# Channel and region options
channel="mu"
region="A"

# Function to run the script
run_script() {
    local process=$1
    local filename_scenario=$2
    local argument_scenario=$3

    local file_name="all_${process}_${filename_scenario}"
    echo "Running script for file: $file_name with argument scenario: $argument_scenario"
    python3 RDataFrame.py "$file_name" "$argument_scenario" --channel $channel --region $region
    echo "$file_name with argument scenario: $argument_scenario done"
}

# Loop over processes and filename scenarios
for process in "${processes[@]}"; do
    for filename_scenario in "${filename_scenarios[@]}"; do
        if [[ "$filename_scenario" == "base" ]]; then
            # For the "base" filename scenario, run all argument scenarios except "base"
            for argument_scenario in "${argument_scenarios[@]}"; do
                run_script "$process" "$filename_scenario" "$argument_scenario"
            done
        else
            # For other filename scenarios, just run the "base" argument scenario
            run_script "$process" "$filename_scenario" "base"
        fi
    done
done
