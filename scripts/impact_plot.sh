t2wDataCard=$1
mass=$2
#combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1 -t -1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.1 | tee doInitialFit.log 
#combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1 -t -1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.1 --parallel 3 | tee doFit.log

#AN
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.1 --cminDefaultMinimizerStrategy 0 | tee doInitialFit.log 
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.1 --cminDefaultMinimizerStrategy 0  --parallel 3 | tee doFit.log

#toy
combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1 --redefineSignalPOIs BR --cminDefaultMinimizerStrategy 0   --setCrossingTolerance=0.0002 --setParameterRanges BR=-0.1,0.1   | tee doInitialFit.log 
combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=-0.1,0.1 --cminDefaultMinimizerStrategy 0 --cminDefaultMinimizerTolerance 0.5  --setCrossingTolerance=0.0002 --parallel 3  | tee doFit.log

combineTool.py -M Impacts -d $t2wDataCard -m $mass -o nuisImpactJSON 
plotImpacts.py --cms-label "Internal" -i nuisImpactJSON -o nuisImpactPDF --blind

