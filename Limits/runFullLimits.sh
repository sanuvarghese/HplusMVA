sed -i 's/160160/8080/' MyHPlusDataCardMaker.C
sed -i 's/160/80/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_13TeV_mu_KinFit_bdt_WH80.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt80.root
combine --rAbsAcc 0.000001 bdt80.root -M AsymptoticLimits --mass 80 
sed -i 's/8080/9090/' MyHPlusDataCardMaker.C
sed -i 's/80/90/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_13TeV_mu_KinFit_bdt_WH90.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt90.root
combine --rAbsAcc 0.000001 bdt90.root -M AsymptoticLimits --mass 90 
sed -i 's/9090/100100/' MyHPlusDataCardMaker.C
sed -i 's/90/100/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_13TeV_mu_KinFit_bdt_WH100.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt100.root
combine --rAbsAcc 0.000001 bdt100.root -M AsymptoticLimits --mass 100 
sed -i 's/100100/110110/' MyHPlusDataCardMaker.C
sed -i 's/100/110/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_13TeV_mu_KinFit_bdt_WH110.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt110.root
combine --rAbsAcc 0.000001 bdt110.root -M AsymptoticLimits --mass 110 
sed -i 's/110110/120120/' MyHPlusDataCardMaker.C
sed -i 's/110/120/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_13TeV_mu_KinFit_bdt_WH120.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt120.root
combine --rAbsAcc 0.000001 bdt120.root -M AsymptoticLimits --mass 120 
sed -i 's/120120/130130/' MyHPlusDataCardMaker.C
sed -i 's/120/130/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_13TeV_mu_KinFit_bdt_WH130.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt130.root
combine --rAbsAcc 0.000001 bdt130.root -M AsymptoticLimits --mass 130 
sed -i 's/130130/140140/' MyHPlusDataCardMaker.C
sed -i 's/130/140/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_13TeV_mu_KinFit_bdt_WH140.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt140.root
combine --rAbsAcc 0.000001 bdt140.root -M AsymptoticLimits --mass 140 
sed -i 's/140140/150150/' MyHPlusDataCardMaker.C
sed -i 's/140/150/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_13TeV_mu_KinFit_bdt_WH150.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt150.root
combine --rAbsAcc 0.000001 bdt150.root -M AsymptoticLimits --mass 150 
sed -i 's/150150/155155/' MyHPlusDataCardMaker.C
sed -i 's/150/155/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_13TeV_mu_KinFit_bdt_WH155.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt155.root
combine --rAbsAcc 0.000001 bdt155.root -M AsymptoticLimits --mass 155 
sed -i 's/155155/160160/' MyHPlusDataCardMaker.C
sed -i 's/155/160/' MyHPlusDataCardMaker.C
root -l -b -q MyHPlusDataCardMaker.C
text2workspace.py datacard_hcs_13TeV_mu_KinFit_bdt_WH160.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o bdt160.root
combine --rAbsAcc 0.000001 bdt160.root -M AsymptoticLimits --mass 160 
