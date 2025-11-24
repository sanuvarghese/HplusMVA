import ROOT
import os
#import shutil
import argparse


def open_and_process_file(process, systematic, year, channel, outputDir):
    if not os.path.exists(outputDir):
        os.makedirs(outputDir)

    baseInputDir = f"/eos/cms/store/group/phys_b2g/savarghe/NewJEC/{year}/Full_Ntuples/{channel}/A/"
    inputFile = f"{baseInputDir}all_{process}_{systematic}_{year}_mu.root"
    #outputFileName = f"{outputDir}/bdt_{process}_{systematic}_{year}_{channel}.root"
    outputFileName = f"{outputDir}/bdt_{process}_{systematic}_{year}_{channel}.root"

    inputFilePtr = ROOT.TFile.Open(inputFile)
    if not inputFilePtr or inputFilePtr.IsZombie():
        print(f"Failed to open file: {inputFile}")
        return

    tree = inputFilePtr.Get("KinFit")
    if not tree:
        print(f"Tree 'KinFit' not found in file: {inputFile}")
        return

    # Assuming TMVA::Reader setup and variable linking is done here in Python for reference

    methodName = "BDT"
    weightfile = os.path.abspath("./TMVA_bdt_planned_weights.xml")  # Ensure correct path
# Define the histogram
#    h1 = ROOT.TH1D("bdt_output", "Classifier Output", 30, 20, 170)


    # C++ code for the event loop including Reader setup and variable linking
    cpp_code = """
    #include <TMVA/Reader.h>
    #include <TFile.h>
    #include <TTree.h>
    #include <TH1D.h>
    #include <string>
#include <cmath> // For std::isnan
    void processEvents(const std::string& fileName, const std::string& treeName, const std::string& sysName, const std::string& weightfile, const std::string& outputFileName) {{
        TFile* file = TFile::Open(fileName.c_str());
        TTree* tree = (TTree*)file->Get(treeName.c_str());
//        TH1D* histo = new TH1D("bdt", "Classifier Output", 30, 20, 170);

        TMVA::Reader reader("!Color:!Silent");

         // Declare variables and link to branches
        // float CvsL_j2, CvsL_j1, CvsB_j1, CvsB_j2, pt_b1, pt_j1, pt_j2, pt_b2, dPhi_j1j2, dPhi_j1b1, CTopVar, CvsL_b1, CvsB_b1, CvsL_b2,// DelR_j1b2, ht_b1b2j1j2, DelR_j2b1, dPhi_lb2, m_b1b2j1j2lv;

 // Declare and initialize variables
    float Weight = 0.0, mjj = 0.0, CvsL_j2 = 0.0, CvsL_j1 = 0.0, CvsB_j1 = 0.0, CvsB_j2 = 0.0;
    float pt_b1 = 0.0, pt_j1 = 0.0, pt_j2 = 0.0, pt_b2 = 0.0, dPhi_j1j2 = 0.0, dPhi_j1b1 = 0.0;
    float CTopVar = 0.0, CvsL_b1 = 0.0, CvsB_b1 = 0.0, CvsL_b2 = 0.0, DelR_j1b2 = 0.0;
    float ht_b1b2j1j2 = 0.0, DelR_j2b1 = 0.0, dPhi_lb2 = 0.0, m_b1b2j1j2lv = 0.0;
   
     // Example for one variable - repeat for all variables used in your analysis
 tree->SetBranchAddress("Weight" ,&Weight);
  tree->SetBranchAddress("mjj",&mjj);
  tree->SetBranchAddress("CvsL_j2",&CvsL_j2);
  tree->SetBranchAddress("CvsL_j1",&CvsL_j1);
  tree->SetBranchAddress("CvsB_j1",&CvsB_j1);
  tree->SetBranchAddress("CvsB_j2",&CvsB_j2);
  //tree->SetBranchAddress("CvsB_j2",&CvsB_j2);                                                                                                                             
  tree->SetBranchAddress("pt_b1",&pt_b1);
  //  tree->SetBranchAddress("pt_b2",&pt_b2);
  //tree->SetBranchAddress("pt_j2",'F');                                                                                                                                    
  tree->SetBranchAddress("pt_j1",&pt_j1);
  tree->SetBranchAddress("pt_j2",&pt_j2);
  tree->SetBranchAddress("pt_b2",&pt_b2);
//tree->SetBranchAddress("mbb",'F');                                                                                                                                      
  //tree->SetBranchAddress("dPhi_j1j2",'F');                                                                                                                                
  tree->SetBranchAddress("dPhi_j1j2",&dPhi_j1j2);
  tree->SetBranchAddress("dPhi_j1b1",&dPhi_j1b1);
  tree->SetBranchAddress("CTopVar",&CTopVar);
  tree->SetBranchAddress("CvsL_b1",&CvsL_b1);
  tree->SetBranchAddress("CvsB_b1",&CvsB_b1);  
    tree->SetBranchAddress("CvsL_b2",&CvsL_b2);
  //tree->SetBranchAddress("CvsL_b2",&CvsL_b2);                                                                                                                             
  //tree->SetBranchAddress("DelR_j1j2",&DelR_j1j2);                                                                                                                         
  tree->SetBranchAddress("DelR_j1b2",&DelR_j1b2);
  //tree->SetBranchAddress("pt_l",&pt_l);                                                                                                                                   
  tree->SetBranchAddress("ht_b1b2j1j2",&ht_b1b2j1j2);
  tree->SetBranchAddress("DelR_j2b1",&DelR_j2b1);
  tree->SetBranchAddress("dPhi_lb2",&dPhi_lb2);
  tree->SetBranchAddress("m_b1b2j1j2lv",&m_b1b2j1j2lv);
        // Repeat SetBranchAddress for other variables...

      	reader.AddVariable("CvsL_j2",&CvsL_j2);
	reader.AddVariable("CvsL_j1",&CvsL_j1);
	reader.AddVariable("CvsB_j1",&CvsB_j1);
	reader.AddVariable("CvsB_j2",&CvsB_j2);
	//reader.AddVariable("CvsB_j2",&CvsB_j2);
	reader.AddVariable("pt_b1",&pt_b1);
	reader.AddVariable("pt_j1",&pt_j1);
	reader.AddVariable("pt_j2",&pt_j2);
	reader.AddVariable("pt_b2",&pt_b2);
	//reader.AddVariable("pt_b1",&pt_b2);
	//reader.AddVariable("mbb",&mbb);
	//reader.AddVariable("dPhi_j1j2",'F');
	reader.AddVariable("dPhi_j1j2",&dPhi_j1j2);
	reader.AddVariable("dPhi_j1b1",&dPhi_j1b1);
	reader.AddVariable("CTopVar",&CTopVar);
	reader.AddVariable("CvsL_b1",&CvsL_b1);
	reader.AddVariable("CvsB_b1",&CvsB_b1);
	reader.AddVariable("CvsL_b2",&CvsL_b2);
	//reader.AddVariable("CvsL_b2",&CvsL_b2);
	//reader.AddVariable("DelR_j1j2",&DelR_j1j2);
	reader.AddVariable("DelR_j1b2",&DelR_j1b2);
	//reader.AddVariable("DelR_j2b1",&DelR_j2b1);
	//reader.AddVariable("pt_l",&pt_l);
	reader.AddVariable("ht_b1b2j1j2",&ht_b1b2j1j2);
	reader.AddVariable("DelR_j2b1",&DelR_j2b1);
	reader.AddVariable("dPhi_lb2",&dPhi_lb2);
	reader.AddVariable("m_b1b2j1j2lv",&m_b1b2j1j2lv);

        reader.BookMVA("BDT", weightfile);
 // Create the histogram
    TH1D* histo = new TH1D("bdt_output", "Classifier Output", 30, 20, 170);

        Long64_t nentries = tree->GetEntries();
        for (Long64_t i = 0; i < nentries; ++i) {{
        if (i%500000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
            tree->GetEntry(i);
            double value = reader.EvaluateMVA("BDT");
 // Check if the BDT output is NaN
    if (std::isnan(value)) {
        std::cout << "Warning: NaN value encountered in BDT output for event " << i << std::endl;
        continue; // Skip this event
    }

    // Check if Weight is NaN
    if (std::isnan(Weight)) {
        std::cout << "Warning: NaN value encountered in Weight for event " << i << std::endl;
        continue; // Skip this event
    }
            if(value < 0.19)continue; //medium wp
            histo->Fill(mjj,Weight);
        }}

        // Save the histogram
        TFile* outputFile =  TFile::Open(outputFileName.c_str(), "RECREATE");
        //TDirectory *sys1 = f->mkdir(sysName);
        TDirectory* sysDir = outputFile->mkdir(sysName.c_str()); // Use sys
        sysDir->cd();
        histo->Write();
        outputFile->Close();
    }}
"""

    ROOT.gInterpreter.Declare(cpp_code)
    #ROOT.gInterpreter.ProcessLine(f"processEvents('{inputFile}', 'KinFit', '{methodName}', '{weightfile}', 'bdt_output')")
