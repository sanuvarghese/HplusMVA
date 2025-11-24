import os
import argparse

# Set up argument parser
parser = argparse.ArgumentParser(description='Generate JDL files for HTCondor submission.')
parser.add_argument('--cmssw_base', type=str, required=True,
                    help='Path to the CMSSW base directory.')
args = parser.parse_args()

# Use arguments
cmssw_base = args.cmssw_base

# Define other variables
year = "2018"
channel = "ele"
output_dir = "/afs/cern.ch/work/s/savarghe/NewJEC/2018/ele/A/LowMass/ExcTight"
error_dir = "/afs/cern.ch/work/s/savarghe/NewJEC/2018/ele/A/LowMass/ExcTight/log"
reader_script_path = "/afs/cern.ch/work/s/savarghe/private/HplusMVA/CMSSW_13_0_10/src/HplusMVA/Reader/Reader.py"  # Just the script name for transfer
jdl_directory = "condor2018ele_topPt_low"

if not os.path.exists(output_dir):
    os.makedirs(output_dir)


if not os.path.exists(jdl_directory):
    os.makedirs(jdl_directory)

#jdl_directory = "./condor"
if not os.path.exists(error_dir):
    os.makedirs(error_dir)

dag_file_path = os.path.join(jdl_directory, "submit_jobs.dag")

# Previously defined systematics for 2018
systematics = [
    # "jerup", "jerdown", #"metup", "metdown",
#     "absmpfbup", "abssclup", "absstatup",
#     "flavorqcdup", "fragup", "timeptetaup",
#     "pudatamcup", "puptbbup", "puptec1up", "puptec2up", "pupthfup", "puptrefup",
#     "relfsrup", "relbalup", "relsampleup",
#     "reljerec1up", "reljerec2up", "reljerhfup",
#     "relptbbup", "relptec1up", "relptec2up", "relpthfup",
#     "relstatecup", "relstatfsrup", "relstathfup",
#     "singpiecalup", "singpihcalup",
#     "absmpfbdown", "absscldown", "absstatdown",
#     "flavorqcddown", "fragdown", "timeptetadown",
#     "pudatamcdown", "puptbbdown", "puptec1down", "puptec2down", "pupthfdown", "puptrefdown",
#     "relfsrdown", "relbaldown", "relsampledown",
#     "reljerec1down", "reljerec2down", "reljerhfdown",
#     "relptbbdown", "relptec1down", "relptec2down", "relpthfdown",
#     "relstatecdown", "relstatfsrdown", "relstathfdown",
#     "singpiecaldown", "singpihcaldown"
# #   
    #"cp5up", "cp5down", "hdampup", "hdampdown", "mtopup", "mtopdown"
]

#Base systematics
base_systematics = [
    # "base",
    # "base_JEC_do",
    # "base_JEC_up",
    # "base_PUWeight_do",
    # "base_PUWeight_up",
    #  "base_bc_lhemuf_do",
    #  "base_bc_lhemuf_up",
    # "base_bc_stat_up",
    # "base_bc_stat_do",
    # "base_bfrag_Up",
    # "base_bfrag_do",
    # "base_extp_do",
    # "base_extp_up",
    # "base_fsr_do",
    # "base_fsr_up",
    # "base_intp_do",
    # "base_intp_up",
    # "base_isr_do",
    # "base_isr_up",
    #  "base_lhemur_do",
    #  "base_lhemur_up",
    #  "base_muEff_do",
    #  "base_muEff_up",
    # "base_pdf_Do",
    # "base_pdf_Up",
    # "base_prefire_do",
    # "base_prefire_up",
    # "base_xdyb_do",
    # "base_xdyb_up",
    # "base_xdyc_do",
    # "base_xdyc_up",
    # "base_xwj_do",
    #"base_xwj_up",
    "base_topPt_up",
    "base_topPt_do"
 ]

# Combine the lists
systematics.extend(base_systematics)

# Define the list of processes
processes = [
   "TTbar", 
     "DataEle", 
     "DataMu",
    "HplusM040", "HplusM050", "HplusM060", "HplusM070", 
     "HplusM080", "HplusM090", "HplusM100",
      "HplusM110", "HplusM120",
      "HplusM130", "HplusM140", "HplusM150",
    "HplusM155", "HplusM160",
# #
#     #
# #     #    Uncomment if needed
# # #     # "HminusM040", "HminusM050", "HminusM060", "HminusM070", "HminusM080", "HminusM090", "HminusM100",
# # #     # "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160",
     "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", #"MCQCDEle",
    "TTGToLL", "TTGToLNu", "TTGToQQ",
    "TTHToNonbb", "TTHTobb", 
    "TTHToGG",
    "TTWJetsToLNu", 
    "TTWJetsToQQ", "TTZToLLNuNu", "TTZToQQ"
 ]



# Prepare to write the DAG file
dag_contents = ""

# Template for the JDL content
jdl_template = """
universe = vanilla
executable = runReader.sh
arguments = "{process} {syst} {year} {channel} {output_dir}"
transfer_input_files = {reader_script_path}, runReader.sh
output = {error_dir}/{process}_{syst}.out
error = {error_dir}/{process}_{syst}.err
log = {error_dir}/{process}_{syst}.log
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
+JobFlavour = "workday"
queue
"""

# Create runReader.sh with dynamic CMSSW base
run_reader_sh_path = 'runReader.sh'
with open(run_reader_sh_path, 'w') as bash_script:
    bash_script.write("""#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd {cmssw_base}/HplusMVA/Reader
eval `scramv1 runtime -sh`
python3 Reader.py $1 $2 $3 $4 $5
""".format(cmssw_base=cmssw_base))
os.chmod(run_reader_sh_path, 0o755)

# # Generate JDL files
# for syst in systematics:
#     jdl_file_path = os.path.join(jdl_directory, f"HplusM130_{syst}.jdl")
#     jdl_content = jdl_template.format(
#         process="HplusM130",
#         syst=syst,
#         year=year,
#         channel=channel,
#         output_dir=output_dir,
#         reader_script_path=reader_script_path
#     )
#     with open(jdl_file_path, "w") as jdl_file:
#         jdl_file.write(jdl_content)
#     print(f"JDL file created: {jdl_file_path}")
#     dag_contents += f"JOB {syst} {jdl_file_path}\n"

# #print("All JDL files have been created.")

# # Write the DAG file
# with open(dag_file_path, "w") as dag_file:
#     dag_file.write(dag_contents)

# Generate JDL files
for process in processes:
    # Determine if the process requires a specific systematic ('base')
    if process.startswith('MC') or process.startswith('Data'):
        # Only create a JDL file for 'base' systematic for these processes
        targeted_systematics = ['base']
    else:
        # For all other processes, consider all systematics
        targeted_systematics = systematics
    
    for syst in targeted_systematics:
        jdl_file_path = os.path.join(jdl_directory, f"{process}_{syst}.jdl")
        jdl_content = jdl_template.format(
            process=process,
            syst=syst,
            year=year,
            channel=channel,
            output_dir=output_dir,
            error_dir=error_dir,
            reader_script_path=reader_script_path
        )
        with open(jdl_file_path, "w") as jdl_file:
            jdl_file.write(jdl_content)
        print(f"JDL file created: {jdl_file_path}")
        dag_contents += f"JOB {process}_{syst} {jdl_file_path}\n"

print(f"DAG file created: {dag_file_path}")
print("All JDL files have been created.")
with open(dag_file_path, "w") as dag_file:                                                                                              
     dag_file.write(dag_contents) 
