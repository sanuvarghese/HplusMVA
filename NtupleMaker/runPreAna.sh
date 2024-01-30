#!/bin/bash

# Array of unique parameter combinations for Hello.C and Hello_sys.C
declare -a params=(
    "TTbar" "singleTop" "DYjets" "Wjets" "VBFusion"
    "DataMu" "DataEle" "HplusM080" "HplusM090" "HplusM100"
    "HplusM110" "HplusM120" "HplusM130" "HplusM140" "HplusM150"
    "HplusM155" "HplusM160"
)

# Systematics variations
declare -a systematics=(
    "jecup" "jecdown" "metdown" "metup" "jerup" "jerdown"
    "iso20" "flavorqcdup" "flavorqcddown" "timeptetaup"
    "timeptetadown" "stotptdown" "stotptup" "stotscaledown"
    "stotscaleup"
)

# Specific systematics for TTbar
declare -a ttbar_systematics=(
    "cp5up" "cp5down" "hdampup" "hdampdown" "mtopdown" "mtopup"
)

# Loop over params and execute Hello.C
for param in "${params[@]}"; do
    root -l -b -q PreAna.C'("'$param'")'
done

# Loop over params and systematics, then execute Hello_sys.C
for param in "${params[@]}"; do
    for sys in "${systematics[@]}"; do
        root -l -b -q PreAna_sys.C'("'$param'","'$sys'")'
    done
done

# Loop over params and systematics, then execute Hello_sys.C for HplusM* and TTbar
for param in "${params[@]}"; do
    if [[ "$param" == HplusM* ]] || [ "$param" == "TTbar" ]; then
        for sys in "${systematics[@]}"; do
            root -l -b -q Hello_sys.C'("'$param'","'$sys'")'
        done
    fi
done