# Correct call to ProcessLine, ensuring string literals are correctly quoted
    ROOT.gInterpreter.ProcessLine(f"""
    processEvents("{inputFile}", 
                  "KinFit","{systematic}",  
                  "/afs/cern.ch/work/s/savarghe/private/HplusMVA/CMSSW_13_0_10/src/HplusMVA/Reader/TMVA_bdt_planned_weights.xml",
                  "{outputFileName}" 
                  )
    """
)
# Define the desired output filename and directory
    #desired_filename = f"bdt_{process}_{systematic}_{year}_{channel}.root"
    #desired_output_path = os.path.join(outputDir, desired_filename)
    # shutil.move("outputFileName.root", desired_output_path)
     # Save results
    #outputFileName = f"test/bdt_{process}_{year}_{channel}.root"
    #outputFile = ROOT.TFile(outputFileName, "RECREATE")

    # Create a directory for the systematic inside the output file
    # sysDir = outputFile.mkdir(systematic)
    # sysDir.cd()
    # h1.Write()
    #outputFile.Close()
    print(f"Analysis completed. Results saved in {os.path.join(outputDir, f'bdt_{process}_{systematic}_{year}_{channel}.root')}")



def main():
    parser = argparse.ArgumentParser(description='Process some files.')
    parser.add_argument('process')
    parser.add_argument('systematic')
    parser.add_argument('year')
    parser.add_argument('channel')
    parser.add_argument('outputDir')
    args = parser.parse_args()

    # Now call your function with the parsed arguments
    open_and_process_file(args.process, args.systematic, args.year, args.channel, args.outputDir)

if __name__ == "__main__":
    main()



