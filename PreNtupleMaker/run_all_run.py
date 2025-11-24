import os
import subprocess

# Define years and channels
years = ["2016", "2017", "2018"]
channels = ["ele", "mu"]

# Define the base directory for runAll.sh
base_target_dir = "/afs/cern.ch/work/s/savarghe/NewJEC/{year}/{channel}/A/transformedHistosLowMass/"

# Loop through all combinations of year and channel
for year in years:
    for channel in channels:
        # Construct the target directory path
        target_dir = base_target_dir.format(year=year, channel=channel)
        
        # Check if the directory exists
        if os.path.isdir(target_dir):
            print(f"Changing to directory: {target_dir}")
            os.chdir(target_dir)
            
            # Check if the runAll.sh script exists
            if os.path.isfile("runAll.sh"):
                print(f"Executing runAll.sh in {target_dir}...")
                try:
                    # Execute the script
                    subprocess.run(["./runAll.sh"], check=True)
                    print(f"Successfully executed runAll.sh in {target_dir}.")
                except subprocess.CalledProcessError as e:
                    print(f"Error executing runAll.sh in {target_dir}: {e}")
            else:
                print(f"runAll.sh not found in {target_dir}. Skipping...")
        else:
            print(f"Directory {target_dir} does not exist. Skipping...")
