#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /afs/cern.ch/work/s/savarghe/private/HplusMVA/CMSSW_13_0_10/src/HplusMVA/Reader
eval `scramv1 runtime -sh`
python3 Reader_base.py $1 $2 $3 $4 $5
