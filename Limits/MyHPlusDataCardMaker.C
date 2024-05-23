#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm> 
#include "MyHPlusDataCardMaker.h"

//----------------------------------------//
//make data card for each mass
//----------------------------------------//

void MyHPlusDataCardMakerMini(TString inFileDir="/afs/cern.ch/work/s/savarghe/NewJEC/2016/mu/A/mergedHistos/LowMass/ExcTight/mass160/", 
			      //TString syear="2016", 
			      TString histSubDir_="KinFit",
			      TString histName="mjj_kfit", 
			      TString channelName="mu", 
			      int mass=160, 
			      TString label="WH160", 
			      TString hPlusFileName="all_Hplus160.root")
{


  MyHPlusDataCardMaker DC;
  //TString baseDir = "topPtWeight";
  TString baseDir = "base";
    TString histSubDir = "";
  bool isMuChannel = false; 
  TString workingpoint = "ExcTight";
  if(channelName=="mu") isMuChannel = true;
  //inFileDir = inFileDir + "/" + syear;



  //int year = syear.Atoi();
  // int year = syear.Atoi();
   double totLumi = 35.9; //2016
  //  if(year==2016)
  //    totLumi = 41.5; // 2016
  //  if(year==2016)
  //   totLumi = 59.7; //2016

  // Open data files
  TFile* fData = TFile::Open(inFileDir+"/hist_DataMu_2016_mu.root");
  TFile* fDataEle = TFile::Open(inFileDir+"/hist_DataEle_2016_mu.root");

  // Open background files
  TFile* fDY = TFile::Open(inFileDir+"/hist_DYjets_2016_mu.root");
  TFile* fWJ = TFile::Open(inFileDir+"/hist_Wjets_2016_mu.root");
  TFile* fST = TFile::Open(inFileDir+"/hist_singleTop_2016_mu.root");
  TFile* fTT = TFile::Open(inFileDir+"/hist_TTbar_2016_mu.root");
  TFile* fVV = TFile::Open(inFileDir+"/hist_VBFusion_2016_mu.root");

  // Open signal file
  TFile* fWH = TFile::Open(inFileDir+"/hist_HplusM160_2016_mu.root");

  // Open other process files
  TFile* fMCQCDEle = TFile::Open(inFileDir+"/hist_MCQCDEle_2016_mu.root");
  TFile* fQCD = TFile::Open(inFileDir+"/hist_MCQCDMu_2016_mu.root");

  TFile* fTG = TFile::Open(inFileDir+"/hist_TTG_2016_mu.root");
  TFile* fTH = TFile::Open(inFileDir+"/hist_TTH_2016_mu.root");
  //TFile* fTTHToNonbb = TFile::Open(inFileDir+"/hist_TTHToNonbb_2016_mu.root");
  //TFile* fTTHTobb = TFile::Open(inFileDir+"/hist_TTHTobb_2016_mu.root");

  //  TFile* fTTWJetsToLNu = TFile::Open(inFileDir+"/hist_TTWJetsToLNu_2016_mu.root");
  TFile* fTW = TFile::Open(inFileDir+"/hist_TTW_2016_mu.root");

  TFile* fTZ = TFile::Open(inFileDir+"/hist_TTZ_2016_mu.root");
  
  //OUTPUT FILE
  // TFile *fout = new TFile(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+workingpoint+histName+TString("_")+label+TString(".root"), "RECREATE");

  // Adjusted OUTPUT FILE creation line without "_output_"
  TFile *fout = new TFile(TString("Shapes_hcs_2016_")+channelName+TString("_")+histSubDir_+TString("_")+workingpoint+histName+TString("_")+label+TString(".root"), "RECREATE");


  //For one extra NP
  bool isExL = false;
  bool isExM = false;
  if(histName.Contains("ExL")) isExL = true;
  if(histName.Contains("ExM")) isExM = true;


double sf_ttbar = 1.0; 
TH1F* ttbar = DC.readWriteHisto(fTT, "base/", histName, sf_ttbar, fout, fTT, "ttbar", true);
TH1F* ttbar_JESUp = DC.readWriteHisto(fTT, "base_JEC_up/", histName, sf_ttbar, fout, fTT, "ttbar_JESUp", true);
TH1F* ttbar_JESDown = DC.readWriteHisto(fTT, "base_JEC_do/", histName, sf_ttbar, fout, fTT, "ttbar_JESDown", true);
TH1F* ttbar_PileupUp = DC.readWriteHisto(fTT, "base_PUWeight_up/", histName, sf_ttbar, fout, fTT, "ttbar_PileupUp", true);
TH1F* ttbar_PileupDown = DC.readWriteHisto(fTT, "base_PUWeight_do/", histName, sf_ttbar, fout, fTT, "ttbar_PileupDown", true);
TH1F* ttbar_JERUp = DC.readWriteHisto(fTT, "reljerec1up/", histName, sf_ttbar, fout, fTT, "ttbar_JERUp", true);
TH1F* ttbar_JERDown = DC.readWriteHisto(fTT, "reljerec1down/", histName, sf_ttbar, fout, fTT, "ttbar_JERDown", true);
TH1F* ttbar_prefireUp = DC.readWriteHisto(fTT, "base_prefire_up/", histName, sf_ttbar, fout, fTT, "ttbar_prefireUp", true);
TH1F* ttbar_prefireDown = DC.readWriteHisto(fTT, "base_prefire_do/", histName, sf_ttbar, fout, fTT, "ttbar_prefireDown", true);
TH1F* ttbar_bc_statUp = DC.readWriteHisto(fTT, "base_bc_stat_up/", histName, sf_ttbar, fout, fTT, "ttbar_bc_statUp", true);
TH1F* ttbar_bc_statDown = DC.readWriteHisto(fTT, "base_bc_stat_do/", histName, sf_ttbar, fout, fTT, "ttbar_bc_statDown", true);
TH1F* ttbar_fsrUp = DC.readWriteHisto(fTT, "base_fsr_up/", histName, sf_ttbar, fout, fTT, "ttbar_fsrUp", true);
TH1F* ttbar_fsrDown = DC.readWriteHisto(fTT, "base_fsr_do/", histName, sf_ttbar, fout, fTT, "ttbar_fsrDown", true);
TH1F* ttbar_isrUp = DC.readWriteHisto(fTT, "base_isr_up/", histName, sf_ttbar, fout, fTT, "ttbar_isrUp", true);
TH1F* ttbar_isrDown = DC.readWriteHisto(fTT, "base_isr_do/", histName, sf_ttbar, fout, fTT, "ttbar_isrDown", true);
TH1F* ttbar_flavorqcdUp = DC.readWriteHisto(fTT, "flavorqcdup/", histName, sf_ttbar, fout, fTT, "ttbar_flavorqcdUp", true);
TH1F* ttbar_flavorqcdDown = DC.readWriteHisto(fTT, "flavorqcddown/", histName, sf_ttbar, fout, fTT, "ttbar_flavorqcdDown", true);
TH1F* ttbar_timeptetaUp = DC.readWriteHisto(fTT, "timeptetaup/", histName, sf_ttbar, fout, fTT, "ttbar_timeptetaUp", true);
TH1F* ttbar_timeptetaDown = DC.readWriteHisto(fTT, "timeptetadown/", histName, sf_ttbar, fout, fTT, "ttbar_timeptetaDown", true);
TH1F* ttbar_jerhfUp = DC.readWriteHisto(fTT, "reljerhfup/", histName, sf_ttbar, fout, fTT, "ttbar_jerhfUp", true);
TH1F* ttbar_jerhfDown = DC.readWriteHisto(fTT, "reljerhfdown/", histName, sf_ttbar, fout, fTT, "ttbar_jerhfDown", true);
TH1F* ttbar_relptbbUp = DC.readWriteHisto(fTT, "relptbbup/", histName, sf_ttbar, fout, fTT, "ttbar_relptbbUp", true);
TH1F* ttbar_relptbbDown = DC.readWriteHisto(fTT, "relptbbdown/", histName, sf_ttbar, fout, fTT, "ttbar_relptbbDown", true);
TH1F* ttbar_relpthfUp = DC.readWriteHisto(fTT, "relpthfup/", histName, sf_ttbar, fout, fTT, "ttbar_relpthfUp", true);
TH1F* ttbar_relpthfDown = DC.readWriteHisto(fTT, "relpthfdown/", histName, sf_ttbar, fout, fTT, "ttbar_relpthfDown", true);
TH1F* ttbar_relstatecUp = DC.readWriteHisto(fTT, "relstatecup/", histName, sf_ttbar, fout, fTT, "ttbar_relstatecUp", true);
TH1F* ttbar_relstatecDown = DC.readWriteHisto(fTT, "relstatecdown/", histName, sf_ttbar, fout, fTT, "ttbar_relstatecDown", true);
TH1F* ttbar_absstatUp = DC.readWriteHisto(fTT, "absstatup/", histName, sf_ttbar, fout, fTT, "ttbar_absstatUp", true);
TH1F* ttbar_absstatDown = DC.readWriteHisto(fTT, "absstatdown/", histName, sf_ttbar, fout, fTT, "ttbar_absstatDown", true);
TH1F* ttbar_abssclUp = DC.readWriteHisto(fTT, "abssclup/", histName, sf_ttbar, fout, fTT, "ttbar_abssclUp", true);
TH1F* ttbar_abssclDown = DC.readWriteHisto(fTT, "absscldown/", histName, sf_ttbar, fout, fTT, "ttbar_abssclDown", true);
TH1F* ttbar_absmpfbUp = DC.readWriteHisto(fTT, "absmpfbup/", histName, sf_ttbar, fout, fTT, "ttbar_absmpfbUp", true);
TH1F* ttbar_absmpfbDown = DC.readWriteHisto(fTT, "absmpfbdown/", histName, sf_ttbar, fout, fTT, "ttbar_absmpfbDown", true);
TH1F* ttbar_lhemuFUp = DC.readWriteHisto(fTT, "base_bc_lhemuf_up/", histName, sf_ttbar, fout, fTT, "ttbar_lhemuFUp", true);
TH1F* ttbar_lhemuFDown = DC.readWriteHisto(fTT, "base_bc_lhemuf_do/", histName, sf_ttbar, fout, fTT, "ttbar_lhemuFDown", true);
TH1F* ttbar_lhemuRUp = DC.readWriteHisto(fTT, "base_lhemur_up/", histName, sf_ttbar, fout, fTT, "ttbar_lhemuRUp", true);
TH1F* ttbar_lhemuRDown = DC.readWriteHisto(fTT, "base_lhemur_do/", histName, sf_ttbar, fout, fTT, "ttbar_lhemuRDown", true);
TH1F* ttbar_bHadronBFUp = DC.readWriteHisto(fTT, "base_bfrag_Up/", histName, sf_ttbar, fout, fTT, "ttbar_bHadronBFUp", true);
TH1F* ttbar_bHadronBFDown = DC.readWriteHisto(fTT, "base_bfrag_do/", histName, sf_ttbar, fout, fTT, "ttbar_bHadronBFDown", true);
TH1F* ttbar_pudataMCUp = DC.readWriteHisto(fTT, "pudatamcup/", histName, sf_ttbar, fout, fTT, "ttbar_pudataMCUp", true);
TH1F* ttbar_pudataMCDown = DC.readWriteHisto(fTT, "pudatamcdown/", histName, sf_ttbar, fout, fTT, "ttbar_pudataMCDown", true);
TH1F* ttbar_relptec2Up = DC.readWriteHisto(fTT, "relptec2up/", histName, sf_ttbar, fout, fTT, "ttbar_relptec2Up", true);
TH1F* ttbar_relptec2Down = DC.readWriteHisto(fTT, "relptec2down/", histName, sf_ttbar, fout, fTT, "ttbar_relptec2Down", true);
TH1F* ttbar_reljerec2Up = DC.readWriteHisto(fTT, "reljerec2up/", histName, sf_ttbar, fout, fTT, "ttbar_reljerec2Up", true);
TH1F* ttbar_reljerec2Down = DC.readWriteHisto(fTT, "reljerec2down/", histName, sf_ttbar, fout, fTT, "ttbar_reljerec2Down", true);
TH1F* ttbar_puptrefUp = DC.readWriteHisto(fTT, "puptrefup/", histName, sf_ttbar, fout, fTT, "ttbar_puptrefUp", true);
TH1F* ttbar_puptrefDown = DC.readWriteHisto(fTT, "puptrefdown/", histName, sf_ttbar, fout, fTT, "ttbar_puptrefDown", true);
TH1F* ttbar_puptec1Up = DC.readWriteHisto(fTT, "puptec1up/", histName, sf_ttbar, fout, fTT, "ttbar_puptec1Up", true);
TH1F* ttbar_puptec1Down = DC.readWriteHisto(fTT, "puptec1down/", histName, sf_ttbar, fout, fTT, "ttbar_puptec1Down", true);
TH1F* ttbar_puptec2Up = DC.readWriteHisto(fTT, "puptec2up/", histName, sf_ttbar, fout, fTT, "ttbar_puptec2Up", true);
TH1F* ttbar_puptec2Down = DC.readWriteHisto(fTT, "puptec2down/", histName, sf_ttbar, fout, fTT, "ttbar_puptec2Down", true);
TH1F* ttbar_base_extpUp = DC.readWriteHisto(fTT, "base_extp_up/", histName, sf_ttbar, fout, fTT, "ttbar_base_extpUp", true);
TH1F* ttbar_base_extpDown = DC.readWriteHisto(fTT, "base_extp_do/", histName, sf_ttbar, fout, fTT, "ttbar_base_extpDown", true);
TH1F* ttbar_base_intpUp = DC.readWriteHisto(fTT, "base_intp_up/", histName, sf_ttbar, fout, fTT, "ttbar_base_intpUp", true);
TH1F* ttbar_base_intpDown = DC.readWriteHisto(fTT, "base_intp_do/", histName, sf_ttbar, fout, fTT, "ttbar_base_intpDown", true);
TH1F* ttbar_base_xdycUp = DC.readWriteHisto(fTT, "base_xdyc_up/", histName, sf_ttbar, fout, fTT, "ttbar_base_xdycUp", true);
TH1F* ttbar_base_xdycDown = DC.readWriteHisto(fTT, "base_xdyc_do/", histName, sf_ttbar, fout, fTT, "ttbar_base_xdycDown", true);
TH1F* ttbar_base_xdybUp = DC.readWriteHisto(fTT, "base_xdyb_up/", histName, sf_ttbar, fout, fTT, "ttbar_base_xdybUp", true);
TH1F* ttbar_base_xdybDown = DC.readWriteHisto(fTT, "base_xdyb_do/", histName, sf_ttbar, fout, fTT, "ttbar_base_xdybDown", true);
TH1F* ttbar_base_muEffUp = DC.readWriteHisto(fTT, "base_muEff_up/", histName, sf_ttbar, fout, fTT, "ttbar_base_muEffUp", true);
TH1F* ttbar_base_muEffDown = DC.readWriteHisto(fTT, "base_muEff_do/", histName, sf_ttbar, fout, fTT, "ttbar_base_muEffDown", true);
TH1F* ttbar_base_pdfUp = DC.readWriteHisto(fTT, "base_pdf_Up/", histName, sf_ttbar, fout, fTT, "ttbar_base_pdfUp", true);
TH1F* ttbar_base_pdfDown = DC.readWriteHisto(fTT, "base_pdf_Do/", histName, sf_ttbar, fout, fTT, "ttbar_base_pdfDown", true);
TH1F* ttbar_singpiecalUp = DC.readWriteHisto(fTT, "/singpiecalup/", histName, sf_ttbar, fout, fTT, "ttbar_singpiecalUp", true);
TH1F* ttbar_singpiecalDown = DC.readWriteHisto(fTT, "/singpiecaldown/", histName, sf_ttbar, fout, fTT, "ttbar_singpiecalDown", true);
TH1F* ttbar_singpihcalUp = DC.readWriteHisto(fTT, "/singpihcalup/", histName, sf_ttbar, fout, fTT, "ttbar_singpihcalUp", true);
TH1F* ttbar_singpihcalDown = DC.readWriteHisto(fTT,"/singpihcaldown/", histName, sf_ttbar, fout, fTT, "ttbar_singpihcalDown", true);



  // Assuming ttbar and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
  //double baseIntegral = ttbar->Integral();

auto normalizeHistogram = [&](TH1F* hist, TH1F* baseHist) {
    if (hist && baseHist && hist->Integral() > 0 && baseHist->Integral() > 0) {
        double baseIntegral = baseHist->Integral();
        hist->Scale(baseIntegral / hist->Integral());
    }
};


normalizeHistogram(ttbar_bc_statUp, ttbar);
normalizeHistogram(ttbar_bc_statDown, ttbar);
normalizeHistogram(ttbar_fsrUp, ttbar);
normalizeHistogram(ttbar_fsrDown, ttbar);
normalizeHistogram(ttbar_isrUp, ttbar);
normalizeHistogram(ttbar_isrDown, ttbar);
normalizeHistogram(ttbar_base_pdfUp, ttbar);
normalizeHistogram(ttbar_base_pdfDown, ttbar);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  ttbar_bc_statUp->Write();
  ttbar_bc_statDown->Write();
  ttbar_fsrUp->Write();
  ttbar_fsrDown->Write();
  ttbar_isrUp->Write();
  ttbar_isrDown->Write();
  ttbar_base_pdfUp->Write();
  ttbar_base_pdfDown->Write();




 double unc_ttbar_ExL = 1.0;
  double unc_ttbar_ExM = 1.0;
  if(isExL){
    TH1F* ttbar_yLyMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* ttbar_yLyMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* ttbar_yLnMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* ttbar_yLnMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_ttbar_ExL = DC.getUncExL(ttbar_yLyMyT, ttbar_yLyMnT, ttbar_yLnMyT, ttbar_yLnMnT);
  }
  if(isExM){
    TH1F* ttbar_yMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* ttbar_yMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_ttbar_ExM = DC.getUncExM(ttbar_yMyT, ttbar_yMnT);
  }
  
  
//ttg
double sf_ttg = 1.0; 
TH1F* ttg = DC.readWriteHisto(fTG, "base/", histName, sf_ttg, fout, fTG, "ttg", true);
TH1F* ttg_JESUp = DC.readWriteHisto(fTG, "base_JEC_up/", histName, sf_ttg, fout, fTG, "ttg_JESUp", true);
TH1F* ttg_JESDown = DC.readWriteHisto(fTG, "base_JEC_do/", histName, sf_ttg, fout, fTG, "ttg_JESDown", true);
TH1F* ttg_PileupUp = DC.readWriteHisto(fTG, "base_PUWeight_up/", histName, sf_ttg, fout, fTG, "ttg_PileupUp", true);
TH1F* ttg_PileupDown = DC.readWriteHisto(fTG, "base_PUWeight_do/", histName, sf_ttg, fout, fTG, "ttg_PileupDown", true);
TH1F* ttg_JERUp = DC.readWriteHisto(fTG, "reljerec1up/", histName, sf_ttg, fout, fTG, "ttg_JERUp", true);
TH1F* ttg_JERDown = DC.readWriteHisto(fTG, "reljerec1down/", histName, sf_ttg, fout, fTG, "ttg_JERDown", true);
TH1F* ttg_prefireUp = DC.readWriteHisto(fTG, "base_prefire_up/", histName, sf_ttg, fout, fTG, "ttg_prefireUp", true);
TH1F* ttg_prefireDown = DC.readWriteHisto(fTG, "base_prefire_do/", histName, sf_ttg, fout, fTG, "ttg_prefireDown", true);
TH1F* ttg_bc_statUp = DC.readWriteHisto(fTG, "base_bc_stat_up/", histName, sf_ttg, fout, fTG, "ttg_bc_statUp", true);
TH1F* ttg_bc_statDown = DC.readWriteHisto(fTG, "base_bc_stat_do/", histName, sf_ttg, fout, fTG, "ttg_bc_statDown", true);
TH1F* ttg_fsrUp = DC.readWriteHisto(fTG, "base_fsr_up/", histName, sf_ttg, fout, fTG, "ttg_fsrUp", true);
TH1F* ttg_fsrDown = DC.readWriteHisto(fTG, "base_fsr_do/", histName, sf_ttg, fout, fTG, "ttg_fsrDown", true);
TH1F* ttg_isrUp = DC.readWriteHisto(fTG, "base_isr_up/", histName, sf_ttg, fout, fTG, "ttg_isrUp", true);
TH1F* ttg_isrDown = DC.readWriteHisto(fTG, "base_isr_do/", histName, sf_ttg, fout, fTG, "ttg_isrDown", true);
TH1F* ttg_flavorqcdUp = DC.readWriteHisto(fTG, "flavorqcdup/", histName, sf_ttg, fout, fTG, "ttg_flavorqcdUp", true);
TH1F* ttg_flavorqcdDown = DC.readWriteHisto(fTG, "flavorqcddown/", histName, sf_ttg, fout, fTG, "ttg_flavorqcdDown", true);
TH1F* ttg_timeptetaUp = DC.readWriteHisto(fTG, "timeptetaup/", histName, sf_ttg, fout, fTG, "ttg_timeptetaUp", true);
TH1F* ttg_timeptetaDown = DC.readWriteHisto(fTG, "timeptetadown/", histName, sf_ttg, fout, fTG, "ttg_timeptetaDown", true);
TH1F* ttg_jerhfUp = DC.readWriteHisto(fTG, "reljerhfup/", histName, sf_ttg, fout, fTG, "ttg_jerhfUp", true);
TH1F* ttg_jerhfDown = DC.readWriteHisto(fTG, "reljerhfdown/", histName, sf_ttg, fout, fTG, "ttg_jerhfDown", true);
TH1F* ttg_relptbbUp = DC.readWriteHisto(fTG, "relptbbup/", histName, sf_ttg, fout, fTG, "ttg_relptbbUp", true);
TH1F* ttg_relptbbDown = DC.readWriteHisto(fTG, "relptbbdown/", histName, sf_ttg, fout, fTG, "ttg_relptbbDown", true);
TH1F* ttg_relpthfUp = DC.readWriteHisto(fTG, "relpthfup/", histName, sf_ttg, fout, fTG, "ttg_relpthfUp", true);
TH1F* ttg_relpthfDown = DC.readWriteHisto(fTG, "relpthfdown/", histName, sf_ttg, fout, fTG, "ttg_relpthfDown", true);
TH1F* ttg_relstatecUp = DC.readWriteHisto(fTG, "relstatecup/", histName, sf_ttg, fout, fTG, "ttg_relstatecUp", true);
TH1F* ttg_relstatecDown = DC.readWriteHisto(fTG, "relstatecdown/", histName, sf_ttg, fout, fTG, "ttg_relstatecDown", true);
TH1F* ttg_absstatUp = DC.readWriteHisto(fTG, "absstatup/", histName, sf_ttg, fout, fTG, "ttg_absstatUp", true);
TH1F* ttg_absstatDown = DC.readWriteHisto(fTG, "absstatdown/", histName, sf_ttg, fout, fTG, "ttg_absstatDown", true);
TH1F* ttg_abssclUp = DC.readWriteHisto(fTG, "abssclup/", histName, sf_ttg, fout, fTG, "ttg_abssclUp", true);
TH1F* ttg_abssclDown = DC.readWriteHisto(fTG, "absscldown/", histName, sf_ttg, fout, fTG, "ttg_abssclDown", true);
TH1F* ttg_absmpfbUp = DC.readWriteHisto(fTG, "absmpfbup/", histName, sf_ttg, fout, fTG, "ttg_absmpfbUp", true);
TH1F* ttg_absmpfbDown = DC.readWriteHisto(fTG, "absmpfbdown/", histName, sf_ttg, fout, fTG, "ttg_absmpfbDown", true);
TH1F* ttg_lhemuFUp = DC.readWriteHisto(fTG, "base_bc_lhemuf_up/", histName, sf_ttg, fout, fTG, "ttg_lhemuFUp", true);
TH1F* ttg_lhemuFDown = DC.readWriteHisto(fTG, "base_bc_lhemuf_do/", histName, sf_ttg, fout, fTG, "ttg_lhemuFDown", true);
TH1F* ttg_lhemuRUp = DC.readWriteHisto(fTG, "base_lhemur_up/", histName, sf_ttg, fout, fTG, "ttg_lhemuRUp", true);
TH1F* ttg_lhemuRDown = DC.readWriteHisto(fTG, "base_lhemur_do/", histName, sf_ttg, fout, fTG, "ttg_lhemuRDown", true);
TH1F* ttg_bHadronBFUp = DC.readWriteHisto(fTG, "base_bfrag_Up/", histName, sf_ttg, fout, fTG, "ttg_bHadronBFUp", true);
TH1F* ttg_bHadronBFDown = DC.readWriteHisto(fTG, "base_bfrag_do/", histName, sf_ttg, fout, fTG, "ttg_bHadronBFDown", true);
TH1F* ttg_pudataMCUp = DC.readWriteHisto(fTG, "pudatamcup/", histName, sf_ttg, fout, fTG, "ttg_pudataMCUp", true);
TH1F* ttg_pudataMCDown = DC.readWriteHisto(fTG, "pudatamcdown/", histName, sf_ttg, fout, fTG, "ttg_pudataMCDown", true);
TH1F* ttg_relptec2Up = DC.readWriteHisto(fTG, "relptec2up/", histName, sf_ttg, fout, fTG, "ttg_relptec2Up", true);
TH1F* ttg_relptec2Down = DC.readWriteHisto(fTG, "relptec2down/", histName, sf_ttg, fout, fTG, "ttg_relptec2Down", true);
TH1F* ttg_reljerec2Up = DC.readWriteHisto(fTG, "reljerec2up/", histName, sf_ttg, fout, fTG, "ttg_reljerec2Up", true);
TH1F* ttg_reljerec2Down = DC.readWriteHisto(fTG, "reljerec2down/", histName, sf_ttg, fout, fTG, "ttg_reljerec2Down", true);
TH1F* ttg_puptrefUp = DC.readWriteHisto(fTG, "puptrefup/", histName, sf_ttg, fout, fTG, "ttg_puptrefUp", true);
TH1F* ttg_puptrefDown = DC.readWriteHisto(fTG, "puptrefdown/", histName, sf_ttg, fout, fTG, "ttg_puptrefDown", true);
TH1F* ttg_puptec1Up = DC.readWriteHisto(fTG, "puptec1up/", histName, sf_ttg, fout, fTG, "ttg_puptec1Up", true);
TH1F* ttg_puptec1Down = DC.readWriteHisto(fTG, "puptec1down/", histName, sf_ttg, fout, fTG, "ttg_puptec1Down", true);
TH1F* ttg_puptec2Up = DC.readWriteHisto(fTG, "puptec2up/", histName, sf_ttg, fout, fTG, "ttg_puptec2Up", true);
TH1F* ttg_puptec2Down = DC.readWriteHisto(fTG, "puptec2down/", histName, sf_ttg, fout, fTG, "ttg_puptec2Down", true);
TH1F* ttg_base_extpUp = DC.readWriteHisto(fTG, "base_extp_up/", histName, sf_ttg, fout, fTG, "ttg_base_extpUp", true);
TH1F* ttg_base_extpDown = DC.readWriteHisto(fTG, "base_extp_do/", histName, sf_ttg, fout, fTG, "ttg_base_extpDown", true);
TH1F* ttg_base_intpUp = DC.readWriteHisto(fTG, "base_intp_up/", histName, sf_ttg, fout, fTG, "ttg_base_intpUp", true);
TH1F* ttg_base_intpDown = DC.readWriteHisto(fTG, "base_intp_do/", histName, sf_ttg, fout, fTG, "ttg_base_intpDown", true);
TH1F* ttg_base_xdycUp = DC.readWriteHisto(fTG, "base_xdyc_up/", histName, sf_ttg, fout, fTG, "ttg_base_xdycUp", true);
TH1F* ttg_base_xdycDown = DC.readWriteHisto(fTG, "base_xdyc_do/", histName, sf_ttg, fout, fTG, "ttg_base_xdycDown", true);
TH1F* ttg_base_xdybUp = DC.readWriteHisto(fTG, "base_xdyb_up/", histName, sf_ttg, fout, fTG, "ttg_base_xdybUp", true);
TH1F* ttg_base_xdybDown = DC.readWriteHisto(fTG, "base_xdyb_do/", histName, sf_ttg, fout, fTG, "ttg_base_xdybDown", true);
TH1F* ttg_base_muEffUp = DC.readWriteHisto(fTG, "base_muEff_up/", histName, sf_ttg, fout, fTG, "ttg_base_muEffUp", true);
TH1F* ttg_base_muEffDown = DC.readWriteHisto(fTG, "base_muEff_do/", histName, sf_ttg, fout, fTG, "ttg_base_muEffDown", true);
TH1F* ttg_base_pdfUp = DC.readWriteHisto(fTG, "base_pdf_Up/", histName, sf_ttg, fout, fTG, "ttg_base_pdfUp", true);
TH1F* ttg_base_pdfDown = DC.readWriteHisto(fTG, "base_pdf_Do/", histName, sf_ttg, fout, fTG, "ttg_base_pdfDown", true);
TH1F* ttg_singpiecalUp = DC.readWriteHisto(fTG, "/singpiecalup/", histName, sf_ttg, fout, fTG, "ttg_singpiecalUp", true);
TH1F* ttg_singpiecalDown = DC.readWriteHisto(fTG, "/singpiecaldown/", histName, sf_ttg, fout, fTG, "ttg_singpiecalDown", true);
TH1F* ttg_singpihcalUp = DC.readWriteHisto(fTG, "/singpihcalup/", histName, sf_ttg, fout, fTG, "ttg_singpihcalUp", true);
TH1F* ttg_singpihcalDown = DC.readWriteHisto(fTG,"/singpihcaldown/", histName, sf_ttg, fout, fTG, "ttg_singpihcalDown", true);

  // Assuming ttg and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
  //double baseIntegral = ttg->Integral();

normalizeHistogram(ttg_bc_statUp, ttg);
normalizeHistogram(ttg_bc_statDown, ttg);
normalizeHistogram(ttg_fsrUp, ttg);
normalizeHistogram(ttg_fsrDown, ttg);
normalizeHistogram(ttg_isrUp, ttg);
normalizeHistogram(ttg_isrDown, ttg);
normalizeHistogram(ttg_base_pdfUp, ttg);
normalizeHistogram(ttg_base_pdfDown, ttg);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  ttg_bc_statUp->Write();
  ttg_bc_statDown->Write();
  ttg_fsrUp->Write();
  ttg_fsrDown->Write();
  ttg_isrUp->Write();
  ttg_isrDown->Write();
  ttg_base_pdfUp->Write();
  ttg_base_pdfDown->Write();




 double unc_ttg_ExL = 1.0;
  double unc_ttg_ExM = 1.0;
  if(isExL){
    TH1F* ttg_yLyMyT = DC.getHisto(fTG, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTG);
    TH1F* ttg_yLyMnT = DC.getHisto(fTG, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTG);
    TH1F* ttg_yLnMyT = DC.getHisto(fTG, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTG);
    TH1F* ttg_yLnMnT = DC.getHisto(fTG, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTG);
    unc_ttg_ExL = DC.getUncExL(ttg_yLyMyT, ttg_yLyMnT, ttg_yLnMyT, ttg_yLnMnT);
  }
  if(isExM){
    TH1F* ttg_yMyT = DC.getHisto(fTG, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTG);
    TH1F* ttg_yMnT = DC.getHisto(fTG, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTG);
    unc_ttg_ExM = DC.getUncExM(ttg_yMyT, ttg_yMnT);
  }
  
 //tth
double sf_tth = 1.0; 
TH1F* tth = DC.readWriteHisto(fTZ, "base/", histName, sf_tth, fout, fTZ, "tth", true);
TH1F* tth_JESUp = DC.readWriteHisto(fTZ, "base_JEC_up/", histName, sf_tth, fout, fTZ, "tth_JESUp", true);
TH1F* tth_JESDown = DC.readWriteHisto(fTZ, "base_JEC_do/", histName, sf_tth, fout, fTZ, "tth_JESDown", true);
TH1F* tth_PileupUp = DC.readWriteHisto(fTZ, "base_PUWeight_up/", histName, sf_tth, fout, fTZ, "tth_PileupUp", true);
TH1F* tth_PileupDown = DC.readWriteHisto(fTZ, "base_PUWeight_do/", histName, sf_tth, fout, fTZ, "tth_PileupDown", true);
TH1F* tth_JERUp = DC.readWriteHisto(fTZ, "reljerec1up/", histName, sf_tth, fout, fTZ, "tth_JERUp", true);
TH1F* tth_JERDown = DC.readWriteHisto(fTZ, "reljerec1down/", histName, sf_tth, fout, fTZ, "tth_JERDown", true);
TH1F* tth_prefireUp = DC.readWriteHisto(fTZ, "base_prefire_up/", histName, sf_tth, fout, fTZ, "tth_prefireUp", true);
TH1F* tth_prefireDown = DC.readWriteHisto(fTZ, "base_prefire_do/", histName, sf_tth, fout, fTZ, "tth_prefireDown", true);
TH1F* tth_bc_statUp = DC.readWriteHisto(fTZ, "base_bc_stat_up/", histName, sf_tth, fout, fTZ, "tth_bc_statUp", true);
TH1F* tth_bc_statDown = DC.readWriteHisto(fTZ, "base_bc_stat_do/", histName, sf_tth, fout, fTZ, "tth_bc_statDown", true);
TH1F* tth_fsrUp = DC.readWriteHisto(fTZ, "base_fsr_up/", histName, sf_tth, fout, fTZ, "tth_fsrUp", true);
TH1F* tth_fsrDown = DC.readWriteHisto(fTZ, "base_fsr_do/", histName, sf_tth, fout, fTZ, "tth_fsrDown", true);
TH1F* tth_isrUp = DC.readWriteHisto(fTZ, "base_isr_up/", histName, sf_tth, fout, fTZ, "tth_isrUp", true);
TH1F* tth_isrDown = DC.readWriteHisto(fTZ, "base_isr_do/", histName, sf_tth, fout, fTZ, "tth_isrDown", true);
TH1F* tth_flavorqcdUp = DC.readWriteHisto(fTZ, "flavorqcdup/", histName, sf_tth, fout, fTZ, "tth_flavorqcdUp", true);
TH1F* tth_flavorqcdDown = DC.readWriteHisto(fTZ, "flavorqcddown/", histName, sf_tth, fout, fTZ, "tth_flavorqcdDown", true);
TH1F* tth_timeptetaUp = DC.readWriteHisto(fTZ, "timeptetaup/", histName, sf_tth, fout, fTZ, "tth_timeptetaUp", true);
TH1F* tth_timeptetaDown = DC.readWriteHisto(fTZ, "timeptetadown/", histName, sf_tth, fout, fTZ, "tth_timeptetaDown", true);
TH1F* tth_jerhfUp = DC.readWriteHisto(fTZ, "reljerhfup/", histName, sf_tth, fout, fTZ, "tth_jerhfUp", true);
TH1F* tth_jerhfDown = DC.readWriteHisto(fTZ, "reljerhfdown/", histName, sf_tth, fout, fTZ, "tth_jerhfDown", true);
TH1F* tth_relptbbUp = DC.readWriteHisto(fTZ, "relptbbup/", histName, sf_tth, fout, fTZ, "tth_relptbbUp", true);
TH1F* tth_relptbbDown = DC.readWriteHisto(fTZ, "relptbbdown/", histName, sf_tth, fout, fTZ, "tth_relptbbDown", true);
TH1F* tth_relpthfUp = DC.readWriteHisto(fTZ, "relpthfup/", histName, sf_tth, fout, fTZ, "tth_relpthfUp", true);
TH1F* tth_relpthfDown = DC.readWriteHisto(fTZ, "relpthfdown/", histName, sf_tth, fout, fTZ, "tth_relpthfDown", true);
TH1F* tth_relstatecUp = DC.readWriteHisto(fTZ, "relstatecup/", histName, sf_tth, fout, fTZ, "tth_relstatecUp", true);
TH1F* tth_relstatecDown = DC.readWriteHisto(fTZ, "relstatecdown/", histName, sf_tth, fout, fTZ, "tth_relstatecDown", true);
TH1F* tth_absstatUp = DC.readWriteHisto(fTZ, "absstatup/", histName, sf_tth, fout, fTZ, "tth_absstatUp", true);
TH1F* tth_absstatDown = DC.readWriteHisto(fTZ, "absstatdown/", histName, sf_tth, fout, fTZ, "tth_absstatDown", true);
TH1F* tth_abssclUp = DC.readWriteHisto(fTZ, "abssclup/", histName, sf_tth, fout, fTZ, "tth_abssclUp", true);
TH1F* tth_abssclDown = DC.readWriteHisto(fTZ, "absscldown/", histName, sf_tth, fout, fTZ, "tth_abssclDown", true);
TH1F* tth_absmpfbUp = DC.readWriteHisto(fTZ, "absmpfbup/", histName, sf_tth, fout, fTZ, "tth_absmpfbUp", true);
TH1F* tth_absmpfbDown = DC.readWriteHisto(fTZ, "absmpfbdown/", histName, sf_tth, fout, fTZ, "tth_absmpfbDown", true);
TH1F* tth_lhemuFUp = DC.readWriteHisto(fTZ, "base_bc_lhemuf_up/", histName, sf_tth, fout, fTZ, "tth_lhemuFUp", true);
TH1F* tth_lhemuFDown = DC.readWriteHisto(fTZ, "base_bc_lhemuf_do/", histName, sf_tth, fout, fTZ, "tth_lhemuFDown", true);
TH1F* tth_lhemuRUp = DC.readWriteHisto(fTZ, "base_lhemur_up/", histName, sf_tth, fout, fTZ, "tth_lhemuRUp", true);
TH1F* tth_lhemuRDown = DC.readWriteHisto(fTZ, "base_lhemur_do/", histName, sf_tth, fout, fTZ, "tth_lhemuRDown", true);
TH1F* tth_bHadronBFUp = DC.readWriteHisto(fTZ, "base_bfrag_Up/", histName, sf_tth, fout, fTZ, "tth_bHadronBFUp", true);
TH1F* tth_bHadronBFDown = DC.readWriteHisto(fTZ, "base_bfrag_do/", histName, sf_tth, fout, fTZ, "tth_bHadronBFDown", true);
TH1F* tth_pudataMCUp = DC.readWriteHisto(fTZ, "pudatamcup/", histName, sf_tth, fout, fTZ, "tth_pudataMCUp", true);
TH1F* tth_pudataMCDown = DC.readWriteHisto(fTZ, "pudatamcdown/", histName, sf_tth, fout, fTZ, "tth_pudataMCDown", true);
TH1F* tth_relptec2Up = DC.readWriteHisto(fTZ, "relptec2up/", histName, sf_tth, fout, fTZ, "tth_relptec2Up", true);
TH1F* tth_relptec2Down = DC.readWriteHisto(fTZ, "relptec2down/", histName, sf_tth, fout, fTZ, "tth_relptec2Down", true);
TH1F* tth_reljerec2Up = DC.readWriteHisto(fTZ, "reljerec2up/", histName, sf_tth, fout, fTZ, "tth_reljerec2Up", true);
TH1F* tth_reljerec2Down = DC.readWriteHisto(fTZ, "reljerec2down/", histName, sf_tth, fout, fTZ, "tth_reljerec2Down", true);
TH1F* tth_puptrefUp = DC.readWriteHisto(fTZ, "puptrefup/", histName, sf_tth, fout, fTZ, "tth_puptrefUp", true);
TH1F* tth_puptrefDown = DC.readWriteHisto(fTZ, "puptrefdown/", histName, sf_tth, fout, fTZ, "tth_puptrefDown", true);
TH1F* tth_puptec1Up = DC.readWriteHisto(fTZ, "puptec1up/", histName, sf_tth, fout, fTZ, "tth_puptec1Up", true);
TH1F* tth_puptec1Down = DC.readWriteHisto(fTZ, "puptec1down/", histName, sf_tth, fout, fTZ, "tth_puptec1Down", true);
TH1F* tth_puptec2Up = DC.readWriteHisto(fTZ, "puptec2up/", histName, sf_tth, fout, fTZ, "tth_puptec2Up", true);
TH1F* tth_puptec2Down = DC.readWriteHisto(fTZ, "puptec2down/", histName, sf_tth, fout, fTZ, "tth_puptec2Down", true);
TH1F* tth_base_extpUp = DC.readWriteHisto(fTZ, "base_extp_up/", histName, sf_tth, fout, fTZ, "tth_base_extpUp", true);
TH1F* tth_base_extpDown = DC.readWriteHisto(fTZ, "base_extp_do/", histName, sf_tth, fout, fTZ, "tth_base_extpDown", true);
TH1F* tth_base_intpUp = DC.readWriteHisto(fTZ, "base_intp_up/", histName, sf_tth, fout, fTZ, "tth_base_intpUp", true);
TH1F* tth_base_intpDown = DC.readWriteHisto(fTZ, "base_intp_do/", histName, sf_tth, fout, fTZ, "tth_base_intpDown", true);
TH1F* tth_base_xdycUp = DC.readWriteHisto(fTZ, "base_xdyc_up/", histName, sf_tth, fout, fTZ, "tth_base_xdycUp", true);
TH1F* tth_base_xdycDown = DC.readWriteHisto(fTZ, "base_xdyc_do/", histName, sf_tth, fout, fTZ, "tth_base_xdycDown", true);
TH1F* tth_base_xdybUp = DC.readWriteHisto(fTZ, "base_xdyb_up/", histName, sf_tth, fout, fTZ, "tth_base_xdybUp", true);
TH1F* tth_base_xdybDown = DC.readWriteHisto(fTZ, "base_xdyb_do/", histName, sf_tth, fout, fTZ, "tth_base_xdybDown", true);
TH1F* tth_base_muEffUp = DC.readWriteHisto(fTZ, "base_muEff_up/", histName, sf_tth, fout, fTZ, "tth_base_muEffUp", true);
TH1F* tth_base_muEffDown = DC.readWriteHisto(fTZ, "base_muEff_do/", histName, sf_tth, fout, fTZ, "tth_base_muEffDown", true);
TH1F* tth_base_pdfUp = DC.readWriteHisto(fTZ, "base_pdf_Up/", histName, sf_tth, fout, fTZ, "tth_base_pdfUp", true);
TH1F* tth_base_pdfDown = DC.readWriteHisto(fTZ, "base_pdf_Do/", histName, sf_tth, fout, fTZ, "tth_base_pdfDown", true);
TH1F* tth_singpiecalUp = DC.readWriteHisto(fTZ, "/singpiecalup/", histName, sf_tth, fout, fTZ, "tth_singpiecalUp", true);
TH1F* tth_singpiecalDown = DC.readWriteHisto(fTZ, "/singpiecaldown/", histName, sf_tth, fout, fTZ, "tth_singpiecalDown", true);
TH1F* tth_singpihcalUp = DC.readWriteHisto(fTZ, "/singpihcalup/", histName, sf_tth, fout, fTZ, "tth_singpihcalUp", true);
TH1F* tth_singpihcalDown = DC.readWriteHisto(fTZ,"/singpihcaldown/", histName, sf_tth, fout, fTZ, "tth_singpihcalDown", true);

  // Assuming tth and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
  //double baseIntegral = tth->Integral();

normalizeHistogram(tth_bc_statUp, tth);
normalizeHistogram(tth_bc_statDown, tth);
normalizeHistogram(tth_fsrUp, tth);
normalizeHistogram(tth_fsrDown, tth);
normalizeHistogram(tth_isrUp, tth);
normalizeHistogram(tth_isrDown, tth);
normalizeHistogram(tth_base_pdfUp, tth);
normalizeHistogram(tth_base_pdfDown, tth);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  tth_bc_statUp->Write();
  tth_bc_statDown->Write();
  tth_fsrUp->Write();
  tth_fsrDown->Write();
  tth_isrUp->Write();
  tth_isrDown->Write();
  tth_base_pdfUp->Write();
  tth_base_pdfDown->Write();




 double unc_tth_ExL = 1.0;
  double unc_tth_ExM = 1.0;
  if(isExL){
    TH1F* tth_yLyMyT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTZ);
    TH1F* tth_yLyMnT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTZ);
    TH1F* tth_yLnMyT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTZ);
    TH1F* tth_yLnMnT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTZ);
    unc_tth_ExL = DC.getUncExL(tth_yLyMyT, tth_yLyMnT, tth_yLnMyT, tth_yLnMnT);
  }
  if(isExM){
    TH1F* tth_yMyT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTZ);
    TH1F* tth_yMnT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTZ);
    unc_tth_ExM = DC.getUncExM(tth_yMyT, tth_yMnT);
  }
 //ttz
