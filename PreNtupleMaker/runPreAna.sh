#!/bin/bash

# Array of unique parameter combinations for Hello.C and Hello_sys.C
declare -a params=(
    "TTbar" "singleTop" "DYjets" "Wjets" "VBFusion"
    #"DataMu" "DataEle"
    "HplusM080" "HplusM090" "HplusM100"
    "HplusM110" "HplusM120" "HplusM130" "HplusM140" "HplusM150"
    "HplusM155" "HplusM160"
    "HplusM040" "HplusM050" "HplusM060" "HplusM070"
    #"HminusM080" "HminusM090" "HminusM100"
#    "HminusM110" "HminusM120" "HminusM130" "HminusM140" "HminusM150" "HminusM155" "HminusM160"
   "TTGToLL" "TTGToLNu" "TTGToQQ" 
    "TTHToNonbb" "TTHTobb" 
"TTHToGG"
    "TTWJetsToLNu" 
"TTWJetsToQQ" "TTZToLLNuNu" "TTZToQQ"
)
declare -a systematics=(
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


# Specific systematics for TTbar
declare -a ttbar_systematics=(
    "cp5up" "cp5down" "hdampup" "hdampdown" "mtopdown" "mtopup"
)

# Loop over params and execute Hello.C
for param in "${params[@]}"; do
    root -l -b -q PreAna.C'("'$param'")'
done

# # Loop over params and systematics, then execute Hello_sys.C
# for param in "${params[@]}"; do
#     for sys in "${systematics[@]}"; do
#         root -l -b -q PreAna_sys.C'("'$param'","'$sys'")'
#     done
# done

# # Loop over params and systematics, then execute Hello_sys.C for HplusM* and TTbar
# for param in "${params[@]}"; do
#     if [[ "$param" == HplusM* ]] || [ "$param" == "TTbar" ]; then
#         for sys in "${ttbar_systematics[@]}"; do
#             root -l -b -q PreAna_sys.C'("'$param'","'$sys'")'
#         done
#     fi
# done
