import ROOT

def PreAna(process):
    inputFilebase = ROOT.TFile.Open(f"/eos/user/i/idas/Output/cms-hcs-run2/CBA_metxycorr/post/2016/all/all_{process}.root")
    
    outputdir = "/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2016/post/post_res/"
    
    wt_before = inputFilebase.Get(f"{process}/base/Iso/_wt_before_mu")
    wt_after = inputFilebase.Get(f"{process}/base/Iso/_wt_after_mu")
    
    xbins = wt_before.GetXaxis().GetNbins()
    
    h1 = ROOT.TH1D("bdt", "Classifier output", 20, 0, 2)
    
    ttbar = ROOT.TChain("Kinfit_Reco")
    ttbar.Add(f"/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_metxycorr/post/2016/{process}_tree_base_*")
    
    # Initialize variables to be read from the tree
    variables = {
	    "sampleWeight": ROOT.Double(),
	    "puJetIDWeight": ROOT.Double(),
	    "prefireWeight": ROOT.Double(),
	    "prefireWeight_Do": ROOT.Double(),
	    "prefireWeight_Up": ROOT.Double(),
	    "PUWeight": ROOT.Double(),
	    "PUWeight_Up": ROOT.Double(),
	    "PUWeight_Do": ROOT.Double(),
	    "muEffWeight": ROOT.Double(),
	    "muEffWeight_Up": ROOT.Double(),
	    "muEffWeight_Do": ROOT.Double(),
	    "eleEffWeight": ROOT.Double(),
	    "eleEffWeight_Up": ROOT.Double(),
	    "eleEffWeight_Do": ROOT.Double(),
	    "bcTagWeight": ROOT.Double(),
	    "bcTagWeight_bfrag_Up": ROOT.Double(),
	    "bcTagWeight_fsr_Up": ROOT.Double(),
	    "bcTagWeight_isr_Up": ROOT.Double(),
	    "bcTagWeight_jer_Up": ROOT.Double(),
	    "bcTagWeight_jes_Up": ROOT.Double(),
	    "bcTagWeight_lhemuf_Up": ROOT.Double(),
	    "bcTagWeight_lhemur_Up": ROOT.Double(),
	    "bcTagWeight_muid_Up": ROOT.Double(),
	    "bcTagWeight_pu_Up": ROOT.Double(),
	    "bcTagWeight_stat_Up": ROOT.Double(),
	    "bcTagWeight_xdyb_Up": ROOT.Double(),
	    "bcTagWeight_xdyc_Up": ROOT.Double(),
	    "bcTagWeight_xst_Up": ROOT.Double(),
	    "bcTagWeight_xwjc_Up": ROOT.Double(),
	    "bcTagWeight_xtt_Up": ROOT.Double(),
	    "bcTagWeight_bfrag_Do": ROOT.Double(),
	    "bcTagWeight_fsr_Do": ROOT.Double(),
	    "bcTagWeight_isr_Do": ROOT.Double(),
	    "bcTagWeight_jer_Do": ROOT.Double(),
	    "bcTagWeight_jes_Do": ROOT.Double(),
	    "bcTagWeight_lhemuf_Do": ROOT.Double(),
	    "bcTagWeight_lhemur_Do": ROOT.Double(),
	    "bcTagWeight_muid_Do": ROOT.Double(),
	    "bcTagWeight_pu_Do": ROOT.Double(),
	    "bcTagWeight_stat_Do": ROOT.Double(),
	    "bcTagWeight_xdyb_Do": ROOT.Double(),
	    "bcTagWeight_xdyc_Do": ROOT.Double(),
	    "bcTagWeight_xst_Do": ROOT.Double(),
	    "bcTagWeight_xwjc_Do": ROOT.Double(),
	    "bcTagWeight_xtt_Do": ROOT.Double(),
	    "bcTagWeight_intp_Up": ROOT.Double(),
	    "bcTagWeight_intp_Do": ROOT.Double(),
	    "bcTagWeight_extp_Up": ROOT.Double(),
	    "bcTagWeight_extp_Do": ROOT.Double(),
	    "jetChadPt": ROOT.Float(),
	    "jetChadEta": ROOT.Float(),
	    "jetChadPhi": ROOT.Float(),
	    "jetChadEnergy": ROOT.Float(),
	    "jetShadPt": ROOT.Float(),
	    "jetShadEta": ROOT.Float(),
	    "jetShadPhi": ROOT.Float(),
	    "jetShadEnergy": ROOT.Float(),
	    "sjhadCvsLdisc": ROOT.Double(),
	    "sjhadCvsBdisc": ROOT.Double(),
	    "cjhadCvsLdisc": ROOT.Double(),
	    "cjhadCvsBdisc": ROOT.Double(),
	    "jetBhadPt": ROOT.Float(),
	    "jetBhadEta": ROOT.Float(),
	    "jetBhadPhi": ROOT.Float(),
	    "jetBhadEnergy": ROOT.Float(),
	    "jetBlepPt": ROOT.Float(),
	    "jetBlepEta": ROOT.Float(),
	    "jetBlepPhi": ROOT.Float(),
	    "jetBlepEnergy": ROOT.Float(),
	    "metPx": ROOT.Float(),
	    "metPy": ROOT.Float(),
	    "metPz": ROOT.Float(),
	    "chi2": ROOT.Double(),
	    "lepPt": ROOT.Float(),
	    "lepEta": ROOT.Float(),
	    "lepPhi": ROOT.Float(),
	    "lepEnergy": ROOT.Float(),
	    "nJet": ROOT.Int(),
	    "wt_ratio": ROOT.Float(),
	    "singleMu": ROOT.Bool(),
	    "singleEle": ROOT.Bool(),
	    "muonIsoCut": ROOT.Bool(),
	    "eleIsoCut": ROOT.Bool(),
	    "isLowMET": ROOT.Bool(),
	    "ISRweight_Up": ROOT.Float(),
	    "ISRweight_Do": ROOT.Float(),
	    "FSRweight_Up": ROOT.Float(),
	    "FSRweight_Do": ROOT.Float(),
	    "muRweight_Up": ROOT.Float(),
	    "muRweight_Do": ROOT.Float(),
	    "muFweight_Up": ROOT.Float(),
	    "muFweight_Do": ROOT.Float(),
	    "pdfweight_Up": ROOT.Float(),
	    "pdfweight_Do": ROOT.Float(),
	    "METPt": ROOT.Float(),
	    "muonpfRelIso": ROOT.Double(),
	    "elepfRelIso": ROOT.Double(),
	}

    
    # Set branch addresses
    for name in variables.keys():
        ttbar.SetBranchAddress(name, ROOT.AddressOf(variables, name))
    
    def readEvents(tree, histo1, histo2, processName):
        newfile = ROOT.TFile(outputdir + "all_" + processName + ".root", "recreate")
        T = ROOT.TTree("Kinfit_Reco", "skimmed test tree")
        
        # Define the branches in the new tree (T)
        wt_ratio = ROOT.Float(0)
        T.Branch("wt_ratio", wt_ratio, "wt_ratio/F")
        
        for ievt in range(tree.GetEntries()):
            if ievt % 500000 == 0:
                print(f"--- ... Processing event: {ievt}")
            
            tree.GetEntry(ievt)
            
            nJet = variables["nJet"]
            wt_before_bin = histo1.GetBinContent(nJet+1)
            wt_after_bin = histo2.GetBinContent(nJet+1)
            wt_ratio[0] = wt_before_bin / wt_after_bin
            
            T.Fill()
            if ievt < 10:
                print(f"nJet {nJet}   wt_ratio  {wt_ratio[0]}")
        
        newtree = T.CloneTree()
        newtree.Print()
        newfile.Write()
    
    readEvents(ttbar, wt_before, wt_after, f"{process}_base")

# Example usage
PreAna("TTbar")