double sf_ttz = 1.0; 
TH1F* ttz = DC.readWriteHisto(fTZ, "base/", histName, sf_ttz, fout, fTZ, "ttz", true);
TH1F* ttz_JESUp = DC.readWriteHisto(fTZ, "base_JEC_up/", histName, sf_ttz, fout, fTZ, "ttz_JESUp", true);
TH1F* ttz_JESDown = DC.readWriteHisto(fTZ, "base_JEC_do/", histName, sf_ttz, fout, fTZ, "ttz_JESDown", true);
TH1F* ttz_PileupUp = DC.readWriteHisto(fTZ, "base_PUWeight_up/", histName, sf_ttz, fout, fTZ, "ttz_PileupUp", true);
TH1F* ttz_PileupDown = DC.readWriteHisto(fTZ, "base_PUWeight_do/", histName, sf_ttz, fout, fTZ, "ttz_PileupDown", true);
TH1F* ttz_JERUp = DC.readWriteHisto(fTZ, "reljerec1up/", histName, sf_ttz, fout, fTZ, "ttz_JERUp", true);
TH1F* ttz_JERDown = DC.readWriteHisto(fTZ, "reljerec1down/", histName, sf_ttz, fout, fTZ, "ttz_JERDown", true);
TH1F* ttz_prefireUp = DC.readWriteHisto(fTZ, "base_prefire_up/", histName, sf_ttz, fout, fTZ, "ttz_prefireUp", true);
TH1F* ttz_prefireDown = DC.readWriteHisto(fTZ, "base_prefire_do/", histName, sf_ttz, fout, fTZ, "ttz_prefireDown", true);
TH1F* ttz_bc_statUp = DC.readWriteHisto(fTZ, "base_bc_stat_up/", histName, sf_ttz, fout, fTZ, "ttz_bc_statUp", true);
TH1F* ttz_bc_statDown = DC.readWriteHisto(fTZ, "base_bc_stat_do/", histName, sf_ttz, fout, fTZ, "ttz_bc_statDown", true);
TH1F* ttz_fsrUp = DC.readWriteHisto(fTZ, "base_fsr_up/", histName, sf_ttz, fout, fTZ, "ttz_fsrUp", true);
TH1F* ttz_fsrDown = DC.readWriteHisto(fTZ, "base_fsr_do/", histName, sf_ttz, fout, fTZ, "ttz_fsrDown", true);
TH1F* ttz_isrUp = DC.readWriteHisto(fTZ, "base_isr_up/", histName, sf_ttz, fout, fTZ, "ttz_isrUp", true);
TH1F* ttz_isrDown = DC.readWriteHisto(fTZ, "base_isr_do/", histName, sf_ttz, fout, fTZ, "ttz_isrDown", true);
TH1F* ttz_flavorqcdUp = DC.readWriteHisto(fTZ, "flavorqcdup/", histName, sf_ttz, fout, fTZ, "ttz_flavorqcdUp", true);
TH1F* ttz_flavorqcdDown = DC.readWriteHisto(fTZ, "flavorqcddown/", histName, sf_ttz, fout, fTZ, "ttz_flavorqcdDown", true);
TH1F* ttz_timeptetaUp = DC.readWriteHisto(fTZ, "timeptetaup/", histName, sf_ttz, fout, fTZ, "ttz_timeptetaUp", true);
TH1F* ttz_timeptetaDown = DC.readWriteHisto(fTZ, "timeptetadown/", histName, sf_ttz, fout, fTZ, "ttz_timeptetaDown", true);
TH1F* ttz_jerhfUp = DC.readWriteHisto(fTZ, "reljerhfup/", histName, sf_ttz, fout, fTZ, "ttz_jerhfUp", true);
TH1F* ttz_jerhfDown = DC.readWriteHisto(fTZ, "reljerhfdown/", histName, sf_ttz, fout, fTZ, "ttz_jerhfDown", true);
TH1F* ttz_relptbbUp = DC.readWriteHisto(fTZ, "relptbbup/", histName, sf_ttz, fout, fTZ, "ttz_relptbbUp", true);
TH1F* ttz_relptbbDown = DC.readWriteHisto(fTZ, "relptbbdown/", histName, sf_ttz, fout, fTZ, "ttz_relptbbDown", true);
TH1F* ttz_relpthfUp = DC.readWriteHisto(fTZ, "relpthfup/", histName, sf_ttz, fout, fTZ, "ttz_relpthfUp", true);
TH1F* ttz_relpthfDown = DC.readWriteHisto(fTZ, "relpthfdown/", histName, sf_ttz, fout, fTZ, "ttz_relpthfDown", true);
TH1F* ttz_relstatecUp = DC.readWriteHisto(fTZ, "relstatecup/", histName, sf_ttz, fout, fTZ, "ttz_relstatecUp", true);
TH1F* ttz_relstatecDown = DC.readWriteHisto(fTZ, "relstatecdown/", histName, sf_ttz, fout, fTZ, "ttz_relstatecDown", true);
TH1F* ttz_absstatUp = DC.readWriteHisto(fTZ, "absstatup/", histName, sf_ttz, fout, fTZ, "ttz_absstatUp", true);
TH1F* ttz_absstatDown = DC.readWriteHisto(fTZ, "absstatdown/", histName, sf_ttz, fout, fTZ, "ttz_absstatDown", true);
TH1F* ttz_abssclUp = DC.readWriteHisto(fTZ, "abssclup/", histName, sf_ttz, fout, fTZ, "ttz_abssclUp", true);
TH1F* ttz_abssclDown = DC.readWriteHisto(fTZ, "absscldown/", histName, sf_ttz, fout, fTZ, "ttz_abssclDown", true);
TH1F* ttz_absmpfbUp = DC.readWriteHisto(fTZ, "absmpfbup/", histName, sf_ttz, fout, fTZ, "ttz_absmpfbUp", true);
TH1F* ttz_absmpfbDown = DC.readWriteHisto(fTZ, "absmpfbdown/", histName, sf_ttz, fout, fTZ, "ttz_absmpfbDown", true);
TH1F* ttz_lhemuFUp = DC.readWriteHisto(fTZ, "base_bc_lhemuf_up/", histName, sf_ttz, fout, fTZ, "ttz_lhemuFUp", true);
TH1F* ttz_lhemuFDown = DC.readWriteHisto(fTZ, "base_bc_lhemuf_do/", histName, sf_ttz, fout, fTZ, "ttz_lhemuFDown", true);
TH1F* ttz_lhemuRUp = DC.readWriteHisto(fTZ, "base_lhemur_up/", histName, sf_ttz, fout, fTZ, "ttz_lhemuRUp", true);
TH1F* ttz_lhemuRDown = DC.readWriteHisto(fTZ, "base_lhemur_do/", histName, sf_ttz, fout, fTZ, "ttz_lhemuRDown", true);
TH1F* ttz_bHadronBFUp = DC.readWriteHisto(fTZ, "base_bfrag_Up/", histName, sf_ttz, fout, fTZ, "ttz_bHadronBFUp", true);
TH1F* ttz_bHadronBFDown = DC.readWriteHisto(fTZ, "base_bfrag_do/", histName, sf_ttz, fout, fTZ, "ttz_bHadronBFDown", true);
TH1F* ttz_pudataMCUp = DC.readWriteHisto(fTZ, "pudatamcup/", histName, sf_ttz, fout, fTZ, "ttz_pudataMCUp", true);
TH1F* ttz_pudataMCDown = DC.readWriteHisto(fTZ, "pudatamcdown/", histName, sf_ttz, fout, fTZ, "ttz_pudataMCDown", true);
TH1F* ttz_relptec2Up = DC.readWriteHisto(fTZ, "relptec2up/", histName, sf_ttz, fout, fTZ, "ttz_relptec2Up", true);
TH1F* ttz_relptec2Down = DC.readWriteHisto(fTZ, "relptec2down/", histName, sf_ttz, fout, fTZ, "ttz_relptec2Down", true);
TH1F* ttz_reljerec2Up = DC.readWriteHisto(fTZ, "reljerec2up/", histName, sf_ttz, fout, fTZ, "ttz_reljerec2Up", true);
TH1F* ttz_reljerec2Down = DC.readWriteHisto(fTZ, "reljerec2down/", histName, sf_ttz, fout, fTZ, "ttz_reljerec2Down", true);
TH1F* ttz_puptrefUp = DC.readWriteHisto(fTZ, "puptrefup/", histName, sf_ttz, fout, fTZ, "ttz_puptrefUp", true);
TH1F* ttz_puptrefDown = DC.readWriteHisto(fTZ, "puptrefdown/", histName, sf_ttz, fout, fTZ, "ttz_puptrefDown", true);
TH1F* ttz_puptec1Up = DC.readWriteHisto(fTZ, "puptec1up/", histName, sf_ttz, fout, fTZ, "ttz_puptec1Up", true);
TH1F* ttz_puptec1Down = DC.readWriteHisto(fTZ, "puptec1down/", histName, sf_ttz, fout, fTZ, "ttz_puptec1Down", true);
TH1F* ttz_puptec2Up = DC.readWriteHisto(fTZ, "puptec2up/", histName, sf_ttz, fout, fTZ, "ttz_puptec2Up", true);
TH1F* ttz_puptec2Down = DC.readWriteHisto(fTZ, "puptec2down/", histName, sf_ttz, fout, fTZ, "ttz_puptec2Down", true);
TH1F* ttz_base_extpUp = DC.readWriteHisto(fTZ, "base_extp_up/", histName, sf_ttz, fout, fTZ, "ttz_base_extpUp", true);
TH1F* ttz_base_extpDown = DC.readWriteHisto(fTZ, "base_extp_do/", histName, sf_ttz, fout, fTZ, "ttz_base_extpDown", true);
TH1F* ttz_base_intpUp = DC.readWriteHisto(fTZ, "base_intp_up/", histName, sf_ttz, fout, fTZ, "ttz_base_intpUp", true);
TH1F* ttz_base_intpDown = DC.readWriteHisto(fTZ, "base_intp_do/", histName, sf_ttz, fout, fTZ, "ttz_base_intpDown", true);
TH1F* ttz_base_xdycUp = DC.readWriteHisto(fTZ, "base_xdyc_up/", histName, sf_ttz, fout, fTZ, "ttz_base_xdycUp", true);
TH1F* ttz_base_xdycDown = DC.readWriteHisto(fTZ, "base_xdyc_do/", histName, sf_ttz, fout, fTZ, "ttz_base_xdycDown", true);
TH1F* ttz_base_xdybUp = DC.readWriteHisto(fTZ, "base_xdyb_up/", histName, sf_ttz, fout, fTZ, "ttz_base_xdybUp", true);
TH1F* ttz_base_xdybDown = DC.readWriteHisto(fTZ, "base_xdyb_do/", histName, sf_ttz, fout, fTZ, "ttz_base_xdybDown", true);
TH1F* ttz_base_muEffUp = DC.readWriteHisto(fTZ, "base_muEff_up/", histName, sf_ttz, fout, fTZ, "ttz_base_muEffUp", true);
TH1F* ttz_base_muEffDown = DC.readWriteHisto(fTZ, "base_muEff_do/", histName, sf_ttz, fout, fTZ, "ttz_base_muEffDown", true);
TH1F* ttz_base_pdfUp = DC.readWriteHisto(fTZ, "base_pdf_Up/", histName, sf_ttz, fout, fTZ, "ttz_base_pdfUp", true);
TH1F* ttz_base_pdfDown = DC.readWriteHisto(fTZ, "base_pdf_Do/", histName, sf_ttz, fout, fTZ, "ttz_base_pdfDown", true);
TH1F* ttz_singpiecalUp = DC.readWriteHisto(fTZ, "/singpiecalup/", histName, sf_ttz, fout, fTZ, "ttz_singpiecalUp", true);
TH1F* ttz_singpiecalDown = DC.readWriteHisto(fTZ, "/singpiecaldown/", histName, sf_ttz, fout, fTZ, "ttz_singpiecalDown", true);
TH1F* ttz_singpihcalUp = DC.readWriteHisto(fTZ, "/singpihcalup/", histName, sf_ttz, fout, fTZ, "ttz_singpihcalUp", true);
TH1F* ttz_singpihcalDown = DC.readWriteHisto(fTZ,"/singpihcaldown/", histName, sf_ttz, fout, fTZ, "ttz_singpihcalDown", true);

  // Assuming ttz and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
  //double baseIntegral = ttz->Integral();


