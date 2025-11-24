import ROOT
from optparse import OptionParser
import sys
import os
from helper import *
from new_syst import *
# Enable multithreading
ROOT.ROOT.EnableImplicitMT(24)  # This will use all available cores by default
def define_variables(df, scenario):
    """
    Define the variables which shall be used for training, including weights depending on the scenario.
    """
#    df = define_weight(df, scenario)
    
    # Define additional derived variables
    return (df
            .Define("mjj", "Compute_mjj(jetChadPt, jetChadEta, jetChadPhi, jetChadEnergy, jetShadPt, jetShadEta, jetShadPhi, jetShadEnergy)")
            .Define("mbb", "Compute_mjj(jetBhadPt, jetBhadEta, jetBhadPhi, jetBhadEnergy, jetBlepPt, jetBlepEta, jetBlepPhi, jetBlepEnergy)")
            .Define("dPhi_j1j2", "DeltaPhi(jetChadPhi, jetShadPhi)")
            .Define("dPhi_j1b1", "DeltaPhi(jetChadPhi, jetBhadPhi)")
            .Define("dPhi_j1b2", "DeltaPhi(jetChadPhi, jetBlepPhi)")
            .Define("DelR_j1j2", "float(sqrt(pow(dPhi_j1j2, 2) + pow(jetChadEta - jetShadEta, 2)))")
            .Define("DelR_j1b2", "float(sqrt(pow(dPhi_j1b2, 2) + pow(jetChadEta - jetBlepEta, 2)))")
            .Define("cjet", "Helper::add_p4(jetChadPt, jetChadEta, jetChadPhi, jetChadEnergy)")
            .Define("sjet", "Helper::add_p4(jetShadPt, jetShadEta, jetShadPhi, jetShadEnergy)")
            .Define("Higgs", "cjet + sjet")
            .Define("bjet_H", "Helper::add_p4(jetBhadPt, jetBhadEta, jetBhadPhi, jetBhadEnergy)")
            .Define("bjet_l", "Helper::add_p4(jetBlepPt, jetBlepEta, jetBlepPhi, jetBlepEnergy)")
            .Define("TopHadron", "bjet_H + Higgs")
            .Define("CTopVar", "float(Helper::CosVector_test(cjet, sjet, cjet, TopHadron, sjet, cjhadCvsLdisc, sjhadCvsLdisc))")
            .Define("ht_b1b2j1j2", "float((TopHadron + bjet_l).Pt())")
            .Define("m_b1b2j1j2lv", "float((bjet_H + bjet_l + Higgs).M())")
            .Define("lep", "Helper::add_p4(lepPt, lepEta, lepPhi, lepEnergy)")
            .Define("met_phi", "metPhi(metPx, metPy)")
            .Define("dPhi_lb2", "DeltaPhi(lepPhi, jetBlepPhi)")
            .Define("dPhi_j2b1", "DeltaPhi(jetShadPhi, jetBhadPhi)")
            .Define("DelR_j2b1", "float(sqrt(pow(dPhi_j2b1, 2) + pow(jetShadEta - jetBhadEta, 2)))")
            .Define("MET", "sqrt(pow(metPx, 2) + pow(metPy, 2))")
            .Define("dPhi_lv", "DeltaPhi(lepPhi, met_phi)")
            .Define("chisq", "chi2")
            # Additional single-variable assignments for convenience
            .Define("CvsL_j2", "float(sjhadCvsLdisc)")
            .Define("CvsL_j1", "float(cjhadCvsLdisc)")
            .Define("CvsB_j1", "float(cjhadCvsBdisc)")
            .Define("CvsB_j2", "float(sjhadCvsBdisc)")
            .Define("pt_b1", "jetBhadPt")
            .Define("pt_j1", "jetChadPt")
            .Define("pt_j2", "jetShadPt")
            .Define("pt_b2", "jetBlepPt")
            .Define("CvsL_b1", "float(bjhadCvsLdisc)")
            .Define("CvsB_b1", "float(bjhadCvsBdisc)")
            .Define("CvsL_b2", "float(bjlepCvsLdisc)")
            .Define("pt_l", "lepPt"))

def process_and_save(signal="TTbar", year=2016, scenario="base"):
    """
    Load the input ROOT file, define variables, and save them with all original branches.
    
    Parameters:
    - signal: The signal process name, e.g., "TTbar".
    - year: The data year, e.g., 2018.
    - scenario: The scenario for defining weights.
    """
    # Construct the input file path
    input_dir = f"/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_metxycorr/post/{year}"
#    input_dir = f"/eos/cms/store/group/phys_b2g/savarghe/NewJEC/CBA_Ntuples/post/{year}"
    input_files = f"{input_dir}/{signal}_tree_base_*"
    
    # Initialize TChain
    ttbar = ROOT.TChain("Kinfit_Reco")
    ttbar.Add(input_files)

    # Initialize RDataFrame
    df = ROOT.RDataFrame(ttbar)

    # Define the new variables
    df = define_variables(df, scenario)

    # Output file setup
    output_dir = f"/eos/cms/store/group/phys_b2g/savarghe/NewJEC/QCD_tree/post/{year}"
    output_file = ROOT.TFile(f"{output_dir}/all_{signal}_{year}.root", "RECREATE")
    output_tree = df.Snapshot("Kinfit_Reco", output_file.GetName())

    # Save and close
    output_file.Write()
    output_file.Close()
    print(f"Output saved to {output_file.GetName()}")

# Example usage
#process_and_save(signal="DataMu", year=2018, scenario="base")
# List of signals to process
signals = [
    "TTbar", "DataMu", "DataEle", "singleTop", "Wjets", "DYjets", "VBFusion",
    "MCQCDMu", "MCQCDEle", "TTGToLL", "TTGToLNu", "TTGToQQ", "TTHToNonbb",
    "TTHTobb", "TTHToGG", "TTWJetsToLNu", "TTWJetsToQQ", "TTZToLLNuNu", "TTZToQQ"
]

# Loop over each signal and process it
for signal in signals:
    print(f"Processing {signal} for year 2016")
    process_and_save(signal=signal, year=2016, scenario="base")
