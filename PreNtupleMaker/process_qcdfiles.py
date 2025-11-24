import os
import ROOT

def determine_exclusive_level(filename):
    """
    Determines the exclusive level based on the filename:
    - "3" at the end of the filename corresponds to "ExcT"
    - "2" at the end of the filename corresponds to "ExcM"
    - "1" at the end of the filename corresponds to "ExcL"
    - "0" at the end of the filename corresponds to no exclusive level.
    
    Returns the suffix for the exclusive level.
    """
    if filename.endswith("_3.root"):
        return "ExcT"
    elif filename.endswith("_2.root"):
        return "ExcM"
    elif filename.endswith("_1.root"):
        return "ExcL"
    elif filename.endswith("_0.root"):
        return ""  # No exclusive level suffix for "0"
    else:
        print("Warning: Could not determine exclusive level, defaulting to ExcT")
        return "ExcT"  # Default to ExcT if not specified

def determine_channel_suffix(filename):
    """
    Determines the channel suffix (_mjj_mu or _mjj_ele) based on the filename.
    """
    if "mu" in filename:
        return "_mjj_mu"
    elif "ele" in filename:
        return "_mjj_ele"
    else:
        print("Warning: Could not determine channel, defaulting to _mjj_mu")
        return "_mjj_mu"  # Default to muon if not specified

def create_qcd_root_file(input_file, output_file):
    """
    Creates a new ROOT file containing 'bdt_output' histograms for nominal, up, and down variations 
    from the input QCD dd ROOT file, stored under base, QCDddUp, and QCDddDown directories.

    Parameters:
    - input_file (str): Path to the QCD dd ROOT file.
    - output_file (str): Path to the output ROOT file to save the histograms.
    """
    # Determine the exclusive level and channel suffix based on the filename
    exclDeg = determine_exclusive_level(input_file)
    channel_suffix = determine_channel_suffix(input_file)
    
    # Open the input ROOT file
    fin = ROOT.TFile.Open(input_file, "READ")
    if not fin or fin.IsZombie():
        print(f"Error: Could not open input file {input_file}")
        return

    # Define histogram names for nominal, up, and down in the input file
    hist_name_nominal = f"QCDdd/base/Iso/_ct_{exclDeg}{channel_suffix}"
    hist_name_up = f"QCDdd/base/Iso/_ct_{exclDeg}{channel_suffix}_up"
    hist_name_down = f"QCDdd/base/Iso/_ct_{exclDeg}{channel_suffix}_down"

    # Get the histograms from the input file
    hist_nominal = fin.Get(hist_name_nominal)
    hist_up = fin.Get(hist_name_up)
    hist_down = fin.Get(hist_name_down)

    # Check if the histograms exist
    if not hist_nominal:
        print(f"Error: Histogram {hist_name_nominal} not found in the input file.")
        fin.Close()
        return
    if not hist_up:
        print(f"Warning: Histogram {hist_name_up} not found in the input file.")
    if not hist_down:
        print(f"Warning: Histogram {hist_name_down} not found in the input file.")

    # Create the output ROOT file
    fout = ROOT.TFile.Open(output_file, "RECREATE")
    if not fout or fout.IsZombie():
        print(f"Error: Could not create output file {output_file}")
        fin.Close()
        return

    # Create base directory and write the nominal histogram as 'bdt_output'
    fout.mkdir("base")
    fout.cd("base")
    if hist_nominal:
        hist_nominal.Write("bdt_output")
        print(f"Copied nominal histogram to base/bdt_output")

    # Create QCDddUp directory and write the up histogram as 'bdt_output' if available
    if hist_up:
        fout.mkdir("QCDddUp")
        fout.cd("QCDddUp")
        hist_up.Write("bdt_output")
        print(f"Copied up histogram to QCDddUp/bdt_output")

    # Create QCDddDown directory and write the down histogram as 'bdt_output' if available
    if hist_down:
        fout.mkdir("QCDddDown")
        fout.cd("QCDddDown")
        hist_down.Write("bdt_output")
        print(f"Copied down histogram to QCDddDown/bdt_output")

    # Close the files
    fout.Close()
    fin.Close()
    print(f"New QCD ROOT file created: {output_file}")

# Main function to process multiple files
def process_all_qcd_files(input_dir, output_dir):
    # Ensure the output directory exists
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # Process each file in the input directory
    for filename in os.listdir(input_dir):
        if filename.endswith(".root"):
            input_path = os.path.join(input_dir, filename)
            output_path = os.path.join(output_dir, filename)
            print(f"Processing {filename}...")
            create_qcd_root_file(input_path, output_path)

# Define input and output directories
input_directory = "/afs/cern.ch/work/s/savarghe/private/HplusMVA/CMSSW_13_0_10/src/HplusMVA/PreNtupleMaker/QCD_root"
output_directory = "/afs/cern.ch/work/s/savarghe/private/HplusMVA/CMSSW_13_0_10/src/HplusMVA/PreNtupleMaker/QCD_root_new"

# Run the processing
process_all_qcd_files(input_directory, output_directory)
