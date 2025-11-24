import ROOT
import os
import fnmatch

# Function to calculate and transform the up/down histograms to be symmetrical
def transform_histograms_symmetric(hCentral, hUp, hDown):
    hUpTransformed = hUp.Clone()  # Clone the up histogram
    hDownTransformed = hDown.Clone()  # Clone the down histogram
    
    # Loop over each bin to apply the transformation
    for i in range(1, hCentral.GetNbinsX() + 1):
        central_value = hCentral.GetBinContent(i)
        up_value = hUp.GetBinContent(i)
        down_value = hDown.GetBinContent(i)
        
        # Calculate the maximum deviation from the central value
        max_deviation = max(abs(up_value - central_value), abs(down_value - central_value))
        
        if central_value != 0:
            relative_uncertainty = max_deviation / central_value
        else:
            relative_uncertainty = 0
        
        # Apply symmetric transformations
        hUpTransformed.SetBinContent(i, central_value * (1 + relative_uncertainty))
        hDownTransformed.SetBinContent(i, central_value * (1 - relative_uncertainty))
        
        # Print the uncertainty for each bin to the terminal
#        print(f"Bin {i}: Central = {central_value}, Up (transformed) = {hUpTransformed.GetBinContent(i)}, Down (transformed) = {hDownTransformed.GetBinContent(i)}")
        
        # Keep the original bin errors
        hUpTransformed.SetBinError(i, hUp.GetBinError(i))
        hDownTransformed.SetBinError(i, hDown.GetBinError(i))
    
    return hUpTransformed, hDownTransformed

# Define the input and output directories
input_directory = "/afs/cern.ch/work/s/savarghe/NewJEC/2018/mu/A/mergedHistos/LowMass/ExcControl/"
output_directory = "/afs/cern.ch/work/s/savarghe/NewJEC/2018/mu/A/transformedHistos/ExcControl/"

# Ensure the output directory exists
os.makedirs(output_directory, exist_ok=True)

# Function to navigate directories and process histograms
def process_directory(input_dir, output_dir):
    # Load the central histogram from the base directory
    base_hist = None
    if "base" in [key.GetName() for key in input_dir.GetListOfKeys()]:
        base_dir = input_dir.Get("base")
        base_hist = base_dir.Get("bdt_output")
        print(f"Loaded central histogram from 'base' directory.")
        
        # Save the base directory and its histograms to the output file
        output_base_dir = output_dir.mkdir("base")
        output_base_dir.cd()
        base_hist.Write()
    else:
        print("Base directory with central histogram not found. Skipping file.")
        return

    # Loop over all keys (directories and histograms) in the current directory
    for key in input_dir.GetListOfKeys():
        key_name = key.GetName()
        obj = key.ReadObj()
        
        if obj.IsA().InheritsFrom("TDirectory"):  # If the object is a directory
            if key_name == "base":
                continue  # Skip processing the base directory again
            
            print(f"Entering directory: {key_name}")  # Debugging output
            # Check if the directory name suggests an up or down variation
            if key_name.lower().endswith("up"):
                # Load the histogram from this directory
                hist = obj.Get("bdt_output")
                if not hist:
                    print(f"Warning: 'bdt_output' histogram not found in {key_name}")
                    continue

                # Try to find the corresponding down directory
                down_dir_name = key_name[:-2] + "down"
                down_dir = input_dir.Get(down_dir_name)
                if not down_dir:
                    # If "down" directory is not found, try "do" instead
                    down_dir_name = key_name[:-2] + "do"
                    down_dir = input_dir.Get(down_dir_name)
                
                if down_dir:
                    down_hist = down_dir.Get("bdt_output")
                    if down_hist:
                        print(f"\nProcessing systematic: {key_name} and {down_dir_name}")
                        # Transform and print the uncertainties
                        up_transformed, down_transformed = transform_histograms_symmetric(base_hist, hist, down_hist)
                        
                        # Save the transformed histograms
                        output_subdir = output_dir.mkdir(key_name)
                        output_subdir.cd()
                        up_transformed.Write()
                        output_subdir = output_dir.mkdir(down_dir_name)
                        output_subdir.cd()
                        down_transformed.Write()
                    else:
                        print(f"Warning: Down histogram 'bdt_output' not found in {down_dir_name}")
                else:
                    print(f"Warning: Corresponding down directory {down_dir_name} not found.")
            # Skip processing of down histogram in this loop as it is handled in the up case
            elif key_name.lower().endswith("down") or key_name.lower().endswith("do"):
                print(f"Skipping processing for {key_name} as it is handled with its corresponding 'up' directory.")
            else:
                print(f"Skipping non-systematic directory: {key_name}")
        
        elif obj.IsA().InheritsFrom("TH1"):  # If the object is a histogram
            print(f"Found histogram: {key_name} but not in a systematic directory, skipping.")
            # Non-systematic histogram, we skip this.

# Process each *_mu.root file in the input directory
for file_name in os.listdir(input_directory):
    print(f"Processing file: {file_name}")  # Debugging output
    if fnmatch.fnmatch(file_name, "*_mu.root"):
        # Open the input ROOT file
        input_file_path = os.path.join(input_directory, file_name)
        input_file = ROOT.TFile(input_file_path, "READ")
        
        # Create the corresponding output ROOT file
        output_file_path = os.path.join(output_directory, file_name)
        output_file = ROOT.TFile(output_file_path, "RECREATE")
        
        # Start processing from the root directory of the input file
        process_directory(input_file, output_file)
        
        # Close the ROOT files
        input_file.Close()
        output_file.Close()
        
        print(f"Processed and saved: {file_name}")

print("Transformation complete. Transformed histograms are saved with original directory structure and names.")
