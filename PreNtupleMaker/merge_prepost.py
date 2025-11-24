import os
import subprocess
from glob import glob

# Define the directories
pre_dir = "root_files/QCDRBI/pre/2016/"
post_dir = "root_files/QCDRBI/post/2016/"
output_dir = "root_files/QCDRBI/2016/"

# Ensure the output directory exists
os.makedirs(output_dir, exist_ok=True)

# Get a list of all files in the pre directory
pre_files = glob(os.path.join(pre_dir, "*.root"))

# Iterate over each file in the pre directory
for pre_file in pre_files:
    # Extract the base file name
    base_name = os.path.basename(pre_file)
    
    # Check if a matching file exists in the post directory
    post_file = os.path.join(post_dir, base_name)
    if os.path.exists(post_file):
        # Define the output file path
        output_file = os.path.join(output_dir, base_name)
        
        # Perform the hadd command to merge the files
        print(f"Merging {pre_file} and {post_file} into {output_file}")
        subprocess.run(["hadd", "-f", output_file, pre_file, post_file])
    else:
        print(f"Matching file for {base_name} not found in post directory.")

print("Merging completed.")
