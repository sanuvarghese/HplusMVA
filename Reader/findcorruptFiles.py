import subprocess
import os

def check_root_file_corruption(directory):
    """Check for corruption in ROOT files located in the specified directory, and delete corrupt files."""
    # List all files in the directory
    files = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]
    
    # Initialize a counter
    files_checked = 0
    corrupt_files_deleted = 0

    for file in files:
        # Prepare the command to check the file using ROOT
        command = ['root', '-l', '-q', os.path.join(directory, file)]

        # Execute the command
        result = subprocess.run(command, capture_output=True, text=True)

        # Increment the counter
        files_checked += 1

        # Print a message every 100 files
        if files_checked % 100 == 0:
            print(f"{files_checked} files have been checked.")

        # Check for errors indicating corruption
        if "failed to read the file type data" in result.stderr:
            print(f"Corrupt file detected and will be deleted: {file}")
            try:
                # Attempt to delete the corrupt file
                os.remove(os.path.join(directory, file))
                corrupt_files_deleted += 1
                print(f"Deleted corrupt file: {file}")
            except Exception as e:
                print(f"Error deleting file {file}: {e}")

    # Print the total number of files checked if not a multiple of 100
    if files_checked % 100 != 0 or files_checked == 0:
        print(f"Total files checked: {files_checked}")

    if corrupt_files_deleted > 0:
        print(f"Total corrupt files deleted: {corrupt_files_deleted}")
    else:
        print("No corrupt files detected.")

# Specify the directory containing your ROOT files
directory = "/afs/cern.ch/work/s/savarghe/NewJEC/2018/ele/A/outputHistos"
check_root_file_corruption(directory)
