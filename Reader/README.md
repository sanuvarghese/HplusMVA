```
ssh -XY <username>@lxplus7.cern.ch
```
```

cmsrel CMSSW_12_3_0
cd CMSSW_12_3_0/src
cmsenv
git cms-init
scram b -j 8
cd Reader/
```
### To run create the MVA histograms

edit the runHisto.sh file and set the desired arguments.

```
processes=("TTbarP" "DY" "ST" "VV" "Wjets" "HplusM80" "HplusM90" "HplusM100" "H\
plusM110" "HplusM120" "HplusM130" "HplusM140" "HplusM150" "HplusM155" "HplusM16\
0")
year="2016"
channel="mu"
mass="80"
wp="medium"  # Set your desired working point here (medium, tight, or loose)    


```
edit the Reader_{wp}.C file to set the desired output file directory for your histograms.

```
TString outputDir = Form("/eos/cms/store/group/phys_b2g/savarghe/HplusHistograms/MVA/%s/%s/ExcTight/", year.Data(), channel.Data());
```

Once you made the necessary changes , execute the script

```
chmod +x runHisto.sh
./runHisto.sh
```