normalizeHistogram(ttz_bc_statUp, ttz);
normalizeHistogram(ttz_bc_statDown, ttz);
normalizeHistogram(ttz_fsrUp, ttz);
normalizeHistogram(ttz_fsrDown, ttz);
normalizeHistogram(ttz_isrUp, ttz);
normalizeHistogram(ttz_isrDown, ttz);
normalizeHistogram(ttz_base_pdfUp, ttz);
normalizeHistogram(ttz_base_pdfDown, ttz);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  ttz_bc_statUp->Write();
  ttz_bc_statDown->Write();
  ttz_fsrUp->Write();
  ttz_fsrDown->Write();
  ttz_isrUp->Write();
  ttz_isrDown->Write();
  ttz_base_pdfUp->Write();
  ttz_base_pdfDown->Write();




 double unc_ttz_ExL = 1.0;
  double unc_ttz_ExM = 1.0;
  if(isExL){
    TH1F* ttz_yLyMyT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTZ);
    TH1F* ttz_yLyMnT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTZ);
    TH1F* ttz_yLnMyT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTZ);
    TH1F* ttz_yLnMnT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTZ);
    unc_ttz_ExL = DC.getUncExL(ttz_yLyMyT, ttz_yLyMnT, ttz_yLnMyT, ttz_yLnMnT);
  }
  if(isExM){
    TH1F* ttz_yMyT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTZ);
    TH1F* ttz_yMnT = DC.getHisto(fTZ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTZ);
    unc_ttz_ExM = DC.getUncExM(ttz_yMyT, ttz_yMnT);
  }
//ttw
double sf_ttw = 1.0; 
TH1F* ttw = DC.readWriteHisto(fTW, "base/", histName, sf_ttw, fout, fTW, "ttw", true);
TH1F* ttw_JESUp = DC.readWriteHisto(fTW, "base_JEC_up/", histName, sf_ttw, fout, fTW, "ttw_JESUp", true);
TH1F* ttw_JESDown = DC.readWriteHisto(fTW, "base_JEC_do/", histName, sf_ttw, fout, fTW, "ttw_JESDown", true);
TH1F* ttw_PileupUp = DC.readWriteHisto(fTW, "base_PUWeight_up/", histName, sf_ttw, fout, fTW, "ttw_PileupUp", true);
TH1F* ttw_PileupDown = DC.readWriteHisto(fTW, "base_PUWeight_do/", histName, sf_ttw, fout, fTW, "ttw_PileupDown", true);
TH1F* ttw_JERUp = DC.readWriteHisto(fTW, "reljerec1up/", histName, sf_ttw, fout, fTW, "ttw_JERUp", true);
TH1F* ttw_JERDown = DC.readWriteHisto(fTW, "reljerec1down/", histName, sf_ttw, fout, fTW, "ttw_JERDown", true);
TH1F* ttw_prefireUp = DC.readWriteHisto(fTW, "base_prefire_up/", histName, sf_ttw, fout, fTW, "ttw_prefireUp", true);
TH1F* ttw_prefireDown = DC.readWriteHisto(fTW, "base_prefire_do/", histName, sf_ttw, fout, fTW, "ttw_prefireDown", true);
TH1F* ttw_bc_statUp = DC.readWriteHisto(fTW, "base_bc_stat_up/", histName, sf_ttw, fout, fTW, "ttw_bc_statUp", true);
TH1F* ttw_bc_statDown = DC.readWriteHisto(fTW, "base_bc_stat_do/", histName, sf_ttw, fout, fTW, "ttw_bc_statDown", true);
TH1F* ttw_fsrUp = DC.readWriteHisto(fTW, "base_fsr_up/", histName, sf_ttw, fout, fTW, "ttw_fsrUp", true);
TH1F* ttw_fsrDown = DC.readWriteHisto(fTW, "base_fsr_do/", histName, sf_ttw, fout, fTW, "ttw_fsrDown", true);
TH1F* ttw_isrUp = DC.readWriteHisto(fTW, "base_isr_up/", histName, sf_ttw, fout, fTW, "ttw_isrUp", true);
TH1F* ttw_isrDown = DC.readWriteHisto(fTW, "base_isr_do/", histName, sf_ttw, fout, fTW, "ttw_isrDown", true);
TH1F* ttw_flavorqcdUp = DC.readWriteHisto(fTW, "flavorqcdup/", histName, sf_ttw, fout, fTW, "ttw_flavorqcdUp", true);
TH1F* ttw_flavorqcdDown = DC.readWriteHisto(fTW, "flavorqcddown/", histName, sf_ttw, fout, fTW, "ttw_flavorqcdDown", true);
TH1F* ttw_timeptetaUp = DC.readWriteHisto(fTW, "timeptetaup/", histName, sf_ttw, fout, fTW, "ttw_timeptetaUp", true);
TH1F* ttw_timeptetaDown = DC.readWriteHisto(fTW, "timeptetadown/", histName, sf_ttw, fout, fTW, "ttw_timeptetaDown", true);
TH1F* ttw_jerhfUp = DC.readWriteHisto(fTW, "reljerhfup/", histName, sf_ttw, fout, fTW, "ttw_jerhfUp", true);
TH1F* ttw_jerhfDown = DC.readWriteHisto(fTW, "reljerhfdown/", histName, sf_ttw, fout, fTW, "ttw_jerhfDown", true);
TH1F* ttw_relptbbUp = DC.readWriteHisto(fTW, "relptbbup/", histName, sf_ttw, fout, fTW, "ttw_relptbbUp", true);
TH1F* ttw_relptbbDown = DC.readWriteHisto(fTW, "relptbbdown/", histName, sf_ttw, fout, fTW, "ttw_relptbbDown", true);
TH1F* ttw_relpthfUp = DC.readWriteHisto(fTW, "relpthfup/", histName, sf_ttw, fout, fTW, "ttw_relpthfUp", true);
TH1F* ttw_relpthfDown = DC.readWriteHisto(fTW, "relpthfdown/", histName, sf_ttw, fout, fTW, "ttw_relpthfDown", true);
TH1F* ttw_relstatecUp = DC.readWriteHisto(fTW, "relstatecup/", histName, sf_ttw, fout, fTW, "ttw_relstatecUp", true);
TH1F* ttw_relstatecDown = DC.readWriteHisto(fTW, "relstatecdown/", histName, sf_ttw, fout, fTW, "ttw_relstatecDown", true);
TH1F* ttw_absstatUp = DC.readWriteHisto(fTW, "absstatup/", histName, sf_ttw, fout, fTW, "ttw_absstatUp", true);
TH1F* ttw_absstatDown = DC.readWriteHisto(fTW, "absstatdown/", histName, sf_ttw, fout, fTW, "ttw_absstatDown", true);
TH1F* ttw_abssclUp = DC.readWriteHisto(fTW, "abssclup/", histName, sf_ttw, fout, fTW, "ttw_abssclUp", true);
TH1F* ttw_abssclDown = DC.readWriteHisto(fTW, "absscldown/", histName, sf_ttw, fout, fTW, "ttw_abssclDown", true);
TH1F* ttw_absmpfbUp = DC.readWriteHisto(fTW, "absmpfbup/", histName, sf_ttw, fout, fTW, "ttw_absmpfbUp", true);
TH1F* ttw_absmpfbDown = DC.readWriteHisto(fTW, "absmpfbdown/", histName, sf_ttw, fout, fTW, "ttw_absmpfbDown", true);
TH1F* ttw_lhemuFUp = DC.readWriteHisto(fTW, "base_bc_lhemuf_up/", histName, sf_ttw, fout, fTW, "ttw_lhemuFUp", true);
TH1F* ttw_lhemuFDown = DC.readWriteHisto(fTW, "base_bc_lhemuf_do/", histName, sf_ttw, fout, fTW, "ttw_lhemuFDown", true);
TH1F* ttw_lhemuRUp = DC.readWriteHisto(fTW, "base_lhemur_up/", histName, sf_ttw, fout, fTW, "ttw_lhemuRUp", true);
TH1F* ttw_lhemuRDown = DC.readWriteHisto(fTW, "base_lhemur_do/", histName, sf_ttw, fout, fTW, "ttw_lhemuRDown", true);
TH1F* ttw_bHadronBFUp = DC.readWriteHisto(fTW, "base_bfrag_Up/", histName, sf_ttw, fout, fTW, "ttw_bHadronBFUp", true);
TH1F* ttw_bHadronBFDown = DC.readWriteHisto(fTW, "base_bfrag_do/", histName, sf_ttw, fout, fTW, "ttw_bHadronBFDown", true);
TH1F* ttw_pudataMCUp = DC.readWriteHisto(fTW, "pudatamcup/", histName, sf_ttw, fout, fTW, "ttw_pudataMCUp", true);
TH1F* ttw_pudataMCDown = DC.readWriteHisto(fTW, "pudatamcdown/", histName, sf_ttw, fout, fTW, "ttw_pudataMCDown", true);
TH1F* ttw_relptec2Up = DC.readWriteHisto(fTW, "relptec2up/", histName, sf_ttw, fout, fTW, "ttw_relptec2Up", true);
TH1F* ttw_relptec2Down = DC.readWriteHisto(fTW, "relptec2down/", histName, sf_ttw, fout, fTW, "ttw_relptec2Down", true);
TH1F* ttw_reljerec2Up = DC.readWriteHisto(fTW, "reljerec2up/", histName, sf_ttw, fout, fTW, "ttw_reljerec2Up", true);
TH1F* ttw_reljerec2Down = DC.readWriteHisto(fTW, "reljerec2down/", histName, sf_ttw, fout, fTW, "ttw_reljerec2Down", true);
TH1F* ttw_puptrefUp = DC.readWriteHisto(fTW, "puptrefup/", histName, sf_ttw, fout, fTW, "ttw_puptrefUp", true);
TH1F* ttw_puptrefDown = DC.readWriteHisto(fTW, "puptrefdown/", histName, sf_ttw, fout, fTW, "ttw_puptrefDown", true);
TH1F* ttw_puptec1Up = DC.readWriteHisto(fTW, "puptec1up/", histName, sf_ttw, fout, fTW, "ttw_puptec1Up", true);
TH1F* ttw_puptec1Down = DC.readWriteHisto(fTW, "puptec1down/", histName, sf_ttw, fout, fTW, "ttw_puptec1Down", true);
TH1F* ttw_puptec2Up = DC.readWriteHisto(fTW, "puptec2up/", histName, sf_ttw, fout, fTW, "ttw_puptec2Up", true);
TH1F* ttw_puptec2Down = DC.readWriteHisto(fTW, "puptec2down/", histName, sf_ttw, fout, fTW, "ttw_puptec2Down", true);
TH1F* ttw_base_extpUp = DC.readWriteHisto(fTW, "base_extp_up/", histName, sf_ttw, fout, fTW, "ttw_base_extpUp", true);
TH1F* ttw_base_extpDown = DC.readWriteHisto(fTW, "base_extp_do/", histName, sf_ttw, fout, fTW, "ttw_base_extpDown", true);
TH1F* ttw_base_intpUp = DC.readWriteHisto(fTW, "base_intp_up/", histName, sf_ttw, fout, fTW, "ttw_base_intpUp", true);
TH1F* ttw_base_intpDown = DC.readWriteHisto(fTW, "base_intp_do/", histName, sf_ttw, fout, fTW, "ttw_base_intpDown", true);
TH1F* ttw_base_xdycUp = DC.readWriteHisto(fTW, "base_xdyc_up/", histName, sf_ttw, fout, fTW, "ttw_base_xdycUp", true);
TH1F* ttw_base_xdycDown = DC.readWriteHisto(fTW, "base_xdyc_do/", histName, sf_ttw, fout, fTW, "ttw_base_xdycDown", true);
TH1F* ttw_base_xdybUp = DC.readWriteHisto(fTW, "base_xdyb_up/", histName, sf_ttw, fout, fTW, "ttw_base_xdybUp", true);
TH1F* ttw_base_xdybDown = DC.readWriteHisto(fTW, "base_xdyb_do/", histName, sf_ttw, fout, fTW, "ttw_base_xdybDown", true);
TH1F* ttw_base_muEffUp = DC.readWriteHisto(fTW, "base_muEff_up/", histName, sf_ttw, fout, fTW, "ttw_base_muEffUp", true);
TH1F* ttw_base_muEffDown = DC.readWriteHisto(fTW, "base_muEff_do/", histName, sf_ttw, fout, fTW, "ttw_base_muEffDown", true);
TH1F* ttw_base_pdfUp = DC.readWriteHisto(fTW, "base_pdf_Up/", histName, sf_ttw, fout, fTW, "ttw_base_pdfUp", true);
TH1F* ttw_base_pdfDown = DC.readWriteHisto(fTW, "base_pdf_Do/", histName, sf_ttw, fout, fTW, "ttw_base_pdfDown", true);
TH1F* ttw_singpiecalUp = DC.readWriteHisto(fTW, "/singpiecalup/", histName, sf_ttw, fout, fTW, "ttw_singpiecalUp", true);
TH1F* ttw_singpiecalDown = DC.readWriteHisto(fTW, "/singpiecaldown/", histName, sf_ttw, fout, fTW, "ttw_singpiecalDown", true);
TH1F* ttw_singpihcalUp = DC.readWriteHisto(fTW, "/singpihcalup/", histName, sf_ttw, fout, fTW, "ttw_singpihcalUp", true);
TH1F* ttw_singpihcalDown = DC.readWriteHisto(fTW,"/singpihcaldown/", histName, sf_ttw, fout, fTW, "ttw_singpihcalDown", true);

  // Assuming ttw and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
  //double baseIntegral = ttw->Integral();

normalizeHistogram(ttw_bc_statUp, ttw);
normalizeHistogram(ttw_bc_statDown, ttw);
normalizeHistogram(ttw_fsrUp, ttw);
normalizeHistogram(ttw_fsrDown, ttw);
normalizeHistogram(ttw_isrUp, ttw);
normalizeHistogram(ttw_isrDown, ttw);
normalizeHistogram(ttw_base_pdfUp, ttw);
normalizeHistogram(ttw_base_pdfDown, ttw);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  ttw_bc_statUp->Write();
  ttw_bc_statDown->Write();
  ttw_fsrUp->Write();
  ttw_fsrDown->Write();
  ttw_isrUp->Write();
  ttw_isrDown->Write();
  ttw_base_pdfUp->Write();
  ttw_base_pdfDown->Write();




 double unc_ttw_ExL = 1.0;
  double unc_ttw_ExM = 1.0;
  if(isExL){
    TH1F* ttw_yLyMyT = DC.getHisto(fTW, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTW);
    TH1F* ttw_yLyMnT = DC.getHisto(fTW, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTW);
    TH1F* ttw_yLnMyT = DC.getHisto(fTW, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTW);
    TH1F* ttw_yLnMnT = DC.getHisto(fTW, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTW);
    unc_ttw_ExL = DC.getUncExL(ttw_yLyMyT, ttw_yLyMnT, ttw_yLnMyT, ttw_yLnMnT);
  }
  if(isExM){
    TH1F* ttw_yMyT = DC.getHisto(fTW, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTW);
    TH1F* ttw_yMnT = DC.getHisto(fTW, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTW);
    unc_ttw_ExM = DC.getUncExM(ttw_yMyT, ttw_yMnT);
  }
   
  
//wjet
  double sf_wjet = 1.0; 
  TH1F* wjet = DC.readWriteHisto(fWJ, "base/", histName, sf_wjet, fout, fWJ, "wjet", true);
  TH1F* wjet_JESUp = DC.readWriteHisto(fWJ, "base_JEC_up/", histName, sf_wjet, fout, fWJ, "wjet_JESUp", true);
  TH1F* wjet_JESDown = DC.readWriteHisto(fWJ, "base_JEC_do/", histName, sf_wjet, fout, fWJ, "wjet_JESDown", true);
  TH1F* wjet_PileupUp = DC.readWriteHisto(fWJ, "base_PUWeight_up/", histName, sf_wjet, fout, fWJ, "wjet_PileupUp", true);
  TH1F* wjet_PileupDown = DC.readWriteHisto(fWJ, "base_PUWeight_do/", histName, sf_wjet, fout, fWJ, "wjet_PileupDown", true);
  TH1F* wjet_JERUp = DC.readWriteHisto(fWJ, "reljerec1up/", histName, sf_wjet, fout, fWJ, "wjet_JERUp", true); // Adjusted based on systematic naming convention
  TH1F* wjet_JERDown = DC.readWriteHisto(fWJ, "reljerec1down/", histName, sf_wjet, fout, fWJ, "wjet_JERDown", true); // Adjusted based on systematic naming convention
  TH1F* wjet_prefireUp = DC.readWriteHisto(fWJ, "base_prefire_up/", histName, sf_wjet, fout, fWJ, "wjet_prefireUp", true);
  TH1F* wjet_prefireDown = DC.readWriteHisto(fWJ, "base_prefire_do/", histName, sf_wjet, fout, fWJ, "wjet_prefireDown", true); // Corrected 'prefireDo' to 'prefireDown'
  TH1F* wjet_bc_statUp = DC.readWriteHisto(fWJ, "base_bc_stat_up/", histName, sf_wjet, fout, fWJ, "wjet_bc_statUp", true); // Adjusted based on systematic naming convention
  TH1F* wjet_bc_statDown = DC.readWriteHisto(fWJ, "base_bc_stat_do/", histName, sf_wjet, fout, fWJ, "wjet_bc_statDown", true); // Adjusted based on systematic naming convention, corrected 'bc_statDo' to 'bc_statDown'
  TH1F* wjet_fsrUp = DC.readWriteHisto(fWJ, "base_fsr_up/", histName, sf_wjet, fout, fWJ, "wjet_fsrUp", true);
  TH1F* wjet_fsrDown = DC.readWriteHisto(fWJ, "base_fsr_do/", histName, sf_wjet, fout, fWJ, "wjet_fsrDown", true); // Corrected 'fsrDo' to 'fsrDown'
  TH1F* wjet_isrUp = DC.readWriteHisto(fWJ, "base_isr_up/", histName, sf_wjet, fout, fWJ, "wjet_isrUp", true);
  TH1F* wjet_isrDown = DC.readWriteHisto(fWJ, "base_isr_do/", histName, sf_wjet, fout, fWJ, "wjet_isrDown", true); // Corrected 'isrDo' to 'isrDown'
  TH1F* wjet_flavorqcdUp = DC.readWriteHisto(fWJ, "flavorqcdup/", histName, sf_wjet, fout, fWJ, "wjet_flavorqcdUp", true); // Adjusted for consistency
  TH1F* wjet_flavorqcdDown = DC.readWriteHisto(fWJ, "flavorqcddown/", histName, sf_wjet, fout, fWJ, "wjet_flavorqcdDown", true); // Corrected 'flavorqcdDo' to 'flavorqcdDown', adjusted for consistency
  // Systematics with direct matches from the list
  TH1F* wjet_timeptetaUp = DC.readWriteHisto(fWJ, "timeptetaup/", histName, sf_wjet, fout, fWJ, "wjet_timeptetaUp", true);
  TH1F* wjet_timeptetaDown = DC.readWriteHisto(fWJ, "timeptetadown/", histName, sf_wjet, fout, fWJ, "wjet_timeptetaDown", true);
  TH1F* wjet_jerhfUp = DC.readWriteHisto(fWJ, "reljerhfup/", histName, sf_wjet, fout, fWJ, "wjet_jerhfUp", true);
  TH1F* wjet_jerhfDown = DC.readWriteHisto(fWJ, "reljerhfdown/", histName, sf_wjet, fout, fWJ, "wjet_jerhfDown", true);
  TH1F* wjet_relptbbUp = DC.readWriteHisto(fWJ, "relptbbup/", histName, sf_wjet, fout, fWJ, "wjet_relptbbUp", true);
  TH1F* wjet_relptbbDown = DC.readWriteHisto(fWJ, "relptbbdown/", histName, sf_wjet, fout, fWJ, "wjet_relptbbDown", true);
  TH1F* wjet_relpthfUp = DC.readWriteHisto(fWJ, "relpthfup/", histName, sf_wjet, fout, fWJ, "wjet_relpthfUp", true);
  TH1F* wjet_relpthfDown = DC.readWriteHisto(fWJ, "relpthfdown/", histName, sf_wjet, fout, fWJ, "wjet_relpthfDown", true);

  TH1F* wjet_relstatecUp = DC.readWriteHisto(fWJ, "relstatecup/", histName, sf_wjet, fout, fWJ, "wjet_relstatecUp", true);
  TH1F* wjet_relstatecDown = DC.readWriteHisto(fWJ, "relstatecdown/", histName, sf_wjet, fout, fWJ, "wjet_relstatecDown", true);

  // Absolute statistical uncertainty
  TH1F* wjet_absstatUp = DC.readWriteHisto(fWJ, "absstatup/", histName, sf_wjet, fout, fWJ, "wjet_absstatUp", true);
  TH1F* wjet_absstatDown = DC.readWriteHisto(fWJ, "absstatdown/", histName, sf_wjet, fout, fWJ, "wjet_absstatDown", true);

  // Absolute scale uncertainty
  TH1F* wjet_abssclUp = DC.readWriteHisto(fWJ, "abssclup/", histName, sf_wjet, fout, fWJ, "wjet_abssclUp", true);
  TH1F* wjet_abssclDown = DC.readWriteHisto(fWJ, "absscldown/", histName, sf_wjet, fout, fWJ, "wjet_abssclDown", true);

  // Absolute MPF bias
  TH1F* wjet_absmpfbUp = DC.readWriteHisto(fWJ, "absmpfbup/", histName, sf_wjet, fout, fWJ, "wjet_absmpfbUp", true);
  TH1F* wjet_absmpfbDown = DC.readWriteHisto(fWJ, "absmpfbdown/", histName, sf_wjet, fout, fWJ, "wjet_absmpfbDown", true);

  // LHE scale uncertainties (muF and muR)
  TH1F* wjet_lhemuFUp = DC.readWriteHisto(fWJ, "base_bc_lhemuf_up/", histName, sf_wjet, fout, fWJ, "wjet_lhemuFUp", true);
  TH1F* wjet_lhemuFDown = DC.readWriteHisto(fWJ, "base_bc_lhemuf_do/", histName, sf_wjet, fout, fWJ, "wjet_lhemuFDown", true);
  TH1F* wjet_lhemuRUp = DC.readWriteHisto(fWJ, "base_lhemur_up/", histName, sf_wjet, fout, fWJ, "wjet_lhemuRUp", true);
  TH1F* wjet_lhemuRDown = DC.readWriteHisto(fWJ, "base_lhemur_do/", histName, sf_wjet, fout, fWJ, "wjet_lhemuRDown", true);

  // b-hadron branching fraction
  TH1F* wjet_bHadronBFUp = DC.readWriteHisto(fWJ, "base_bfrag_Up/", histName, sf_wjet, fout, fWJ, "wjet_bHadronBFUp", true);
  TH1F* wjet_bHadronBFDown = DC.readWriteHisto(fWJ, "base_bfrag_do/", histName, sf_wjet, fout, fWJ, "wjet_bHadronBFDown", true);

  // Pileup data/MC corrections
  TH1F* wjet_pudataMCUp = DC.readWriteHisto(fWJ, "pudatamcup/", histName, sf_wjet, fout, fWJ, "wjet_pudataMCUp", true);
  TH1F* wjet_pudataMCDown = DC.readWriteHisto(fWJ, "pudatamcdown/", histName, sf_wjet, fout, fWJ, "wjet_pudataMCDown", true);


  TH1F* wjet_relptec2Up = DC.readWriteHisto(fWJ, "relptec2up/", histName, sf_wjet, fout, fWJ, "wjet_relptec2Up", true);
  TH1F* wjet_relptec2Down = DC.readWriteHisto(fWJ, "relptec2down/", histName, sf_wjet, fout, fWJ, "wjet_relptec2Down", true);

  TH1F* wjet_reljerec1Up = DC.readWriteHisto(fWJ, "reljerec1up/", histName, sf_wjet, fout, fWJ, "wjet_reljerec1Up", true);
  TH1F* wjet_reljerec1Do = DC.readWriteHisto(fWJ, "reljerec1down/", histName, sf_wjet, fout, fWJ, "wjet_reljerec1Down", true);

  TH1F* wjet_reljerec2Up = DC.readWriteHisto(fWJ, "reljerec2up/", histName, sf_wjet, fout, fWJ, "wjet_reljerec2Up", true);
  TH1F* wjet_reljerec2Do = DC.readWriteHisto(fWJ, "reljerec2down/", histName, sf_wjet, fout, fWJ, "wjet_reljerec2Down", true);

  TH1F* wjet_puptrefUp = DC.readWriteHisto(fWJ, "puptrefup/", histName, sf_wjet, fout, fWJ, "wjet_puptrefUp", true); // Assuming there's an up variation
  TH1F* wjet_puptrefDo = DC.readWriteHisto(fWJ, "puptrefdown/", histName, sf_wjet, fout, fWJ, "wjet_puptrefDown", true);
  TH1F* wjet_puptec1Up = DC.readWriteHisto(fWJ, "puptec1up/", histName, sf_wjet, fout, fWJ, "wjet_puptec1Up", true);
  TH1F* wjet_puptec1Do = DC.readWriteHisto(fWJ, "puptec1down/", histName, sf_wjet, fout, fWJ, "wjet_puptec1Down", true);

  TH1F* wjet_puptec2Up = DC.readWriteHisto(fWJ, "puptec2up/", histName, sf_wjet, fout, fWJ, "wjet_puptec2Up", true);
  TH1F* wjet_puptec2Do = DC.readWriteHisto(fWJ, "puptec2down/", histName, sf_wjet, fout, fWJ, "wjet_puptec2Down", true);


  // External parameters (extp) variations
  TH1F* wjet_base_extpUp = DC.readWriteHisto(fWJ, "base_extp_up/", histName, sf_wjet, fout, fWJ, "wjet_base_extpUp", true);
  TH1F* wjet_base_extpDo = DC.readWriteHisto(fWJ, "base_extp_do/", histName, sf_wjet, fout, fWJ, "wjet_base_extpDown", true);

  // Internal parameters (intp) variations
  TH1F* wjet_base_intpUp = DC.readWriteHisto(fWJ, "base_intp_up/", histName, sf_wjet, fout, fWJ, "wjet_base_intpUp", true);
  TH1F* wjet_base_intpDo = DC.readWriteHisto(fWJ, "base_intp_do/", histName, sf_wjet, fout, fWJ, "wjet_base_intpDown", true);

  // Cross-section DY corrections (xdyc) variations
  TH1F* wjet_base_xdycUp = DC.readWriteHisto(fWJ, "base_xdyc_up/", histName, sf_wjet, fout, fWJ, "wjet_base_xdycUp", true);
  TH1F* wjet_base_xdycDo = DC.readWriteHisto(fWJ, "base_xdyc_do/", histName, sf_wjet, fout, fWJ, "wjet_base_xdycDown", true);

  // Cross-section DYb corrections (xdyb) variations
  TH1F* wjet_base_xdybUp = DC.readWriteHisto(fWJ, "base_xdyb_up/", histName, sf_wjet, fout, fWJ, "wjet_base_xdybUp", true);
  TH1F* wjet_base_xdybDo = DC.readWriteHisto(fWJ, "base_xdyb_do/", histName, sf_wjet, fout, fWJ, "wjet_base_xdybDown", true);

  // Muon efficiency (muEff) corrections variations
  TH1F* wjet_base_muEffUp = DC.readWriteHisto(fWJ, "base_muEff_up/", histName, sf_wjet, fout, fWJ, "wjet_base_muEffUp", true);
  TH1F* wjet_base_muEffDo = DC.readWriteHisto(fWJ, "base_muEff_do/", histName, sf_wjet, fout, fWJ, "wjet_base_muEffDown", true);
  // PDF variations
  TH1F* wjet_base_pdfUp = DC.readWriteHisto(fWJ, "base_pdf_Up/", histName, sf_wjet, fout, fWJ, "wjet_base_pdfUp", true);
  TH1F* wjet_base_pdfDo = DC.readWriteHisto(fWJ, "base_pdf_Do/", histName, sf_wjet, fout, fWJ, "wjet_base_pdfDown", true);
  // Read and write histograms for systematic variations of wjet
 TH1F* wjet_singpiecalUp = DC.readWriteHisto(fWJ,"/singpiecalup/", histName, sf_wjet, fout, fWJ, "wjet_singpiecalUp", true);
 TH1F* wjet_singpiecalDown = DC.readWriteHisto(fWJ, "/singpiecaldown/", histName, sf_wjet, fout, fWJ, "wjet_singpiecalDown", true);
 TH1F* wjet_singpihcalUp = DC.readWriteHisto(fWJ,"/singpihcalup/", histName, sf_wjet, fout, fWJ, "wjet_singpihcalUp", true);
  TH1F* wjet_singpihcalDown = DC.readWriteHisto(fWJ,"/singpihcaldown/", histName, sf_wjet, fout, fWJ, "wjet_singpihcalDown", true);


  // Assuming wjet and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
 //double baseIntegral_wjet = wjet->Integral();

