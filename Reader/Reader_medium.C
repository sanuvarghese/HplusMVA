void Reader_medium(const TString& year, const TString& process, const TString& channel, const TString& mass) {


  TMVA::Tools::Instance();

    TString methodName = "BDT";

    TString baseDir = Form("/eos/cms/store/group/phys_b2g/savarghe/HplusNtuples/%s/muon/", year.Data());
    TString outputDir = Form("/eos/cms/store/group/phys_b2g/savarghe/HplusHistograms/MVA/%s/%s/ExcMedium/", year.Data(), channel.Data());
    // Create the TFile with the output file name
    TString outputFileName = outputDir + "UL16histlistBDT" + process + "_passwp_" + channel + ".root";
    // Check if the output directory exists, and create it if it doesn't
    // if (!gSystem->AccessPathName(outputDir)) {
    //   gSystem->mkdir(outputDir);
    // }
    // Use the system command to create the output directory and its parent directories
    const char *mkdirCommand = Form("mkdir -p %s", outputDir.Data());
    std::system(mkdirCommand);

    //    TFile *f = new TFile(outputFileName, "RECREATE");
    // Construct the file names using the provided year, process, channel, and mass
    TString inputFileBase = baseDir + Form("all_%s_base_%s_%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileJecUp = baseDir + Form("all_%s_jecup_%s_bc_jes_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileJecDown = baseDir + Form("all_%s_jecdown_%s_bc_jes_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileJerDown = baseDir + Form("all_%s_jerdown_%s_bc_jer_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileJerUp = baseDir + Form("all_%s_jerup_%s_bc_jer_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileIso20 = baseDir + Form("all_%s_iso20_%s_%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileMetDown = baseDir + Form("all_%s_metdown_%s_%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileMetUp = baseDir + Form("all_%s_metup_%s_%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFilePuUp = baseDir + Form("all_%s_base_%s_puUp%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFilePuDown = baseDir + Form("all_%s_base_%s_puDo%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFilePrefireUp = baseDir + Form("all_%s_base_%s_prefireUp%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFilePrefireDown = baseDir + Form("all_%s_base_%s_prefireDo%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileLepEffDown = baseDir + Form("all_%s_base_%s_mueffDo%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileLepEffUp = baseDir + Form("all_%s_base_%s_mueffUp%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcStatDo = baseDir + Form("all_%s_base_%s_bc_stat_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcLhemufDo = baseDir + Form("all_%s_base_%s_bc_lhemuf_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcLhemurDo = baseDir + Form("all_%s_base_%s_bc_lhemur_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcXdybDo = baseDir + Form("all_%s_base_%s_bc_xdyb_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcXdycDo = baseDir + Form("all_%s_base_%s_bc_xdyc_Do%s.root", process.Data(), year.Data(), channel.Data());
    // TString inputFileBcXstDo = baseDir + Form("all_%s_base_%s_bc_xst_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcXwjcDo = baseDir + Form("all_%s_base_%s_bc_xwjc_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcStatUp = baseDir + Form("all_%s_base_%s_bc_stat_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcLhemufUp = baseDir + Form("all_%s_base_%s_bc_lhemuf_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcLhemurUp = baseDir + Form("all_%s_base_%s_bc_lhemur_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcXdybUp = baseDir + Form("all_%s_base_%s_bc_xdyb_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcXdycUp = baseDir + Form("all_%s_base_%s_bc_xdyc_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcXwjcUp = baseDir + Form("all_%s_base_%s_bc_xwjc_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcIntpUp = baseDir + Form("all_%s_base_%s_bc_intp_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcIntpDo = baseDir + Form("all_%s_base_%s_bc_intp_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcExtpUp = baseDir + Form("all_%s_base_%s_bc_extp_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileBcExtpDo = baseDir + Form("all_%s_base_%s_bc_extp_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileFsrUp = baseDir + Form("all_%s_base_%s_bc_fsr_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileFsrDo = baseDir + Form("all_%s_base_%s_bc_fsr_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileIsrUp = baseDir + Form("all_%s_base_%s_bc_isr_Up%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFileIsrDo = baseDir + Form("all_%s_base_%s_bc_isr_Do%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFilePdfUp = baseDir + Form("all_%s_base_%s_pdfUp%s.root", process.Data(), year.Data(), channel.Data());
    TString inputFilePdfDo = baseDir + Form("all_%s_base_%s_pdfDo%s.root", process.Data(), year.Data(), channel.Data());

    // Open the input files
    TFile *inputFileBasePtr = TFile::Open(inputFileBase);
    TFile *inputFileJecUpPtr = TFile::Open(inputFileJecUp);
    TFile *inputFileJecDownPtr = TFile::Open(inputFileJecDown);
    TFile *inputFileJerDownPtr = TFile::Open(inputFileJerDown);
    TFile *inputFileJerUpPtr = TFile::Open(inputFileJerUp);
    TFile *inputFileIso20Ptr = TFile::Open(inputFileIso20);
    TFile *inputFileMetDownPtr = TFile::Open(inputFileMetDown);
    TFile *inputFileMetUpPtr = TFile::Open(inputFileMetUp);
    TFile *inputFilePuUpPtr = TFile::Open(inputFilePuUp);
    TFile *inputFilePuDownPtr = TFile::Open(inputFilePuDown);
    TFile *inputFilePrefireUpPtr = TFile::Open(inputFilePrefireUp);
    TFile *inputFilePrefireDownPtr = TFile::Open(inputFilePrefireDown);
    TFile *inputFileLepEffDownPtr = TFile::Open(inputFileLepEffDown);
    TFile *inputFileLepEffUpPtr = TFile::Open(inputFileLepEffUp);
    TFile *inputFileBcStatDoPtr = TFile::Open(inputFileBcStatDo);
    TFile *inputFileBcLhemufDoPtr = TFile::Open(inputFileBcLhemufDo);
    TFile *inputFileBcLhemurDoPtr = TFile::Open(inputFileBcLhemurDo);
    TFile *inputFileBcXdybDoPtr = TFile::Open(inputFileBcXdybDo);
    TFile *inputFileBcXdycDoPtr = TFile::Open(inputFileBcXdycDo);
    // TFile *inputFileBcXstDoPtr = TFile::Open(inputFileBcXstDo);
    TFile *inputFileBcXwjcDoPtr = TFile::Open(inputFileBcXwjcDo);
    TFile *inputFileBcStatUpPtr = TFile::Open(inputFileBcStatUp);
    TFile *inputFileBcLhemufUpPtr = TFile::Open(inputFileBcLhemufUp);
    TFile *inputFileBcLhemurUpPtr = TFile::Open(inputFileBcLhemurUp);
    TFile *inputFileBcXdybUpPtr = TFile::Open(inputFileBcXdybUp);
    TFile *inputFileBcXdycUpPtr = TFile::Open(inputFileBcXdycUp);
    TFile *inputFileBcXwjcUpPtr = TFile::Open(inputFileBcXwjcUp);
    TFile *inputFileBcIntpUpPtr = TFile::Open(inputFileBcIntpUp);
    TFile *inputFileBcIntpDoPtr = TFile::Open(inputFileBcIntpDo);
    TFile *inputFileBcExtpUpPtr = TFile::Open(inputFileBcExtpUp);
    TFile *inputFileBcExtpDoPtr = TFile::Open(inputFileBcExtpDo);
    TFile *inputFileFsrUpPtr = TFile::Open(inputFileFsrUp);
    TFile *inputFileFsrDoPtr = TFile::Open(inputFileFsrDo);
    TFile *inputFileIsrUpPtr = TFile::Open(inputFileIsrUp);
    TFile *inputFileIsrDoPtr = TFile::Open(inputFileIsrDo);
    TFile *inputFilePdfUpPtr = TFile::Open(inputFilePdfUp);
    TFile *inputFilePdfDoPtr = TFile::Open(inputFilePdfDo);


    auto base_tree = (TTree*) inputFileBasePtr->Get("KinFit");
auto sys1_tree = (TTree*) inputFileJecUpPtr->Get("KinFit");
auto sys2_tree = (TTree*) inputFileJecDownPtr->Get("KinFit");
auto sys3_tree = (TTree*) inputFileJerUpPtr->Get("KinFit");
auto sys4_tree = (TTree*) inputFileJerDownPtr->Get("KinFit");
auto sys5_tree = (TTree*) inputFileMetUpPtr->Get("KinFit");
auto sys6_tree = (TTree*) inputFileMetDownPtr->Get("KinFit");
auto sys7_tree = (TTree*) inputFilePuUpPtr->Get("KinFit");
auto sys8_tree = (TTree*) inputFilePuDownPtr->Get("KinFit");
auto sys9_tree = (TTree*) inputFilePrefireUpPtr->Get("KinFit");
auto sys10_tree = (TTree*) inputFilePrefireDownPtr->Get("KinFit");
auto sys11_tree = (TTree*) inputFileLepEffDownPtr->Get("KinFit");
auto sys12_tree = (TTree*) inputFileLepEffUpPtr->Get("KinFit");
auto sys13_tree = (TTree*) inputFileBcStatDoPtr->Get("KinFit");
auto sys14_tree = (TTree*) inputFileBcStatUpPtr->Get("KinFit");
//auto sys15_tree = (TTree*) inputFilebc_stat_Do->Get("KinFit");
auto sys15_tree = (TTree*) inputFileFsrUpPtr->Get("KinFit");
auto sys16_tree = (TTree*) inputFileFsrDoPtr->Get("KinFit");
auto sys17_tree = (TTree*) inputFileIsrUpPtr->Get("KinFit");
auto sys18_tree = (TTree*) inputFileIsrDoPtr->Get("KinFit");
// auto sys14_tree = (TTree*) inputFilebc_pu_Do ->Get("KinFit");
// auto sys15_tree = (TTree*) inputFilebc_muid_Do->Get("KinFit");
auto sys19_tree = (TTree*) inputFileBcLhemufDoPtr->Get("KinFit");
auto sys20_tree = (TTree*) inputFileBcLhemufUpPtr->Get("KinFit");
auto sys21_tree = (TTree*) inputFileBcLhemurDoPtr->Get("KinFit");
auto sys22_tree = (TTree*) inputFileBcLhemurUpPtr->Get("KinFit");
auto sys23_tree = (TTree*) inputFileBcXdybDoPtr->Get("KinFit");
auto sys24_tree = (TTree*) inputFileBcXdybUpPtr->Get("KinFit");
auto sys25_tree = (TTree*) inputFileBcXdycDoPtr->Get("KinFit");
auto sys26_tree = (TTree*) inputFileBcXdycUpPtr->Get("KinFit");
auto sys27_tree = (TTree*) inputFileBcXwjcDoPtr->Get("KinFit");
auto sys28_tree = (TTree*) inputFileBcXwjcUpPtr->Get("KinFit");
auto sys29_tree = (TTree*) inputFileBcIntpDoPtr->Get("KinFit");
auto sys30_tree = (TTree*) inputFileBcIntpUpPtr->Get("KinFit");
auto sys31_tree = (TTree*) inputFileBcExtpDoPtr->Get("KinFit");
auto sys32_tree = (TTree*) inputFileBcExtpUpPtr->Get("KinFit");
auto sys33_tree = (TTree*) inputFilePdfDoPtr->Get("KinFit");
auto sys34_tree = (TTree*) inputFilePdfUpPtr->Get("KinFit");

 TMVA::Reader reader( "!Color:!Silent" );

Float_t         Weight;
Float_t          mjj;
Float_t         CvsL_j2;
Float_t         CvsL_j1;
Float_t          CvsB_j1;
Float_t         CvsB_j2;
Float_t          pt_j1;
Float_t          pt_j2;
Float_t          pt_b2;
Float_t          pt_b1;
Float_t          dPhi_j1b1;
Float_t         CTopVar;
Float_t         CvsL_b1;
Float_t          CvsB_b1;
Float_t         CvsL_b2;
Float_t          DelR_j1j2;
Float_t          DelR_j1b2;
Float_t         pt_l;
 Float_t         dPhi_j1j2;
Float_t         ht_b1b2j1j2;
Float_t          DelR_j2b1;
Float_t          dPhi_lb2;
Float_t        m_b1b2j1j2lv;
 Float_t        chisq;
 Float_t        mbb;

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
//reader.AddVariable("chisq",&chisq);

TString weightfile = "TMVA_bdt_planned_weights.xml";

reader.BookMVA( methodName,weightfile);

auto h1 = new TH1D("bdt","Classifier output ",30,20,170);
auto h2 = new TH1D("bdt","Classifier output",30,20,170);
auto h3 = new TH1D("bdt","Classifier output",30,20,170);
auto h4 = new TH1D("bdt","Classifier output",30,20,170);
auto h5 = new TH1D("bdt","Classifier output",30,20,170);
auto h6 = new TH1D("bdt","Classifier output",30,20,170);
auto h7 = new TH1D("bdt","Classifier output",30,20,170);
auto h8 = new TH1D("bdt","Classifier output",30,20,170);
auto h9 = new TH1D("bdt","Classifier output",30,20,170);
auto h10 = new TH1D("bdt","Classifier output",30,20,170);
auto h11 = new TH1D("bdt","Classifier output",30,20,170);
auto h12 = new TH1D("bdt","Classifier output",30,20,170);
auto h13 = new TH1D("bdt","Classifier output",30,20,170);
auto h14 = new TH1D("bdt","Classifier output",30,20,170);
auto h15 = new TH1D("bdt","Classifier output",30,20,170);
auto h16 = new TH1D("bdt","Classifier output",30,20,170);
auto h17 = new TH1D("bdt","Classifier output",30,20,170);
auto h18 = new TH1D("bdt","Classifier output",30,20,170);
auto h19 = new TH1D("bdt","Classifier output",30,20,170);
auto h20 = new TH1D("bdt","Classifier output",30,20,170);
auto h21 = new TH1D("bdt","Classifier output",30,20,170);
auto h22 = new TH1D("bdt","Classifier output",30,20,170);
auto h23 = new TH1D("bdt","Classifier output",30,20,170);
auto h24 = new TH1D("bdt","Classifier output",30,20,170);
auto h25 = new TH1D("bdt","Classifier output",30,20,170);
auto h26 = new TH1D("bdt","Classifier output",30,20,170);
auto h27 = new TH1D("bdt","Classifier output",30,20,170);
auto h28 = new TH1D("bdt","Classifier output",30,20,170);
auto h29 = new TH1D("bdt","Classifier output",30,20,170);
auto h30 = new TH1D("bdt","Classifier output",30,20,170);
auto h31 = new TH1D("bdt","Classifier output",30,20,170);
auto h32 = new TH1D("bdt","Classifier output",30,20,170);
auto h33 = new TH1D("bdt","Classifier output",30,20,170);
auto h34 = new TH1D("bdt","Classifier output",30,20,170);
auto h35 = new TH1D("bdt","Classifier output",30,20,170);
auto h36 = new TH1D("bdt","Classifier output",30,20,170);
auto h37 = new TH1D("bdt","Classifier output",30,20,170);
auto h38 = new TH1D("bdt","Classifier output",30,20,170);
auto h39 = new TH1D("bdt","Classifier output",30,20,170);
auto h40 = new TH1D("bdt","Classifier output",30,20,170);
auto h41 = new TH1D("bdt","Classifier output",30,20,170);
auto h42 = new TH1D("bdt","Classifier output",30,20,170);
auto h43 = new TH1D("bdt","Classifier output",30,20,170);
std::vector<float> vout;
std::vector<float> vout2;
std::vector<float> vout3;
std::vector<float> vout4;

 auto readEvents = [&](TTree & tree, TH1 & histo) {
  tree.SetBranchAddress("Weight" ,&Weight);
  tree.SetBranchAddress("mjj",&mjj);
  tree.SetBranchAddress("CvsL_j2",&CvsL_j2);
  tree.SetBranchAddress("CvsL_j1",&CvsL_j1);
  tree.SetBranchAddress("CvsB_j1",&CvsB_j1);
  tree.SetBranchAddress("CvsB_j2",&CvsB_j2);
  //tree.SetBranchAddress("CvsB_j2",&CvsB_j2);                                                                                                                             
  tree.SetBranchAddress("pt_b1",&pt_b1);
  //  tree.SetBranchAddress("pt_b2",&pt_b2);
  //tree.SetBranchAddress("pt_j2",'F');                                                                                                                                    
  tree.SetBranchAddress("pt_j1",&pt_j1);
  tree.SetBranchAddress("pt_j2",&pt_j2);
  tree.SetBranchAddress("pt_b2",&pt_b2);
//tree.SetBranchAddress("mbb",'F');                                                                                                                                      
  //tree.SetBranchAddress("dPhi_j1j2",'F');                                                                                                                                
  tree.SetBranchAddress("dPhi_j1j2",&dPhi_j1j2);
  tree.SetBranchAddress("dPhi_j1b1",&dPhi_j1b1);
  tree.SetBranchAddress("CTopVar",&CTopVar);
  tree.SetBranchAddress("CvsL_b1",&CvsL_b1);
  tree.SetBranchAddress("CvsB_b1",&CvsB_b1);  
tree.SetBranchAddress("CvsL_b2",&CvsL_b2);
  //tree.SetBranchAddress("CvsL_b2",&CvsL_b2);                                                                                                                             
  //tree.SetBranchAddress("DelR_j1j2",&DelR_j1j2);                                                                                                                         
  tree.SetBranchAddress("DelR_j1b2",&DelR_j1b2);
  //tree.SetBranchAddress("pt_l",&pt_l);                                                                                                                                   
  tree.SetBranchAddress("ht_b1b2j1j2",&ht_b1b2j1j2);
  tree.SetBranchAddress("DelR_j2b1",&DelR_j2b1);
  tree.SetBranchAddress("dPhi_lb2",&dPhi_lb2);
  tree.SetBranchAddress("m_b1b2j1j2lv",&m_b1b2j1j2lv);
  //tree.SetBranchAddress("chisq",&chisq);    
//reader.AddVariable("dPhi_j1b2",'F')
  vout.clear(); 
  vout.resize(tree.GetEntries());
  for (Long64_t ievt=0; ievt < tree.GetEntries();ievt++) {

      if (ievt%500000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

      tree.GetEntry(ievt);
   
      auto output = reader.EvaluateMVA(methodName);
      
      if(output < -0.02 || output > 0.19)continue; //medium wp

      //  histo.Fill(output,Weight);
      histo.Fill(mjj,Weight);
        vout[ievt] = output;  
  }
};
// read events and fill histogram
readEvents(*base_tree,*h1);

//std::vector<float> bkg_result = vout;

readEvents(*sys1_tree,*h2);

readEvents(*sys2_tree,*h3);

readEvents(*sys3_tree,*h4);


readEvents(*sys4_tree,*h5);
readEvents(*sys5_tree,*h6);
readEvents(*sys6_tree,*h7);
readEvents(*sys7_tree,*h8);
readEvents(*sys8_tree,*h9);
readEvents(*sys9_tree,*h10);
readEvents(*sys10_tree,*h11);
readEvents(*sys11_tree,*h12);
readEvents(*sys12_tree,*h13);
readEvents(*sys13_tree,*h14);
readEvents(*sys14_tree,*h15);
readEvents(*sys15_tree,*h16);
readEvents(*sys16_tree,*h17);
readEvents(*sys17_tree,*h18);
readEvents(*sys18_tree,*h19);
readEvents(*sys19_tree,*h20);
readEvents(*sys20_tree,*h21);
readEvents(*sys21_tree,*h22);
readEvents(*sys22_tree,*h23);
readEvents(*sys23_tree,*h24);
//readEvents(*sys_tree,*h16);
readEvents(*sys24_tree,*h25);
readEvents(*sys25_tree,*h26);
readEvents(*sys26_tree,*h27);
readEvents(*sys27_tree,*h28);
readEvents(*sys28_tree,*h29);
readEvents(*sys29_tree,*h30);
readEvents(*sys30_tree,*h31);
readEvents(*sys31_tree,*h32);
readEvents(*sys32_tree,*h33);
readEvents(*sys33_tree,*h34);
readEvents(*sys34_tree,*h35);

//TFile *f = new TFile("UL16histlistBDT"+process+"_passwp_"+channel+".root","RECREATE");
//TString outputFileName = outputDir + "UL16histlistBDT" + process + "_passwp_" + channel + ".root";
 // Create the TFile with the output file name
 TFile *f = new TFile(outputFileName, "RECREATE");

 TDirectory *base = f->mkdir("base");
TDirectory *sys1 = f->mkdir("jecUp");
TDirectory *sys2 = f->mkdir("jecDo");
TDirectory *sys3 = f->mkdir("jerUp");
TDirectory *sys4 = f->mkdir("jerDo");
TDirectory *sys5 = f->mkdir("metDo");
TDirectory *sys6 = f->mkdir("metUp");
TDirectory *sys7 = f->mkdir("puUp");
TDirectory *sys8 = f->mkdir("puDo");
TDirectory *sys9 = f->mkdir("prefireUp");
TDirectory *sys10 = f->mkdir("prefireDo");
TDirectory *sys11 = f->mkdir("lepEffDo");
TDirectory *sys12 = f->mkdir("lepEFFUp");
TDirectory *sys13 = f->mkdir("bc_statDo");
TDirectory *sys14 = f->mkdir("bc_statUp");
TDirectory *sys15 = f->mkdir("fsrUp");
TDirectory *sys16 = f->mkdir("fsrDo");
TDirectory *sys17 = f->mkdir("isrUp");
TDirectory *sys18 = f->mkdir("isrDo");
TDirectory *sys19 = f->mkdir("mufDo");
TDirectory *sys20 = f->mkdir("mufUp");
TDirectory *sys21 = f->mkdir("murDo");
TDirectory *sys22 = f->mkdir("murUp");
TDirectory *sys23 = f->mkdir("bc_xdybDo");
TDirectory *sys24 = f->mkdir("bc_xdybUp");
TDirectory *sys25 = f->mkdir("bc_xdycDo");
TDirectory *sys26 = f->mkdir("bc_xdycUp");
TDirectory *sys27 = f->mkdir("bc_xwjcDo");
TDirectory *sys28 = f->mkdir("bc_xwjcUp");
TDirectory *sys29 = f->mkdir("bc_intpDo");
TDirectory *sys30 = f->mkdir("bc_intpUp");
TDirectory *sys31 = f->mkdir("bc_extpDo");
TDirectory *sys32 = f->mkdir("bc_extpUp");
TDirectory *sys33 = f->mkdir("bc_pdfDo");
TDirectory *sys34 = f->mkdir("bc_pdfUp");
 base->cd();
//h1->Scale(1/0.1215);
h1->Write();
   //h2->Write() ;  
   //h->Write();
f->ls();


sys1->cd();
//h2->Scale(1/0.1215);
h2->Write();
sys2->cd();
//h3->Scale(1/0.1215);
h3->Write();
sys3->cd();
//h4->Scale(1/0.1215);
h4->Write();
sys4->cd();
//h5->Scale(1/0.1215);
h5->Write();
sys5->cd();
//h6->Scale(1/0.1215);
h6->Write();
sys6->cd();
//h7->Scale(1/0.1215);
h7->Write();
sys7->cd();
//h8->Scale(1/0.1215);
h8->Write();
sys8->cd();
//h9->Scale(1/0.1215);
h9->Write();
sys9->cd();
//h10->Scale(1/0.1215);
h10->Write();
sys10->cd();
//h11->Scale(1/0.1215);
h11->Write();
sys11->cd();
//h12->Scale(1/0.1215);
h12->Write();
sys12->cd();
//h13->Scale(1/0.1215);
h13->Write();
sys13->cd();
 h14->Scale(h1->Integral()/h14->Integral());
h14->Write();
sys14->cd();
//h15->Scale(1/0.1215);
 h15->Scale(h1->Integral()/h15->Integral());

h15->Write();
sys15->cd();
//h15->Scale(1/0.1215);
 h16->Scale(h1->Integral()/h16->Integral());

h16->Write();
//h1->Write();
sys16->cd();
 h17->Scale(h1->Integral()/h17->Integral());

//h12->Scale(1/0.1215);
h17->Write();
sys17->cd();
//h13->Scale(1/0.1215);
 h18->Scale(h1->Integral()/h18->Integral());

h18->Write();
sys18->cd();
//h14->Scale(1/0.1215);
 h19->Scale(h1->Integral()/h19->Integral());

h19->Write();
sys19->cd();
//h15->Scale(1/0.1215);
h20->Write();
sys20->cd();
//h15->Scale(1/0.1215);
h21->Write();
sys21->cd();
//h22->Scale(2/0.2225);
h22->Write();
sys22->cd();
//h23->Scale(2/0.2225);
h23->Write();
sys23->cd();
//h24->Scale(2/0.2225);
h24->Write();
sys24->cd();
//h25->Scale(2/0.2225);
h25->Write();
sys25->cd();
//h25->Scale(2/0.2225);
h26->Write();
//h2->Write();
sys26->cd();
//h22->Scale(2/0.2225);
h27->Write();
sys27->cd();
//h23->Scale(2/0.2225);
h28->Write();
sys28->cd();
//h24->Scale(2/0.2225);
h29->Write();
sys30->cd();
//h24->Scale(2/0.2225);
h31->Write();
sys31->cd();
//h33->Scale(3/0.3335);
h32->Write();
sys32->cd();
//h33->Scale(3/0.3335);
h33->Write();
sys33->cd();
//h34->Scale(3/0.3335);
h34->Write();
sys34->cd();
//h35->Scale(3/0.3335);
h35->Write();

 
f->Close();

}
