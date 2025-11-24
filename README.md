# HplusMVA

## Creating  Ntuples and running BDT

First step is to make the PreNtuples from the KinFit tree files (best to setup in CMSSW_13_1_0 env).

```
cd PreNtupleMaker
#open create_jdl_files.py and make necessary changes
python3 create_jdl_files.py
./submit_jobs.sh
```

Then go to the NtupleMaker directory and then submit the Ntuple making jobs.

```
cd NtupleMaker
#open create_jdl_files.py and make necessary changes
python3 create_jdl_files.py
./submit_jobs.sh
```
Once the Ntuples are made, the next step is to run the BDT Analyser
```
cd Reader
#open create_jdl_files.py and make necessary changes
python3 create_jdl_files.py --cmssw_base {cmssw src location}
./submit_jobs.sh

```

Adapt Reader.py for the different categories.

Once the jobs are done, run on the ouput files

```
./mergeHistos.sh 

python3 transform.py #transforms to symmetrical up/down systematics

```
Once the transformed histograms are produced, then run the Limit extraction

```
# After setting up Combine

cd Limits

#edit MyHPlusDataCardMaker.C to the relevant year/category

bash runLimits.sh

```