normalizeHistogram(wjet_bc_statUp, wjet);
normalizeHistogram(wjet_bc_statDown, wjet);
normalizeHistogram(wjet_fsrUp, wjet);
normalizeHistogram(wjet_fsrDown, wjet);
normalizeHistogram(wjet_isrUp, wjet);
normalizeHistogram(wjet_isrDown, wjet);
normalizeHistogram(wjet_base_pdfUp, wjet);
normalizeHistogram(wjet_base_pdfDo, wjet);

  double unc_wjet_ExL = 1.0;
  double unc_wjet_ExM = 1.0;
  if(isExL){
    TH1F* wjet_yLyMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* wjet_yLyMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* wjet_yLnMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* wjet_yLnMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_wjet_ExL = DC.getUncExL(wjet_yLyMyT, wjet_yLyMnT, wjet_yLnMyT, wjet_yLnMnT);
  }
  if(isExM){
    TH1F* wjet_yMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* wjet_yMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_wjet_ExM = DC.getUncExM(wjet_yMyT, wjet_yMnT);
  }

 //zjet
  double sf_zjet = 1.0; 
  TH1F* zjet = DC.readWriteHisto(fDY, "base/", histName, sf_zjet, fout, fDY, "zjet", true);
  TH1F* zjet_JESUp = DC.readWriteHisto(fDY, "base_JEC_up/", histName, sf_zjet, fout, fDY, "zjet_JESUp", true);
  TH1F* zjet_JESDown = DC.readWriteHisto(fDY, "base_JEC_do/", histName, sf_zjet, fout, fDY, "zjet_JESDown", true);
  TH1F* zjet_PileupUp = DC.readWriteHisto(fDY, "base_PUWeight_up/", histName, sf_zjet, fout, fDY, "zjet_PileupUp", true);
  TH1F* zjet_PileupDown = DC.readWriteHisto(fDY, "base_PUWeight_do/", histName, sf_zjet, fout, fDY, "zjet_PileupDown", true);
  TH1F* zjet_JERUp = DC.readWriteHisto(fDY, "reljerec1up/", histName, sf_zjet, fout, fDY, "zjet_JERUp", true); // Adjusted based on systematic naming convention
  TH1F* zjet_JERDown = DC.readWriteHisto(fDY, "reljerec1down/", histName, sf_zjet, fout, fDY, "zjet_JERDown", true); // Adjusted based on systematic naming convention
  TH1F* zjet_prefireUp = DC.readWriteHisto(fDY, "base_prefire_up/", histName, sf_zjet, fout, fDY, "zjet_prefireUp", true);
  TH1F* zjet_prefireDown = DC.readWriteHisto(fDY, "base_prefire_do/", histName, sf_zjet, fout, fDY, "zjet_prefireDown", true); // Corrected 'prefireDo' to 'prefireDown'
  TH1F* zjet_bc_statUp = DC.readWriteHisto(fDY, "base_bc_stat_up/", histName, sf_zjet, fout, fDY, "zjet_bc_statUp", true); // Adjusted based on systematic naming convention
  TH1F* zjet_bc_statDown = DC.readWriteHisto(fDY, "base_bc_stat_do/", histName, sf_zjet, fout, fDY, "zjet_bc_statDown", true); // Adjusted based on systematic naming convention, corrected 'bc_statDo' to 'bc_statDown'
  TH1F* zjet_fsrUp = DC.readWriteHisto(fDY, "base_fsr_up/", histName, sf_zjet, fout, fDY, "zjet_fsrUp", true);
  TH1F* zjet_fsrDown = DC.readWriteHisto(fDY, "base_fsr_do/", histName, sf_zjet, fout, fDY, "zjet_fsrDown", true); // Corrected 'fsrDo' to 'fsrDown'
  TH1F* zjet_isrUp = DC.readWriteHisto(fDY, "base_isr_up/", histName, sf_zjet, fout, fDY, "zjet_isrUp", true);
  TH1F* zjet_isrDown = DC.readWriteHisto(fDY, "base_isr_do/", histName, sf_zjet, fout, fDY, "zjet_isrDown", true); // Corrected 'isrDo' to 'isrDown'
  TH1F* zjet_flavorqcdUp = DC.readWriteHisto(fDY, "flavorqcdup/", histName, sf_zjet, fout, fDY, "zjet_flavorqcdUp", true); // Adjusted for consistency
  TH1F* zjet_flavorqcdDown = DC.readWriteHisto(fDY, "flavorqcddown/", histName, sf_zjet, fout, fDY, "zjet_flavorqcdDown", true); // Corrected 'flavorqcdDo' to 'flavorqcdDown', adjusted for consistency
  // Systematics with direct matches from the list
  TH1F* zjet_timeptetaUp = DC.readWriteHisto(fDY, "timeptetaup/", histName, sf_zjet, fout, fDY, "zjet_timeptetaUp", true);
  TH1F* zjet_timeptetaDown = DC.readWriteHisto(fDY, "timeptetadown/", histName, sf_zjet, fout, fDY, "zjet_timeptetaDown", true);
  TH1F* zjet_jerhfUp = DC.readWriteHisto(fDY, "reljerhfup/", histName, sf_zjet, fout, fDY, "zjet_jerhfUp", true);
  TH1F* zjet_jerhfDown = DC.readWriteHisto(fDY, "reljerhfdown/", histName, sf_zjet, fout, fDY, "zjet_jerhfDown", true);
  TH1F* zjet_relptbbUp = DC.readWriteHisto(fDY, "relptbbup/", histName, sf_zjet, fout, fDY, "zjet_relptbbUp", true);
  TH1F* zjet_relptbbDown = DC.readWriteHisto(fDY, "relptbbdown/", histName, sf_zjet, fout, fDY, "zjet_relptbbDown", true);
  TH1F* zjet_relpthfUp = DC.readWriteHisto(fDY, "relpthfup/", histName, sf_zjet, fout, fDY, "zjet_relpthfUp", true);
  TH1F* zjet_relpthfDown = DC.readWriteHisto(fDY, "relpthfdown/", histName, sf_zjet, fout, fDY, "zjet_relpthfDown", true);

  TH1F* zjet_relstatecUp = DC.readWriteHisto(fDY, "relstatecup/", histName, sf_zjet, fout, fDY, "zjet_relstatecUp", true);
  TH1F* zjet_relstatecDown = DC.readWriteHisto(fDY, "relstatecdown/", histName, sf_zjet, fout, fDY, "zjet_relstatecDown", true);

  // Absolute statistical uncertainty
  TH1F* zjet_absstatUp = DC.readWriteHisto(fDY, "absstatup/", histName, sf_zjet, fout, fDY, "zjet_absstatUp", true);
  TH1F* zjet_absstatDown = DC.readWriteHisto(fDY, "absstatdown/", histName, sf_zjet, fout, fDY, "zjet_absstatDown", true);

  // Absolute scale uncertainty
  TH1F* zjet_abssclUp = DC.readWriteHisto(fDY, "abssclup/", histName, sf_zjet, fout, fDY, "zjet_abssclUp", true);
  TH1F* zjet_abssclDown = DC.readWriteHisto(fDY, "absscldown/", histName, sf_zjet, fout, fDY, "zjet_abssclDown", true);

  // Absolute MPF bias
  TH1F* zjet_absmpfbUp = DC.readWriteHisto(fDY, "absmpfbup/", histName, sf_zjet, fout, fDY, "zjet_absmpfbUp", true);
  TH1F* zjet_absmpfbDown = DC.readWriteHisto(fDY, "absmpfbdown/", histName, sf_zjet, fout, fDY, "zjet_absmpfbDown", true);

  // LHE scale uncertainties (muF and muR)
  TH1F* zjet_lhemuFUp = DC.readWriteHisto(fDY, "base_bc_lhemuf_up/", histName, sf_zjet, fout, fDY, "zjet_lhemuFUp", true);
  TH1F* zjet_lhemuFDown = DC.readWriteHisto(fDY, "base_bc_lhemuf_do/", histName, sf_zjet, fout, fDY, "zjet_lhemuFDown", true);
  TH1F* zjet_lhemuRUp = DC.readWriteHisto(fDY, "base_lhemur_up/", histName, sf_zjet, fout, fDY, "zjet_lhemuRUp", true);
  TH1F* zjet_lhemuRDown = DC.readWriteHisto(fDY, "base_lhemur_do/", histName, sf_zjet, fout, fDY, "zjet_lhemuRDown", true);

  // b-hadron branching fraction
  TH1F* zjet_bHadronBFUp = DC.readWriteHisto(fDY, "base_bfrag_Up/", histName, sf_zjet, fout, fDY, "zjet_bHadronBFUp", true);
  TH1F* zjet_bHadronBFDown = DC.readWriteHisto(fDY, "base_bfrag_do/", histName, sf_zjet, fout, fDY, "zjet_bHadronBFDown", true);

  // Pileup data/MC corrections
  TH1F* zjet_pudataMCUp = DC.readWriteHisto(fDY, "pudatamcup/", histName, sf_zjet, fout, fDY, "zjet_pudataMCUp", true);
  TH1F* zjet_pudataMCDown = DC.readWriteHisto(fDY, "pudatamcdown/", histName, sf_zjet, fout, fDY, "zjet_pudataMCDown", true);



  TH1F* zjet_relptec2Up = DC.readWriteHisto(fDY, "relptec2up/", histName, sf_zjet, fout, fDY, "zjet_relptec2Up", true);
  TH1F* zjet_relptec2Down = DC.readWriteHisto(fDY, "relptec2down/", histName, sf_zjet, fout, fDY, "zjet_relptec2Down", true);

  TH1F* zjet_reljerec1Up = DC.readWriteHisto(fDY, "reljerec1up/", histName, sf_zjet, fout, fDY, "zjet_reljerec1Up", true);
  TH1F* zjet_reljerec1Do = DC.readWriteHisto(fDY, "reljerec1down/", histName, sf_zjet, fout, fDY, "zjet_reljerec1Down", true);

  TH1F* zjet_reljerec2Up = DC.readWriteHisto(fDY, "reljerec2up/", histName, sf_zjet, fout, fDY, "zjet_reljerec2Up", true);
  TH1F* zjet_reljerec2Do = DC.readWriteHisto(fDY, "reljerec2down/", histName, sf_zjet, fout, fDY, "zjet_reljerec2Down", true);

  TH1F* zjet_puptrefUp = DC.readWriteHisto(fDY, "puptrefup/", histName, sf_zjet, fout, fDY, "zjet_puptrefUp", true); // Assuming there's an up variation
  TH1F* zjet_puptrefDo = DC.readWriteHisto(fDY, "puptrefdown/", histName, sf_zjet, fout, fDY, "zjet_puptrefDown", true);
  TH1F* zjet_puptec1Up = DC.readWriteHisto(fDY, "puptec1up/", histName, sf_zjet, fout, fDY, "zjet_puptec1Up", true);
  TH1F* zjet_puptec1Do = DC.readWriteHisto(fDY, "puptec1down/", histName, sf_zjet, fout, fDY, "zjet_puptec1Down", true);

  TH1F* zjet_puptec2Up = DC.readWriteHisto(fDY, "puptec2up/", histName, sf_zjet, fout, fDY, "zjet_puptec2Up", true);
  TH1F* zjet_puptec2Do = DC.readWriteHisto(fDY, "puptec2down/", histName, sf_zjet, fout, fDY, "zjet_puptec2Down", true);


  // External parameters (extp) variations
  TH1F* zjet_base_extpUp = DC.readWriteHisto(fDY, "base_extp_up/", histName, sf_zjet, fout, fDY, "zjet_base_extpUp", true);
  TH1F* zjet_base_extpDo = DC.readWriteHisto(fDY, "base_extp_do/", histName, sf_zjet, fout, fDY, "zjet_base_extpDown", true);

  // Internal parameters (intp) variations
  TH1F* zjet_base_intpUp = DC.readWriteHisto(fDY, "base_intp_up/", histName, sf_zjet, fout, fDY, "zjet_base_intpUp", true);
  TH1F* zjet_base_intpDo = DC.readWriteHisto(fDY, "base_intp_do/", histName, sf_zjet, fout, fDY, "zjet_base_intpDown", true);

  // Cross-section DY corrections (xdyc) variations
  TH1F* zjet_base_xdycUp = DC.readWriteHisto(fDY, "base_xdyc_up/", histName, sf_zjet, fout, fDY, "zjet_base_xdycUp", true);
  TH1F* zjet_base_xdycDo = DC.readWriteHisto(fDY, "base_xdyc_do/", histName, sf_zjet, fout, fDY, "zjet_base_xdycDown", true);

  // Cross-section DYb corrections (xdyb) variations
  TH1F* zjet_base_xdybUp = DC.readWriteHisto(fDY, "base_xdyb_up/", histName, sf_zjet, fout, fDY, "zjet_base_xdybUp", true);
  TH1F* zjet_base_xdybDo = DC.readWriteHisto(fDY, "base_xdyb_do/", histName, sf_zjet, fout, fDY, "zjet_base_xdybDown", true);

  // Muon efficiency (muEff) corrections variations
  TH1F* zjet_base_muEffUp = DC.readWriteHisto(fDY, "base_muEff_up/", histName, sf_zjet, fout, fDY, "zjet_base_muEffUp", true);
  TH1F* zjet_base_muEffDo = DC.readWriteHisto(fDY, "base_muEff_do/", histName, sf_zjet, fout, fDY, "zjet_base_muEffDown", true);
  // PDF variations
  TH1F* zjet_base_pdfUp = DC.readWriteHisto(fDY, "base_pdf_Up/", histName, sf_zjet, fout, fDY, "zjet_base_pdfUp", true);
  TH1F* zjet_base_pdfDo = DC.readWriteHisto(fDY, "base_pdf_Do/", histName, sf_zjet, fout, fDY, "zjet_base_pdfDown", true);
  // Read and write histograms for systematic variations of zjet
  TH1F* zjet_singpiecalUp = DC.readWriteHisto(fDY,"/singpiecalup/", histName, sf_zjet, fout, fDY, "zjet_singpiecalUp", true);
  TH1F* zjet_singpiecalDown = DC.readWriteHisto(fDY,"/singpiecaldown/", histName, sf_zjet, fout, fDY, "zjet_singpiecalDown", true);
  TH1F* zjet_singpihcalUp = DC.readWriteHisto(fDY,"/singpihcalup/", histName, sf_zjet, fout, fDY, "zjet_singpihcalUp", true);
  TH1F* zjet_singpihcalDown = DC.readWriteHisto(fDY,"/singpihcaldown/", histName, sf_zjet, fout, fDY, "zjet_singpihcalDown", true);


  // Assuming zjet and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
  //double baseIntegral = zjet->Integral();

// double baseIntegral_zjet = zjet->Integral();

normalizeHistogram(zjet_bc_statUp, zjet);
normalizeHistogram(zjet_bc_statDown, zjet);
normalizeHistogram(zjet_fsrUp, zjet);
normalizeHistogram(zjet_fsrDown, zjet);
normalizeHistogram(zjet_isrUp, zjet);
normalizeHistogram(zjet_isrDown, zjet);
normalizeHistogram(zjet_base_pdfUp, zjet);
normalizeHistogram(zjet_base_pdfDo, zjet);
  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  zjet_bc_statUp->Write();
  zjet_bc_statDown->Write();
  zjet_fsrUp->Write();
  zjet_fsrDown->Write();
  zjet_isrUp->Write();
  zjet_isrDown->Write();
  zjet_base_pdfUp->Write();
  zjet_base_pdfDo->Write();


  double unc_zjet_ExL = 1.0;
  double unc_zjet_ExM = 1.0;
  if(isExL){
    TH1F* zjet_yLyMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* zjet_yLyMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* zjet_yLnMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* zjet_yLnMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_zjet_ExL = DC.getUncExL(zjet_yLyMyT, zjet_yLyMnT, zjet_yLnMyT, zjet_yLnMnT);
  }
  if(isExM){
    TH1F* zjet_yMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* zjet_yMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_zjet_ExM = DC.getUncExM(zjet_yMyT, zjet_yMnT);
  }


//stop
  double sf_stop = 1.0; 
  TH1F* stop = DC.readWriteHisto(fST, "base/", histName, sf_stop, fout, fST, "stop", true);
  TH1F* stop_JESUp = DC.readWriteHisto(fST, "base_JEC_up/", histName, sf_stop, fout, fST, "stop_JESUp", true);
  TH1F* stop_JESDown = DC.readWriteHisto(fST, "base_JEC_do/", histName, sf_stop, fout, fST, "stop_JESDown", true);
  TH1F* stop_PileupUp = DC.readWriteHisto(fST, "base_PUWeight_up/", histName, sf_stop, fout, fST, "stop_PileupUp", true);
  TH1F* stop_PileupDown = DC.readWriteHisto(fST, "base_PUWeight_do/", histName, sf_stop, fout, fST, "stop_PileupDown", true);
  TH1F* stop_JERUp = DC.readWriteHisto(fST, "reljerec1up/", histName, sf_stop, fout, fST, "stop_JERUp", true); // Adjusted based on systematic naming convention
  TH1F* stop_JERDown = DC.readWriteHisto(fST, "reljerec1down/", histName, sf_stop, fout, fST, "stop_JERDown", true); // Adjusted based on systematic naming convention
  TH1F* stop_prefireUp = DC.readWriteHisto(fST, "base_prefire_up/", histName, sf_stop, fout, fST, "stop_prefireUp", true);
  TH1F* stop_prefireDown = DC.readWriteHisto(fST, "base_prefire_do/", histName, sf_stop, fout, fST, "stop_prefireDown", true); // Corrected 'prefireDo' to 'prefireDown'
  TH1F* stop_bc_statUp = DC.readWriteHisto(fST, "base_bc_stat_up/", histName, sf_stop, fout, fST, "stop_bc_statUp", true); // Adjusted based on systematic naming convention
  TH1F* stop_bc_statDown = DC.readWriteHisto(fST, "base_bc_stat_do/", histName, sf_stop, fout, fST, "stop_bc_statDown", true); // Adjusted based on systematic naming convention, corrected 'bc_statDo' to 'bc_statDown'
  TH1F* stop_fsrUp = DC.readWriteHisto(fST, "base_fsr_up/", histName, sf_stop, fout, fST, "stop_fsrUp", true);
  TH1F* stop_fsrDown = DC.readWriteHisto(fST, "base_fsr_do/", histName, sf_stop, fout, fST, "stop_fsrDown", true); // Corrected 'fsrDo' to 'fsrDown'
  TH1F* stop_isrUp = DC.readWriteHisto(fST, "base_isr_up/", histName, sf_stop, fout, fST, "stop_isrUp", true);
  TH1F* stop_isrDown = DC.readWriteHisto(fST, "base_isr_do/", histName, sf_stop, fout, fST, "stop_isrDown", true); // Corrected 'isrDo' to 'isrDown'
  TH1F* stop_flavorqcdUp = DC.readWriteHisto(fST, "flavorqcdup/", histName, sf_stop, fout, fST, "stop_flavorqcdUp", true); // Adjusted for consistency
  TH1F* stop_flavorqcdDown = DC.readWriteHisto(fST, "flavorqcddown/", histName, sf_stop, fout, fST, "stop_flavorqcdDown", true); // Corrected 'flavorqcdDo' to 'flavorqcdDown', adjusted for consistency
  // Systematics with direct matches from the list
  TH1F* stop_timeptetaUp = DC.readWriteHisto(fST, "timeptetaup/", histName, sf_stop, fout, fST, "stop_timeptetaUp", true);
  TH1F* stop_timeptetaDown = DC.readWriteHisto(fST, "timeptetadown/", histName, sf_stop, fout, fST, "stop_timeptetaDown", true);
  TH1F* stop_jerhfUp = DC.readWriteHisto(fST, "reljerhfup/", histName, sf_stop, fout, fST, "stop_jerhfUp", true);
  TH1F* stop_jerhfDown = DC.readWriteHisto(fST, "reljerhfdown/", histName, sf_stop, fout, fST, "stop_jerhfDown", true);
  TH1F* stop_relptbbUp = DC.readWriteHisto(fST, "relptbbup/", histName, sf_stop, fout, fST, "stop_relptbbUp", true);
  TH1F* stop_relptbbDown = DC.readWriteHisto(fST, "relptbbdown/", histName, sf_stop, fout, fST, "stop_relptbbDown", true);
  TH1F* stop_relpthfUp = DC.readWriteHisto(fST, "relpthfup/", histName, sf_stop, fout, fST, "stop_relpthfUp", true);
  TH1F* stop_relpthfDown = DC.readWriteHisto(fST, "relpthfdown/", histName, sf_stop, fout, fST, "stop_relpthfDown", true);

  TH1F* stop_relstatecUp = DC.readWriteHisto(fST, "relstatecup/", histName, sf_stop, fout, fST, "stop_relstatecUp", true);
  TH1F* stop_relstatecDown = DC.readWriteHisto(fST, "relstatecdown/", histName, sf_stop, fout, fST, "stop_relstatecDown", true);

  // Absolute statistical uncertainty
  TH1F* stop_absstatUp = DC.readWriteHisto(fST, "absstatup/", histName, sf_stop, fout, fST, "stop_absstatUp", true);
  TH1F* stop_absstatDown = DC.readWriteHisto(fST, "absstatdown/", histName, sf_stop, fout, fST, "stop_absstatDown", true);

  // Absolute scale uncertainty
  TH1F* stop_abssclUp = DC.readWriteHisto(fST, "abssclup/", histName, sf_stop, fout, fST, "stop_abssclUp", true);
  TH1F* stop_abssclDown = DC.readWriteHisto(fST, "absscldown/", histName, sf_stop, fout, fST, "stop_abssclDown", true);

  // Absolute MPF bias
  TH1F* stop_absmpfbUp = DC.readWriteHisto(fST, "absmpfbup/", histName, sf_stop, fout, fST, "stop_absmpfbUp", true);
  TH1F* stop_absmpfbDown = DC.readWriteHisto(fST, "absmpfbdown/", histName, sf_stop, fout, fST, "stop_absmpfbDown", true);

  // LHE scale uncertainties (muF and muR)
  TH1F* stop_lhemuFUp = DC.readWriteHisto(fST, "base_bc_lhemuf_up/", histName, sf_stop, fout, fST, "stop_lhemuFUp", true);
  TH1F* stop_lhemuFDown = DC.readWriteHisto(fST, "base_bc_lhemuf_do/", histName, sf_stop, fout, fST, "stop_lhemuFDown", true);
  TH1F* stop_lhemuRUp = DC.readWriteHisto(fST, "base_lhemur_up/", histName, sf_stop, fout, fST, "stop_lhemuRUp", true);
  TH1F* stop_lhemuRDown = DC.readWriteHisto(fST, "base_lhemur_do/", histName, sf_stop, fout, fST, "stop_lhemuRDown", true);

  // b-hadron branching fraction
  TH1F* stop_bHadronBFUp = DC.readWriteHisto(fST, "base_bfrag_Up/", histName, sf_stop, fout, fST, "stop_bHadronBFUp", true);
  TH1F* stop_bHadronBFDown = DC.readWriteHisto(fST, "base_bfrag_do/", histName, sf_stop, fout, fST, "stop_bHadronBFDown", true);

  // Pileup data/MC corrections
  TH1F* stop_pudataMCUp = DC.readWriteHisto(fST, "pudatamcup/", histName, sf_stop, fout, fST, "stop_pudataMCUp", true);
  TH1F* stop_pudataMCDown = DC.readWriteHisto(fST, "pudatamcdown/", histName, sf_stop, fout, fST, "stop_pudataMCDown", true);




  TH1F* stop_relptec2Up = DC.readWriteHisto(fST, "relptec2up/", histName, sf_stop, fout, fST, "stop_relptec2Up", true);
  TH1F* stop_relptec2Down = DC.readWriteHisto(fST, "relptec2down/", histName, sf_stop, fout, fST, "stop_relptec2Down", true);

  TH1F* stop_reljerec1Up = DC.readWriteHisto(fST, "reljerec1up/", histName, sf_stop, fout, fST, "stop_reljerec1Up", true);
  TH1F* stop_reljerec1Do = DC.readWriteHisto(fST, "reljerec1down/", histName, sf_stop, fout, fST, "stop_reljerec1Down", true);

  TH1F* stop_reljerec2Up = DC.readWriteHisto(fST, "reljerec2up/", histName, sf_stop, fout, fST, "stop_reljerec2Up", true);
  TH1F* stop_reljerec2Do = DC.readWriteHisto(fST, "reljerec2down/", histName, sf_stop, fout, fST, "stop_reljerec2Down", true);

  TH1F* stop_puptrefUp = DC.readWriteHisto(fST, "puptrefup/", histName, sf_stop, fout, fST, "stop_puptrefUp", true); // Assuming there's an up variation
  TH1F* stop_puptrefDo = DC.readWriteHisto(fST, "puptrefdown/", histName, sf_stop, fout, fST, "stop_puptrefDown", true);
  TH1F* stop_puptec1Up = DC.readWriteHisto(fST, "puptec1up/", histName, sf_stop, fout, fST, "stop_puptec1Up", true);
  TH1F* stop_puptec1Do = DC.readWriteHisto(fST, "puptec1down/", histName, sf_stop, fout, fST, "stop_puptec1Down", true);

  TH1F* stop_puptec2Up = DC.readWriteHisto(fST, "puptec2up/", histName, sf_stop, fout, fST, "stop_puptec2Up", true);
  TH1F* stop_puptec2Do = DC.readWriteHisto(fST, "puptec2down/", histName, sf_stop, fout, fST, "stop_puptec2Down", true);


  // External parameters (extp) variations
  TH1F* stop_base_extpUp = DC.readWriteHisto(fST, "base_extp_up/", histName, sf_stop, fout, fST, "stop_base_extpUp", true);
  TH1F* stop_base_extpDo = DC.readWriteHisto(fST, "base_extp_do/", histName, sf_stop, fout, fST, "stop_base_extpDown", true);

  // Internal parameters (intp) variations
  TH1F* stop_base_intpUp = DC.readWriteHisto(fST, "base_intp_up/", histName, sf_stop, fout, fST, "stop_base_intpUp", true);
  TH1F* stop_base_intpDo = DC.readWriteHisto(fST, "base_intp_do/", histName, sf_stop, fout, fST, "stop_base_intpDown", true);

  // Cross-section DY corrections (xdyc) variations
  TH1F* stop_base_xdycUp = DC.readWriteHisto(fST, "base_xdyc_up/", histName, sf_stop, fout, fST, "stop_base_xdycUp", true);
  TH1F* stop_base_xdycDo = DC.readWriteHisto(fST, "base_xdyc_do/", histName, sf_stop, fout, fST, "stop_base_xdycDown", true);

  // Cross-section DYb corrections (xdyb) variations
  TH1F* stop_base_xdybUp = DC.readWriteHisto(fST, "base_xdyb_up/", histName, sf_stop, fout, fST, "stop_base_xdybUp", true);
  TH1F* stop_base_xdybDo = DC.readWriteHisto(fST, "base_xdyb_do/", histName, sf_stop, fout, fST, "stop_base_xdybDown", true);

  // Muon efficiency (muEff) corrections variations
  TH1F* stop_base_muEffUp = DC.readWriteHisto(fST, "base_muEff_up/", histName, sf_stop, fout, fST, "stop_base_muEffUp", true);
  TH1F* stop_base_muEffDo = DC.readWriteHisto(fST, "base_muEff_do/", histName, sf_stop, fout, fST, "stop_base_muEffDown", true);
  // PDF variations
  TH1F* stop_base_pdfUp = DC.readWriteHisto(fST, "base_pdf_Up/", histName, sf_stop, fout, fST, "stop_base_pdfUp", true);
  TH1F* stop_base_pdfDo = DC.readWriteHisto(fST, "base_pdf_Do/", histName, sf_stop, fout, fST, "stop_base_pdfDown", true);
  // Read and write histograms for systematic variations of stop
 TH1F* stop_singpiecalUp = DC.readWriteHisto(fST, "/singpiecalup/", histName, sf_stop, fout, fST, "stop_singpiecalUp", true);
 TH1F* stop_singpiecalDown = DC.readWriteHisto(fST, "/singpiecaldown/", histName, sf_stop, fout, fST, "stop_singpiecalDown", true);
 TH1F* stop_singpihcalUp = DC.readWriteHisto(fST, "/singpihcalup/", histName, sf_stop, fout, fST, "stop_singpihcalUp", true);
 TH1F* stop_singpihcalDown = DC.readWriteHisto(fST, "/singpihcaldown/", histName, sf_stop, fout, fST, "stop_singpihcalDown", true);


