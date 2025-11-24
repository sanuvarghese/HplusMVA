#!/bin/bash

# Initial setup for 40 GeV
#sed -i 's/160160/4040/' MyHPlusDataCardMaker_lowmass.C
#sed -i 's/160/40/' MyHPlusDataCardMaker_lowmass.C
root -l -b -q MyHPlusDataCardMaker_lowmass.C
text2workspace.py datacard_hcs_2018_mu_KinFit_bdt_outputExcTight_WH40.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt40.root
#combine --rAbsAcc 0.000001 bdt40.root -M AsymptoticLimits --mass 40 --run blind

# Reset for next iterations
sed -i 's/4040/4040/' MyHPlusDataCardMaker_lowmass.C
sed -i 's/40/40/' MyHPlusDataCardMaker_lowmass.C

# Loop through the specified masses
for mass in {50..70..10}
do
    # Calculate previous mass for sed replacement
    prev_mass=$((mass - 10))
    sed -i "s/${prev_mass}${prev_mass}/${mass}${mass}/" MyHPlusDataCardMaker_lowmass.C
    sed -i "s/${prev_mass}/${mass}/" MyHPlusDataCardMaker_lowmass.C

    # Generate data cards
    root -l -b -q MyHPlusDataCardMaker_lowmass.C

    # Generate workspace
    workspace_file="bdt${mass}.root"
    datacard_file="datacard_hcs_2018_mu_KinFit_bdt_outputExcTight_WH${mass}.txt"
    text2workspace.py $datacard_file -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o $workspace_file

    # Statistical analysis
 #   combine --rAbsAcc 0.000001 $workspace_file -M AsymptoticLimits --mass $mass --run blind
done

# Return to 40 GeV at the end
sed -i 's/7070/4040/' MyHPlusDataCardMaker_lowmass.C
sed -i 's/70/40/' MyHPlusDataCardMaker_lowmass.C
