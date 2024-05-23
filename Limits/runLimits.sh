#!/bin/bash

# Initial setup for 155 GeV
sed -i 's/160160/155155/' MyHPlusDataCardMaker.C
sed -i 's/160/155/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_2016_mu_KinFit_bdt_outputExcTight_WH155.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt155.root
combine --rAbsAcc 0.000001 bdt155.root -M AsymptoticLimits --mass 155 -t -1

# Reset for next iterations
sed -i 's/155155/4040/' MyHPlusDataCardMaker.C
sed -i 's/155/40/' MyHPlusDataCardMaker.C

# Loop through the specified masses
for mass in {40..160..10}
do
    if [ $mass -ne 40 ]; then # Skip the sed replacement for the first iteration as it's already done
        # Calculate previous mass for sed replacement
        prev_mass=$((mass - 10))
        sed -i "s/${prev_mass}${prev_mass}/${mass}${mass}/" MyHPlusDataCardMaker.C
        sed -i "s/${prev_mass}/${mass}/" MyHPlusDataCardMaker.C
    fi

    # Generate data cards
    root -l -b -q MyHPlusDataCardMaker.C

    # Generate workspace
    workspace_file="bdt${mass}.root"
    datacard_file="datacard_hcs_2016_mu_KinFit_bdt_outputExcTight_WH${mass}.txt"
    text2workspace.py $datacard_file -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o $workspace_file

    # Statistical analysis
    combine --rAbsAcc 0.000001 $workspace_file -M AsymptoticLimits --mass $mass -t -1
done
