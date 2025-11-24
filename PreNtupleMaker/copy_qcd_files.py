import os
import shutil

# Define paths and configuration
years = ["2016", "2017", "2018"]
channels = ["ele", "mu"]
exclusive_levels = {
    1: "ExcLoose",
    2: "ExcMedium",
    3: "ExcTight"
}
source_dir = "/afs/cern.ch/work/s/savarghe/private/HplusMVA/CMSSW_13_0_10/src/HplusMVA/PreNtupleMaker/QCD_root_new"
base_target_dir = "/afs/cern.ch/work/s/savarghe/NewJEC/{year}/{channel}/A/transformedHistos/{excl_dir}"

# Function to copy and rename files
def copy_files():
    for year in years:
        for channel in channels:
            for excl_level, excl_dir in exclusive_levels.items():
                # Construct source and target paths
                source_file = os.path.join(source_dir, f"all_QCDdd_{year}_{channel}_{excl_level}.root")
                target_dir = base_target_dir.format(year=year, channel=channel, excl_dir=excl_dir)
                target_file = os.path.join(target_dir, f"QCD_dd_{year}.root")

                # Ensure the target directory exists
                os.makedirs(target_dir, exist_ok=True)

                # Copy the file and rename
                if os.path.exists(source_file):
                    shutil.copy2(source_file, target_file)
                    print(f"Copied {source_file} to {target_file}")
                else:
                    print(f"Warning: Source file {source_file} does not exist.")

# Run the copy operation
copy_files()
