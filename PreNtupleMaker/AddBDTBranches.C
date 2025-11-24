#include <TMVA/Reader.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath> // for std::isnan

void add_bdt_branches(const std::string& process, int year) {
    // Define paths
    std::string baseInputDir = "/eos/cms/store/group/phys_b2g/savarghe/NewJEC/QCD_tree/" + std::to_string(year) + "/";
    std::string inputFileName = baseInputDir + "all_" + process + "_" + std::to_string(year) + ".root";
    std::string outputFileName = baseInputDir + "/WithBDT_lowmass/" + process + "_tree_base_" + std::to_string(year) + ".root";

    // Open the input file in read mode
    TFile* inputFile = TFile::Open(inputFileName.c_str(), "READ");
    if (!inputFile || inputFile->IsZombie()) {
        std::cerr << "Error: Unable to open file " << inputFileName << std::endl;
        return;
    }

    TTree* tree = dynamic_cast<TTree*>(inputFile->Get("Kinfit_Reco"));
    if (!tree) {
        std::cerr << "Error: TTree 'Kinfit_Reco' not found in file " << inputFileName << std::endl;
        inputFile->Close();
        return;
    }

    // Create a new output file with RECREATE mode
    TFile* outputFile = TFile::Open(outputFileName.c_str(), "RECREATE");
    TTree* newTree = tree->CloneTree(0); // Clone structure, no data

    // Define the TMVA Reader
    TMVA::Reader reader("!Color:!Silent");
    std::string weightfile = "/afs/cern.ch/work/s/savarghe/private/HplusMVA/CMSSW_13_0_10/src/HplusMVA/Reader/TMVA_bdt_planned_weights_lowmass1.xml";

    // Declare and initialize variables
    float Weight = 0.0, mjj = 0.0, CvsL_j2 = 0.0, CvsL_j1 = 0.0, CvsB_j1 = 0.0, CvsB_j2 = 0.0;
    float pt_b1 = 0.0, pt_j1 = 0.0, pt_j2 = 0.0, pt_b2 = 0.0, dPhi_j1j2 = 0.0, dPhi_j1b1 = 0.0;
    float CTopVar = 0.0, CvsL_b1 = 0.0, CvsB_b1 = 0.0, CvsL_b2 = 0.0, DelR_j1b2 = 0.0;
    float ht_b1b2j1j2 = 0.0, DelR_j2b1 = 0.0, dPhi_lb2 = 0.0, m_b1b2j1j2lv = 0.0;

    // Link variables to branches
    tree->SetBranchAddress("CvsL_j2", &CvsL_j2);
    tree->SetBranchAddress("CvsL_j1", &CvsL_j1);
    tree->SetBranchAddress("CvsB_j1", &CvsB_j1);
    tree->SetBranchAddress("CvsB_j2", &CvsB_j2);
    tree->SetBranchAddress("pt_b1", &pt_b1);
    tree->SetBranchAddress("pt_j1", &pt_j1);
    tree->SetBranchAddress("pt_j2", &pt_j2);
    tree->SetBranchAddress("pt_b2", &pt_b2);
    tree->SetBranchAddress("dPhi_j1j2", &dPhi_j1j2);
    tree->SetBranchAddress("dPhi_j1b1", &dPhi_j1b1);
    tree->SetBranchAddress("CTopVar", &CTopVar);
    tree->SetBranchAddress("CvsL_b1", &CvsL_b1);
    tree->SetBranchAddress("CvsB_b1", &CvsB_b1);
    tree->SetBranchAddress("CvsL_b2", &CvsL_b2);
    tree->SetBranchAddress("DelR_j1b2", &DelR_j1b2);
    tree->SetBranchAddress("ht_b1b2j1j2", &ht_b1b2j1j2);
    tree->SetBranchAddress("DelR_j2b1", &DelR_j2b1);
    tree->SetBranchAddress("dPhi_lb2", &dPhi_lb2);
    tree->SetBranchAddress("m_b1b2j1j2lv", &m_b1b2j1j2lv);

    // Add variables to the TMVA Reader
    reader.AddVariable("CvsL_j2", &CvsL_j2);
    reader.AddVariable("CvsL_j1", &CvsL_j1);
    reader.AddVariable("CvsB_j1", &CvsB_j1);
    reader.AddVariable("CvsB_j2", &CvsB_j2);
    reader.AddVariable("pt_b1", &pt_b1);
    reader.AddVariable("pt_j1", &pt_j1);
    reader.AddVariable("pt_j2", &pt_j2);
    reader.AddVariable("pt_b2", &pt_b2);
    reader.AddVariable("dPhi_j1j2", &dPhi_j1j2);
    reader.AddVariable("dPhi_j1b1", &dPhi_j1b1);
    reader.AddVariable("CTopVar", &CTopVar);
    reader.AddVariable("CvsL_b1", &CvsL_b1);
    reader.AddVariable("CvsB_b1", &CvsB_b1);
    reader.AddVariable("CvsL_b2", &CvsL_b2);
    reader.AddVariable("DelR_j1b2", &DelR_j1b2);
    reader.AddVariable("ht_b1b2j1j2", &ht_b1b2j1j2);
    reader.AddVariable("DelR_j2b1", &DelR_j2b1);
    reader.AddVariable("dPhi_lb2", &dPhi_lb2);
    reader.AddVariable("m_b1b2j1j2lv", &m_b1b2j1j2lv);

    // Book the BDT
    reader.BookMVA("BDT", weightfile);

    // Create new branches for the exclusive categories
    bool isExcControl, isExcLoose, isExcMedium, isExcTight;
     newTree->Branch("isExcControl", &isExcControl, "isExcControl/O");
     newTree->Branch("isExcLoose", &isExcLoose, "isExcLoose/O");
     newTree->Branch("isExcMedium", &isExcMedium, "isExcMedium/O");
     newTree->Branch("isExcTight", &isExcTight, "isExcTight/O");

    // Event loop
    Long64_t nentries = tree->GetEntries();
    for (Long64_t i = 0; i < nentries; ++i) {
        if (i % 500000 == 0) std::cout << "--- Processing event: " << i << std::endl;
        tree->GetEntry(i);

        double bdt_score = reader.EvaluateMVA("BDT");

        // Check BDT output for NaN values
        if (std::isnan(bdt_score)) {
            std::cout << "Warning: NaN BDT score for event " << i << std::endl;
            isExcControl = isExcLoose = isExcMedium = isExcTight = false;
        } else {
            // Set the exclusive category flags based on BDT score
	    isExcControl = (bdt_score > -0.6 && bdt_score <= -0.24);
            isExcLoose = (bdt_score > -0.24 && bdt_score <= -0.04);
            isExcMedium = (bdt_score > -0.04 && bdt_score <= 0.11);
            isExcTight = (bdt_score > 0.11);
         }

        // Fill new branches for this event
	        newTree->Fill();
    }

    // Write and close the new output file
    outputFile->Write();
    outputFile->Close();
    inputFile->Close();
    std::cout << "Completed processing for " << process << " (" << year << ")" << std::endl;
}

// Main function to process all specified processes
int AddBDTBranches() {
    std::vector<std::string> processes = {
      "TTbar",
      "DataMu", "DataEle",
      "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle",
      "TTGToLL", "TTGToLNu", "TTGToQQ", "TTHToNonbb", "TTHTobb", "TTHToGG",
      "TTWJetsToLNu", "TTWJetsToQQ", "TTZToLLNuNu", "TTZToQQ"
    };

    int year = 2017;
    for (const auto& process : processes) {
        std::cout << "Processing " << process << " for year " << year << std::endl;
        add_bdt_branches(process, year);
    }
    return 0;  // Indicate successful execution
}