normalizeHistogram(stop_bc_statUp, stop);
normalizeHistogram(stop_bc_statDown, stop);
normalizeHistogram(stop_fsrUp, stop);
normalizeHistogram(stop_fsrDown, stop);
normalizeHistogram(stop_isrUp, stop);
normalizeHistogram(stop_isrDown, stop);
normalizeHistogram(stop_base_pdfUp, stop);
normalizeHistogram(stop_base_pdfDo, stop);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  stop_bc_statUp->Write();
  stop_bc_statDown->Write();
  stop_fsrUp->Write();
  stop_fsrDown->Write();
  stop_isrUp->Write();
  stop_isrDown->Write();
  stop_base_pdfUp->Write();
  stop_base_pdfDo->Write();
double unc_stop_ExL = 1.0;
  double unc_stop_ExM = 1.0;
  if(isExL){
    TH1F* stop_yLyMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* stop_yLyMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* stop_yLnMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* stop_yLnMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_stop_ExL = DC.getUncExL(stop_yLyMyT, stop_yLyMnT, stop_yLnMyT, stop_yLnMnT);
  }
  if(isExM){
    TH1F* stop_yMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* stop_yMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_stop_ExM = DC.getUncExM(stop_yMyT, stop_yMnT);
  }

 //vv
  double sf_vv = 1.0; 
  TH1F* vv = DC.readWriteHisto(fVV, "base/", histName, sf_vv, fout, fVV, "vv", true);
  TH1F* vv_JESUp = DC.readWriteHisto(fVV, "base_JEC_up/", histName, sf_vv, fout, fVV, "vv_JESUp", true);
  TH1F* vv_JESDown = DC.readWriteHisto(fVV, "base_JEC_do/", histName, sf_vv, fout, fVV, "vv_JESDown", true);
  TH1F* vv_PileupUp = DC.readWriteHisto(fVV, "base_PUWeight_up/", histName, sf_vv, fout, fVV, "vv_PileupUp", true);
  TH1F* vv_PileupDown = DC.readWriteHisto(fVV, "base_PUWeight_do/", histName, sf_vv, fout, fVV, "vv_PileupDown", true);
  TH1F* vv_JERUp = DC.readWriteHisto(fVV, "reljerec1up/", histName, sf_vv, fout, fVV, "vv_JERUp", true); // Adjusted based on systematic naming convention
  TH1F* vv_JERDown = DC.readWriteHisto(fVV, "reljerec1down/", histName, sf_vv, fout, fVV, "vv_JERDown", true); // Adjusted based on systematic naming convention
  TH1F* vv_prefireUp = DC.readWriteHisto(fVV, "base_prefire_up/", histName, sf_vv, fout, fVV, "vv_prefireUp", true);
  TH1F* vv_prefireDown = DC.readWriteHisto(fVV, "base_prefire_do/", histName, sf_vv, fout, fVV, "vv_prefireDown", true); // Corrected 'prefireDo' to 'prefireDown'
  TH1F* vv_bc_statUp = DC.readWriteHisto(fVV, "base_bc_stat_up/", histName, sf_vv, fout, fVV, "vv_bc_statUp", true); // Adjusted based on systematic naming convention
  TH1F* vv_bc_statDown = DC.readWriteHisto(fVV, "base_bc_stat_do/", histName, sf_vv, fout, fVV, "vv_bc_statDown", true); // Adjusted based on systematic naming convention, corrected 'bc_statDo' to 'bc_statDown'
  TH1F* vv_fsrUp = DC.readWriteHisto(fVV, "base_fsr_up/", histName, sf_vv, fout, fVV, "vv_fsrUp", true);
  TH1F* vv_fsrDown = DC.readWriteHisto(fVV, "base_fsr_do/", histName, sf_vv, fout, fVV, "vv_fsrDown", true); // Corrected 'fsrDo' to 'fsrDown'
  TH1F* vv_isrUp = DC.readWriteHisto(fVV, "base_isr_up/", histName, sf_vv, fout, fVV, "vv_isrUp", true);
  TH1F* vv_isrDown = DC.readWriteHisto(fVV, "base_isr_do/", histName, sf_vv, fout, fVV, "vv_isrDown", true); // Corrected 'isrDo' to 'isrDown'
  TH1F* vv_flavorqcdUp = DC.readWriteHisto(fVV, "flavorqcdup/", histName, sf_vv, fout, fVV, "vv_flavorqcdUp", true); // Adjusted for consistency
  TH1F* vv_flavorqcdDown = DC.readWriteHisto(fVV, "flavorqcddown/", histName, sf_vv, fout, fVV, "vv_flavorqcdDown", true); // Corrected 'flavorqcdDo' to 'flavorqcdDown', adjusted for consistency
  // Systematics with direct matches from the list
  TH1F* vv_timeptetaUp = DC.readWriteHisto(fVV, "timeptetaup/", histName, sf_vv, fout, fVV, "vv_timeptetaUp", true);
  TH1F* vv_timeptetaDown = DC.readWriteHisto(fVV, "timeptetadown/", histName, sf_vv, fout, fVV, "vv_timeptetaDown", true);
  TH1F* vv_jerhfUp = DC.readWriteHisto(fVV, "reljerhfup/", histName, sf_vv, fout, fVV, "vv_jerhfUp", true);
  TH1F* vv_jerhfDown = DC.readWriteHisto(fVV, "reljerhfdown/", histName, sf_vv, fout, fVV, "vv_jerhfDown", true);
  TH1F* vv_relptbbUp = DC.readWriteHisto(fVV, "relptbbup/", histName, sf_vv, fout, fVV, "vv_relptbbUp", true);
  TH1F* vv_relptbbDown = DC.readWriteHisto(fVV, "relptbbdown/", histName, sf_vv, fout, fVV, "vv_relptbbDown", true);
  TH1F* vv_relpthfUp = DC.readWriteHisto(fVV, "relpthfup/", histName, sf_vv, fout, fVV, "vv_relpthfUp", true);
  TH1F* vv_relpthfDown = DC.readWriteHisto(fVV, "relpthfdown/", histName, sf_vv, fout, fVV, "vv_relpthfDown", true);

  TH1F* vv_relstatecUp = DC.readWriteHisto(fVV, "relstatecup/", histName, sf_vv, fout, fVV, "vv_relstatecUp", true);
  TH1F* vv_relstatecDown = DC.readWriteHisto(fVV, "relstatecdown/", histName, sf_vv, fout, fVV, "vv_relstatecDown", true);

  // Absolute statistical uncertainty
  TH1F* vv_absstatUp = DC.readWriteHisto(fVV, "absstatup/", histName, sf_vv, fout, fVV, "vv_absstatUp", true);
  TH1F* vv_absstatDown = DC.readWriteHisto(fVV, "absstatdown/", histName, sf_vv, fout, fVV, "vv_absstatDown", true);

  // Absolute scale uncertainty
  TH1F* vv_abssclUp = DC.readWriteHisto(fVV, "abssclup/", histName, sf_vv, fout, fVV, "vv_abssclUp", true);
  TH1F* vv_abssclDown = DC.readWriteHisto(fVV, "absscldown/", histName, sf_vv, fout, fVV, "vv_abssclDown", true);

  // Absolute MPF bias
  TH1F* vv_absmpfbUp = DC.readWriteHisto(fVV, "absmpfbup/", histName, sf_vv, fout, fVV, "vv_absmpfbUp", true);
  TH1F* vv_absmpfbDown = DC.readWriteHisto(fVV, "absmpfbdown/", histName, sf_vv, fout, fVV, "vv_absmpfbDown", true);

  // LHE scale uncertainties (muF and muR)
  TH1F* vv_lhemuFUp = DC.readWriteHisto(fVV, "base_bc_lhemuf_up/", histName, sf_vv, fout, fVV, "vv_lhemuFUp", true);
  TH1F* vv_lhemuFDown = DC.readWriteHisto(fVV, "base_bc_lhemuf_do/", histName, sf_vv, fout, fVV, "vv_lhemuFDown", true);
  TH1F* vv_lhemuRUp = DC.readWriteHisto(fVV, "base_lhemur_up/", histName, sf_vv, fout, fVV, "vv_lhemuRUp", true);
  TH1F* vv_lhemuRDown = DC.readWriteHisto(fVV, "base_lhemur_do/", histName, sf_vv, fout, fVV, "vv_lhemuRDown", true);

  // b-hadron branching fraction
  TH1F* vv_bHadronBFUp = DC.readWriteHisto(fVV, "base_bfrag_Up/", histName, sf_vv, fout, fVV, "vv_bHadronBFUp", true);
  TH1F* vv_bHadronBFDown = DC.readWriteHisto(fVV, "base_bfrag_do/", histName, sf_vv, fout, fVV, "vv_bHadronBFDown", true);

  // Pileup data/MC corrections
  TH1F* vv_pudataMCUp = DC.readWriteHisto(fVV, "pudatamcup/", histName, sf_vv, fout, fVV, "vv_pudataMCUp", true);
  TH1F* vv_pudataMCDown = DC.readWriteHisto(fVV, "pudatamcdown/", histName, sf_vv, fout, fVV, "vv_pudataMCDown", true);


 

  TH1F* vv_relptec2Up = DC.readWriteHisto(fVV, "relptec2up/", histName, sf_vv, fout, fVV, "vv_relptec2Up", true);
  TH1F* vv_relptec2Down = DC.readWriteHisto(fVV, "relptec2down/", histName, sf_vv, fout, fVV, "vv_relptec2Down", true);

  TH1F* vv_reljerec1Up = DC.readWriteHisto(fVV, "reljerec1up/", histName, sf_vv, fout, fVV, "vv_reljerec1Up", true);
  TH1F* vv_reljerec1Do = DC.readWriteHisto(fVV, "reljerec1down/", histName, sf_vv, fout, fVV, "vv_reljerec1Down", true);

  TH1F* vv_reljerec2Up = DC.readWriteHisto(fVV, "reljerec2up/", histName, sf_vv, fout, fVV, "vv_reljerec2Up", true);
  TH1F* vv_reljerec2Do = DC.readWriteHisto(fVV, "reljerec2down/", histName, sf_vv, fout, fVV, "vv_reljerec2Down", true);

  TH1F* vv_puptrefUp = DC.readWriteHisto(fVV, "puptrefup/", histName, sf_vv, fout, fVV, "vv_puptrefUp", true); // Assuming there's an up variation
  TH1F* vv_puptrefDo = DC.readWriteHisto(fVV, "puptrefdown/", histName, sf_vv, fout, fVV, "vv_puptrefDown", true);
  TH1F* vv_puptec1Up = DC.readWriteHisto(fVV, "puptec1up/", histName, sf_vv, fout, fVV, "vv_puptec1Up", true);
  TH1F* vv_puptec1Do = DC.readWriteHisto(fVV, "puptec1down/", histName, sf_vv, fout, fVV, "vv_puptec1Down", true);

  TH1F* vv_puptec2Up = DC.readWriteHisto(fVV, "puptec2up/", histName, sf_vv, fout, fVV, "vv_puptec2Up", true);
  TH1F* vv_puptec2Do = DC.readWriteHisto(fVV, "puptec2down/", histName, sf_vv, fout, fVV, "vv_puptec2Down", true);


  // External parameters (extp) variations
  TH1F* vv_base_extpUp = DC.readWriteHisto(fVV, "base_extp_up/", histName, sf_vv, fout, fVV, "vv_base_extpUp", true);
  TH1F* vv_base_extpDo = DC.readWriteHisto(fVV, "base_extp_do/", histName, sf_vv, fout, fVV, "vv_base_extpDown", true);

  // Internal parameters (intp) variations
  TH1F* vv_base_intpUp = DC.readWriteHisto(fVV, "base_intp_up/", histName, sf_vv, fout, fVV, "vv_base_intpUp", true);
  TH1F* vv_base_intpDo = DC.readWriteHisto(fVV, "base_intp_do/", histName, sf_vv, fout, fVV, "vv_base_intpDown", true);

  // Cross-section DY corrections (xdyc) variations
  TH1F* vv_base_xdycUp = DC.readWriteHisto(fVV, "base_xdyc_up/", histName, sf_vv, fout, fVV, "vv_base_xdycUp", true);
  TH1F* vv_base_xdycDo = DC.readWriteHisto(fVV, "base_xdyc_do/", histName, sf_vv, fout, fVV, "vv_base_xdycDown", true);

  // Cross-section DYb corrections (xdyb) variations
  TH1F* vv_base_xdybUp = DC.readWriteHisto(fVV, "base_xdyb_up/", histName, sf_vv, fout, fVV, "vv_base_xdybUp", true);
  TH1F* vv_base_xdybDo = DC.readWriteHisto(fVV, "base_xdyb_do/", histName, sf_vv, fout, fVV, "vv_base_xdybDown", true);

  // Muon efficiency (muEff) corrections variations
  TH1F* vv_base_muEffUp = DC.readWriteHisto(fVV, "base_muEff_up/", histName, sf_vv, fout, fVV, "vv_base_muEffUp", true);
  TH1F* vv_base_muEffDo = DC.readWriteHisto(fVV, "base_muEff_do/", histName, sf_vv, fout, fVV, "vv_base_muEffDown", true);
  // PDF variations
  TH1F* vv_base_pdfUp = DC.readWriteHisto(fVV, "base_pdf_Up/", histName, sf_vv, fout, fVV, "vv_base_pdfUp", true);
  TH1F* vv_base_pdfDo = DC.readWriteHisto(fVV, "base_pdf_Do/", histName, sf_vv, fout, fVV, "vv_base_pdfDown", true);
  // Read and write histograms for systematic variations of vv
    TH1F* vv_singpiecalUp = DC.readWriteHisto(fVV,"/singpiecalup/", histName, sf_vv, fout, fVV, "vv_singpiecalUp", true);
  TH1F* vv_singpiecalDown = DC.readWriteHisto(fVV,"/singpiecaldown/", histName, sf_vv, fout, fVV, "vv_singpiecalDown", true);
  TH1F* vv_singpihcalUp = DC.readWriteHisto(fVV,"/singpihcalup/", histName, sf_vv, fout, fVV, "vv_singpihcalUp", true);
  TH1F* vv_singpihcalDown = DC.readWriteHisto(fVV,"/singpihcaldown/", histName, sf_vv, fout, fVV, "vv_singpihcalDown", true);
 
  
normalizeHistogram(vv_bc_statUp, vv);
normalizeHistogram(vv_bc_statDown, vv);
normalizeHistogram(vv_fsrUp, vv);
normalizeHistogram(vv_fsrDown, vv);
normalizeHistogram(vv_isrUp, vv);
normalizeHistogram(vv_isrDown, vv);
normalizeHistogram(vv_base_pdfUp, vv);
normalizeHistogram(vv_base_pdfDo, vv);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  vv_bc_statUp->Write();
  vv_bc_statDown->Write();
  vv_fsrUp->Write();
  vv_fsrDown->Write();
  vv_isrUp->Write();
  vv_isrDown->Write();
  vv_base_pdfUp->Write();
  vv_base_pdfDo->Write();



double unc_vv_ExL = 1.0;
  double unc_vv_ExM = 1.0;
  if(isExL){
    TH1F* vv_yLyMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* vv_yLyMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* vv_yLnMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* vv_yLnMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_vv_ExL = DC.getUncExL(vv_yLyMyT, vv_yLyMnT, vv_yLnMyT, vv_yLnMnT);
  }
  if(isExM){
    TH1F* vv_yMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* vv_yMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_vv_ExM = DC.getUncExM(vv_yMyT, vv_yMnT);
  }

  //QCD MC
  double sf_qcd = 0.03;

  //   TH1F* qcd_dd = DC.readWriteHisto(fQCD_dd, "", qhist, sf_qcd, fout, fQCD_dd, "qcd", true);
     
     TH1F* qcd_dd = DC.readWriteHisto(fQCD, "base/", histName, sf_qcd, fout, fQCD, "qcd", true);
  // double stat_unc_qcd = DC.getStatUnc(qcd_dd, 0);
  // // cout<<"qcd stat unc: "<<stat_unc_qcd<<endl;
  // // cout<<"qcd = "<<qcd_dd->Integral()<<endl;
  // double qcd_unc = DC.getSysUncQcd(fData, fTT, fST, fWJ, fDY,  fVV, histSubDir_+"/", histName, false);
   
  //Data
  double sf_data = 1.0; //should be 1, always
//  TH1F* data_obs = DC.readWriteHisto(fData, baseDir+"/"+histSubDir, histName, sf_data, fout, fData, "data_obs", true);
  TH1F* data_obs = DC.readWriteHisto(fData, "base/", histName, sf_data, fout, fData, "data_obs", true);
  cout<<"data_obs================: "<<data_obs->Integral()<<endl;

//wh
  double sf_wh = 1.0; 
  TH1F* wh = DC.readWriteHisto(fWH, "base/", histName, sf_wh, fout, fTT, label, true);
  TH1F* wh_JESUp = DC.readWriteHisto(fWH, "base_JEC_up/", histName, sf_wh, fout, fTT, label +"_JESUp", true);
  TH1F* wh_JESDown = DC.readWriteHisto(fWH, "base_JEC_do/", histName, sf_wh, fout, fTT, label+"_JESDown", true);
  TH1F* wh_PileupUp = DC.readWriteHisto(fWH, "base_PUWeight_up/", histName, sf_wh, fout, fTT, label+"_PileupUp", true);
  TH1F* wh_PileupDown = DC.readWriteHisto(fWH, "base_PUWeight_do/", histName, sf_wh, fout, fTT, label+"_PileupDown", true);
  TH1F* wh_JERUp = DC.readWriteHisto(fWH, "reljerec1up/", histName, sf_wh, fout, fTT, label+"_JERUp", true); // Adjusted based on systematic naming convention
  TH1F* wh_JERDown = DC.readWriteHisto(fWH, "reljerec1down/", histName, sf_wh, fout, fTT, label+"_JERDown", true); // Adjusted based on systematic naming convention
  TH1F* wh_prefireUp = DC.readWriteHisto(fWH, "base_prefire_up/", histName, sf_wh, fout, fTT, label+"_prefireUp", true);
  TH1F* wh_prefireDown = DC.readWriteHisto(fWH, "base_prefire_do/", histName, sf_wh, fout, fTT, label+"_prefireDown", true); // Corrected 'prefireDo' to 'prefireDown'
  TH1F* wh_bc_statUp = DC.readWriteHisto(fWH, "base_bc_stat_up/", histName, sf_wh, fout, fTT, label+"_bc_statUp", true); // Adjusted based on systematic naming convention
  TH1F* wh_bc_statDown = DC.readWriteHisto(fWH, "base_bc_stat_do/", histName, sf_wh, fout, fTT, label+"_bc_statDown", true); // Adjusted based on systematic naming convention, corrected 'bc_statDo' to 'bc_statDown'
  TH1F* wh_fsrUp = DC.readWriteHisto(fWH, "base_fsr_up/", histName, sf_wh, fout, fTT, label+"_fsrUp", true);
  TH1F* wh_fsrDown = DC.readWriteHisto(fWH, "base_fsr_do/", histName, sf_wh, fout, fTT, label+"_fsrDown", true); // Corrected 'fsrDo' to 'fsrDown'
  TH1F* wh_isrUp = DC.readWriteHisto(fWH, "base_isr_up/", histName, sf_wh, fout, fTT, label+"_isrUp", true);
  TH1F* wh_isrDown = DC.readWriteHisto(fWH, "base_isr_do/", histName, sf_wh, fout, fTT, label+"_isrDown", true); // Corrected 'isrDo' to 'isrDown'
  TH1F* wh_flavorqcdUp = DC.readWriteHisto(fWH, "flavorqcdup/", histName, sf_wh, fout, fTT, label+"_flavorqcdUp", true); // Adjusted for consistency
  TH1F* wh_flavorqcdDown = DC.readWriteHisto(fWH, "flavorqcddown/", histName, sf_wh, fout, fTT, label+"_flavorqcdDown", true); // Corrected 'flavorqcdDo' to 'flavorqcdDown', adjusted for consistency
  // Systematics with direct matches from the list
  TH1F* wh_timeptetaUp = DC.readWriteHisto(fWH, "timeptetaup/", histName, sf_wh, fout, fTT, label+"_timeptetaUp", true);
  TH1F* wh_timeptetaDown = DC.readWriteHisto(fWH, "timeptetadown/", histName, sf_wh, fout, fTT, label+"_timeptetaDown", true);
  TH1F* wh_jerhfUp = DC.readWriteHisto(fWH, "reljerhfup/", histName, sf_wh, fout, fTT, label+"_jerhfUp", true);
  TH1F* wh_jerhfDown = DC.readWriteHisto(fWH, "reljerhfdown/", histName, sf_wh, fout, fTT,label+ "_jerhfDown", true);
  TH1F* wh_relptbbUp = DC.readWriteHisto(fWH, "relptbbup/", histName, sf_wh, fout, fTT, label+"_relptbbUp", true);
  TH1F* wh_relptbbDown = DC.readWriteHisto(fWH, "relptbbdown/", histName, sf_wh, fout, fTT, label+"_relptbbDown", true);
  TH1F* wh_relpthfUp = DC.readWriteHisto(fWH, "relpthfup/", histName, sf_wh, fout, fTT, label+"_relpthfUp", true);
  TH1F* wh_relpthfDown = DC.readWriteHisto(fWH, "relpthfdown/", histName, sf_wh, fout, fTT, label+"_relpthfDown", true);

  TH1F* wh_relstatecUp = DC.readWriteHisto(fWH, "relstatecup/", histName, sf_wh, fout, fTT, label+"_relstatecUp", true);
  TH1F* wh_relstatecDown = DC.readWriteHisto(fWH, "relstatecdown/", histName, sf_wh, fout, fTT, label+"_relstatecDown", true);

  // Absolute statistical uncertainty
  TH1F* wh_absstatUp = DC.readWriteHisto(fWH, "absstatup/", histName, sf_wh, fout, fTT, label+"_absstatUp", true);
  TH1F* wh_absstatDown = DC.readWriteHisto(fWH, "absstatdown/", histName, sf_wh, fout, fTT, label+"_absstatDown", true);

  // Absolute scale uncertainty
  TH1F* wh_abssclUp = DC.readWriteHisto(fWH, "abssclup/", histName, sf_wh, fout, fTT, label+"_abssclUp", true);
  TH1F* wh_abssclDown = DC.readWriteHisto(fWH, "absscldown/", histName, sf_wh, fout, fTT, label+"_abssclDown", true);

  // Absolute MPF bias
  TH1F* wh_absmpfbUp = DC.readWriteHisto(fWH, "absmpfbup/", histName, sf_wh, fout, fTT, label+"_absmpfbUp", true);
  TH1F* wh_absmpfbDown = DC.readWriteHisto(fWH, "absmpfbdown/", histName, sf_wh, fout, fTT, label+"_absmpfbDown", true);

  // LHE scale uncertainties (muF and muR)
  TH1F* wh_lhemuFUp = DC.readWriteHisto(fWH, "base_bc_lhemuf_up/", histName, sf_wh, fout, fTT, label+"_lhemuFUp", true);
  TH1F* wh_lhemuFDown = DC.readWriteHisto(fWH, "base_bc_lhemuf_do/", histName, sf_wh, fout, fTT, label+"_lhemuFDown", true);
  TH1F* wh_lhemuRUp = DC.readWriteHisto(fWH, "base_lhemur_up/", histName, sf_wh, fout, fTT, label+"_lhemuRUp", true);
  TH1F* wh_lhemuRDown = DC.readWriteHisto(fWH, "base_lhemur_do/", histName, sf_wh, fout, fTT, label+"_lhemuRDown", true);

  // b-hadron branching fraction
  TH1F* wh_bHadronBFUp = DC.readWriteHisto(fWH, "base_bfrag_Up/", histName, sf_wh, fout, fTT, label+"_bHadronBFUp", true);
  TH1F* wh_bHadronBFDown = DC.readWriteHisto(fWH, "base_bfrag_do/", histName, sf_wh, fout, fTT, label+"_bHadronBFDown", true);

  // Pileup data/MC corrections
  TH1F* wh_pudataMCUp = DC.readWriteHisto(fWH, "pudatamcup/", histName, sf_wh, fout, fTT, label+"_pudataMCUp", true);
  TH1F* wh_pudataMCDown = DC.readWriteHisto(fWH, "pudatamcdown/", histName, sf_wh, fout, fTT, label+"_pudataMCDown", true);




  TH1F* wh_relptec2Up = DC.readWriteHisto(fWH, "relptec2up/", histName, sf_wh, fout, fTT, label+"_relptec2Up", true);
  TH1F* wh_relptec2Down = DC.readWriteHisto(fWH, "relptec2down/", histName, sf_wh, fout, fTT, label+"_relptec2Down", true);

  TH1F* wh_reljerec1Up = DC.readWriteHisto(fWH, "reljerec1up/", histName, sf_wh, fout, fTT, label+"_reljerec1Up", true);
  TH1F* wh_reljerec1Do = DC.readWriteHisto(fWH, "reljerec1down/", histName, sf_wh, fout, fTT, label+"_reljerec1Down", true);

  TH1F* wh_reljerec2Up = DC.readWriteHisto(fWH, "reljerec2up/", histName, sf_wh, fout, fTT, label+"_reljerec2Up", true);
  TH1F* wh_reljerec2Do = DC.readWriteHisto(fWH, "reljerec2down/", histName, sf_wh, fout, fTT, label+"_reljerec2Down", true);

  TH1F* wh_puptrefUp = DC.readWriteHisto(fWH, "puptrefup/", histName, sf_wh, fout, fTT, label+"_puptrefUp", true); // Assuming there's an up variation
  TH1F* wh_puptrefDo = DC.readWriteHisto(fWH, "puptrefdown/", histName, sf_wh, fout, fTT,label+"_puptrefDown", true);
  TH1F* wh_puptec1Up = DC.readWriteHisto(fWH, "puptec1up/", histName, sf_wh, fout, fTT, label+"_puptec1Up", true);
  TH1F* wh_puptec1Do = DC.readWriteHisto(fWH, "puptec1down/", histName, sf_wh, fout, fTT, label+"_puptec1Down", true);

  TH1F* wh_puptec2Up = DC.readWriteHisto(fWH, "puptec2up/", histName, sf_wh, fout, fTT, label+"_puptec2Up", true);
  TH1F* wh_puptec2Do = DC.readWriteHisto(fWH, "puptec2down/", histName, sf_wh, fout, fTT, label+"_puptec2Down", true);


  // External parameters (extp) variations
  TH1F* wh_base_extpUp = DC.readWriteHisto(fWH, "base_extp_up/", histName, sf_wh, fout, fTT, label+"_base_extpUp", true);
  TH1F* wh_base_extpDo = DC.readWriteHisto(fWH, "base_extp_do/", histName, sf_wh, fout, fTT, label+"_base_extpDown", true);

  // Internal parameters (intp) variations
  TH1F* wh_base_intpUp = DC.readWriteHisto(fWH, "base_intp_up/", histName, sf_wh, fout, fTT, label+"_base_intpUp", true);
  TH1F* wh_base_intpDo = DC.readWriteHisto(fWH, "base_intp_do/", histName, sf_wh, fout, fTT, label+"_base_intpDown", true);

  // Cross-section DY corrections (xdyc) variations
  TH1F* wh_base_xdycUp = DC.readWriteHisto(fWH, "base_xdyc_up/", histName, sf_wh, fout, fTT, label+"_base_xdycUp", true);
  TH1F* wh_base_xdycDo = DC.readWriteHisto(fWH, "base_xdyc_do/", histName, sf_wh, fout, fTT, label+"_base_xdycDown", true);

  // Cross-section DYb corrections (xdyb) variations
  TH1F* wh_base_xdybUp = DC.readWriteHisto(fWH, "base_xdyb_up/", histName, sf_wh, fout, fTT, label+"_base_xdybUp", true);
  TH1F* wh_base_xdybDo = DC.readWriteHisto(fWH, "base_xdyb_do/", histName, sf_wh, fout, fTT, label+"_base_xdybDown", true);

  // Muon efficiency (muEff) corrections variations
  TH1F* wh_base_muEffUp = DC.readWriteHisto(fWH, "base_muEff_up/", histName, sf_wh, fout, fTT, label+"_base_muEffUp", true);
  TH1F* wh_base_muEffDo = DC.readWriteHisto(fWH, "base_muEff_do/", histName, sf_wh, fout, fTT, label+"_base_muEffDown", true);
  // PDF variations
  TH1F* wh_base_pdfUp = DC.readWriteHisto(fWH, "base_pdf_Up/", histName, sf_wh, fout, fTT, label+"_base_pdfUp", true);
  TH1F* wh_base_pdfDo = DC.readWriteHisto(fWH, "base_pdf_Do/", histName, sf_wh, fout, fTT,label+ "_base_pdfDown", true);

  TH1F* wh_singpiecalUp = DC.readWriteHisto(fWH,"/singpiecalup/", histName, sf_wh, fout, fTT, "wh_singpiecalUp", true);
  TH1F* wh_singpiecalDown = DC.readWriteHisto(fWH,"/singpiecaldown/", histName, sf_wh, fout, fTT, "wh_singpiecalDown", true);
  TH1F* wh_singpihcalUp = DC.readWriteHisto(fWH, "/singpihcalup/", histName, sf_wh, fout, fTT, "wh_singpihcalUp", true);
  TH1F* wh_singpihcalDown = DC.readWriteHisto(fWH,"/singpihcaldown/", histName, sf_wh, fout, fTT, "wh_singpihcalDown", true);
  
