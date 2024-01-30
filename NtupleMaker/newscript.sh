#!/bin/bash

# Array of unique parameter combinations for Hello.C
declare -a hello_params=(
    "TTbar"
    "singleTop"
    "DYjets"
    "Wjets"
    "VBFusion"
    "DataMu"
    "DataEle"
    "HplusM080"
    "HplusM090"
    "HplusM100"
    "HplusM110"
    "HplusM120"
    "HplusM130"
    "HplusM140"
    "HplusM150"
    "HplusM155"
    "HplusM160"
)

# Array of unique parameter combinations for Hello_sys.C
declare -a hello_sys_params=(
    "TTbar"
    "singleTop"
    "DYjets"
    "Wjets"
    "flavorqcdup"
    "flavorqcddown"
    "timeptetaup"
    "timeptetadown"
    "stotptdown"
    "stotptup"
    "stotscaledown"
    "stotscaleup"
)

# Systematics variations
declare -a systematics=(
    "jecup"
    "jecdown"
    "metdown"
    "metup"
    "jerup"
    "jerdown"
    "iso20"
    "flavorqcdup"                                                                                                                             "flavorqcddown"                                                                                                                           "timeptetaup"                                                                                                                          
33    "timeptetadown"                                                                                                                        
34    "stotptdown"                                                                                                                           
35    "stotptup"                                                                                                                             
36    "stotscaledown"                                                                                                                        
37    "stotscaleup"
)

# Specific systematics for TTbar
declare -a ttbar_systematics=(
    "cp5up"
    "cp5down"
    "hdampup"
    "hdampdown"
    "mtopdown"
    "mtopup"
)

# Loop over hello_params and execute Hello.C
for param in "${hello_params[@]}"; do
    root -l -b -q Hello.C'("'$param'")'
done

# Loop over hello_sys_params and systematics, then execute Hello_sys.C
for sys_param in "${hello_sys_params[@]}"; do
    for sys in "${systematics[@]}"; do
        root -l -b -q Hello_sys.C'("'$sys_param'","'$sys'")'
    done
done

# Loop for TTbar specific systematics
for sys in "${ttbar_systematics[@]}"; do
    root -l -b -q Hello_sys.C'("TTbar","'$sys'")'
done
