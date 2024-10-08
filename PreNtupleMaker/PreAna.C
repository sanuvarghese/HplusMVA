void PreAna(TString process) {

  TFile *inputFilebase = TFile::Open("/eos/user/i/idas/Output/cms-hcs-run2/CBA_jecsyst/post/2016/all/all_"+process+".root");

  TString outputdir = "/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2016/post/post_res/";

  auto wt_before = (TH1D*) inputFilebase->Get(process+"/base/Iso/_wt_before_mu");

  auto wt_after = (TH1D*) inputFilebase->Get(process+"/base/Iso/_wt_after_mu");

  Float_t         weight_before;
  Float_t         weight_after;
  Float_t         weight_ratio;

  int xbins=wt_before->GetXaxis()->GetNbins();

  //TFile *treeFile = TFile::Open("TTbar_tree_base_19of45.root");
  //auto base_tree = (TTree*) treeFile->Get("Kinfit_Reco");

  auto h1 = new TH1D("bdt","Classifier output ",20,0,2);

  TChain *ttbar= new TChain("Kinfit_Reco");
  ttbar->Add("/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_jecsyst/post/2016/"+process+"_tree_base_*");

  Double_t         sampleWeight;
  Double_t puJetIDWeight; 
  Double_t prefireWeight;
  Double_t prefireWeight_Do; 
  Double_t prefireWeight_Up; 
  Double_t PUWeight; 
  Double_t PUWeight_Up; 
  Double_t PUWeight_Do;
  Double_t muEffWeight; 
  Double_t muEffWeight_Up; 
  Double_t muEffWeight_Do; 
  Double_t eleEffWeight; 
  Double_t eleEffWeight_Up; 
  Double_t eleEffWeight_Do; 
  Double_t bcTagWeight; 
  Double_t bcTagWeight_bfrag_Up; 
  Double_t bcTagWeight_fsr_Up; 
  Double_t bcTagWeight_isr_Up; 
  Double_t bcTagWeight_jer_Up; 
  Double_t bcTagWeight_jes_Up; 
  Double_t bcTagWeight_lhemuf_Up; 
  Double_t bcTagWeight_lhemur_Up; 
  Double_t bcTagWeight_muid_Up; 
  Double_t bcTagWeight_pu_Up; 
  Double_t bcTagWeight_stat_Up; 
  Double_t bcTagWeight_xdyb_Up;
  Double_t bcTagWeight_xdyc_Up; 
  Double_t bcTagWeight_xst_Up; 
  Double_t bcTagWeight_xwjc_Up; 
  Double_t bcTagWeight_xtt_Up; 
  Double_t bcTagWeight_bfrag_Do;
  Double_t bcTagWeight_fsr_Do;
  Double_t bcTagWeight_isr_Do;
  Double_t bcTagWeight_jer_Do;
  Double_t bcTagWeight_jes_Do;
  Double_t bcTagWeight_lhemuf_Do;
  Double_t bcTagWeight_lhemur_Do;
  Double_t bcTagWeight_muid_Do;
  Double_t bcTagWeight_pu_Do;
  Double_t bcTagWeight_stat_Do;
  Double_t bcTagWeight_xdyb_Do;
  Double_t bcTagWeight_xdyc_Do;
  Double_t bcTagWeight_xst_Do;
  Double_t bcTagWeight_xwjc_Do;
  Double_t bcTagWeight_xtt_Do;
  Double_t bcTagWeight_intp_Up;
  Double_t bcTagWeight_intp_Do;
  Double_t bcTagWeight_extp_Up;
  Double_t bcTagWeight_extp_Do;
  Float_t         jetChadPt;
  Float_t         jetChadEta;
  Float_t         jetChadPhi;
  Float_t         jetChadEnergy;
  Float_t         jetShadPt;
  Float_t         jetShadEta;
  Float_t         jetShadPhi;
  Float_t         jetShadEnergy;
  Double_t         sjhadCvsLdisc;
  Double_t         sjhadCvsBdisc;
  Double_t         cjhadCvsLdisc;
  Double_t         cjhadCvsBdisc;
  Float_t         jetBhadPt;
  Float_t         jetBhadEta;
  Float_t         jetBhadPhi;
  Float_t         jetBhadEnergy;
  Float_t         jetBlepPt;
  Float_t         jetBlepEta;
  Float_t         jetBlepPhi;
  Float_t         jetBlepEnergy;
  Float_t        metPx;
  Float_t        metPy;
  Float_t        metPz;
  Double_t        chi2;
  //Float_t        bcTagWeight;
  Double_t        bjhadCvsLdisc;
  Double_t        bjhadCvsBdisc;
  Double_t        bjlepCvsLdisc;
  Double_t        bjlepCvsBdisc;
  Float_t         lepPt;
  Float_t         lepEta;
  Float_t         lepPhi;
  Float_t         lepEnergy;
  //Float_t        chi2;
  Int_t  nJet;
  Float_t      wt_ratio;
  Bool_t      singleMu;
  Bool_t      singleEle;
  Bool_t      muonIsoCut;
  Bool_t      eleIsoCut;
  Bool_t      isLowMET;
  Float_t      ISRweight_Up;
  Float_t      ISRweight_Do;
  Float_t      FSRweight_Up;
  Float_t      FSRweight_Do;
  Float_t      muRweight_Do;
  Float_t      muRweight_Up;
  Float_t      muFweight_Do;
  Float_t      muFweight_Up;
  Float_t      pdfweight_Up;
  Float_t      pdfweight_Do;
  Float_t      METPt;
  Double_t      muonpfRelIso;
  Double_t      elepfRelIso;
  // Float_t   
//  Double_t      isLowMET;
  //Float_t      eleIsoCut;


  auto readEvents = [&](TTree & tree, TH1D & histo1 , TH1D & histo2,TString processName) {
    //TFile newfile("all_"+processName+".root", "recreate");    
    tree.SetBranchAddress("nJet",&nJet);
    //tree.SetBranchAddress("wt_ratio",&wt_ratio);
    tree.SetBranchAddress("sampleWeight",&sampleWeight);
    tree.SetBranchAddress("puJetIDWeight",&puJetIDWeight);
    tree.SetBranchAddress("prefireWeight",&prefireWeight);
    tree.SetBranchAddress("prefireWeight_Do",&prefireWeight_Do);
    tree.SetBranchAddress("prefireWeight_Up",&prefireWeight_Up);
    tree.SetBranchAddress("PUWeight",&PUWeight);
    tree.SetBranchAddress("PUWeight_Up",&PUWeight_Up);
    tree.SetBranchAddress("PUWeight_Do",&PUWeight_Do);
    tree.SetBranchAddress("muEffWeight",&muEffWeight);
    tree.SetBranchAddress("muEffWeight_Up",&muEffWeight_Up);
    tree.SetBranchAddress("muEffWeight_Do",&muEffWeight_Do);
    tree.SetBranchAddress("eleEffWeight",&eleEffWeight);
    tree.SetBranchAddress("eleEffWeight_Up",&eleEffWeight_Up);
    tree.SetBranchAddress("eleEffWeight_Do",&eleEffWeight_Do);
    tree.SetBranchAddress("bcTagWeight",&bcTagWeight);
    tree.SetBranchAddress("bcTagWeight_bfrag_Up",&bcTagWeight_bfrag_Up);
    tree.SetBranchAddress("bcTagWeight_fsr_Up",&bcTagWeight_fsr_Up);
    tree.SetBranchAddress("bcTagWeight_isr_Up",&bcTagWeight_isr_Up);
    tree.SetBranchAddress("bcTagWeight_jer_Up",&bcTagWeight_jer_Up);
    tree.SetBranchAddress("bcTagWeight_jes_Up",&bcTagWeight_jes_Up);
    tree.SetBranchAddress("bcTagWeight_lhemuf_Up",&bcTagWeight_lhemuf_Up);
    tree.SetBranchAddress("bcTagWeight_lhemur_Up",&bcTagWeight_lhemur_Up);
    tree.SetBranchAddress("bcTagWeight_muid_Up",&bcTagWeight_muid_Up);
    tree.SetBranchAddress("bcTagWeight_pu_Up",&bcTagWeight_pu_Up);
    tree.SetBranchAddress("bcTagWeight_stat_Up",&bcTagWeight_stat_Up);
    tree.SetBranchAddress("bcTagWeight_xdyb_Up",&bcTagWeight_xdyb_Up);
    tree.SetBranchAddress("bcTagWeight_xdyc_Up",&bcTagWeight_xdyc_Up);
    tree.SetBranchAddress("bcTagWeight_xst_Up",&bcTagWeight_xst_Up);
    tree.SetBranchAddress("bcTagWeight_xwjc_Up",&bcTagWeight_xwjc_Up);
    tree.SetBranchAddress("bcTagWeight_xtt_Up",&bcTagWeight_xtt_Up);
    tree.SetBranchAddress("bcTagWeight_bfrag_Do",&bcTagWeight_bfrag_Do);
    tree.SetBranchAddress("bcTagWeight_fsr_Do",&bcTagWeight_fsr_Do);
    tree.SetBranchAddress("bcTagWeight_isr_Do",&bcTagWeight_isr_Do);
    tree.SetBranchAddress("bcTagWeight_jer_Do",&bcTagWeight_jer_Do);
    tree.SetBranchAddress("bcTagWeight_jes_Do",&bcTagWeight_jes_Do);
    tree.SetBranchAddress("bcTagWeight_lhemuf_Do",&bcTagWeight_lhemuf_Do);
    tree.SetBranchAddress("bcTagWeight_lhemur_Do",&bcTagWeight_lhemur_Do);
    tree.SetBranchAddress("bcTagWeight_muid_Do",&bcTagWeight_muid_Do);
    tree.SetBranchAddress("bcTagWeight_pu_Do",&bcTagWeight_pu_Do);
    tree.SetBranchAddress("bcTagWeight_stat_Do",&bcTagWeight_stat_Do);
    tree.SetBranchAddress("bcTagWeight_xdyb_Do",&bcTagWeight_xdyb_Do);
    tree.SetBranchAddress("bcTagWeight_xdyc_Do",&bcTagWeight_xdyc_Do);
    tree.SetBranchAddress("bcTagWeight_xst_Do",&bcTagWeight_xst_Do);
    tree.SetBranchAddress("bcTagWeight_xwjc_Do",&bcTagWeight_xwjc_Do);
    tree.SetBranchAddress("bcTagWeight_xtt_Do",&bcTagWeight_xtt_Do);
tree.SetBranchAddress("bcTagWeight_intp_Up",&bcTagWeight_intp_Up);
tree.SetBranchAddress("bcTagWeight_intp_Do",&bcTagWeight_intp_Do);
tree.SetBranchAddress("bcTagWeight_extp_Up",&bcTagWeight_extp_Up);
tree.SetBranchAddress("bcTagWeight_extp_Do",&bcTagWeight_extp_Do);
    tree.SetBranchAddress("jetChadPt",&jetChadPt);
    tree.SetBranchAddress("jetChadEta",&jetChadEta);
    tree.SetBranchAddress("jetChadPhi",&jetChadPhi);
    tree.SetBranchAddress("jetChadEnergy",&jetChadEnergy);
    tree.SetBranchAddress("jetShadPt",&jetShadPt);
    tree.SetBranchAddress("jetShadEta",&jetShadEta);
    tree.SetBranchAddress("jetShadPhi",&jetShadPhi);
    tree.SetBranchAddress("jetShadEnergy",&jetShadEnergy);
    tree.SetBranchAddress("sjhadCvsLdisc",&sjhadCvsLdisc);
    tree.SetBranchAddress("cjhadCvsLdisc",&cjhadCvsLdisc);
    tree.SetBranchAddress("cjhadCvsBdisc",&cjhadCvsBdisc);
    tree.SetBranchAddress("sjhadCvsBdisc",&sjhadCvsBdisc);
    tree.SetBranchAddress("jetBhadPt",&jetBhadPt);
    tree.SetBranchAddress("jetBhadEta",&jetBhadEta);
    tree.SetBranchAddress("jetBhadPhi",&jetBhadPhi);
    tree.SetBranchAddress("jetBhadEnergy",&jetBhadEnergy);
    tree.SetBranchAddress("jetBlepPt",&jetBlepPt);
    tree.SetBranchAddress("jetBlepEta",&jetBlepEta);
    tree.SetBranchAddress("jetBlepPhi",&jetBlepPhi);
    tree.SetBranchAddress("jetBlepEnergy",&jetBlepEnergy);
    tree.SetBranchAddress("bjhadCvsLdisc",&bjhadCvsLdisc);
    tree.SetBranchAddress("bjhadCvsBdisc",&bjhadCvsBdisc);
    tree.SetBranchAddress("bjlepCvsBdisc",&bjlepCvsBdisc);
    tree.SetBranchAddress("bjlepCvsLdisc",&bjlepCvsLdisc);
    tree.SetBranchAddress("lepPt",&lepPt);
    tree.SetBranchAddress("lepEta",&lepEta);
    tree.SetBranchAddress("lepPhi",&lepPhi);
    tree.SetBranchAddress("lepEnergy",&lepEnergy);
    tree.SetBranchAddress("metPx",&metPx);
    tree.SetBranchAddress("metPy",&metPy);
    tree.SetBranchAddress("metPz",&metPz);
    tree.SetBranchAddress("chi2",&chi2);
    tree.SetBranchAddress("nJet",&nJet);
tree.SetBranchAddress("singleMu",&singleMu);
tree.SetBranchAddress("singleEle",&singleEle);
tree.SetBranchAddress("muonIsoCut",&muonIsoCut);
tree.SetBranchAddress("eleIsoCut",&eleIsoCut);
tree.SetBranchAddress("isLowMET",&isLowMET);
tree.SetBranchAddress("ISRweight_Up",&ISRweight_Up);
tree.SetBranchAddress("FSRweight_Up",&FSRweight_Up);
tree.SetBranchAddress("ISRweight_Do",&ISRweight_Do);
tree.SetBranchAddress("FSRweight_Do",&FSRweight_Do);
//tree.SetBranchAddress("isLowMET",&isLowMET);
tree.SetBranchAddress("muRweight_Up",&muRweight_Up);
tree.SetBranchAddress("muFweight_Up",&muFweight_Up);
tree.SetBranchAddress("muRweight_Do",&muRweight_Do);
tree.SetBranchAddress("muFweight_Do",&muFweight_Do);
tree.SetBranchAddress("pdfweight_Do",&pdfweight_Do);
tree.SetBranchAddress("pdfweight_Up",&pdfweight_Up);
tree.SetBranchAddress("muonpfRelIso",&muonpfRelIso);
tree.SetBranchAddress("elepfRelIso",&elepfRelIso);
tree.SetBranchAddress("METPt",&METPt);

TFile newfile(outputdir+"all_"+processName+".root", "recreate");
    TTree *T = new TTree("Kinfit_Reco","skimmed test tree");
    //TTree *T= tree.CloneTree();
    T->Branch("wt_ratio",&wt_ratio,"pz/F");
    T->Branch("sampleWeight",&sampleWeight);
    T->Branch("puJetIDWeight",&puJetIDWeight);
    T->Branch("prefireWeight",&prefireWeight);
    T->Branch("prefireWeight_Do",&prefireWeight_Do);
    T->Branch("prefireWeight_Up",&prefireWeight_Up);
    T->Branch("PUWeight",&PUWeight);
    T->Branch("PUWeight_Up",&PUWeight_Up);
    T->Branch("PUWeight_Do",&PUWeight_Do);
    T->Branch("muEffWeight",&muEffWeight);
    T->Branch("muEffWeight_Up",&muEffWeight_Up);
    T->Branch("muEffWeight_Do",&muEffWeight_Do);
    T->Branch("eleEffWeight",&eleEffWeight);
    T->Branch("eleEffWeight_Up",&eleEffWeight_Up);
    T->Branch("eleEffWeight_Do",&eleEffWeight_Do);
    T->Branch("bcTagWeight",&bcTagWeight);
    T->Branch("bcTagWeight_bfrag_Up",&bcTagWeight_bfrag_Up);
    T->Branch("bcTagWeight_fsr_Up",&bcTagWeight_fsr_Up);
    T->Branch("bcTagWeight_isr_Up",&bcTagWeight_isr_Up);
    T->Branch("bcTagWeight_jer_Up",&bcTagWeight_jer_Up);
    T->Branch("bcTagWeight_jes_Up",&bcTagWeight_jes_Up);
    T->Branch("bcTagWeight_lhemuf_Up",&bcTagWeight_lhemuf_Up);
    T->Branch("bcTagWeight_lhemur_Up",&bcTagWeight_lhemur_Up);
    T->Branch("bcTagWeight_muid_Up",&bcTagWeight_muid_Up);
    T->Branch("bcTagWeight_pu_Up",&bcTagWeight_pu_Up);
    T->Branch("bcTagWeight_stat_Up",&bcTagWeight_stat_Up);
    T->Branch("bcTagWeight_xdyb_Up",&bcTagWeight_xdyb_Up);
    T->Branch("bcTagWeight_xdyc_Up",&bcTagWeight_xdyc_Up);
    T->Branch("bcTagWeight_xst_Up",&bcTagWeight_xst_Up);
    T->Branch("bcTagWeight_xwjc_Up",&bcTagWeight_xwjc_Up);
    T->Branch("bcTagWeight_xtt_Up",&bcTagWeight_xtt_Up);
    T->Branch("bcTagWeight_bfrag_Do",&bcTagWeight_bfrag_Do);
    T->Branch("bcTagWeight_fsr_Do",&bcTagWeight_fsr_Do);
    T->Branch("bcTagWeight_isr_Do",&bcTagWeight_isr_Do);
    T->Branch("bcTagWeight_jer_Do",&bcTagWeight_jer_Do);
    T->Branch("bcTagWeight_jes_Do",&bcTagWeight_jes_Do);
    T->Branch("bcTagWeight_lhemuf_Do",&bcTagWeight_lhemuf_Do);
    T->Branch("bcTagWeight_lhemur_Do",&bcTagWeight_lhemur_Do);
    T->Branch("bcTagWeight_muid_Do",&bcTagWeight_muid_Do);
    T->Branch("bcTagWeight_pu_Do",&bcTagWeight_pu_Do);
    T->Branch("bcTagWeight_stat_Do",&bcTagWeight_stat_Do);
    T->Branch("bcTagWeight_xdyb_Do",&bcTagWeight_xdyb_Do);
T->Branch("bcTagWeight_xdyc_Do",&bcTagWeight_xdyc_Do);
    T->Branch("bcTagWeight_xst_Do",&bcTagWeight_xst_Do);
  T->Branch("bcTagWeight_xwjc_Do",&bcTagWeight_xwjc_Do);
  T->Branch("bcTagWeight_xtt_Do",&bcTagWeight_xtt_Do);
T->Branch("jetChadPt",&jetChadPt);
    T->Branch("jetChadEta",&jetChadEta);
    T->Branch("jetChadPhi",&jetChadPhi);
    T->Branch("jetChadEnergy",&jetChadEnergy);
    T->Branch("jetShadPt",&jetShadPt);
    T->Branch("jetShadEta",&jetShadEta);
    T->Branch("jetShadPhi",&jetShadPhi);
    T->Branch("jetShadEnergy",&jetShadEnergy);
    T->Branch("sjhadCvsLdisc",&sjhadCvsLdisc);
    T->Branch("cjhadCvsLdisc",&cjhadCvsLdisc);
    T->Branch("cjhadCvsBdisc",&cjhadCvsBdisc);
    T->Branch("sjhadCvsBdisc",&sjhadCvsBdisc);
    T->Branch("jetBhadPt",&jetBhadPt);
    T->Branch("jetBhadEta",&jetBhadEta);
    T->Branch("jetBhadPhi",&jetBhadPhi);
    T->Branch("jetBhadEnergy",&jetBhadEnergy);
    T->Branch("jetBlepPt",&jetBlepPt);
    T->Branch("jetBlepEta",&jetBlepEta);
    T->Branch("jetBlepPhi",&jetBlepPhi);
    T->Branch("jetBlepEnergy",&jetBlepEnergy);
    T->Branch("bjhadCvsLdisc",&bjhadCvsLdisc);
    T->Branch("bjhadCvsBdisc",&bjhadCvsBdisc);
    T->Branch("bjlepCvsBdisc",&bjlepCvsBdisc);
    T->Branch("bjlepCvsLdisc",&bjlepCvsLdisc);
    T->Branch("lepPt",&lepPt);
    T->Branch("lepEta",&lepEta);
    T->Branch("lepPhi",&lepPhi);
    T->Branch("lepEnergy",&lepEnergy);
    T->Branch("metPx",&metPx);
    T->Branch("metPy",&metPy);
    T->Branch("metPz",&metPz);
    T->Branch("chi2",&chi2);
    T->Branch("nJet",&nJet);
T->Branch("singleMu",&singleMu);
T->Branch("singleEle",&singleEle);
T->Branch("muonIsoCut",&muonIsoCut);
T->Branch("eleIsoCut",&eleIsoCut);
T->Branch("isLowMET",&isLowMET);
T->Branch("ISRweight_Up",&ISRweight_Up);
T->Branch("FSRweight_Up",&FSRweight_Up);
T->Branch("ISRweight_Do",&ISRweight_Do);
T->Branch("FSRweight_Do",&FSRweight_Do);
T->Branch("muRweight_Up",&muRweight_Up);
T->Branch("muFweight_Up",&muFweight_Up);
T->Branch("muRweight_Do",&muRweight_Do);
T->Branch("muFweight_Do",&muFweight_Do);
T->Branch("pdfweight_Do",&pdfweight_Do);
T->Branch("pdfweight_Up",&pdfweight_Up);
T->Branch("muonpfRelIso",&muonpfRelIso);
T->Branch("elepfRelIso",&elepfRelIso);
T->Branch("METPt",&METPt);
T->Branch("bcTagWeight_intp_Up",&bcTagWeight_intp_Up);
T->Branch("bcTagWeight_intp_Do",&bcTagWeight_intp_Do);
T->Branch("bcTagWeight_extp_Up",&bcTagWeight_extp_Up);
T->Branch("bcTagWeight_extp_Do",&bcTagWeight_extp_Do);


    //reader.AddVariable("dPhi_j1b2",'F')
    //vout.clear(); 
    //vout.resize(tree.GetEntries());
    for (Long64_t ievt=0; ievt < tree.GetEntries();ievt++) {

      if (ievt%500000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

      tree.GetEntry(ievt);
      
   
      float_t wt_before_bin = histo1.GetBinContent(nJet+1);
      float_t wt_after_bin = histo2.GetBinContent(nJet+1);
      wt_ratio = wt_before_bin/wt_after_bin;
      T->Fill() ;
            if (ievt<10 )std::cout<<"nJet"<<nJet<<"   wt_ratio  "<<wt_ratio<<endl;
    }
    
    // oldtree->SetBranchStatus(activeBranchName, 1);
 
    // Create a new file + a clone of old tree in new file
//    TFile newfile("all_"+processName+".root", "recreate");
    auto newtree = T->CloneTree();
 
    newtree->Print();
    newfile.Write();
    
    //TFile* file = new TFile("testNew.root", "RECREATE");
    
    // TTree *T = new TTree("T","test circular buffers");
    //  TTree *T = new TTree("T","test circular buffers");
    //T->Branch("wt_ratio",&wt_ratio,"pz/F");
    //    T->Write();
  };

  readEvents(*ttbar,*wt_before ,*wt_after,process+"_base");

}