normalizeHistogram(wh_bc_statUp, wh);
normalizeHistogram(wh_bc_statDown, wh);
normalizeHistogram(wh_fsrUp, wh);
normalizeHistogram(wh_fsrDown, wh);
normalizeHistogram(wh_isrUp, wh);
normalizeHistogram(wh_isrDown, wh);
normalizeHistogram(wh_base_pdfUp, wh);
normalizeHistogram(wh_base_pdfDo, wh);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  wh_bc_statUp->Write();
  wh_bc_statDown->Write();
  wh_fsrUp->Write();
  wh_fsrDown->Write();
  wh_isrUp->Write();
  wh_isrDown->Write();
  wh_base_pdfUp->Write();
  wh_base_pdfDo->Write();


 double unc_wh_ExL = 1.0;
  double unc_wh_ExM = 1.0;
  if(isExL){
    TH1F* wh_yLyMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT, sf_wh);
    TH1F* wh_yLyMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT, sf_wh);
    TH1F* wh_yLnMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT, sf_wh);
    TH1F* wh_yLnMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT, sf_wh);
    unc_wh_ExL = DC.getUncExL(wh_yLyMyT, wh_yLyMnT, wh_yLnMyT, wh_yLnMnT);
  }
  if(isExM){
    TH1F* wh_yMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT, sf_wh);
    TH1F* wh_yMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT, sf_wh);
    unc_wh_ExM = DC.getUncExM(wh_yMyT, wh_yMnT);
  }
  

//open input template data card
  ifstream in;
  char* c = new char[1160];
  in.open("MyTemplateDataCard.txt");
  //create output data card for 13 TeV
  string outDataCard = "datacard_hcs_2016_WH.txt";
  string histName_str(histSubDir_+TString("_")+histName+workingpoint);
  if(isMuChannel) outDataCard = "datacard_hcs_2016_mu_"+histName_str+"_WH%d.txt"; 
  else outDataCard = "datacard_hcs_2016_ele_"+histName_str+"_WH%d.txt";
  ofstream out(Form(outDataCard.c_str(), mass));
  out.precision(8);

  time_t secs=time(0);
  tm *t=localtime(&secs);
 while (in.good()){
    in.getline(c,1160,'\n');
    if (in.good()){
      string line(c);
      if(line.find("Date")!=string::npos){
        string day = string(Form("%d",t->tm_mday));
        string month = string(Form("%d",t->tm_mon+1));
        string year = string(Form("%d",t->tm_year+11160));
        line.replace( line.find("XXX") , 3 , day+"/"+month+"/"+year);
        out << line << endl;
      }
      else if(line.find("Description")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        line.replace( line.find("ZZZ") , 3 , string(Form("%f", totLumi)) ); 
        line.replace( line.find("CCC") , 3 , string(Form("%s", string(channelName).c_str())) ); 
        out << line << endl;
      }
      else if(line.find("shapes")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(TString("Shapes_hcs_2016_")+channelName+TString("_")+histSubDir_+TString("_")+workingpoint+histName+TString("_")+label));
        out << line << endl;
      }
      else if(line.find("Observation")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(Form("%.0f", data_obs->Integral())));
        out << line << endl;
      }
      else if(line.find("process")!=string::npos && line.find("WH")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        out << line << endl;
      }
      else if(line.find("rate")!=string::npos){
        string rate = "rate               ";  
        string space = "     ";
        out << rate ;
        out << space << wh->Integral()
            << space << ttbar->Integral()
            << space << wjet->Integral()
            << space << zjet->Integral()
            << space << stop->Integral()
            << space << vv->Integral()
	   << space << qcd_dd->Integral()
            << endl;
      }
    else if (line.find("CMS_pileup") != string::npos) {
        DC.replaceSystematicUnc(line,wh, wh_PileupUp, wh_PileupDown, ttbar, ttbar_PileupUp, ttbar_PileupDown, wjet, wjet_PileupUp, wjet_PileupDown, zjet, zjet_PileupUp, zjet_PileupDown, stop, stop_PileupUp, stop_PileupDown, vv, vv_PileupUp, vv_PileupDown, out);
    }
    else if (line.find("CMS_scale_j") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_JESUp, wh_JESDown, ttbar, ttbar_JESUp, ttbar_JESDown, wjet, wjet_JESUp, wjet_JESDown, zjet, zjet_JESUp, zjet_JESDown, stop, stop_JESUp, stop_JESDown, vv, vv_JESUp, vv_JESDown, out);
    }
    else if (line.find("CMS_res_j") != string::npos) {
       DC.replaceSystematicUnc(line,wh, wh_JERUp, wh_JERDown, ttbar, ttbar_JERUp, ttbar_JERDown, wjet, wjet_JERUp, wjet_JERDown, zjet, zjet_JERUp, zjet_JERDown, stop, stop_JERUp, stop_JERDown, vv, vv_JERUp, vv_JERDown, out);
    }
    else if (line.find("CMS_timepteta") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_timeptetaUp, wh_timeptetaDown, ttbar, ttbar_timeptetaUp, ttbar_timeptetaDown, wjet, wjet_timeptetaUp, wjet_timeptetaDown, zjet, zjet_timeptetaUp, zjet_timeptetaDown, stop, stop_timeptetaUp, stop_timeptetaDown, vv, vv_timeptetaUp, vv_timeptetaDown, out);
    }
    else if (line.find("CMS_jerhf") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_jerhfUp, wh_jerhfDown, ttbar, ttbar_jerhfUp, ttbar_jerhfDown, wjet, wjet_jerhfUp, wjet_jerhfDown, zjet, zjet_jerhfUp, zjet_jerhfDown, stop, stop_jerhfUp, stop_jerhfDown, vv, vv_jerhfUp, vv_jerhfDown, out);
    }
    else if (line.find("CMS_relptbb") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_relptbbUp, wh_relptbbDown, ttbar, ttbar_relptbbUp, ttbar_relptbbDown, wjet, wjet_relptbbUp, wjet_relptbbDown, zjet, zjet_relptbbUp, zjet_relptbbDown, stop, stop_relptbbUp, stop_relptbbDown, vv, vv_relptbbUp, vv_relptbbDown, out);
    }
    else if (line.find("CMS_relpthf") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_relpthfUp, wh_relpthfDown, ttbar, ttbar_relpthfUp, ttbar_relpthfDown, wjet, wjet_relpthfUp, wjet_relpthfDown, zjet, zjet_relpthfUp, zjet_relpthfDown, stop, stop_relpthfUp, stop_relpthfDown, vv, vv_relpthfUp, vv_relpthfDown, out);
    }
    else if (line.find("CMS_relstatec") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_relstatecUp, wh_relstatecDown, ttbar, ttbar_relstatecUp, ttbar_relstatecDown, wjet, wjet_relstatecUp, wjet_relstatecDown, zjet, zjet_relstatecUp, zjet_relstatecDown, stop, stop_relstatecUp, stop_relstatecDown, vv, vv_relstatecUp, vv_relstatecDown, out);
    }
    else if (line.find("CMS_absstat") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_absstatUp, wh_absstatDown, ttbar, ttbar_absstatUp, ttbar_absstatDown, wjet, wjet_absstatUp, wjet_absstatDown, zjet, zjet_absstatUp, zjet_absstatDown, stop, stop_absstatUp, stop_absstatDown, vv, vv_absstatUp, vv_absstatDown, out);
    }
    else if (line.find("CMS_absscl") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_abssclUp, wh_abssclDown, ttbar, ttbar_abssclUp, ttbar_abssclDown, wjet, wjet_abssclUp, wjet_abssclDown, zjet, zjet_abssclUp, zjet_abssclDown, stop, stop_abssclUp, stop_abssclDown, vv, vv_abssclUp, vv_abssclDown, out);
    }
    else if (line.find("CMS_absmpfb") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_absmpfbUp, wh_absmpfbDown, ttbar, ttbar_absmpfbUp, ttbar_absmpfbDown, wjet, wjet_absmpfbUp, wjet_absmpfbDown, zjet, zjet_absmpfbUp, zjet_absmpfbDown, stop, stop_absmpfbUp, stop_absmpfbDown, vv, vv_absmpfbUp, vv_absmpfbDown, out);
    }
    else if (line.find("CMS_lhemuF") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_lhemuFUp, wh_lhemuFDown, ttbar, ttbar_lhemuFUp, ttbar_lhemuFDown, wjet, wjet_lhemuFUp, wjet_lhemuFDown, zjet, zjet_lhemuFUp, zjet_lhemuFDown, stop, stop_lhemuFUp, stop_lhemuFDown, vv, vv_lhemuFUp, vv_lhemuFDown, out);
    }
    else if (line.find("CMS_lhemuR") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_lhemuRUp, wh_lhemuRDown, ttbar, ttbar_lhemuRUp, ttbar_lhemuRDown, wjet, wjet_lhemuRUp, wjet_lhemuRDown, zjet, zjet_lhemuRUp, zjet_lhemuRDown, stop, stop_lhemuRUp, stop_lhemuRDown, vv, vv_lhemuRUp, vv_lhemuRDown, out);
    }
    else if (line.find("CMS_bHadronBF") != string::npos) {
        DC.replaceSystematicUnc(line,wh, wh_bHadronBFUp, wh_bHadronBFDown, ttbar, ttbar_bHadronBFUp, ttbar_bHadronBFDown, wjet, wjet_bHadronBFUp, wjet_bHadronBFDown, zjet, zjet_bHadronBFUp, zjet_bHadronBFDown, stop, stop_bHadronBFUp, stop_bHadronBFDown, vv, vv_bHadronBFUp, vv_bHadronBFDown, out);
    }
    else if (line.find("CMS_pudataMC") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_pudataMCUp, wh_pudataMCDown, ttbar, ttbar_pudataMCUp, ttbar_pudataMCDown, wjet, wjet_pudataMCUp, wjet_pudataMCDown, zjet, zjet_pudataMCUp, zjet_pudataMCDown, stop, stop_pudataMCUp, stop_pudataMCDown, vv, vv_pudataMCUp, vv_pudataMCDown, out);
    }
    else if (line.find("CMS_relptec2") != string::npos) {
        DC.replaceSystematicUnc(line, wh, wh_relptec2Up, wh_relptec2Down, ttbar, ttbar_relptec2Up, ttbar_relptec2Down, wjet, wjet_relptec2Up, wjet_relptec2Down, zjet, zjet_relptec2Up, zjet_relptec2Down, stop, stop_relptec2Up, stop_relptec2Down, vv, vv_relptec2Up, vv_relptec2Down, out);
    }
    else if (line.find("CMS_flavorqcd") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_flavorqcdUp, wh_flavorqcdDown, ttbar, ttbar_flavorqcdUp, ttbar_flavorqcdDown, wjet, wjet_flavorqcdUp, wjet_flavorqcdDown, zjet, zjet_flavorqcdUp, zjet_flavorqcdDown, stop, stop_flavorqcdUp, stop_flavorqcdDown, vv, vv_flavorqcdUp, vv_flavorqcdDown, out);
    }
    else { // Default without changes
        out << line << endl;
    }
}

  } 
  if(isExL){
    string rate = "CMS_eff_cExL       lnN";  
    string space = "     ";
    out << rate ;
    out << space <<string(Form("%.3f", unc_wh_ExL))
        << space <<string(Form("%.3f", unc_ttbar_ExL))
        << space <<string(Form("%.3f", unc_wjet_ExL))
        << space <<string(Form("%.3f", unc_zjet_ExL))
        << space <<string(Form("%.3f", unc_stop_ExL))
        << space <<string(Form("%.3f", unc_vv_ExL))
        << space <<string(Form("%.3f", 1.0))
        << endl;
  }
  if(isExM){
    string rate = "CMS_eff_cExM       lnN";  
    string space = "     ";
    out << rate ;
    out << space <<string(Form("%.3f", unc_wh_ExM))
        << space <<string(Form("%.3f", unc_ttbar_ExM))
        << space <<string(Form("%.3f", unc_wjet_ExM))
        << space <<string(Form("%.3f", unc_zjet_ExM))
        << space <<string(Form("%.3f", unc_stop_ExM))
        << space <<string(Form("%.3f", unc_vv_ExM))
        << space <<string(Form("%.3f", 1.0))
        << endl;
  }
  out<<"* autoMCStats 0 1"<<endl;
  out<<"qcdrate rateParam * qcd 1.0 [0.0,2.0]"<<endl;
  out.close();
  in.close();
  fout->Close();
}

