import os
import subprocess

def parse_jdl_file(jdl_file):
    """
    Parse a .jdl file to extract the necessary information to run the job locally.
    """
    with open(jdl_file, 'r') as file:
        lines = file.readlines()

    # Initialize variables
    executable = None
    arguments = None
    output = None
    error = None

    # Read the .jdl file and extract executable, arguments, output, and error paths
    for line in lines:
        if line.startswith('executable'):
            executable = line.split('=')[-1].strip().strip('"')
        elif line.startswith('arguments'):
            arguments = line.split('=')[-1].strip().strip('"')
        elif line.startswith('output'):
            output = line.split('=')[-1].strip().strip('"')
        elif line.startswith('error'):
            error = line.split('=')[-1].strip().strip('"')
    
    return executable, arguments, output, error

def execute_job(executable, arguments, output, error):
    """
    Execute the job locally using the extracted executable and arguments.
    Redirect stdout and stderr to specified files.
    """
    # Build the command
    command = f"{executable} {arguments}"
    
    # Open output and error files
    with open(output, 'w') as out_file, open(error, 'w') as err_file:
        # Run the command locally
        result = subprocess.run(command, shell=True, stdout=out_file, stderr=err_file)
    
    return result.returncode

def run_all_jobs(jdl_directory):
    """
    Run all jobs by reading .jdl files from the specified directory.
    """
    for file_name in os.listdir(jdl_directory):
        if file_name.endswith('.jdl'):
            jdl_file = os.path.join(jdl_directory, file_name)
            executable, arguments, output, error = parse_jdl_file(jdl_file)
            
            if executable and arguments:
                print(f"Executing job from: {jdl_file}")
                retcode = execute_job(executable, arguments, output, error)
                if retcode == 0:
                    print(f"Job {file_name} completed successfully.")
                else:
                    print(f"Job {file_name} failed with return code {retcode}.")
            else:
                print(f"Invalid .jdl file: {jdl_file}")

if __name__ == "__main__":
    jdl_directory = "jdl2016"  # Directory containing .jdl files
    run_all_jobs(jdl_directory)
