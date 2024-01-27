#!/bin/bash

processes=("TTbarP" "DY" "ST" "VV" "Wjets" "HplusM80" "HplusM90" "HplusM100" "HplusM110" "HplusM120" "HplusM130" "HplusM140" "HplusM150" "HplusM155" "HplusM160")
year="2016"
channel="mu"
mass="80"
wp="medium"  # Set your desired working point here (medium, tight, or loose)

for process in "${processes[@]}"; do
  command="root -l -b -q 'Reader_${wp}.C(\"$year\", \"$process\", \"$channel\", \"$mass\")'"
  echo "Running: $command"
  eval $command
done