void MyHPlusDataCardMakerNano(TString inFileDir="/afs/cern.ch/work/s/savarghe/private/histoproducer/CMSSW_12_3_0_pre6/src/2016/muon/mass160/",
			      TString syear="2016", 
			      TString histSubDir_="KinFit", 
			      TString histName="bdt", 
			      TString channelName="mu", 
			      int mass=160, 
			      TString label="WH160", 
			      TString hPlusFileName="all_HplusM160.root")
  {

  bool isBinStat = false;  int nonStatBins = 30;
  MyHPlusDataCardMaker DC;
  //TString baseDir = "topPtWeight";
  TString baseDir = "base";
  TString histSubDir = "/Iso/";
  bool isMuChannel = false; 
  if(channelName=="mu") isMuChannel = true;
  inFileDir = inFileDir + "/" + syear;
  int year = syear.Atoi();
  double totLumi = 35.9; //2016
  float lumiUnc = 1.012;//2.5% for 2016 following https://twiki.cern.ch/twiki/bin/viewauth/CMS/TWikiLUM
  if(year==2016){
    totLumi = 41.5; // 2016
    lumiUnc = 1.023; //
  }
  if(year==2016){
    totLumi = 59.7; //2016
    lumiUnc = 1.025; //
  }
  histName += channelName;
  
  printf("==== Year : %d ======\n",year);
  ///INPUT FILES
  TFile* fData    = TFile::Open(inFileDir+"/UL16histlistBDTTTbarP160postchannel.root");
  //bkg
  TFile* fVV      = TFile::Open(inFileDir+"/UL16histlistBDTVV160postchannel.root");
  TFile* fDY      = TFile::Open(inFileDir+"/UL16histlistBDTDY160postchannel.root  ");
  TFile* fWJ      = TFile::Open(inFileDir+"/UL16histlistBDTWjets160postchannel.root  ");
  //TFile* fQCD     = TFile::Open(inFileDir+"/all_QCD.root");
  TFile* fST      = TFile::Open(inFileDir+"/UL16histlistBDTST160postchannel.root");
  TFile* fTT      = TFile::Open(inFileDir+"/UL16histlistBDTTTbarP160postchannel.root");
  //signal
  TFile *fWH  = TFile::Open(inFileDir+"/UL16histlistBDTHplusM160160postchannel.root");
  TString sigFile = hPlusFileName;
  //data driven qcd
  //TFile* fQCD_dd = TFile::Open(inFileDir+"/all_QCDdd.root"); 
  
  //OUTPUT FILE
  TFile *fout = new TFile(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+histName+TString("_")+label+TString("_")+syear+TString(".root"), "RECREATE");

  //For one extra NP
  bool isExL = false;
  bool isExM = false;
  if(histName.Contains("ExL")) isExL = true;
  if(histName.Contains("ExM")) isExM = true;

  //ttbar
  double sf_ttbar = 1.0; 
  baseDir = "TTbar";
  TH1F* ttbar = DC.readWriteHisto(fTT, "base/", histName, sf_ttbar, fout, fTT,  "ttbar", true);
  TH1F* ttbar_JESUp = DC.readWriteHisto(fTT, "jecUp/", histName, sf_ttbar, fout, fTT, "ttbar_JESUp", true);
  TH1F* ttbar_JESDown = DC.readWriteHisto(fTT, "jecDo/", histName, sf_ttbar, fout, fTT, "ttbar_JESDown", true);
  TH1F* ttbar_PileupUp = DC.readWriteHisto(fTT, "puUp/", histName, sf_ttbar, fout, fTT, "ttbar_PileupUp", true);
  TH1F* ttbar_PileupDown = DC.readWriteHisto(fTT, "puDo/", histName, sf_ttbar, fout, fTT, "ttbar_PileupDown", true);
  TH1F* ttbar_JERUp = DC.readWriteHisto(fTT, "jerUp/", histName, sf_ttbar, fout, fTT, "ttbar_JERUp", true);
  TH1F* ttbar_jerhfDown = DC.readWriteHisto(fTT, "jerDo/", histName, sf_ttbar, fout, fTT, "ttbar_jerhfDown", true);
  // TH1F* ttbar_topPtUp = DC.readWriteHisto(fTT, "TopPtPlus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_topPtUp", true);
  // TH1F* ttbar_topPtDown = DC.readWriteHisto(fTT, "TopPtMinus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_topPtDown", true);
  TH1F* ttbar_prefireUp = DC.readWriteHisto(fTT, "prefireUp/", histName, sf_ttbar, fout, fTT, "ttbar_prefireUp", true);
  TH1F* ttbar_prefireDo = DC.readWriteHisto(fTT, "prefireDo/", histName, sf_ttbar, fout, fTT, "ttbar_prefireDown", true);
  //TH1F* ttbar_lepEffUp = DC.readWriteHisto(fTT, "lepEffUp/", histName, sf_ttbar, fout, fTT, "ttbar_lepEffUp", true);
  //TH1F* ttbar_lepEffDo = DC.readWriteHisto(fTT, "lepEffDo/", histName, sf_ttbar, fout, fTT, "ttbar_lepEffDown", true);
  TH1F* ttbar_bc_statUp = DC.readWriteHisto(fTT, "bc_statUp/", histName, sf_ttbar, fout, fTT, "ttbar_bc_statUp", true);
  TH1F* ttbar_bc_statDown = DC.readWriteHisto(fTT, "bc_statDo/", histName, sf_ttbar, fout, fTT, "ttbar_bc_statDown", true);
  TH1F* ttbar_fsrUp = DC.readWriteHisto(fWJ, "fsrUp/", histName, sf_ttbar, fout, fTT, "ttbar_fsrUp", true);
  TH1F* ttbar_fsrDown = DC.readWriteHisto(fWJ, "fsrDo/", histName, sf_ttbar, fout, fTT, "ttbar_fsrDown", true);  
if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *ttbar_bin_stat_Up = DC.readWriteHisto(fTT, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT, Form("ttbar_CMS_stat_cat1_ttbar_bin_%dUp",ibin), true);
      TH1F *ttbar_bin_stat_Down = DC.readWriteHisto(fTT, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT, Form("ttbar_CMS_stat_cat1_ttbar_bin_%dDown",ibin), true);
    }
  }
  
  double unc_ttbar_ExL = 1.0;
  double unc_ttbar_ExM = 1.0;
  if(isExL){
    TH1F* ttbar_yLyMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* ttbar_yLyMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* ttbar_yLnMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* ttbar_yLnMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_ttbar_ExL = DC.getUncExL(ttbar_yLyMyT, ttbar_yLyMnT, ttbar_yLnMyT, ttbar_yLnMnT);
  }
  if(isExM){
    TH1F* ttbar_yMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* ttbar_yMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_ttbar_ExM = DC.getUncExM(ttbar_yMyT, ttbar_yMnT);
  }

  // double sf_ttbar_cp5Up = 1; 
  // TH1F* ttbar_cp5Up = DC.readWriteHisto(fTT, baseDir+"/cp5up"+histSubDir, histName, sf_ttbar_cp5Up, fout, fTT, "ttbar_CP5_ttUp", true, true, ttbar);
  // double sf_ttbar_cp5Down = 1; 
  // TH1F* ttbar_cp5Down = DC.readWriteHisto(fTT, baseDir+"/cp5down"+histSubDir, histName, sf_ttbar_cp5Down, fout, fTT, "ttbar_CP5_ttDown", true, true, ttbar);
  // double sf_ttbar_mtop1715 = 1; 
  // TH1F* ttbar_mtop1715 = DC.readWriteHisto(fTT, baseDir+"/mtopup"+histSubDir, histName, sf_ttbar_mtop1715, fout, fTT, "ttbar_topMass_ttUp", true, true, ttbar);
  // double sf_ttbar_mtop1735 = 1; 
  // TH1F* ttbar_mtop1735 = DC.readWriteHisto(fTT, baseDir+"/mtopdown"+histSubDir, histName, sf_ttbar_mtop1735, fout, fTT, "ttbar_topMass_ttDown", true, true, ttbar);
  // double sf_ttbar_matchingUp = 1; 
  // TH1F* ttbar_matchingUp = DC.readWriteHisto(fTT, baseDir+"/hdampup"+histSubDir, histName, sf_ttbar_matchingUp, fout, fTT, "ttbar_hDamp_ttUp", true, true, ttbar);
  // double sf_ttbar_matchingDown = 1; 
  // TH1F* ttbar_matchingDown = DC.readWriteHisto(fTT, baseDir+"/hdampdown"+histSubDir, histName, sf_ttbar_matchingDown, fout, fTT, "ttbar_hDamp_ttDown", true, true, ttbar);

  //w+jets
  double sf_wjet = 1;
  TH1F* wjet = DC.readWriteHisto(fWJ,"base/", histName, sf_wjet, fout, fWJ, "wjet", true);
  TH1F* wjet_JESUp = DC.readWriteHisto(fWJ, "jecUp/", histName, sf_wjet, fout, fWJ, "wjet_JESUp", true);
  TH1F* wjet_JESDown = DC.readWriteHisto(fWJ, "jecDo/", histName, sf_wjet, fout, fWJ, "wjet_JESDown", true);
  TH1F* wjet_PileupUp = DC.readWriteHisto(fWJ, "puUp/", histName, sf_wjet, fout, fWJ, "wjet_PileupUp", true);
  TH1F* wjet_PileupDown = DC.readWriteHisto(fWJ, "puDo/", histName, sf_wjet, fout, fWJ, "wjet_PileupDown", true);
  TH1F* wjet_JERUp = DC.readWriteHisto(fWJ, "jerUp/", histName, sf_wjet, fout, fWJ, "wjet_JERUp", true);
  TH1F* wjet_jerhfDown = DC.readWriteHisto(fWJ, "jerDo/", histName, sf_wjet, fout, fWJ, "wjet_jerhfDown", true);
  TH1F* wjet_prefireUp = DC.readWriteHisto(fWJ, "prefireUp/", histName, sf_wjet, fout, fWJ, "wjet_prefireUp", true);
  TH1F* wjet_prefireDo = DC.readWriteHisto(fWJ, "prefireDo/", histName, sf_wjet, fout, fWJ, "wjet_prefireDown", true);
  //TH1F* wjet_lepEffUp = DC.readWriteHisto(fWJ, "lepEffUp/", histName, sf_wjet, fout, fWJ, "wjet_lepEffUp", true);
  //TH1F* wjet_lepEffDo = DC.readWriteHisto(fWJ, "lepEffDo/", histName, sf_wjet, fout, fWJ, "wjet_lepEffDown", true);
  TH1F* wjet_bc_statUp = DC.readWriteHisto(fWJ, "bc_statUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_statUp", true);
  TH1F* wjet_bc_statDown = DC.readWriteHisto(fWJ, "bc_statDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_statDown", true);
  // TH1F* wjet_bc_puUp = DC.readWriteHisto(fWJ, "bc_puUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_puUp", true);
  // TH1F* wjet_bc_puDo = DC.readWriteHisto(fWJ, "bc_puDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_puDown", true);
  // TH1F* wjet_bc_muidUp = DC.readWriteHisto(fWJ, "bc_muidDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_muidUp", true);
  // TH1F* wjet_bc_muidDo = DC.readWriteHisto(fWJ, "bc_muidDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_muidDown", true);
  // TH1F* wjet_bc_lhemufUp = DC.readWriteHisto(fWJ, "bc_lhemufUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_lhemufUp", true);
  // TH1F* wjet_bc_lhemufDo = DC.readWriteHisto(fWJ, "bc_lhemufDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_lhemufDown", true);
  // TH1F* wjet_bc_lhemurUp = DC.readWriteHisto(fWJ, "bc_lhemurUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_lhemurUp", true);
  // TH1F* wjet_bc_lhemurDo = DC.readWriteHisto(fWJ, "bc_lhemurDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_lhemurDown", true);
  // TH1F* wjet_bc_isrUp = DC.readWriteHisto(fWJ, "bc_isrUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_isrUp", true);
  // TH1F* wjet_bc_isrDo = DC.readWriteHisto(fWJ, "bc_isrDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_isrDown", true);
  // TH1F* wjet_bc_fsrUp = DC.readWriteHisto(fWJ, "bc_fsrUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_fsrUp", true);
  // TH1F* wjet_bc_fsrDo = DC.readWriteHisto(fWJ, "bc_fsrDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_fsrDown", true);
  // TH1F* wjet_bc_xdyUp = DC.readWriteHisto(fWJ, "bc_xdyUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_xdyUp", true);
  // TH1F* wjet_bc_xdyDo = DC.readWriteHisto(fWJ, "bc_xdyDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_xdyDown", true);
  // TH1F* wjet_bc_xstUp = DC.readWriteHisto(fWJ, "bc_xstUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_xstUp", true);
  // TH1F* wjet_bc_xstDo = DC.readWriteHisto(fWJ, "bc_xstDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_xstDown", true);
  // TH1F* wjet_bc_xwjUp = DC.readWriteHisto(fWJ, "bc_xwjUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_xwjUp", true);
  // TH1F* wjet_bc_xwjDo = DC.readWriteHisto(fWJ, "bc_xwjDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_xwjDown", true);
  // TH1F* wjet_bc_xttUp = DC.readWriteHisto(fWJ, "bc_xttUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_xttUp", true);
  // TH1F* wjet_bc_xttDo = DC.readWriteHisto(fWJ, "bc_xttDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_xttDown", true);
  // TH1F* wjet_bc_jesUp = DC.readWriteHisto(fWJ, "bc_jesUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_jesUp", true);
  // TH1F* wjet_bc_jesDo = DC.readWriteHisto(fWJ, "bc_jesDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_jesDown", true);
  // TH1F* wjet_bc_jerUp = DC.readWriteHisto(fWJ, "bc_jerUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_jerUp", true);
  // TH1F* wjet_bc_jerDo = DC.readWriteHisto(fWJ, "bc_jerDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_jerDown", true);
  // TH1F* wjet_bc_bfragUp = DC.readWriteHisto(fWJ, "bc_bfragUp/", histName, sf_wjet, fout, fWJ, "wjet_bc_bfragUp", true);
  // TH1F* wjet_bc_bfragDo = DC.readWriteHisto(fWJ, "bc_bfragDo/", histName, sf_wjet, fout, fWJ, "wjet_bc_bfragDown", true);
  TH1F* wjet_fsrUp = DC.readWriteHisto(fWJ, "fsrUp/", histName, sf_wjet, fout, fWJ, "wjet_fsrUp", true);
  TH1F* wjet_fsrDown = DC.readWriteHisto(fWJ, "fsrDo/", histName, sf_wjet, fout, fWJ, "wjet_fsrDown", true);
  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *wjet_bin_stat_Up = DC.readWriteHisto(fWJ, baseDir+"/base"+histSubDir, histName, sf_wjet, fout, fTT, Form("wjet_CMS_stat_cat1_wjet_bin_%dUp",ibin), true);
      TH1F *wjet_bin_stat_Do = DC.readWriteHisto(fWJ, baseDir+"/base"+histSubDir, histName, sf_wjet, fout, fTT, Form("wjet_CMS_stat_cat1_wjet_bin_%dDown",ibin), true);
    }
  }

  double unc_wjet_ExL = 1.0;
  double unc_wjet_ExM = 1.0;
  if(isExL){
    TH1F* wjet_yLyMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* wjet_yLyMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* wjet_yLnMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* wjet_yLnMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_wjet_ExL = DC.getUncExL(wjet_yLyMyT, wjet_yLyMnT, wjet_yLnMyT, wjet_yLnMnT);
  }
  if(isExM){
    TH1F* wjet_yMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* wjet_yMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_wjet_ExM = DC.getUncExM(wjet_yMyT, wjet_yMnT);
  }

  //Z+Jets
  double sf_zjet = 1;
  //baseDir = "base";
  TH1F* zjet = DC.readWriteHisto(fDY,"base/", histName, sf_zjet, fout, fDY, "zjet", true);
  TH1F* zjet_JESUp = DC.readWriteHisto(fDY, "jecUp/", histName, sf_zjet, fout, fDY, "zjet_JESUp", true);
  TH1F* zjet_JESDown = DC.readWriteHisto(fDY, "jecDo/", histName, sf_zjet, fout, fDY, "zjet_JESDown", true);
  TH1F* zjet_PileupUp = DC.readWriteHisto(fDY, "puUp/", histName, sf_zjet, fout, fDY, "zjet_PileupUp", true);
  TH1F* zjet_PileupDown = DC.readWriteHisto(fDY, "puDo/", histName, sf_zjet, fout, fDY, "zjet_PileupDown", true);
  TH1F* zjet_JERUp = DC.readWriteHisto(fDY, "jerUp/", histName, sf_zjet, fout, fDY, "zjet_JERUp", true);
  TH1F* zjet_jerhfDown = DC.readWriteHisto(fDY, "jerDo/", histName, sf_zjet, fout, fDY, "zjet_jerhfDown", true);
  TH1F* zjet_prefireUp = DC.readWriteHisto(fDY, "prefireUp/", histName, sf_zjet, fout, fDY, "zjet_prefireUp", true);
  TH1F* zjet_prefireDo = DC.readWriteHisto(fDY, "prefireDo/", histName, sf_zjet, fout, fDY, "zjet_prefireDown", true);
  //TH1F* zjet_lepEffUp = DC.readWriteHisto(fDY, "lepEffUp/", histName, sf_zjet, fout, fDY, "zjet_lepEffUp", true);
  //TH1F* zjet_lepEffDo = DC.readWriteHisto(fDY, "lepEffDo/", histName, sf_zjet, fout, fDY, "zjet_lepEffDown", true);
  TH1F* zjet_bc_statUp = DC.readWriteHisto(fDY, "bc_statUp/", histName, sf_zjet, fout, fDY, "zjet_bc_statUp", true);
  TH1F* zjet_bc_statDown = DC.readWriteHisto(fDY, "bc_statDo/", histName, sf_zjet, fout, fDY, "zjet_bc_statDown", true);
  // TH1F* zjet_bc_puUp = DC.readWriteHisto(fDY, "bc_puUp/", histName, sf_zjet, fout, fDY, "zjet_bc_puUp", true);
  // TH1F* zjet_bc_puDo = DC.readWriteHisto(fDY, "bc_puDo/", histName, sf_zjet, fout, fDY, "zjet_bc_puDown", true);
  // TH1F* zjet_bc_muidUp = DC.readWriteHisto(fDY, "bc_muidDo/", histName, sf_zjet, fout, fDY, "zjet_bc_muidUp", true);
  // TH1F* zjet_bc_muidDo = DC.readWriteHisto(fDY, "bc_muidDo/", histName, sf_zjet, fout, fDY, "zjet_bc_muidDown", true);
  // TH1F* zjet_bc_lhemufUp = DC.readWriteHisto(fDY, "bc_lhemufUp/", histName, sf_zjet, fout, fDY, "zjet_bc_lhemufUp", true);
  // TH1F* zjet_bc_lhemufDo = DC.readWriteHisto(fDY, "bc_lhemufDo/", histName, sf_zjet, fout, fDY, "zjet_bc_lhemufDown", true);
  // TH1F* zjet_bc_lhemurUp = DC.readWriteHisto(fDY, "bc_lhemurUp/", histName, sf_zjet, fout, fDY, "zjet_bc_lhemurUp", true);
  // TH1F* zjet_bc_lhemurDo = DC.readWriteHisto(fDY, "bc_lhemurDo/", histName, sf_zjet, fout, fDY, "zjet_bc_lhemurDown", true);
  // TH1F* zjet_bc_isrUp = DC.readWriteHisto(fDY, "bc_isrUp/", histName, sf_zjet, fout, fDY, "zjet_bc_isrUp", true);
  // TH1F* zjet_bc_isrDo = DC.readWriteHisto(fDY, "bc_isrDo/", histName, sf_zjet, fout, fDY, "zjet_bc_isrDown", true);
  // TH1F* zjet_bc_fsrUp = DC.readWriteHisto(fDY, "bc_fsrUp/", histName, sf_zjet, fout, fDY, "zjet_bc_fsrUp", true);
  // TH1F* zjet_bc_fsrDo = DC.readWriteHisto(fDY, "bc_fsrDo/", histName, sf_zjet, fout, fDY, "zjet_bc_fsrDown", true);
  // TH1F* zjet_bc_xdyUp = DC.readWriteHisto(fDY, "bc_xdyUp/", histName, sf_zjet, fout, fDY, "zjet_bc_xdyUp", true);
  // TH1F* zjet_bc_xdyDo = DC.readWriteHisto(fDY, "bc_xdyDo/", histName, sf_zjet, fout, fDY, "zjet_bc_xdyDown", true);
  // TH1F* zjet_bc_xstUp = DC.readWriteHisto(fDY, "bc_xstUp/", histName, sf_zjet, fout, fDY, "zjet_bc_xstUp", true);
  // TH1F* zjet_bc_xstDo = DC.readWriteHisto(fDY, "bc_xstDo/", histName, sf_zjet, fout, fDY, "zjet_bc_xstDown", true);
  // TH1F* zjet_bc_xwjUp = DC.readWriteHisto(fDY, "bc_xwjUp/", histName, sf_zjet, fout, fDY, "zjet_bc_xwjUp", true);
  // TH1F* zjet_bc_xwjDo = DC.readWriteHisto(fDY, "bc_xwjDo/", histName, sf_zjet, fout, fDY, "zjet_bc_xwjDown", true);
  // TH1F* zjet_bc_xttUp = DC.readWriteHisto(fDY, "bc_xttUp/", histName, sf_zjet, fout, fDY, "zjet_bc_xttUp", true);
  // TH1F* zjet_bc_xttDo = DC.readWriteHisto(fDY, "bc_xttDo/", histName, sf_zjet, fout, fDY, "zjet_bc_xttDown", true);
  // TH1F* zjet_bc_jesUp = DC.readWriteHisto(fDY, "bc_jesUp/", histName, sf_zjet, fout, fDY, "zjet_bc_jesUp", true);
  // TH1F* zjet_bc_jesDo = DC.readWriteHisto(fDY, "bc_jesDo/", histName, sf_zjet, fout, fDY, "zjet_bc_jesDown", true);
  // TH1F* zjet_bc_jerUp = DC.readWriteHisto(fDY, "bc_jerUp/", histName, sf_zjet, fout, fDY, "zjet_bc_jerUp", true);
  // TH1F* zjet_bc_jerDo = DC.readWriteHisto(fDY, "bc_jerDo/", histName, sf_zjet, fout, fDY, "zjet_bc_jerDown", true);
  // TH1F* zjet_bc_bfragUp = DC.readWriteHisto(fDY, "bc_bfragUp/", histName, sf_zjet, fout, fDY, "zjet_bc_bfragUp", true);
  // TH1F* zjet_bc_bfragDo = DC.readWriteHisto(fDY, "bc_bfragDo/", histName, sf_zjet, fout, fDY, "zjet_bc_bfragDown", true);
  TH1F* zjet_fsrUp = DC.readWriteHisto(fDY, "fsrUp/", histName, sf_zjet, fout, fDY, "zjet_fsrUp", true);
  TH1F* zjet_fsrDown = DC.readWriteHisto(fDY, "fsrDo/", histName, sf_zjet, fout, fDY, "zjet_fsrDown", true);  
  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *zjet_bin_stat_Up = DC.readWriteHisto(fDY, baseDir+"/base"+histSubDir, histName, sf_zjet, fout, fTT, Form("zjet_CMS_stat_cat1_zjet_bin_%dUp",ibin), true);
      TH1F *zjet_bin_stat_Do = DC.readWriteHisto(fDY, baseDir+"/base"+histSubDir, histName, sf_zjet, fout, fTT, Form("zjet_CMS_stat_cat1_zjet_bin_%dDown",ibin), true);
    }
  }

  double unc_zjet_ExL = 1.0;
  double unc_zjet_ExM = 1.0;
  if(isExL){
    TH1F* zjet_yLyMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* zjet_yLyMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* zjet_yLnMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* zjet_yLnMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_zjet_ExL = DC.getUncExL(zjet_yLyMyT, zjet_yLyMnT, zjet_yLnMyT, zjet_yLnMnT);
  }
  if(isExM){
    TH1F* zjet_yMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* zjet_yMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_zjet_ExM = DC.getUncExM(zjet_yMyT, zjet_yMnT);
  }

  //SingleTop
  double sf_stop = 1.0;
  TH1F* stop = DC.readWriteHisto(fST,"base/", histName, sf_stop, fout, fST, "stop", true);
  TH1F* stop_JESUp = DC.readWriteHisto(fST, "jecUp/", histName, sf_stop, fout, fST, "stop_JESUp", true);
  TH1F* stop_JESDown = DC.readWriteHisto(fST, "jecDo/", histName, sf_stop, fout, fST, "stop_JESDown", true);
  TH1F* stop_PileupUp = DC.readWriteHisto(fST, "puUp/", histName, sf_stop, fout, fST, "stop_PileupUp", true);
  TH1F* stop_PileupDown = DC.readWriteHisto(fST, "puDo/", histName, sf_stop, fout, fST, "stop_PileupDown", true);
  TH1F* stop_JERUp = DC.readWriteHisto(fST, "jerUp/", histName, sf_stop, fout, fST, "stop_JERUp", true);
  TH1F* stop_jerhfDown = DC.readWriteHisto(fST, "jerDo/", histName, sf_stop, fout, fST, "stop_jerhfDown", true);
  TH1F* stop_prefireUp = DC.readWriteHisto(fST, "prefireUp/", histName, sf_stop, fout, fST, "stop_prefireUp", true);
  TH1F* stop_prefireDo = DC.readWriteHisto(fST, "prefireDo/", histName, sf_stop, fout, fST, "stop_prefireDown", true);
  //TH1F* stop_lepEffUp = DC.readWriteHisto(fST, "lepEffUp/", histName, sf_stop, fout, fST, "stop_lepEffUp", true);
  //TH1F* stop_lepEffDo = DC.readWriteHisto(fST, "lepEffDo/", histName, sf_stop, fout, fST, "stop_lepEffDown", true);
  TH1F* stop_bc_statUp = DC.readWriteHisto(fST, "bc_statUp/", histName, sf_stop, fout, fST, "stop_bc_statUp", true);
  TH1F* stop_bc_statDown = DC.readWriteHisto(fST, "bc_statDo/", histName, sf_stop, fout, fST, "stop_bc_statDown", true);
  // TH1F* stop_bc_puUp = DC.readWriteHisto(fST, "bc_puUp/", histName, sf_stop, fout, fST, "stop_bc_puUp", true);
  // TH1F* stop_bc_puDo = DC.readWriteHisto(fST, "bc_puDo/", histName, sf_stop, fout, fST, "stop_bc_puDown", true);
  // TH1F* stop_bc_muidUp = DC.readWriteHisto(fST, "bc_muidDo/", histName, sf_stop, fout, fST, "stop_bc_muidUp", true);
  // TH1F* stop_bc_muidDo = DC.readWriteHisto(fST, "bc_muidDo/", histName, sf_stop, fout, fST, "stop_bc_muidDown", true);
  // TH1F* stop_bc_lhemufUp = DC.readWriteHisto(fST, "bc_lhemufUp/", histName, sf_stop, fout, fST, "stop_bc_lhemufUp", true);
  // TH1F* stop_bc_lhemufDo = DC.readWriteHisto(fST, "bc_lhemufDo/", histName, sf_stop, fout, fST, "stop_bc_lhemufDown", true);
  // TH1F* stop_bc_lhemurUp = DC.readWriteHisto(fST, "bc_lhemurUp/", histName, sf_stop, fout, fST, "stop_bc_lhemurUp", true);
  // TH1F* stop_bc_lhemurDo = DC.readWriteHisto(fST, "bc_lhemurDo/", histName, sf_stop, fout, fST, "stop_bc_lhemurDown", true);
  // TH1F* stop_bc_isrUp = DC.readWriteHisto(fST, "bc_isrUp/", histName, sf_stop, fout, fST, "stop_bc_isrUp", true);
  // TH1F* stop_bc_isrDo = DC.readWriteHisto(fST, "bc_isrDo/", histName, sf_stop, fout, fST, "stop_bc_isrDown", true);
  // TH1F* stop_bc_fsrUp = DC.readWriteHisto(fST, "bc_fsrUp/", histName, sf_stop, fout, fST, "stop_bc_fsrUp", true);
  // TH1F* stop_bc_fsrDo = DC.readWriteHisto(fST, "bc_fsrDo/", histName, sf_stop, fout, fST, "stop_bc_fsrDown", true);
  // TH1F* stop_bc_xdyUp = DC.readWriteHisto(fST, "bc_xdyUp/", histName, sf_stop, fout, fST, "stop_bc_xdyUp", true);
  // TH1F* stop_bc_xdyDo = DC.readWriteHisto(fST, "bc_xdyDo/", histName, sf_stop, fout, fST, "stop_bc_xdyDown", true);
  // TH1F* stop_bc_xstUp = DC.readWriteHisto(fST, "bc_xstUp/", histName, sf_stop, fout, fST, "stop_bc_xstUp", true);
  // TH1F* stop_bc_xstDo = DC.readWriteHisto(fST, "bc_xstDo/", histName, sf_stop, fout, fST, "stop_bc_xstDown", true);
  // TH1F* stop_bc_xwjUp = DC.readWriteHisto(fST, "bc_xwjUp/", histName, sf_stop, fout, fST, "stop_bc_xwjUp", true);
  // TH1F* stop_bc_xwjDo = DC.readWriteHisto(fST, "bc_xwjDo/", histName, sf_stop, fout, fST, "stop_bc_xwjDown", true);
  // TH1F* stop_bc_xttUp = DC.readWriteHisto(fST, "bc_xttUp/", histName, sf_stop, fout, fST, "stop_bc_xttUp", true);
  // TH1F* stop_bc_xttDo = DC.readWriteHisto(fST, "bc_xttDo/", histName, sf_stop, fout, fST, "stop_bc_xttDown", true);
  // TH1F* stop_bc_jesUp = DC.readWriteHisto(fST, "bc_jesUp/", histName, sf_stop, fout, fST, "stop_bc_jesUp", true);
  // TH1F* stop_bc_jesDo = DC.readWriteHisto(fST, "bc_jesDo/", histName, sf_stop, fout, fST, "stop_bc_jesDown", true);
  // TH1F* stop_bc_jerUp = DC.readWriteHisto(fST, "bc_jerUp/", histName, sf_stop, fout, fST, "stop_bc_jerUp", true);
  // TH1F* stop_bc_jerDo = DC.readWriteHisto(fST, "bc_jerDo/", histName, sf_stop, fout, fST, "stop_bc_jerDown", true);
  // TH1F* stop_bc_bfragUp = DC.readWriteHisto(fST, "bc_bfragUp/", histName, sf_stop, fout, fST, "stop_bc_bfragUp", true);
  // TH1F* stop_bc_bfragDo = DC.readWriteHisto(fST, "bc_bfragDo/", histName, sf_stop, fout, fST, "stop_bc_bfragDown", true);
  TH1F* stop_fsrUp = DC.readWriteHisto(fST, "fsrUp/", histName, sf_stop, fout, fST, "stop_fsrUp", true);
  TH1F* stop_fsrDown = DC.readWriteHisto(fST, "fsrDo/", histName, sf_stop, fout, fST, "stop_fsrDown", true);
  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *stop_bin_stat_Up = DC.readWriteHisto(fST, baseDir+"/base"+histSubDir, histName, sf_stop, fout, fTT, Form("stop_CMS_stat_cat1_stop_bin_%dUp",ibin), true);
      TH1F *stop_bin_stat_Do = DC.readWriteHisto(fST, baseDir+"/base"+histSubDir, histName, sf_stop, fout, fTT, Form("stop_CMS_stat_cat1_stop_bin_%dDown",ibin), true);
    }
  }

  double unc_stop_ExL = 1.0;
  double unc_stop_ExM = 1.0;
  if(isExL){
    TH1F* stop_yLyMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* stop_yLyMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* stop_yLnMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* stop_yLnMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_stop_ExL = DC.getUncExL(stop_yLyMyT, stop_yLyMnT, stop_yLnMyT, stop_yLnMnT);
  }
  if(isExM){
    TH1F* stop_yMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* stop_yMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_stop_ExM = DC.getUncExM(stop_yMyT, stop_yMnT);
  }

  //Dibosons
  double sf_vv = 1;
  TH1F* vv = DC.readWriteHisto(fVV,"base/", histName, sf_vv, fout, fVV, "vv", true);
  TH1F* vv_JESUp = DC.readWriteHisto(fVV, "jecUp/", histName, sf_vv, fout, fVV, "vv_JESUp", true);
  TH1F* vv_JESDown = DC.readWriteHisto(fVV, "jecDo/", histName, sf_vv, fout, fVV, "vv_JESDown", true);
  TH1F* vv_PileupUp = DC.readWriteHisto(fVV, "puUp/", histName, sf_vv, fout, fVV, "vv_PileupUp", true);
  TH1F* vv_PileupDown = DC.readWriteHisto(fVV, "puDo/", histName, sf_vv, fout, fVV, "vv_PileupDown", true);
  TH1F* vv_JERUp = DC.readWriteHisto(fVV, "jerUp/", histName, sf_vv, fout, fVV, "vv_JERUp", true);
  TH1F* vv_jerhfDown = DC.readWriteHisto(fVV, "jerDo/", histName, sf_vv, fout, fVV, "vv_jerhfDown", true);
  TH1F* vv_prefireUp = DC.readWriteHisto(fVV, "prefireUp/", histName, sf_vv, fout, fVV, "vv_prefireUp", true);
  TH1F* vv_prefireDo = DC.readWriteHisto(fVV, "prefireDo/", histName, sf_vv, fout, fVV, "vv_prefireDown", true);
  //TH1F* vv_lepEffUp = DC.readWriteHisto(fVV, "lepEffUp/", histName, sf_vv, fout, fVV, "vv_lepEffUp", true);
  //TH1F* vv_lepEffDo = DC.readWriteHisto(fVV, "lepEffDo/", histName, sf_vv, fout, fVV, "vv_lepEffDown", true);
  TH1F* vv_bc_statUp = DC.readWriteHisto(fVV, "bc_statUp/", histName, sf_vv, fout, fVV, "vv_bc_statUp", true);
  TH1F* vv_bc_statDown = DC.readWriteHisto(fVV, "bc_statDo/", histName, sf_vv, fout, fVV, "vv_bc_statDown", true);
  TH1F* vv_fsrUp = DC.readWriteHisto(fWJ, "fsrUp/", histName, sf_vv, fout, fVV, "vv_fsrUp", true);
  TH1F* vv_fsrDown = DC.readWriteHisto(fWJ, "fsrDo/", histName, sf_vv, fout, fVV, "vv_fsrDown", true);
  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *vv_bin_stat_Up = DC.readWriteHisto(fVV, baseDir+"/base"+histSubDir, histName, sf_vv, fout, fTT, Form("vv_CMS_stat_cat1_vv_bin_%dUp",ibin), true);
      TH1F *vv_bin_stat_Do = DC.readWriteHisto(fVV, baseDir+"/base"+histSubDir, histName, sf_vv, fout, fTT, Form("vv_CMS_stat_cat1_vv_bin_%dDown",ibin), true);
    }
  }
  double unc_vv_ExL = 1.0;
  double unc_vv_ExM = 1.0;
  if(isExL){
    TH1F* vv_yLyMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* vv_yLyMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* vv_yLnMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* vv_yLnMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_vv_ExL = DC.getUncExL(vv_yLyMyT, vv_yLyMnT, vv_yLnMyT, vv_yLnMnT);
  }
  if(isExM){
    TH1F* vv_yMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* vv_yMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_vv_ExM = DC.getUncExM(vv_yMyT, vv_yMnT);
  }

  //QCD MC
  double sf_qcd = 1.0;
  /*
  TH1F* qcd = DC.readWriteHisto(fQCD, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true);
  TH1F* qcd_JESUp = DC.readWriteHisto(fQCD, baseDir+"/jecup"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JESUp", true);
  TH1F* qcd_JESDown = DC.readWriteHisto(fQCD, baseDir+"/jecdown"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JESDown", true);
  TH1F* qcd_PileupUp = DC.readWriteHisto(fQCD, baseDir+"/puup"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_PileupUp", true);
  TH1F* qcd_PileupDown = DC.readWriteHisto(fQCD, baseDir+"/pudown"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_PileupDown", true);
  TH1F* qcd_JERUp = DC.readWriteHisto(fQCD, baseDir+"/jerup"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JERUp", true);
  TH1F* qcd_jerhfDown = DC.readWriteHisto(fQCD, baseDir+"/jerdown"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_jerhfDown", true);
  //TH1F* qcd_bcTag1Up = DC.readWriteHisto(fQCD, baseDir+"/bctag1up"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag1Up", true);
  //TH1F* qcd_bcTag1Down = DC.readWriteHisto(fQCD, baseDir+"/bctag1down"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag1Down", true);
  //TH1F* qcd_bcTag2Up = DC.readWriteHisto(fQCD, baseDir+"/bctag2up"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag2Up", true);
  //TH1F* qcd_bcTag2Down = DC.readWriteHisto(fQCD, baseDir+"/bctag2down"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag2Down", true);
  //TH1F* qcd_bcTag3Up = DC.readWriteHisto(fQCD, baseDir+"/bctag3up"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag3Up", true);
  //TH1F* qcd_bcTag3Down = DC.readWriteHisto(fQCD, baseDir+"/bctag3down"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag3Down", true);
  */
  //QCD data driven
  //cout<<baseDir+"/base"+histSubDir+"/"+histName<<endl;
  // baseDir = "QCDdd";
  // TH1F* qcd_dd = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true);
  // double stat_unc_qcd = DC.getStatUnc(qcd_dd, 0);
  // // cout<<"qcd stat unc: "<<stat_unc_qcd<<endl;
  // // cout<<"qcd = "<<qcd_dd->Integral()<<endl;
  // //double qcd_unc = DC.getSysUncQcd(fData, fTT, fST, fWJ, fDY,  fVV, histSubDir_+"/", histName, false);
  // cout << "histname : "<<histName << endl;  
  // double qcd_unc = DC.getSysUncQcdNano(isMuChannel, fData, fTT, fST, fWJ, fDY,  fVV, histSubDir_+"/", histName, false);
  // if(isBinStat){
  //   for(int ibin = 1; ibin <= nonStatBins ; ibin++){
  //     TH1F *qcd_bin_stat_Up = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, Form("qcd_CMS_stat_cat1_qcd_bin_%dUp",ibin), true);
  //     TH1F *qcd_bin_stat_Do = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, Form("qcd_CMS_stat_cat1_qcd_bin_%dDown",ibin), true);
  //   }
  // }


  //Data
  double sf_data = 1.0; //should be 1, always
  baseDir = (isMuChannel) ? "DataMu" : "DataEle";
  TH1F* data_obs = DC.readWriteHisto(fData, baseDir+"/base"+histSubDir, histName, sf_data, fout, fTT, "data_obs", true);
  //TH1F* data_obs = DC.readWriteHisto(fTT, "TTbar/base"+histSubDir, histName, sf_data, fout, fTT, "data_obs", true);
  cout<<":data_obs ================: "<<data_obs->Integral()<<endl;

  //wh
  double sf_wh = 1.0;
  //double sf_wh = 1.0/2.0;
  baseDir = Form("HplusM%03d",mass);
  //baseDir = Form("HplmiM%03d",mass);
  TH1F* wh = DC.readWriteHisto(fWH,"base/", histName, sf_wh, fout, fWH, "wh", true);
  TH1F* wh_JESUp = DC.readWriteHisto(fWH, "jecUp/", histName, sf_wh, fout, fWH, "wh_JESUp", true);
  TH1F* wh_JESDown = DC.readWriteHisto(fWH, "jecDo/", histName, sf_wh, fout, fWH, "wh_JESDown", true);
  TH1F* wh_PileupUp = DC.readWriteHisto(fWH, "puUp/", histName, sf_wh, fout, fWH, "wh_PileupUp", true);
  TH1F* wh_PileupDown = DC.readWriteHisto(fWH, "puDo/", histName, sf_wh, fout, fWH, "wh_PileupDown", true);
  TH1F* wh_JERUp = DC.readWriteHisto(fWH, "jerUp/", histName, sf_wh, fout, fWH, "wh_JERUp", true);
  TH1F* wh_jerhfDown = DC.readWriteHisto(fWH, "jerDo/", histName, sf_wh, fout, fWH, "wh_jerhfDown", true);
  TH1F* wh_prefireUp = DC.readWriteHisto(fWH, "prefireUp/", histName, sf_wh, fout, fWH, "wh_prefireUp", true);
  TH1F* wh_prefireDo = DC.readWriteHisto(fWH, "prefireDo/", histName, sf_wh, fout, fWH, "wh_prefireDown", true);
  //TH1F* wh_lepEffUp = DC.readWriteHisto(fWH, "lepEffUp/", histName, sf_wh, fout, fWH, "wh_lepEffUp", true);
  //TH1F* wh_lepEffDo = DC.readWriteHisto(fWH, "lepEffDo/", histName, sf_wh, fout, fWH, "wh_lepEffDown", true);
  TH1F* wh_bc_statUp = DC.readWriteHisto(fWH, "bc_statUp/", histName, sf_wh, fout, fWH, "wh_bc_statUp", true);
  TH1F* wh_bc_statDown = DC.readWriteHisto(fWH, "bc_statDo/", histName, sf_wh, fout, fWH, "wh_bc_statDown", true);
  // TH1F* wh_bc_puUp = DC.readWriteHisto(fWH, "bc_puUp/", histName, sf_wh, fout, fWH, "wh_bc_puUp", true);
  // TH1F* wh_bc_puDo = DC.readWriteHisto(fWH, "bc_puDo/", histName, sf_wh, fout, fWH, "wh_bc_puDown", true);
  // TH1F* wh_bc_muidUp = DC.readWriteHisto(fWH, "bc_muidDo/", histName, sf_wh, fout, fWH, "wh_bc_muidUp", true);
  // TH1F* wh_bc_muidDo = DC.readWriteHisto(fWH, "bc_muidDo/", histName, sf_wh, fout, fWH, "wh_bc_muidDown", true);
  // TH1F* wh_bc_lhemufUp = DC.readWriteHisto(fWH, "bc_lhemufUp/", histName, sf_wh, fout, fWH, "wh_bc_lhemufUp", true);
  // TH1F* wh_bc_lhemufDo = DC.readWriteHisto(fWH, "bc_lhemufDo/", histName, sf_wh, fout, fWH, "wh_bc_lhemufDown", true);
  // TH1F* wh_bc_lhemurUp = DC.readWriteHisto(fWH, "bc_lhemurUp/", histName, sf_wh, fout, fWH, "wh_bc_lhemurUp", true);
  // TH1F* wh_bc_lhemurDo = DC.readWriteHisto(fWH, "bc_lhemurDo/", histName, sf_wh, fout, fWH, "wh_bc_lhemurDown", true);
  // TH1F* wh_bc_isrUp = DC.readWriteHisto(fWH, "bc_isrUp/", histName, sf_wh, fout, fWH, "wh_bc_isrUp", true);
  // TH1F* wh_bc_isrDo = DC.readWriteHisto(fWH, "bc_isrDo/", histName, sf_wh, fout, fWH, "wh_bc_isrDown", true);
  // TH1F* wh_bc_fsrUp = DC.readWriteHisto(fWH, "bc_fsrUp/", histName, sf_wh, fout, fWH, "wh_bc_fsrUp", true);
  // TH1F* wh_bc_fsrDo = DC.readWriteHisto(fWH, "bc_fsrDo/", histName, sf_wh, fout, fWH, "wh_bc_fsrDown", true);
  // TH1F* wh_bc_xdyUp = DC.readWriteHisto(fWH, "bc_xdyUp/", histName, sf_wh, fout, fWH, "wh_bc_xdyUp", true);
  // TH1F* wh_bc_xdyDo = DC.readWriteHisto(fWH, "bc_xdyDo/", histName, sf_wh, fout, fWH, "wh_bc_xdyDown", true);
  // TH1F* wh_bc_xstUp = DC.readWriteHisto(fWH, "bc_xstUp/", histName, sf_wh, fout, fWH, "wh_bc_xstUp", true);
  // TH1F* wh_bc_xstDo = DC.readWriteHisto(fWH, "bc_xstDo/", histName, sf_wh, fout, fWH, "wh_bc_xstDown", true);
  // TH1F* wh_bc_xwjUp = DC.readWriteHisto(fWH, "bc_xwjUp/", histName, sf_wh, fout, fWH, "wh_bc_xwjUp", true);
  // TH1F* wh_bc_xwjDo = DC.readWriteHisto(fWH, "bc_xwjDo/", histName, sf_wh, fout, fWH, "wh_bc_xwjDown", true);
  // TH1F* wh_bc_xttUp = DC.readWriteHisto(fWH, "bc_xttUp/", histName, sf_wh, fout, fWH, "wh_bc_xttUp", true);
  // TH1F* wh_bc_xttDo = DC.readWriteHisto(fWH, "bc_xttDo/", histName, sf_wh, fout, fWH, "wh_bc_xttDown", true);
  // TH1F* wh_bc_jesUp = DC.readWriteHisto(fWH, "bc_jesUp/", histName, sf_wh, fout, fWH, "wh_bc_jesUp", true);
  // TH1F* wh_bc_jesDo = DC.readWriteHisto(fWH, "bc_jesDo/", histName, sf_wh, fout, fWH, "wh_bc_jesDown", true);
  // TH1F* wh_bc_jerUp = DC.readWriteHisto(fWH, "bc_jerUp/", histName, sf_wh, fout, fWH, "wh_bc_jerUp", true);
  // TH1F* wh_bc_jerDo = DC.readWriteHisto(fWH, "bc_jerDo/", histName, sf_wh, fout, fWH, "wh_bc_jerDown", true);
  // TH1F* wh_bc_bfragUp = DC.readWriteHisto(fWH, "bc_bfragUp/", histName, sf_wh, fout, fWH, "wh_bc_bfragUp", true);
  // TH1F* wh_bc_bfragDo = DC.readWriteHisto(fWH, "bc_bfragDo/", histName, sf_wh, fout, fWH, "wh_bc_bfragDown", true);
  TH1F* wh_fsrUp = DC.readWriteHisto(fWH, "fsrUp/", histName, sf_wh, fout, fWH, "wh_fsrUp", true);
  TH1F* wh_fsrDown = DC.readWriteHisto(fWH, "fsrDo/", histName, sf_wh, fout, fWH, "wh_fsrDown", true);
  TH1F* wh_isrUp = DC.readWriteHisto(fWH, "isrUp/", histName, sf_wh, fout, fWH, "wh_isrUp", true);
  TH1F* wh_isrDown = DC.readWriteHisto(fWH, "isrDo/", histName, sf_wh, fout, fWH, "wh_isrDown", true);

  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F* wh_bin_stat_Up = DC.readWriteHisto(fWH, baseDir+"/base"+histSubDir, histName, sf_wh, fout, fTT, label+Form("_CMS_stat_cat1_WH_bin_%dUp",ibin), true);
      TH1F* wh_bin_stat_Down = DC.readWriteHisto(fWH, baseDir+"/base"+histSubDir, histName, sf_wh, fout, fTT, label+Form("_CMS_stat_cat1_WH_bin_%dDown",ibin), true);
    }
  }

  double unc_wh_ExL = 1.0;
  double unc_wh_ExM = 1.0;
  if(isExL){
    TH1F* wh_yLyMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT, sf_wh);
    TH1F* wh_yLyMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT, sf_wh);
    TH1F* wh_yLnMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT, sf_wh);
    TH1F* wh_yLnMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT, sf_wh);
    unc_wh_ExL = DC.getUncExL(wh_yLyMyT, wh_yLyMnT, wh_yLnMyT, wh_yLnMnT);
  }
  if(isExM){
    TH1F* wh_yMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT, sf_wh);
    TH1F* wh_yMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT, sf_wh);
    unc_wh_ExM = DC.getUncExM(wh_yMyT, wh_yMnT);
  }
  
  //open input template data card
  ifstream in;
  char* c = new char[1160];
  in.open("MyTemplateDataCard_NanoAOD_15_Optimum.txt");
  //create output data card for 13 TeV
  string outDataCard = "datacard_hcs_13TeV_WH.txt";
  string histName_str(histSubDir_+TString("_")+histName);
  string thisYear = syear.Data();
  if(isMuChannel) outDataCard = "datacard_hcs_13TeV_mu_"+histName_str+"_WH%d"+"_"+thisYear+".txt"; 
  else outDataCard = "datacard_hcs_13TeV_ele_"+histName_str+"_WH%d"+"_"+thisYear+".txt";
  ofstream out(Form(outDataCard.c_str(), mass));
  out.precision(8);

  
  time_t secs=time(0);
  tm *t=localtime(&secs);
  while (in.good()){
    in.getline(c,1160,'\n');
    if (in.good()){
      string line(c);
      if(line.find("Date")!=string::npos){
        string day = string(Form("%d",t->tm_mday));
        string month = string(Form("%d",t->tm_mon+1));
        string year = string(Form("%d",t->tm_year+11160));
        line.replace( line.find("XXX") , 3 , day+"/"+month+"/"+year);
        out << line << endl;
	
      }
      else if(line.find("Description")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        line.replace( line.find("ZZZ") , 3 , string(Form("%f", totLumi)) ); 
        line.replace( line.find("CCC") , 3 , string(Form("%s", string(channelName).c_str())) ); 
        out << line << endl;
	
      }
      else if(line.find("shapes")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+histName+TString("_")+label+TString("_")+syear));
        out << line << endl;
	
      }
      else if(line.find("Observation")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(Form("%.0f", data_obs->Integral())));
        out << line << endl;
	
      }
      else if(line.find("process")!=string::npos && line.find("WH")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        out << line << endl;
	
      }
      else if(line.find("rate")!=string::npos){
        string rate = "rate               ";  
        string space = "     ";
        out << rate ;
        out << space << wh->Integral()
            << space << ttbar->Integral()
	    << space << wjet->Integral()
	    << space << zjet->Integral()
	    << space << stop->Integral()
	    << space << vv->Integral()
	  //            << space << qcd_dd->Integral()
            << endl;
	
      }
      else if(line.find("CMS_lumi_13TeV ")!=string::npos){
	
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", lumiUnc)) );
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", lumiUnc)) ); 
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", lumiUnc)) ); 
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", lumiUnc)) ); 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", lumiUnc)) ); 
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", lumiUnc)) ); 
        out << line << endl;

      }
      // else if(line.find("CMS_eff_lep ")!=string::npos){  

      //   if(isMuChannel) line.replace( line.find("lep") , 4 , string(Form("%s", "m")));   
      //   else line.replace( line.find("lep") , 4 , string(Form("%s", "e")));

      // 	float leptonUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_LeptonUp, wh_LeptonDown) : 1.00;
      // 	line.replace( line.find("HHHH") , 4 , string(Form("%.3f", leptonUnc_wh)) );
        
      // 	float leptonUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_LeptonUp, ttbar_LeptonDown) : 1.00; 
      // 	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", leptonUnc_ttbar)) ); 
	
      // 	float leptonUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_LeptonUp, wjet_LeptonDown) : 1.00;
      // 	line.replace( line.find("WWWW") , 4 , string(Form("%.3f", leptonUnc_wjet)) ); 
	
      // 	float leptonUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_LeptonUp, zjet_LeptonDown) : 1.00;
      // 	line.replace( line.find("DDDD") , 4 , string(Form("%.3f", leptonUnc_zjet)) ); 
	
      // 	float leptonUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_LeptonUp, stop_LeptonDown) : 1.00; 
      // 	line.replace( line.find("SSSS") , 4 , string(Form("%.3f", leptonUnc_stop)) ); 

      // 	float leptonUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_LeptonUp, vv_LeptonDown) : 1.00;
      // 	line.replace( line.find("VVVV") , 4 , string(Form("%.3f", leptonUnc_vv)) ); 
	
      //   out << line << endl;	
	
      // }  
      // else if(line.find("CMS_prefire ")!=string::npos){

      //   float prefireUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_PrefireUp, wh_PrefireDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", prefireUnc_wh)) );
        
      //   float prefireUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_PrefireUp, ttbar_PrefireDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", prefireUnc_ttbar)) ); 
        
      //   float prefireUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_PrefireUp, wjet_PrefireDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", prefireUnc_wjet)) ); 
       
      //   float prefireUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_PrefireUp, zjet_PrefireDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", prefireUnc_zjet)) ); 

      //   float prefireUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_PrefireUp, stop_PrefireDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", prefireUnc_stop)) ); 

      //   float prefireUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_PrefireUp, vv_PrefireDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", prefireUnc_vv)) ); 
      //   out << line << endl;

      // }
      // else if(line.find("CMS_pujetid ")!=string::npos){
	
      //   float pujetidUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_PUJetIDUp, wh_PUJetIDDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", pujetidUnc_wh)) );
        
      //   float pujetidUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_PUJetIDUp, ttbar_PUJetIDDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", pujetidUnc_ttbar)) ); 
        
      //   float pujetidUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_PUJetIDUp, wjet_PUJetIDDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", pujetidUnc_wjet)) ); 
	
      //   float pujetidUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_PUJetIDUp, zjet_PUJetIDDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", pujetidUnc_zjet)) ); 
	
      //   float pujetidUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_PUJetIDUp, stop_PUJetIDDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", pujetidUnc_stop)) ); 
	
      //   float pujetidUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_PUJetIDUp, vv_PUJetIDDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", pujetidUnc_vv)) );
	
      //   out << line << endl;
	
      // }
      else if(line.find("CMS_pileup ")!=string::npos){

        float PileupUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_PileupUp, wh_PileupDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", PileupUnc_wh)) );
        
        float PileupUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_PileupUp, ttbar_PileupDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", PileupUnc_ttbar)) ); 
        
        float PileupUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_PileupUp, wjet_PileupDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", PileupUnc_wjet)) ); 
       
        float PileupUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_PileupUp, zjet_PileupDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", PileupUnc_zjet)) ); 
        
        float PileupUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_PileupUp, stop_PileupDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", PileupUnc_stop)) ); 

        float PileupUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_PileupUp, vv_PileupDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", PileupUnc_vv)) ); 
        out << line << endl;	
	
      }
      else if(line.find("CMS_scale_j ")!=string::npos){
        float JESUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_JESUp, wh_JESDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JESUnc_wh)) );
        
        float JESUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_JESUp, ttbar_JESDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JESUnc_ttbar)) ); 
        
        float JESUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_JESUp, wjet_JESDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JESUnc_wjet)) ); 
       
        float JESUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_JESUp, zjet_JESDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JESUnc_zjet)) ); 
        
        float JESUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_JESUp, stop_JESDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JESUnc_stop)) ); 

        float JESUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_JESUp, vv_JESDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JESUnc_vv)) ); 
        out << line << endl;
	
      }
      else if(line.find("CMS_res_j ")!=string::npos){
        float JERUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_JERUp, wh_jerhfDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JERUnc_wh)) );
        
        float JERUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_JERUp, ttbar_jerhfDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JERUnc_ttbar)) ); 
        
        float JERUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_JERUp, wjet_jerhfDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JERUnc_wjet)) ); 
       
        float JERUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_JERUp, zjet_jerhfDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JERUnc_zjet)) ); 
        
        float JERUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_JERUp, stop_jerhfDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JERUnc_stop)) ); 

        float JERUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_JERUp, vv_jerhfDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JERUnc_vv)) ); 
        out << line << endl;
	
      }
      // else if(line.find("CMS_norm_qcd ")!=string::npos){  
      //   line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", qcd_unc)));   
      //   //if(isMuChannel) line.replace( line.find("QQQQ") , 4 , string(Form("%.4f", 1.10)));   
      //   //else line.replace(line.find("QQQQ") , 4 , string(Form("%.4f", 1.10)));   
      //   out << line << endl;
	
      // }
      // else if(line.find("CMS_CP5_tt ")!=string::npos){
      // 	float scaleUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_cp5Up, ttbar_cp5Down) : 1.00; 
      // 	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", scaleUnc_ttbar)) ); 
      // 	out << line << endl;
	
      // }
      // else if(line.find("CMS_hDamp_tt ")!=string::npos){
      //   float matchUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_matchingUp, ttbar_matchingDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", matchUnc_ttbar)) ); 
      //   out << line << endl;
	
      // }
      // else if(line.find("CMS_topMass_tt ")!=string::npos){
      // 	float mtopUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_mtop1735, ttbar_mtop1715) : 1.00; 
      // 	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", mtopUnc_ttbar)) ); 
      // 	out << line << endl;
	
      // }
      // else if(line.find("CMS_pdf ")!=string::npos){
      //   float pdfUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_pdfUp, wh_pdfDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", pdfUnc_wh)) );
        
      //   float pdfUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_pdfUp, ttbar_pdfDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", pdfUnc_ttbar)) ); 
        
      //   float pdfUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_pdfUp, wjet_pdfDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", pdfUnc_wjet)) ); 
       
      //   float pdfUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_pdfUp, zjet_pdfDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", pdfUnc_zjet)) ); 
        
      //   float pdfUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_pdfUp, stop_pdfDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", pdfUnc_stop)) ); 

      //   float pdfUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_pdfUp, vv_pdfDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", pdfUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_isr ")!=string::npos){
      //   float isrUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_isrUp, wh_isrDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", isrUnc_wh)) );
        
      //   float isrUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_isrUp, ttbar_isrDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", isrUnc_ttbar)) ); 
        
      //   float isrUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_isrUp, wjet_isrDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", isrUnc_wjet)) ); 
       
      //   float isrUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_isrUp, zjet_isrDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", isrUnc_zjet)) ); 
        
      //   float isrUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_isrUp, stop_isrDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", isrUnc_stop)) ); 

      //   float isrUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_isrUp, vv_isrDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", isrUnc_vv)) ); 
      //   out << line << endl;
      // }
      else if(line.find("CMS_fsr ")!=string::npos){
        float fsrUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_fsrUp, wh_fsrDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", fsrUnc_wh)) );
        
        float fsrUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_fsrUp, ttbar_fsrDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", fsrUnc_ttbar)) ); 
        
        float fsrUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_fsrUp, wjet_fsrDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", fsrUnc_wjet)) ); 
       
        float fsrUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_fsrUp, zjet_fsrDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", fsrUnc_zjet)) ); 
        
        float fsrUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_fsrUp, stop_fsrDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", fsrUnc_stop)) ); 

        float fsrUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_fsrUp, vv_fsrDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", fsrUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_bcstat ")!=string::npos){
        float bcstatUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bc_statUp, wh_bc_statDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcstatUnc_wh)) );
        
        float bcstatUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bc_statUp, ttbar_bc_statDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcstatUnc_ttbar)) ); 
        
        float bcstatUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bc_statUp, wjet_bc_statDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcstatUnc_wjet)) ); 
       
        float bcstatUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bc_statUp, zjet_bc_statDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcstatUnc_zjet)) ); 
        
        float bcstatUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bc_statUp, stop_bc_statDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcstatUnc_stop)) ); 

        float bcstatUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bc_statUp, vv_bc_statDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcstatUnc_vv)) ); 
        out << line << endl;
      }
      // else if(line.find("CMS_bclhemuf ")!=string::npos){
      //   // float bclhemufUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bclhemufUp, wh_bclhemufDown) : 1.00;
      //   // line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bclhemufUnc_wh)) );
        
      //   float bclhemufUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bclhemufUp, ttbar_bclhemufDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bclhemufUnc_ttbar)) ); 
        
      //   // float bclhemufUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bclhemufUp, wjet_bclhemufDown) : 1.00;
      //   // line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bclhemufUnc_wjet)) ); 
       
      //   // float bclhemufUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bclhemufUp, zjet_bclhemufDown) : 1.00;
      //   // line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bclhemufUnc_zjet)) ); 
        
      //   // float bclhemufUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bclhemufUp, stop_bclhemufDown) : 1.00; 
      //   // line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bclhemufUnc_stop)) ); 

      //   // float bclhemufUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bclhemufUp, vv_bclhemufDown) : 1.00;
      //   // line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bclhemufUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bclhemur ")!=string::npos){
      //   // float bclhemurUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bclhemurUp, wh_bclhemurDown) : 1.00;
      //   // line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bclhemurUnc_wh)) );
        
      //   float bclhemurUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bclhemurUp, ttbar_bclhemurDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bclhemurUnc_ttbar)) ); 
        
      //   // float bclhemurUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bclhemurUp, wjet_bclhemurDown) : 1.00;
      //   // line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bclhemurUnc_wjet)) ); 
       
      //   // float bclhemurUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bclhemurUp, zjet_bclhemurDown) : 1.00;
      //   // line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bclhemurUnc_zjet)) ); 
        
      //   // float bclhemurUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bclhemurUp, stop_bclhemurDown) : 1.00; 
      //   // line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bclhemurUnc_stop)) ); 

      //   // float bclhemurUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bclhemurUp, vv_bclhemurDown) : 1.00;
      //   // line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bclhemurUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcbfrag ")!=string::npos){
      //   float bcbfragUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcbfragUp, wh_bcbfragDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcbfragUnc_wh)) );
        
      //   float bcbfragUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcbfragUp, ttbar_bcbfragDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcbfragUnc_ttbar)) ); 
        
      //   float bcbfragUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcbfragUp, wjet_bcbfragDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcbfragUnc_wjet)) ); 
       
      //   float bcbfragUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcbfragUp, zjet_bcbfragDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcbfragUnc_zjet)) ); 
        
      //   float bcbfragUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcbfragUp, stop_bcbfragDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcbfragUnc_stop)) ); 

      //   float bcbfragUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcbfragUp, vv_bcbfragDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcbfragUnc_vv)) ); 
      //   out << line << endl;
      // }      
      // else if(line.find("CMS_bcxdy ")!=string::npos){
      //   float bcxdyUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxdyUp, wh_bcxdyDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxdyUnc_wh)) );
        
      //   float bcxdyUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxdyUp, ttbar_bcxdyDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxdyUnc_ttbar)) ); 
        
      //   float bcxdyUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxdyUp, wjet_bcxdyDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxdyUnc_wjet)) ); 
       
      //   float bcxdyUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxdyUp, zjet_bcxdyDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxdyUnc_zjet)) ); 
        
      //   float bcxdyUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxdyUp, stop_bcxdyDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxdyUnc_stop)) ); 

      //   float bcxdyUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxdyUp, vv_bcxdyDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxdyUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcxst ")!=string::npos){
      //   float bcxstUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxstUp, wh_bcxstDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxstUnc_wh)) );
        
      //   float bcxstUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxstUp, ttbar_bcxstDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxstUnc_ttbar)) ); 
        
      //   float bcxstUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxstUp, wjet_bcxstDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxstUnc_wjet)) ); 
       
      //   float bcxstUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxstUp, zjet_bcxstDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxstUnc_zjet)) ); 
        
      //   float bcxstUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxstUp, stop_bcxstDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxstUnc_stop)) ); 

      //   float bcxstUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxstUp, vv_bcxstDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxstUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcxwj ")!=string::npos){
      //   float bcxwjUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxwjUp, wh_bcxwjDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxwjUnc_wh)) );
        
      //   float bcxwjUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxwjUp, ttbar_bcxwjDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxwjUnc_ttbar)) ); 
        
      //   float bcxwjUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxwjUp, wjet_bcxwjDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxwjUnc_wjet)) ); 
       
      //   float bcxwjUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxwjUp, zjet_bcxwjDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxwjUnc_zjet)) ); 
        
      //   float bcxwjUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxwjUp, stop_bcxwjDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxwjUnc_stop)) ); 

      //   float bcxwjUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxwjUp, vv_bcxwjDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxwjUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcxtt ")!=string::npos){
      //   float bcxttUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxttUp, wh_bcxttDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxttUnc_wh)) );
        
      //   float bcxttUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxttUp, ttbar_bcxttDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxttUnc_ttbar)) ); 
        
      //   float bcxttUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxttUp, wjet_bcxttDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxttUnc_wjet)) ); 
       
      //   float bcxttUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxttUp, zjet_bcxttDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxttUnc_zjet)) ); 
        
      //   float bcxttUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxttUp, stop_bcxttDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxttUnc_stop)) ); 

      //   float bcxttUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxttUp, vv_bcxttDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxttUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcxdyb ")!=string::npos){
      //   float bcxdybUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxdybUp, wh_bcxdybDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxdybUnc_wh)) );
        
      //   float bcxdybUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxdybUp, ttbar_bcxdybDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxdybUnc_ttbar)) ); 
        
      //   float bcxdybUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxdybUp, wjet_bcxdybDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxdybUnc_wjet)) ); 
       
      //   float bcxdybUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxdybUp, zjet_bcxdybDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxdybUnc_zjet)) ); 
        
      //   float bcxdybUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxdybUp, stop_bcxdybDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxdybUnc_stop)) ); 

      //   float bcxdybUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxdybUp, vv_bcxdybDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxdybUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcxdyc ")!=string::npos){
      //   float bcxdycUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxdycUp, wh_bcxdycDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxdycUnc_wh)) );
        
      //   float bcxdycUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxdycUp, ttbar_bcxdycDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxdycUnc_ttbar)) ); 
        
      //   float bcxdycUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxdycUp, wjet_bcxdycDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxdycUnc_wjet)) ); 
       
      //   float bcxdycUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxdycUp, zjet_bcxdycDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxdycUnc_zjet)) ); 
        
      //   float bcxdycUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxdycUp, stop_bcxdycDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxdycUnc_stop)) ); 

      //   float bcxdycUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxdycUp, vv_bcxdycDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxdycUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcxwjc ")!=string::npos){
      //   float bcxwjcUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxwjcUp, wh_bcxwjcDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxwjcUnc_wh)) );
        
      //   float bcxwjcUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxwjcUp, ttbar_bcxwjcDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxwjcUnc_ttbar)) ); 
        
      //   float bcxwjcUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxwjcUp, wjet_bcxwjcDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxwjcUnc_wjet)) ); 
       
      //   float bcxwjcUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxwjcUp, zjet_bcxwjcDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxwjcUnc_zjet)) ); 
        
      //   float bcxwjcUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxwjcUp, stop_bcxwjcDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxwjcUnc_stop)) ); 

      //   float bcxwjcUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxwjcUp, vv_bcxwjcDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxwjcUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcintp ")!=string::npos){
      //   float bcintpUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcintpUp, wh_bcintpDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcintpUnc_wh)) );
        
      //   float bcintpUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcintpUp, ttbar_bcintpDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcintpUnc_ttbar)) ); 
        
      //   float bcintpUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcintpUp, wjet_bcintpDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcintpUnc_wjet)) ); 
       
      //   float bcintpUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcintpUp, zjet_bcintpDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcintpUnc_zjet)) ); 
        
      //   float bcintpUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcintpUp, stop_bcintpDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcintpUnc_stop)) ); 

      //   float bcintpUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcintpUp, vv_bcintpDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcintpUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcextp ")!=string::npos){
      //   float bcextpUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcextpUp, wh_bcextpDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcextpUnc_wh)) );
        
      //   float bcextpUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcextpUp, ttbar_bcextpDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcextpUnc_ttbar)) ); 
        
      //   float bcextpUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcextpUp, wjet_bcextpDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcextpUnc_wjet)) ); 
       
      //   float bcextpUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcextpUp, zjet_bcextpDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcextpUnc_zjet)) ); 
        
      //   float bcextpUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcextpUp, stop_bcextpDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcextpUnc_stop)) ); 

      //   float bcextpUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcextpUp, vv_bcextpDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcextpUnc_vv)) ); 
      //   out << line << endl;
      // }
      else{ //default without changes
        out << line << endl;
	//
      }
    }
    
  }
  
  if(isExL){
    string rate = "CMS_eff_cExL       lnN";  
    string space = "     ";
    out << rate ;
    out << space <<string(Form("%.3f", unc_wh_ExL))
        << space <<string(Form("%.3f", unc_ttbar_ExL))
        << space <<string(Form("%.3f", unc_wjet_ExL))
        << space <<string(Form("%.3f", unc_zjet_ExL))
        << space <<string(Form("%.3f", unc_stop_ExL))
        << space <<string(Form("%.3f", unc_vv_ExL))
        << space <<string(Form("%.3f", 1.0))
        << endl;
  }
  if(isExM){
    string rate = "CMS_eff_cExM       lnN";  
    string space = "     ";
    out << rate ;
    out << space <<string(Form("%.3f", unc_wh_ExM))
        << space <<string(Form("%.3f", unc_ttbar_ExM))
        << space <<string(Form("%.3f", unc_wjet_ExM))
        << space <<string(Form("%.3f", unc_zjet_ExM))
        << space <<string(Form("%.3f", unc_stop_ExM))
        << space <<string(Form("%.3f", unc_vv_ExM))
        << space <<string(Form("%.3f", 1.0))
        << endl;
  }
  if(!isBinStat)
    out<<"* autoMCStats 0 1"<<endl;
  out.close();
  in.close();
  fout->Close();
  delete fout;
}


