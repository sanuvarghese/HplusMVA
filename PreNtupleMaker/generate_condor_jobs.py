import os

# Define your parameters, systematics, and base directory
# Define your parameters
params = [
    # Uncomment any parameters you wish to include in your analysis
    "TTbar", "singleTop", "DYjets", "Wjets", "VBFusion",
    "DataMu", "DataEle", "HplusM080", "HplusM090", "HplusM100",
    "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150",
    "HplusM155", "HplusM160", 
    "HplusM040", "HplusM050", "HplusM060", "HplusM070","MCQCDMu","MCQCDEle",
    # "HminusM080", "HminusM090", "HminusM100",
    # "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160",
     "TTGToLL", "TTGToLNu", "TTGToQQ",
    "TTHToNonbb", "TTHTobb",
     "TTHToGG",
    "TTWJetsToLNu",
     "TTWJetsToQQ", "TTZToLLNuNu", "TTZToQQ",
]

# Define your systematics
systematics = [
    # "absmpfbup", "abssclup", "absstatup",
    # "flavorqcdup", "fragup", "timeptetaup",
    # "pudatamcup", "puptbbup", "puptec1up", "puptec2up", "pupthfup", "puptrefup",
    # "relfsrup", "relbalup", "relsampleup",
    # "reljerec1up", "reljerec2up", "reljerhfup",
    # "relptbbup", "relptec1up", "relptec2up", "relpthfup",
    # "relstatecup", "relstatfsrup", "relstathfup",
    # "singpiecalup", "singpihcalup",
    # "absmpfbdown", "absscldown", "absstatdown",
    # "flavorqcddown", "fragdown", "timeptetadown",
    # "pudatamcdown", "puptbbdown", "puptec1down", "puptec2down", "pupthfdown", "puptrefdown",
    # "relfsrdown", "relbaldown", "relsampledown",
    # "reljerec1down", "reljerec2down", "reljerhfdown",
    # "relptbbdown", "relptec1down", "relptec2down", "relpthfdown",
    # "relstatecdown", "relstatfsrdown", "relstathfdown",
    # "singpiecaldown", "singpihcaldown",
    "jerup", "jerdown" 
]

# Specific systematics for TTbar
ttbar_systematics = [
#    "cp5up", "cp5down", "hdampup", "hdampdown", "mtopdown", "mtopup",
]

base_dir = "./"
out_dir = "/afs/cern.ch/work/s/savarghe/private/JEC_metxy/2016/preAna/output"
error_dir = "/afs/cern.ch/work/s/savarghe/private/JEC_metxy/2016/preAna/error"
log_dir = "/afs/cern.ch/work/s/savarghe/private/JEC_metxy/2016/preAna/log"

jdl_dir = os.path.join(base_dir, "jdl2016")

# Create the directories if they don't exist
for directory in [out_dir, error_dir, log_dir]:
    os.makedirs(directory, exist_ok=True)

run_script_path = os.path.join(base_dir, 'runROOTAnalysis.sh')

# Get the current working directory                                                                                                       
current_working_dir = os.getcwd()

# Ensure the JDL directory exists
os.makedirs(jdl_dir, exist_ok=True)

# Generate the bash script for running ROOT analysis
with open(run_script_path, 'w') as bash_script:
    bash_script_content = f"""#!/bin/bash
# Setup CMS environment
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd {current_working_dir}   
eval `scramv1 runtime -sh`

# Check if a systematic argument is provided
if [ -z "$2" ]; then
    root -l -b -q PreAna.C'("'"$1"'")'
else
    root -l -b -q PreAna_sys.C'("'"$1"'","'"$2"'")'
fi
"""
    bash_script.write(bash_script_content)

# Make the script executable
os.chmod(run_script_path, 0o755)

# Template for the JDL content
jdl_template = """universe = vanilla
executable = {run_script_path}
arguments = "$(process) $(systematic)"
output = {out_dir}/$(process)_$(systematic).out
error = {error_dir}/$(process)_$(systematic).err
log = {log_dir}/$(process)_$(systematic).log
should_transfer_files = YES
requirements = (OpSysAndVer =?= "CentOS7") 
+JobFlavour = "workday"  
when_to_transfer_output = ON_EXIT
queue
"""

# Generate JDL files
for process in params:
    for systematic in [""] + systematics:  # Include a blank systematic for base case
        jdl_content = jdl_template.format(
            run_script_path=run_script_path,
            base_dir=base_dir,
            out_dir=out_dir,
            error_dir=error_dir,
            log_dir=log_dir,
            process=process,
            systematic=systematic
        )
        jdl_file_path = os.path.join(jdl_dir, f"{process}_{systematic if systematic else 'base'}.jdl")
        with open(jdl_file_path, 'w') as jdl_file:
            jdl_file.write(jdl_content.replace("$(process)", process).replace("$(systematic)", systematic))
        print(f"Generated JDL file: {jdl_file_path}")
# Separate loop for generating JDL files for TTbar processes with TTbar specific systematics
for process in params:
    if process.startswith("TTbar"):
        for ttbar_syst in ttbar_systematics:
            jdl_content = jdl_template.format(
                run_script_path=run_script_path,
                base_dir=base_dir,
                out_dir=out_dir,
                error_dir=error_dir,
                log_dir=log_dir,
                process=process,
                systematic=ttbar_syst
            )
            jdl_file_path = os.path.join(jdl_dir, f"{process}_{ttbar_syst}.jdl")
            with open(jdl_file_path, 'w') as jdl_file:
                jdl_file.write(jdl_content.replace("$(process)", process).replace("$(systematic)", ttbar_syst))
            print(f"Generated JDL file for TTbar systematic: {jdl_file_path}")
