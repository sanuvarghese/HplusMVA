import os

# Get the current working directory
current_working_dir = os.getcwd()


# Common directory for output, error, and log files
common_dir = "/afs/cern.ch/work/s/savarghe/private/NewJEC/Ntuple/ele/2016"

output_dir = os.path.join(common_dir, "output")
error_dir = os.path.join(common_dir, "error")
log_dir = os.path.join(common_dir, "log")

# Ensure the directories exist
for dir_path in [output_dir, error_dir, log_dir]:
    os.makedirs(dir_path, exist_ok=True)



processes = [
     "TTbar", "DataMu", "DataEle",
    "HplusM040", "HplusM050", "HplusM060", "HplusM070", 
    "HplusM080", "HplusM090", "HplusM100",
    "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
    "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle",
    "TTGToLL", "TTGToLNu", "TTGToQQ", 
"TTHToNonbb", "TTHTobb", 
   "TTHToGG",
    "TTWJetsToLNu", 
"TTWJetsToQQ", "TTZToLLNuNu", "TTZToQQ",
]

filename_scenarios = [
    "base", "iso20", "metup", "metdown", "cp5up", "cp5down", "hdampup", "hdampdown", "mtopup", "mtopdown",
    "absmpfbup", "abssclup", "absstatup", "flavorqcdup", "fragup", "timeptetaup",
    "pudatamcup", "puptbbup", "puptec1up", "puptec2up", "pupthfup", "puptrefup",
    "relfsrup", "relbalup", "relsampleup", "reljerec1up", "reljerec2up", "reljerhfup",
    "relptbbup", "relptec1up", "relptec2up", "relpthfup", "relstatecup", "relstatfsrup", "relstathfup",
    "singpiecalup", "singpihcalup", "absmpfbdown", "absscldown", "absstatdown",
    "flavorqcddown", "fragdown", "timeptetadown", "pudatamcdown", "puptbbdown", "puptec1down", 
    "puptec2down", "pupthfdown", "puptrefdown", "relfsrdown", "relbaldown", "relsampledown",
    "reljerec1down", "reljerec2down", "reljerhfdown", "relptbbdown", "relptec1down", "relptec2down",
    "relpthfdown", "relstatecdown", "relstatfsrdown", "relstathfdown", "singpiecaldown", "singpihcaldown",
]

argument_scenarios = [
    "base", "PUWeight_do", "PUWeight_up", "prefire_up", "prefire_do",
    "muEff_do", "muEff_up", "bc_stat_up", "bc_stat_do", "bc_lhemuf_do", "bc_lhemuf_up", "lhemur_up",
    "lhemur_do", "isr_up", "isr_do", "fsr_up", "fsr_do", "xdyb_up", "xdyb_do", "xdyc_up",
    "xdyc_do", "intp_up", "intp_do", "extp_up", "extp_do", "xwj_up","xwj_do", "bfrag_do", "bfrag_Up",
    "pdf_Up", "pdf_Do", "JEC_up", "JEC_do",
]

channel = "ele"
region = "A"
jdl_directory = "./condor_2016" + channel + region

# Ensure the JDL directory exists
if not os.path.exists(jdl_directory):
    os.makedirs(jdl_directory)


jdl_template = """
universe = vanilla
executable = runRDataFrame.sh
arguments = "{process} {filename_scenario} {argument_scenario} {channel}  {region}"
output = {output_dir}/{process}_{filename_scenario}_{argument_scenario}.out
error = {error_dir}/{process}_{filename_scenario}_{argument_scenario}.err
log = {log_dir}/{process}_{filename_scenario}_{argument_scenario}.log
should_transfer_files = YES
requirements = (OpSysAndVer =?= "CentOS7")
when_to_transfer_output = ON_EXIT
+JobFlavour = "longlunch"
queue
"""




# Create the runRDataFrame.sh script
run_script_path = 'runRDataFrame.sh'
#run_script_path = 'runRDataFrame.sh'

with open(run_script_path, 'w') as bash_script:
    bash_script_content = f"""#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd {current_working_dir}
eval `scramv1 runtime -sh`
# Run the Python script
# Construct the file name based on arguments
file_name="all_${{1}}_${{2}}"

echo "Running script for file: $file_name with argument scenario: $3"

# Now, run RDataFrame.py with all passed arguments
python3 RDataFrame.py "$file_name" "$3" --channel "$4" --region "$5"

echo "$file_name with argument scenario: $3 done"
"""
    bash_script.write(bash_script_content)
os.chmod(run_script_path, 0o755)
# Ensure to pass the correct keyword arguments to format() based on your template's placeholders
def create_jdl(process, filename_scenario, argument_scenario):
    jdl_content = jdl_template.format(
        process=process,
        filename_scenario=filename_scenario,
        argument_scenario=argument_scenario,
        channel=channel,
        region=region,
        output_dir=output_dir,
        error_dir=error_dir,
        log_dir=log_dir
    )
    
    jdl_file_path = os.path.join(jdl_directory, f"{process}_{filename_scenario}_{argument_scenario}.jdl")
    with open(jdl_file_path, "w") as jdl_file:
        jdl_file.write(jdl_content)
    print(f"JDL file created: {jdl_file_path}")
#    add_job_to_dag(process, filename_scenario, argument_scenario)

#Generate JDL files based on the logic
for process in processes:
    for filename_scenario in filename_scenarios:
        if filename_scenario == "base":
            for argument_scenario in argument_scenarios:
                if argument_scenario != "base":  # Skip 'base' for 'base' filename scenario
                    create_jdl(process, filename_scenario, argument_scenario)
        else:
            create_jdl(process, filename_scenario, "base")

# with open(dag_file_path, "w") as dag_file:
#     dag_file.write(dag_contents)
# print(f"DAG file created: {dag_file_path}")
# Dedicated loop for 'base' filename_scenario and 'base' argument_scenario
for process in processes:
    create_jdl(process, "base", "base")
