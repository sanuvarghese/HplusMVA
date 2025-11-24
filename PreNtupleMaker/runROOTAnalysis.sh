#!/bin/bash
# Setup CMS environment
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /afs/cern.ch/work/s/savarghe/private/HplusMVA/CMSSW_13_0_10/src/HplusMVA/PreNtupleMaker   
eval `scramv1 runtime -sh`

# Check if a systematic argument is provided
if [ -z "$2" ]; then
    root -l -b -q PreAna.C'("'"$1"'")'
else
    root -l -b -q PreAna_sys.C'("'"$1"'","'"$2"'")'
fi