// void MyHPlusDataCardMaker(TString inFileDir="stack_201160418_Mu_Sys_PreAppComent",
// 			  TString year="2016", 
// 			  TString histSubDir_="KinFit",
// 			  TString histName="mjj_kfit", 
// 			  TString channelName="mu", 
// 			  int mass=160, 
// 			  TString label="WH160", 
// 			  TString hPlusFileName="all_Hplus160.root")
//   {

//     //MyHPlusDataCardMakerMini(inFileDir, year, histSubDir_, histName, channelName, mass, label, hPlusFileName);
//     MyHPlusDataCardMakerNano(inFileDir, year, histSubDir_, histName, channelName, mass, label, hPlusFileName);


//   }
void MyHPlusDataCardMaker(TString inFileDir="/afs/cern.ch/work/s/savarghe/NewJEC/2016/mu/A/mergedHistos/LowMass/ExcTight/mass160/",
			    TString histSubDir_="KinFit",
			      TString histName="bdt_output",
			      TString channelName="mu",
			      int mass=160,
			      TString label="WH160",
			      TString hPlusFileName="hist_HplusM160_2016_mu.root")
{

  MyHPlusDataCardMakerMini(inFileDir, histSubDir_, histName, channelName, mass, label, hPlusFileName);                                                            
  //  MyHPlusDataCardMakerNano(inFileDir, histSubDir_, histName, channelName, mass, label, hPlusFileName);


}
