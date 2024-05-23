import ROOT
import ctypes

def PreAna(process):
    # Open the ROOT file
    inputFilepath = f"/eos/user/i/idas/Output/cms-hcs-run2/CBA_jecsyst/post/2016/all/all_{process}.root"
    inputFilebase = ROOT.TFile.Open(inputFilepath)
    
    # Ensure the file is open
    if not inputFilebase:
        print(f"Failed to open file {inputFilepath}")
        return

    # Retrieve histograms
    wt_before = inputFilebase.Get(f"{process}/base/Iso/_wt_before_mu")
    wt_after = inputFilebase.Get(f"{process}/base/Iso/_wt_after_mu")
    
    # Create a histogram for analysis
    h1 = ROOT.TH1D("bdt", "Classifier output ", 20, 0, 2)

    # Setup TChain
    ttbar = ROOT.TChain("Kinfit_Reco")
    ttbar.Add(f"/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_jecsyst/post/2016/{process}_tree_base_*")

    # Define and initialize variables with ctypes
    variables = {
        "sampleWeight": ctypes.c_double(0),
        "puJetIDWeight": ctypes.c_double(0),
        "prefireWeight": ctypes.c_double(0),
        "prefireWeight_Do": ctypes.c_double(0),
        "prefireWeight_Up": ctypes.c_double(0),
        "PUWeight": ctypes.c_double(0),
        "PUWeight_Up": ctypes.c_double(0),
        "PUWeight_Do": ctypes.c_double(0),
        "muEffWeight": ctypes.c_double(0),
        "muEffWeight_Up": ctypes.c_double(0),
        "muEffWeight_Do": ctypes.c_double(0),
        "eleEffWeight": ctypes.c_double(0),
        "eleEffWeight_Up": ctypes.c_double(0),
        "eleEffWeight_Do": ctypes.c_double(0),
        "bcTagWeight": ctypes.c_double(0),
        # Continue for all weights and variables
        "nJet": ctypes.c_int(0),
        "wt_ratio": ctypes.c_float(0),
        # Additional variables as needed
    }

    # Set branch addresses
    for name, var in variables.items():
        ttbar.SetBranchAddress(name, ctypes.byref(var))

    # Process events
    outputdir = "/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2016/post/post_res/"
    newfile = ROOT.TFile(f"{outputdir}all_{process}_base.root", "recreate")
    T = ROOT.TTree("Kinfit_Reco", "skimmed test tree")

    # Add branches to the new tree
    for name, var in variables.items():
        T.Branch(name, ctypes.byref(var), f"{name}/D")

    for ievt in range(ttbar.GetEntries()):
        ttbar.GetEntry(ievt)
        
        # Example calculation (you would insert your logic here)
        wt_before_bin = wt_before.GetBinContent(variables["nJet"].value + 1)
        wt_after_bin = wt_after.GetBinContent(variables["nJet"].value + 1)
        variables["wt_ratio"].value = wt_before_bin / wt_after_bin if wt_after_bin else 1.0
        
        T.Fill()

    newfile.Write()
    newfile.Close()

# Example usage
PreAna("TTbar")

