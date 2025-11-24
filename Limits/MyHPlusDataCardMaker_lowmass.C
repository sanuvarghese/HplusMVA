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

void MyHPlusDataCardMakerMini(TString inFileDir="/afs/cern.ch/work/s/savarghe/NewJEC/2018/mu/A/transformedHistosLowMass/ExcTight/mass40/", 
			      //TString syear="2018", 
			      TString histSubDir_="KinFit",
			      TString histName="mjj_kfit", 
			      TString channelName="mu", 
			      int mass=40, 
			      TString label="WH40", 
			      TString hPlusFileName="all_Hplus40.root")
{


  MyHPlusDataCardMaker DC;
  //TString baseDir = "topPtWeight";
  TString baseDir = "base";
    TString histSubDir = "";
  bool isMuChannel = false; 
  TString workingpoint = "ExcTight";
  if(channelName=="mu") isMuChannel = true;
  //inFileDir = inFileDir + "/" + syear;

  TString year = "2018";

  //int year = syear.Atoi();
  // int year = syear.Atoi();
   double totLumi = 35.9; //2018
  //  if(year==2018)
  //    totLumi = 41.5; // 2018
  //  if(year==2018)
  //   totLumi = 59.7; //2018

  // Open data files
  TFile* fData = TFile::Open(inFileDir+"/hist_UltimDataMu_2018_mu.root");
  TFile* fDataEle = TFile::Open(inFileDir+"/hist_DataEle_2018_mu.root");

  // Open background files
  TFile* fDY = TFile::Open(inFileDir+"/hist_DYjets_2018_mu.root");
  TFile* fWJ = TFile::Open(inFileDir+"/hist_Wjets_2018_mu.root");
  TFile* fST = TFile::Open(inFileDir+"/hist_singleTop_2018_mu.root");
  TFile* fTT = TFile::Open(inFileDir+"/hist_TTbar_2018_mu.root");
  TFile* fVV = TFile::Open(inFileDir+"/hist_VBFusion_2018_mu.root");

  // Open signal file
  TFile* fWH = TFile::Open(inFileDir+"/hist_HplusM40_2018_mu.root");

  // Open other process files
  TFile* fMCQCDEle = TFile::Open(inFileDir+"QCD_dd_2018.root");
  TFile* fQCD = TFile::Open(inFileDir+"QCD_dd_2018.root ");

  TFile* fTG = TFile::Open(inFileDir+"/hist_TTG_2018_mu.root");
  TFile* fTH = TFile::Open(inFileDir+"/hist_TTH_2018_mu.root");
  //TFile* fTTHToNonbb = TFile::Open(inFileDir+"/hist_TTHToNonbb_2018_mu.root");
  //TFile* fTTHTobb = TFile::Open(inFileDir+"/hist_TTHTobb_2018_mu.root");

  //  TFile* fTTWJetsToLNu = TFile::Open(inFileDir+"/hist_TTWJetsToLNu_2018_mu.root");
  TFile* fTW = TFile::Open(inFileDir+"/hist_TTW_2018_mu.root");

  TFile* fTZ = TFile::Open(inFileDir+"/hist_TTZ_2018_mu.root");
  
  //OUTPUT FILE
  // TFile *fout = new TFile(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+workingpoint+histName+TString("_")+label+TString(".root"), "RECREATE");

  // Adjusted OUTPUT FILE creation line without "_output_"
  TFile *fout = new TFile(TString("Shapes_hcs_2018_")+channelName+TString("_")+histSubDir_+TString("_")+workingpoint+histName+TString("_")+label+TString(".root"), "RECREATE");


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
TH1F* ttbar_JERUp = DC.readWriteHisto(fTT, "jerup/", histName, sf_ttbar, fout, fTT, "ttbar_JER_"+ year + "Up", true);
TH1F* ttbar_JERDown = DC.readWriteHisto(fTT, "jerdown/", histName, sf_ttbar, fout, fTT, "ttbar_JER_"+ year + "Down", true);
TH1F* ttbar_prefireUp = DC.readWriteHisto(fTT, "base_prefire_up/", histName, sf_ttbar, fout, fTT, "ttbar_prefireUp", true);
TH1F* ttbar_prefireDown = DC.readWriteHisto(fTT, "base_prefire_do/", histName, sf_ttbar, fout, fTT, "ttbar_prefireDown", true);
TH1F* ttbar_fsrUp = DC.readWriteHisto(fTT, "base_fsr_up/", histName, sf_ttbar, fout, fTT, "ttbar_fsrUp", true);
TH1F* ttbar_fsrDown = DC.readWriteHisto(fTT, "base_fsr_do/", histName, sf_ttbar, fout, fTT, "ttbar_fsrDown", true);
TH1F* ttbar_isrUp = DC.readWriteHisto(fTT, "base_isr_up/", histName, sf_ttbar, fout, fTT, "ttbar_isrUp", true);
TH1F* ttbar_isrDown = DC.readWriteHisto(fTT, "base_isr_do/", histName, sf_ttbar, fout, fTT, "ttbar_isrDown", true);
TH1F* ttbar_flavorqcdUp = DC.readWriteHisto(fTT, "flavorqcdup/", histName, sf_ttbar, fout, fTT, "ttbar_flavorqcdUp", true);
TH1F* ttbar_flavorqcdDown = DC.readWriteHisto(fTT, "flavorqcddown/", histName, sf_ttbar, fout, fTT, "ttbar_flavorqcdDown", true);
TH1F* ttbar_timeptetaUp = DC.readWriteHisto(fTT, "timeptetaup/", histName, sf_ttbar, fout, fTT, "ttbar_timepteta_"+ year + "Up", true);
TH1F* ttbar_timeptetaDown = DC.readWriteHisto(fTT, "timeptetadown/", histName, sf_ttbar, fout, fTT, "ttbar_timepteta_"+ year + "Down", true);
TH1F* ttbar_jerhfUp = DC.readWriteHisto(fTT, "reljerhfup/", histName, sf_ttbar, fout, fTT, "ttbar_jerhfUp", true);
TH1F* ttbar_jerhfDown = DC.readWriteHisto(fTT, "reljerhfdown/", histName, sf_ttbar, fout, fTT, "ttbar_jerhfDown", true);
TH1F* ttbar_relptbbUp = DC.readWriteHisto(fTT, "relptbbup/", histName, sf_ttbar, fout, fTT, "ttbar_relptbbUp", true);
TH1F* ttbar_relptbbDown = DC.readWriteHisto(fTT, "relptbbdown/", histName, sf_ttbar, fout, fTT, "ttbar_relptbbDown", true);
TH1F* ttbar_relpthfUp = DC.readWriteHisto(fTT, "relpthfup/", histName, sf_ttbar, fout, fTT, "ttbar_relpthfUp", true);
TH1F* ttbar_relpthfDown = DC.readWriteHisto(fTT, "relpthfdown/", histName, sf_ttbar, fout, fTT, "ttbar_relpthfDown", true);
TH1F* ttbar_relstatecUp = DC.readWriteHisto(fTT, "relstatecup/", histName, sf_ttbar, fout, fTT, "ttbar_relstatec_"+ year +"Up", true);
TH1F* ttbar_relstatecDown = DC.readWriteHisto(fTT, "relstatecdown/", histName, sf_ttbar, fout, fTT, "ttbar_relstatec_"+ year +"Down", true);
TH1F* ttbar_relsampleUp = DC.readWriteHisto(fTT, "relsampleup/", histName, sf_ttbar, fout, fTT, "ttbar_relsample_"+ year +"Up", true);

TH1F* ttbar_relsampleDown = DC.readWriteHisto(fTT, "relsampledown/", histName, sf_ttbar, fout, fTT, "ttbar_relsample_"+ year +"Down", true);
TH1F* ttbar_absstatUp = DC.readWriteHisto(fTT, "absstatup/", histName, sf_ttbar, fout, fTT, "ttbar_absstat_"+ year +"Up", true);
TH1F* ttbar_absstatDown = DC.readWriteHisto(fTT, "absstatdown/", histName, sf_ttbar, fout, fTT, "ttbar_absstat_"+ year +"Down", true);
TH1F* ttbar_abssclUp = DC.readWriteHisto(fTT, "abssclup/", histName, sf_ttbar, fout, fTT, "ttbar_abssclUp", true);
TH1F* ttbar_abssclDown = DC.readWriteHisto(fTT, "absscldown/", histName, sf_ttbar, fout, fTT, "ttbar_abssclDown", true);
TH1F* ttbar_absmpfbUp = DC.readWriteHisto(fTT, "absmpfbup/", histName, sf_ttbar, fout, fTT, "ttbar_absmpfbUp", true);
TH1F* ttbar_absmpfbDown = DC.readWriteHisto(fTT, "absmpfbdown/", histName, sf_ttbar, fout, fTT, "ttbar_absmpfbDown", true);
TH1F* ttbar_fragUp = DC.readWriteHisto(fTT, "fragup/", histName, sf_ttbar, fout, fTT, "ttbar_fragUp", true);
TH1F* ttbar_fragDown = DC.readWriteHisto(fTT, "fragdown/", histName, sf_ttbar, fout, fTT, "ttbar_fragDown", true);
TH1F* ttbar_pudataMCUp = DC.readWriteHisto(fTT, "pudatamcup/", histName, sf_ttbar, fout, fTT, "ttbar_pudataMCUp", true);
TH1F* ttbar_pudataMCDown = DC.readWriteHisto(fTT, "pudatamcdown/", histName, sf_ttbar, fout, fTT, "ttbar_pudataMCDown", true);
TH1F* ttbar_relptec1Up = DC.readWriteHisto(fTT, "relptec1up/", histName, sf_ttbar, fout, fTT, "ttbar_relptec1_" + year + "Up", true);
TH1F* ttbar_relptec1Down = DC.readWriteHisto(fTT, "relptec1down/", histName, sf_ttbar, fout, fTT, "ttbar_relptec1_" + year + "Down", true);
TH1F* ttbar_relptec2Up = DC.readWriteHisto(fTT, "relptec2up/", histName, sf_ttbar, fout, fTT, "ttbar_relptec2_"+ year +"Up", true);
TH1F* ttbar_relptec2Down = DC.readWriteHisto(fTT, "relptec2down/", histName, sf_ttbar, fout, fTT, "ttbar_relptec2_"+ year +"Down", true);
TH1F* ttbar_reljerec1Up = DC.readWriteHisto(fTT, "reljerec1up/", histName, sf_ttbar, fout, fTT, "ttbar_reljerec1_" + year + "Up", true);
TH1F* ttbar_reljerec1Down = DC.readWriteHisto(fTT, "reljerec1down/", histName, sf_ttbar, fout, fTT, "ttbar_reljerec1_" + year + "Down", true);
TH1F* ttbar_reljerec2Up = DC.readWriteHisto(fTT, "reljerec2up/", histName, sf_ttbar, fout, fTT, "ttbar_reljerec2_"+ year +"Up", true);
TH1F* ttbar_reljerec2Down = DC.readWriteHisto(fTT, "reljerec2down/", histName, sf_ttbar, fout, fTT, "ttbar_reljerec2_"+ year +"Down", true);
TH1F* ttbar_puptrefUp = DC.readWriteHisto(fTT, "puptrefup/", histName, sf_ttbar, fout, fTT, "ttbar_puptrefUp", true);
TH1F* ttbar_puptrefDown = DC.readWriteHisto(fTT, "puptrefdown/", histName, sf_ttbar, fout, fTT, "ttbar_puptrefDown", true);
TH1F* ttbar_puptec1Up = DC.readWriteHisto(fTT, "puptec1up/", histName, sf_ttbar, fout, fTT, "ttbar_puptec1Up", true);
TH1F* ttbar_puptec1Down = DC.readWriteHisto(fTT, "puptec1down/", histName, sf_ttbar, fout, fTT, "ttbar_puptec1Down", true);
TH1F* ttbar_puptec2Up = DC.readWriteHisto(fTT, "puptec2up/", histName, sf_ttbar, fout, fTT, "ttbar_puptec2Up", true);
TH1F* ttbar_puptec2Down = DC.readWriteHisto(fTT, "puptec2down/", histName, sf_ttbar, fout, fTT, "ttbar_puptec2Down", true);
TH1F* ttbar_bc_statUp = DC.readWriteHisto(fTT, "base_bc_stat_up/", histName, sf_ttbar, fout, fTT, "ttbar_bcstat_" + year +"_"+ workingpoint + "Up", true);                                                                                                                    
TH1F* ttbar_bc_statDown = DC.readWriteHisto(fTT, "base_bc_stat_do/", histName, sf_ttbar, fout, fTT, "ttbar_bcstat_"+ year +"_"+ +workingpoint + "Down", true); 
 TH1F* ttbar_lhemuFUp = DC.readWriteHisto(fTT, "base_bc_lhemuf_up/", histName, sf_ttbar, fout, fTT, "ttbar_lhemuF_"+ year +"_"+workingpoint+"Up", true);
 TH1F* ttbar_lhemuFDown = DC.readWriteHisto(fTT, "base_bc_lhemuf_do/", histName, sf_ttbar, fout, fTT, "ttbar_lhemuF_"+ year +"_"+workingpoint+"Down", true);
 TH1F* ttbar_lhemuRUp = DC.readWriteHisto(fTT, "base_lhemur_up/", histName, sf_ttbar, fout, fTT, "ttbar_lhemuR_"+ year +"_" + workingpoint +"Up", true);                                                                                                                       
TH1F* ttbar_lhemuRDown = DC.readWriteHisto(fTT, "base_lhemur_do/", histName, sf_ttbar, fout, fTT, "ttbar_lhemuR_"+ year +"_"+workingpoint + "Down", true);     
 TH1F* ttbar_extpUp = DC.readWriteHisto(fTT, "base_extp_up/", histName, sf_ttbar, fout, fTT, "ttbar_bcextp_" + year +"_"+ workingpoint+"Up", true);
TH1F* ttbar_extpDown = DC.readWriteHisto(fTT, "base_extp_do/", histName, sf_ttbar, fout, fTT, "ttbar_bcextp_" + year + "_" + workingpoint + "Down", true);
TH1F* ttbar_intpUp = DC.readWriteHisto(fTT, "base_intp_up/", histName, sf_ttbar, fout, fTT, "ttbar_bcintp_"+ year + "_" + workingpoint+"Up", true);
TH1F* ttbar_intpDown = DC.readWriteHisto(fTT, "base_intp_do/", histName, sf_ttbar, fout, fTT, "ttbar_bcintp_"+ year + "_" + workingpoint+"Down", true);
TH1F* ttbar_xdycUp = DC.readWriteHisto(fTT, "base_xdyc_up/", histName, sf_ttbar, fout, fTT, "ttbar_bcxdyc_"+ year +"_" + workingpoint+"Up", true);
TH1F* ttbar_xdycDown = DC.readWriteHisto(fTT, "base_xdyc_do/", histName, sf_ttbar, fout, fTT, "ttbar_bcxdyc_"+ year + "_" + workingpoint+"Down", true);
TH1F* ttbar_xdybUp = DC.readWriteHisto(fTT, "base_xdyb_up/", histName, sf_ttbar, fout, fTT, "ttbar_bcxdyb_" +year + "_" + workingpoint + "Up", true);
TH1F* ttbar_xdybDown = DC.readWriteHisto(fTT, "base_xdyb_do/", histName, sf_ttbar, fout, fTT, "ttbar_bcxdyb_" +year + "_" + workingpoint + "Down", true);
TH1F* ttbar_xwjcUp = DC.readWriteHisto(fTT, "base_xwj_up/", histName, sf_ttbar, fout, fTT, "ttbar_bcxwjc_"+ year  + "_" + workingpoint +"Up", true);
TH1F* ttbar_xwjcDown = DC.readWriteHisto(fTT, "base_xwj_do/", histName, sf_ttbar, fout, fTT, "ttbar_bcxwjc_" +year + "_" + workingpoint +"Down", true);
TH1F* ttbar_muEffUp = DC.readWriteHisto(fTT, "base_muEff_up/", histName, sf_ttbar, fout, fTT, "ttbar_muEffUp", true);
TH1F* ttbar_muEffDown = DC.readWriteHisto(fTT, "base_muEff_do/", histName, sf_ttbar, fout, fTT, "ttbar_muEffDown", true);
// TH1F* ttbar_base_pdfUp = DC.readWriteHisto(fTT, "base_prefire_up/", histName, sf_ttbar, fout, fTT, "ttbar_base_pdfUp", true);
//TH1F* ttbar_base_pdfDown = DC.readWriteHisto(fTT, "base_prefire_do/", histName, sf_ttbar, fout, fTT, "ttbar_base_pdfDown", true);
TH1F* ttbar_singpiecalUp = DC.readWriteHisto(fTT, "/singpiecalup/", histName, sf_ttbar, fout, fTT, "ttbar_singpiecalUp", true);
TH1F* ttbar_singpiecalDown = DC.readWriteHisto(fTT, "/singpiecaldown/", histName, sf_ttbar, fout, fTT, "ttbar_singpiecalDown", true);
TH1F* ttbar_singpihcalUp = DC.readWriteHisto(fTT, "/singpihcalup/", histName, sf_ttbar, fout, fTT, "ttbar_singpihcalUp", true);
TH1F* ttbar_singpihcalDown = DC.readWriteHisto(fTT,"/singpihcaldown/", histName, sf_ttbar, fout, fTT, "ttbar_singpihcalDown", true);
// For relstathf systematic
TH1F* ttbar_relstathfUp = DC.readWriteHisto(fTT, "relstathfup/", histName, sf_ttbar, fout, fTT, "ttbar_relstathf_"+ year +"Up", true);
TH1F* ttbar_relstathfDown = DC.readWriteHisto(fTT, "relstathfdown/", histName, sf_ttbar, fout, fTT, "ttbar_relstathf_"+ year +"Down", true);
// For relstatfsr systematic
TH1F* ttbar_relstatfsrUp = DC.readWriteHisto(fTT, "relstatfsrup/", histName, sf_ttbar, fout, fTT, "ttbar_relstatfsr_"+ year +"Up", true);
TH1F* ttbar_relstatfsrDown = DC.readWriteHisto(fTT, "relstatfsrdown/", histName, sf_ttbar, fout, fTT, "ttbar_relstatfsr_"+ year +"Down", true);
 TH1F* ttbar_relfsrUp = DC.readWriteHisto(fTT, "relfsrup/", histName, sf_ttbar, fout, fTT, "ttbar_relfsrUp", true);
TH1F* ttbar_relfsrDown = DC.readWriteHisto(fTT, "relfsrdown/", histName, sf_ttbar, fout, fTT, "ttbar_relfsrDown", true);
TH1F* ttbar_relbalUp = DC.readWriteHisto(fTT, "relbalup/", histName, sf_ttbar, fout, fTT, "ttbar_relbalUp", true);
TH1F* ttbar_relbalDown = DC.readWriteHisto(fTT, "relbaldown/", histName, sf_ttbar, fout, fTT, "ttbar_relbalDown", true);
TH1F* ttbar_reljerhfUp = DC.readWriteHisto(fTT, "reljerhfup/", histName, sf_ttbar, fout, fTT, "ttbar_reljerhfUp", true);
TH1F* ttbar_reljerhfDown = DC.readWriteHisto(fTT, "reljerhfdown/", histName, sf_ttbar, fout, fTT, "ttbar_reljerhfDown", true);
// For cp5 systematic
TH1F* ttbar_cp5Up = DC.readWriteHisto(fTT, "cp5up/", histName, sf_ttbar, fout, fTT, "ttbar_cp5_ttUp", true);
TH1F* ttbar_cp5Down = DC.readWriteHisto(fTT, "cp5down/", histName, sf_ttbar, fout, fTT, "ttbar_cp5_ttDown", true);

// For hdamp systematic
TH1F* ttbar_hdampUp = DC.readWriteHisto(fTT, "hdampup/", histName, sf_ttbar, fout, fTT, "ttbar_hdamp_ttUp", true);
TH1F* ttbar_hdampDown = DC.readWriteHisto(fTT, "hdampdown/", histName, sf_ttbar, fout, fTT, "ttbar_hdamp_ttDown", true);

// For mtop systematic
TH1F* ttbar_mtopUp = DC.readWriteHisto(fTT, "mtopup/", histName, sf_ttbar, fout, fTT, "ttbar_topmass_ttUp", true);
TH1F* ttbar_mtopDown = DC.readWriteHisto(fTT, "mtopdown/", histName, sf_ttbar, fout, fTT, "ttbar_topmass_ttDown", true);
 TH1F* ttbar_pdfUp = DC.readWriteHisto(fTT, "base_prefire_up/", histName, sf_ttbar, fout, fTT, "ttbar_pdfUp", true);
TH1F* ttbar_pdfDown = DC.readWriteHisto(fTT, "base_prefire_do/", histName, sf_ttbar, fout, fTT, "ttbar_pdfDown", true);
TH1F* ttbar_puptbbUp = DC.readWriteHisto(fTT, "puptbbup/", histName, sf_ttbar, fout, fTT, "ttbar_puptbbUp", true);
TH1F* ttbar_puptbbDown = DC.readWriteHisto(fTT, "puptbbdown/", histName, sf_ttbar, fout, fTT, "ttbar_puptbbDown", true);
TH1F* ttbar_pupthfUp = DC.readWriteHisto(fTT, "pupthfup/", histName, sf_ttbar, fout, fTT, "ttbar_pupthfUp", true);
TH1F* ttbar_pupthfDown = DC.readWriteHisto(fTT, "pupthfdown/", histName, sf_ttbar, fout, fTT, "ttbar_pupthfDown", true);
TH1F* ttbar_topPtUp = DC.readWriteHisto(fTT, "base_topPt_up/", histName, sf_ttbar, fout, fTT, "ttbar_topPtUp", true);
TH1F* ttbar_topPtDown = DC.readWriteHisto(fTT, "base_topPt_do/", histName, sf_ttbar, fout, fTT, "ttbar_topPtDown", true);
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
// normalizeHistogram(ttbar_base_pdfUp, ttbar);
// normalizeHistogram(ttbar_base_pdfDown, ttbar);
// Normalize all bctagging uncertainties
normalizeHistogram(ttbar_lhemuFUp, ttbar);
normalizeHistogram(ttbar_lhemuFDown, ttbar);
normalizeHistogram(ttbar_lhemuRUp, ttbar);
normalizeHistogram(ttbar_lhemuRDown, ttbar);
normalizeHistogram(ttbar_extpUp, ttbar);
normalizeHistogram(ttbar_extpDown, ttbar);
normalizeHistogram(ttbar_intpUp, ttbar);
normalizeHistogram(ttbar_intpDown, ttbar);
normalizeHistogram(ttbar_xdycUp, ttbar);
normalizeHistogram(ttbar_xdycDown, ttbar);
normalizeHistogram(ttbar_xdybUp, ttbar);
normalizeHistogram(ttbar_xdybDown, ttbar);
normalizeHistogram(ttbar_xwjcUp, ttbar);
normalizeHistogram(ttbar_xwjcDown, ttbar);
  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  ttbar_bc_statUp->Write();
  ttbar_bc_statDown->Write();
  ttbar_fsrUp->Write();
  ttbar_fsrDown->Write();
  ttbar_isrUp->Write();
  ttbar_isrDown->Write();
  ttbar_lhemuFUp->Write();
ttbar_lhemuFDown->Write();
ttbar_lhemuRUp->Write();
ttbar_lhemuRDown->Write();
ttbar_extpUp->Write();
ttbar_extpDown->Write();
ttbar_intpUp->Write();
ttbar_intpDown->Write();
ttbar_xdycUp->Write();
ttbar_xdycDown->Write();
ttbar_xdybUp->Write();
ttbar_xdybDown->Write();
ttbar_xwjcUp->Write();
ttbar_xwjcDown->Write();

  // ttbar_base_pdfUp->Write();
  // ttbar_base_pdfDown->Write();




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
TH1F* ttg = DC.readWriteHisto(fTG, "base/", histName, sf_ttg, fout, fTT, "ttg", true);
TH1F* ttg_JESUp = DC.readWriteHisto(fTG, "base_JEC_up/", histName, sf_ttg, fout, fTT, "ttg_JESUp", true);
TH1F* ttg_JESDown = DC.readWriteHisto(fTG, "base_JEC_do/", histName, sf_ttg, fout, fTT, "ttg_JESDown", true);
TH1F* ttg_PileupUp = DC.readWriteHisto(fTG, "base_PUWeight_up/", histName, sf_ttg, fout, fTT, "ttg_PileupUp", true);
TH1F* ttg_PileupDown = DC.readWriteHisto(fTG, "base_PUWeight_do/", histName, sf_ttg, fout, fTT, "ttg_PileupDown", true);
TH1F* ttg_JERUp = DC.readWriteHisto(fTG, "jerup/", histName, sf_ttg, fout, fTT, "ttg_JER_"+ year + "Up", true);
TH1F* ttg_JERDown = DC.readWriteHisto(fTG, "jerdown/", histName, sf_ttg, fout, fTT, "ttg_JER_"+ year + "Down", true);
TH1F* ttg_prefireUp = DC.readWriteHisto(fTG, "base_prefire_up/", histName, sf_ttg, fout, fTT, "ttg_prefireUp", true);
TH1F* ttg_prefireDown = DC.readWriteHisto(fTG, "base_prefire_do/", histName, sf_ttg, fout, fTT, "ttg_prefireDown", true);
TH1F* ttg_fsrUp = DC.readWriteHisto(fTG, "base_fsr_up/", histName, sf_ttg, fout, fTT, "ttg_fsrUp", true);
TH1F* ttg_fsrDown = DC.readWriteHisto(fTG, "base_fsr_do/", histName, sf_ttg, fout, fTT, "ttg_fsrDown", true);
TH1F* ttg_isrUp = DC.readWriteHisto(fTG, "base_isr_up/", histName, sf_ttg, fout, fTT, "ttg_isrUp", true);
TH1F* ttg_isrDown = DC.readWriteHisto(fTG, "base_isr_do/", histName, sf_ttg, fout, fTT, "ttg_isrDown", true);
TH1F* ttg_flavorqcdUp = DC.readWriteHisto(fTG, "flavorqcdup/", histName, sf_ttg, fout, fTT, "ttg_flavorqcdUp", true);
TH1F* ttg_flavorqcdDown = DC.readWriteHisto(fTG, "flavorqcddown/", histName, sf_ttg, fout, fTT, "ttg_flavorqcdDown", true);
TH1F* ttg_timeptetaUp = DC.readWriteHisto(fTG, "timeptetaup/", histName, sf_ttg, fout, fTT, "ttg_timepteta_"+ year + "Up", true);
TH1F* ttg_timeptetaDown = DC.readWriteHisto(fTG, "timeptetadown/", histName, sf_ttg, fout, fTT, "ttg_timepteta_"+ year + "Down", true);
TH1F* ttg_jerhfUp = DC.readWriteHisto(fTG, "reljerhfup/", histName, sf_ttg, fout, fTT, "ttg_jerhfUp", true);
TH1F* ttg_jerhfDown = DC.readWriteHisto(fTG, "reljerhfdown/", histName, sf_ttg, fout, fTT, "ttg_jerhfDown", true);
TH1F* ttg_relptbbUp = DC.readWriteHisto(fTG, "relptbbup/", histName, sf_ttg, fout, fTT, "ttg_relptbbUp", true);
TH1F* ttg_relptbbDown = DC.readWriteHisto(fTG, "relptbbdown/", histName, sf_ttg, fout, fTT, "ttg_relptbbDown", true);
TH1F* ttg_relpthfUp = DC.readWriteHisto(fTG, "relpthfup/", histName, sf_ttg, fout, fTT, "ttg_relpthfUp", true);
TH1F* ttg_relpthfDown = DC.readWriteHisto(fTG, "relpthfdown/", histName, sf_ttg, fout, fTT, "ttg_relpthfDown", true);
TH1F* ttg_relstatecUp = DC.readWriteHisto(fTG, "relstatecup/", histName, sf_ttg, fout, fTT, "ttg_relstatec_" + year + "Up", true);
TH1F* ttg_relstatecDown = DC.readWriteHisto(fTG, "relstatecdown/", histName, sf_ttg, fout, fTT, "ttg_relstatec_" + year + "Down", true);
TH1F* ttg_absstatUp = DC.readWriteHisto(fTG, "absstatup/", histName, sf_ttg, fout, fTT, "ttg_absstat_" + year + "Up", true);
TH1F* ttg_absstatDown = DC.readWriteHisto(fTG, "absstatdown/", histName, sf_ttg, fout, fTT, "ttg_absstat_" + year + "Down", true);
TH1F* ttg_abssclUp = DC.readWriteHisto(fTG, "abssclup/", histName, sf_ttg, fout, fTT, "ttg_abssclUp", true);
TH1F* ttg_abssclDown = DC.readWriteHisto(fTG, "absscldown/", histName, sf_ttg, fout, fTT, "ttg_abssclDown", true);
TH1F* ttg_absmpfbUp = DC.readWriteHisto(fTG, "absmpfbup/", histName, sf_ttg, fout, fTT, "ttg_absmpfbUp", true);
TH1F* ttg_absmpfbDown = DC.readWriteHisto(fTG, "absmpfbdown/", histName, sf_ttg, fout, fTT, "ttg_absmpfbDown", true);
TH1F* ttg_fragUp = DC.readWriteHisto(fTG, "fragup/", histName, sf_ttg, fout, fTT, "ttg_fragUp", true);
TH1F* ttg_fragDown = DC.readWriteHisto(fTG, "fragdown/", histName, sf_ttg, fout, fTT, "ttg_fragDown", true);
TH1F* ttg_pudataMCUp = DC.readWriteHisto(fTG, "pudatamcup/", histName, sf_ttg, fout, fTT, "ttg_pudataMCUp", true);
TH1F* ttg_pudataMCDown = DC.readWriteHisto(fTG, "pudatamcdown/", histName, sf_ttg, fout, fTT, "ttg_pudataMCDown", true);
TH1F* ttg_relptec1Up = DC.readWriteHisto(fTG, "relptec1up/", histName, sf_ttg, fout, fTT, "ttg_relptec1_" + year + "Up", true);
TH1F* ttg_relptec1Down = DC.readWriteHisto(fTG, "relptec1down/", histName, sf_ttg, fout, fTT, "ttg_relptec1_" + year + "Down", true);
TH1F* ttg_relptec2Up = DC.readWriteHisto(fTG, "relptec2up/", histName, sf_ttg, fout, fTT, "ttg_relptec2_" + year + "Up", true);
TH1F* ttg_relptec2Down = DC.readWriteHisto(fTG, "relptec2down/", histName, sf_ttg, fout, fTT, "ttg_relptec2_" + year + "Down", true);
TH1F* ttg_reljerec1Up = DC.readWriteHisto(fTG, "reljerec1up/", histName, sf_ttg, fout, fTT, "ttg_reljerec1_" + year + "Up", true);
TH1F* ttg_reljerec1Down = DC.readWriteHisto(fTG, "reljerec1down/", histName, sf_ttg, fout, fTT, "ttg_reljerec1_" + year + "Down", true);
TH1F* ttg_reljerec2Up = DC.readWriteHisto(fTG, "reljerec2up/", histName, sf_ttg, fout, fTT, "ttg_reljerec2_" + year + "Up", true);
TH1F* ttg_reljerec2Down = DC.readWriteHisto(fTG, "reljerec2down/", histName, sf_ttg, fout, fTT, "ttg_reljerec2_" + year + "Down", true);
TH1F* ttg_puptrefUp = DC.readWriteHisto(fTG, "puptrefup/", histName, sf_ttg, fout, fTT, "ttg_puptrefUp", true);
TH1F* ttg_puptrefDown = DC.readWriteHisto(fTG, "puptrefdown/", histName, sf_ttg, fout, fTT, "ttg_puptrefDown", true);
TH1F* ttg_puptec1Up = DC.readWriteHisto(fTG, "puptec1up/", histName, sf_ttg, fout, fTT, "ttg_puptec1Up", true);
TH1F* ttg_puptec1Down = DC.readWriteHisto(fTG, "puptec1down/", histName, sf_ttg, fout, fTT, "ttg_puptec1Down", true);
TH1F* ttg_puptec2Up = DC.readWriteHisto(fTG, "puptec2up/", histName, sf_ttg, fout, fTT, "ttg_puptec2Up", true);
TH1F* ttg_puptec2Down = DC.readWriteHisto(fTG, "puptec2down/", histName, sf_ttg, fout, fTT, "ttg_puptec2Down", true);
// B-tagging decorrelated systematics
TH1F* ttg_bc_statUp = DC.readWriteHisto(fTG, "base_bc_stat_up/", histName, sf_ttg, fout, fTT, "ttg_bcstat_" + year + "_" + workingpoint + "Up", true);
TH1F* ttg_bc_statDown = DC.readWriteHisto(fTG, "base_bc_stat_do/", histName, sf_ttg, fout, fTT, "ttg_bcstat_" + year + "_" + workingpoint + "Down", true);
TH1F* ttg_lhemuFUp = DC.readWriteHisto(fTG, "base_bc_lhemuf_up/", histName, sf_ttg, fout, fTT, "ttg_lhemuF_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttg_lhemuFDown = DC.readWriteHisto(fTG, "base_bc_lhemuf_do/", histName, sf_ttg, fout, fTT, "ttg_lhemuF_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttg_lhemuRUp = DC.readWriteHisto(fTG, "base_lhemur_up/", histName, sf_ttg, fout, fTT, "ttg_lhemuR_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttg_lhemuRDown = DC.readWriteHisto(fTG, "base_lhemur_do/", histName, sf_ttg, fout, fTT, "ttg_lhemuR_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttg_extpUp = DC.readWriteHisto(fTG, "base_extp_up/", histName, sf_ttg, fout, fTT, "ttg_bcextp_" + year + "_" + workingpoint + "Up", true);
TH1F* ttg_extpDown = DC.readWriteHisto(fTG, "base_extp_do/", histName, sf_ttg, fout, fTT, "ttg_bcextp_" + year + "_" + workingpoint + "Down", true);
TH1F* ttg_intpUp = DC.readWriteHisto(fTG, "base_intp_up/", histName, sf_ttg, fout, fTT, "ttg_bcintp_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttg_intpDown = DC.readWriteHisto(fTG, "base_intp_do/", histName, sf_ttg, fout, fTT, "ttg_bcintp_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttg_xdycUp = DC.readWriteHisto(fTG, "base_xdyc_up/", histName, sf_ttg, fout, fTT, "ttg_bcxdyc_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttg_xdycDown = DC.readWriteHisto(fTG, "base_xdyc_do/", histName, sf_ttg, fout, fTT, "ttg_bcxdyc_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttg_xdybUp = DC.readWriteHisto(fTG, "base_xdyb_up/", histName, sf_ttg, fout, fTT, "ttg_bcxdyb_" + year + "_" + workingpoint + "Up", true);
TH1F* ttg_xdybDown = DC.readWriteHisto(fTG, "base_xdyb_do/", histName, sf_ttg, fout, fTT, "ttg_bcxdyb_" + year + "_" + workingpoint + "Down", true);
TH1F* ttg_xwjcUp = DC.readWriteHisto(fTG, "base_xwj_up/", histName, sf_ttg, fout, fTT, "ttg_bcxwjc_" + year + "_" + workingpoint + "Up", true);
TH1F* ttg_xwjcDown = DC.readWriteHisto(fTG, "base_xwj_do/", histName, sf_ttg, fout, fTT, "ttg_bcxwjc_" + year + "_" + workingpoint + "Down", true);
TH1F* ttg_muEffUp = DC.readWriteHisto(fTG, "base_muEff_up/", histName, sf_ttg, fout, fTT, "ttg_muEffUp", true);
TH1F* ttg_muEffDown = DC.readWriteHisto(fTG, "base_muEff_do/", histName, sf_ttg, fout, fTT, "ttg_muEffDown", true);
TH1F* ttg_singpiecalUp = DC.readWriteHisto(fTG, "/singpiecalup/", histName, sf_ttg, fout, fTT, "ttg_singpiecalUp", true);
TH1F* ttg_singpiecalDown = DC.readWriteHisto(fTG, "/singpiecaldown/", histName, sf_ttg, fout, fTT, "ttg_singpiecalDown", true);
TH1F* ttg_singpihcalUp = DC.readWriteHisto(fTG, "/singpihcalup/", histName, sf_ttg, fout, fTT, "ttg_singpihcalUp", true);
TH1F* ttg_singpihcalDown = DC.readWriteHisto(fTG,"/singpihcaldown/", histName, sf_ttg, fout, fTT, "ttg_singpihcalDown", true);
TH1F* ttg_relsampleUp = DC.readWriteHisto(fTG, "relsampleup/", histName, sf_ttg, fout, fTT, "ttg_relsample_" + year + "Up", true);
TH1F* ttg_relsampleDown = DC.readWriteHisto(fTG, "relsampledown/", histName, sf_ttg, fout, fTT, "ttg_relsample_" + year + "Down", true);
TH1F* ttg_relstatfsrUp = DC.readWriteHisto(fTG, "relstatfsrup/", histName, sf_ttg, fout, fTT, "ttg_relstatfsr_" + year + "Up", true);
TH1F* ttg_relstatfsrDown = DC.readWriteHisto(fTG, "relstatfsrdown/", histName, sf_ttg, fout, fTT, "ttg_relstatfsr_" + year + "Down", true);
TH1F* ttg_relfsrUp = DC.readWriteHisto(fTG, "relfsrup/", histName, sf_ttg, fout, fTT, "ttg_relfsrUp", true);
TH1F* ttg_relfsrDown = DC.readWriteHisto(fTG, "relfsrdown/", histName, sf_ttg, fout, fTT, "ttg_relfsrDown", true);
TH1F* ttg_relbalUp = DC.readWriteHisto(fTG, "relbalup/", histName, sf_ttg, fout, fTT, "ttg_relbalUp", true);
TH1F* ttg_relbalDown = DC.readWriteHisto(fTG, "relbaldown/", histName, sf_ttg, fout, fTT, "ttg_relbalDown", true);

TH1F* ttg_relstathfUp = DC.readWriteHisto(fTG, "relstathfup/", histName, sf_ttg, fout, fTT, "ttg_relstathf_" + year + "Up", true);
TH1F* ttg_relstathfDown = DC.readWriteHisto(fTG, "relstathfdown/", histName, sf_ttg, fout, fTT, "ttg_relstathf_" + year + "Down", true);

TH1F* ttg_pdfUp = DC.readWriteHisto(fTG, "base_prefire_up/", histName, sf_ttg, fout, fTT, "ttg_pdfUp", true);
TH1F* ttg_pdfDown = DC.readWriteHisto(fTG, "base_prefire_do/", histName, sf_ttg, fout, fTT, "ttg_pdfDown", true);
TH1F* ttg_puptbbUp = DC.readWriteHisto(fTG, "puptbbup/", histName, sf_ttg, fout, fTT, "ttg_puptbbUp", true);
TH1F* ttg_puptbbDown = DC.readWriteHisto(fTG, "puptbbdown/", histName, sf_ttg, fout, fTT, "ttg_puptbbDown", true);
TH1F* ttg_reljerhfUp = DC.readWriteHisto(fTG, "reljerhfup/", histName, sf_ttg, fout, fTT, "ttg_reljerhfUp", true);
TH1F* ttg_reljerhfDown = DC.readWriteHisto(fTG, "reljerhfdown/", histName, sf_ttg, fout, fTT, "ttg_reljerhfDown", true);
TH1F* ttg_pupthfUp = DC.readWriteHisto(fTG, "pupthfup/", histName, sf_ttg, fout, fTT, "ttg_pupthfUp", true);
TH1F* ttg_pupthfDown = DC.readWriteHisto(fTG, "pupthfdown/", histName, sf_ttg, fout, fTT, "ttg_pupthfDown", true);
 

  // Assuming ttg and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
  //double baseIntegral = ttg->Integral();

normalizeHistogram(ttg_bc_statUp, ttg);
normalizeHistogram(ttg_bc_statDown, ttg);
normalizeHistogram(ttg_fsrUp, ttg);
normalizeHistogram(ttg_fsrDown, ttg);
normalizeHistogram(ttg_isrUp, ttg);
normalizeHistogram(ttg_isrDown, ttg);
// normalizeHistogram(ttg_base_pdfUp, ttg);
// normalizeHistogram(ttg_base_pdfDown, ttg);
// normalizeHistogram(ttg_lhemuFUp, ttg);
// normalizeHistogram(ttg_lhemuFDown, ttg);
// normalizeHistogram(ttg_lhemuRUp, ttg);
// normalizeHistogram(ttg_lhemuRDown, ttg);
// normalizeHistogram(ttg_extpUp, ttg);
// normalizeHistogram(ttg_extpDown, ttg);
// normalizeHistogram(ttg_intpUp, ttg);
// normalizeHistogram(ttg_intpDown, ttg);
// normalizeHistogram(ttg_xdycUp, ttg);
// normalizeHistogram(ttg_xdycDown, ttg);
// normalizeHistogram(ttg_xdybUp, ttg);
// normalizeHistogram(ttg_xdybDown, ttg);
// normalizeHistogram(ttg_xwjcUp, ttg);
// normalizeHistogram(ttg_xwjcDown, ttg);
  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  ttg_bc_statUp->Write();
  ttg_bc_statDown->Write();
  ttg_fsrUp->Write();
  ttg_fsrDown->Write();
  ttg_isrUp->Write();
  ttg_isrDown->Write();
  // ttg_base_pdfUp->Write();
  // ttg_base_pdfDown->Write();
// ttg_lhemuFUp->Write();
// ttg_lhemuFDown->Write();
// ttg_lhemuRUp->Write();
// ttg_lhemuRDown->Write();
// ttg_extpUp->Write();
// ttg_extpDown->Write();
// ttg_intpUp->Write();
// ttg_intpDown->Write();
// ttg_xdycUp->Write();
// ttg_xdycDown->Write();
// ttg_xdybUp->Write();
// ttg_xdybDown->Write();
// ttg_xwjcUp->Write();
// ttg_xwjcDown->Write();



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
TH1F* tth = DC.readWriteHisto(fTH, "base/", histName, sf_tth, fout, fTT, "tth", true);
TH1F* tth_JESUp = DC.readWriteHisto(fTH, "base_JEC_up/", histName, sf_tth, fout, fTT, "tth_JESUp", true);
TH1F* tth_JESDown = DC.readWriteHisto(fTH, "base_JEC_do/", histName, sf_tth, fout, fTT, "tth_JESDown", true);
TH1F* tth_PileupUp = DC.readWriteHisto(fTH, "base_PUWeight_up/", histName, sf_tth, fout, fTT, "tth_PileupUp", true);
TH1F* tth_PileupDown = DC.readWriteHisto(fTH, "base_PUWeight_do/", histName, sf_tth, fout, fTT, "tth_PileupDown", true);
TH1F* tth_JERUp = DC.readWriteHisto(fTH, "jerup/", histName, sf_tth, fout, fTT, "tth_JER_"+ year + "Up", true);
TH1F* tth_JERDown = DC.readWriteHisto(fTH, "jerdown/", histName, sf_tth, fout, fTT, "tth_JER_"+ year + "Down", true);
TH1F* tth_prefireUp = DC.readWriteHisto(fTH, "base_prefire_up/", histName, sf_tth, fout, fTT, "tth_prefireUp", true);
TH1F* tth_prefireDown = DC.readWriteHisto(fTH, "base_prefire_do/", histName, sf_tth, fout, fTT, "tth_prefireDown", true);
TH1F* tth_fsrUp = DC.readWriteHisto(fTH, "base_fsr_up/", histName, sf_tth, fout, fTT, "tth_fsrUp", true);
TH1F* tth_fsrDown = DC.readWriteHisto(fTH, "base_fsr_do/", histName, sf_tth, fout, fTT, "tth_fsrDown", true);
TH1F* tth_isrUp = DC.readWriteHisto(fTH, "base_isr_up/", histName, sf_tth, fout, fTT, "tth_isrUp", true);
TH1F* tth_isrDown = DC.readWriteHisto(fTH, "base_isr_do/", histName, sf_tth, fout, fTT, "tth_isrDown", true);
TH1F* tth_flavorqcdUp = DC.readWriteHisto(fTH, "flavorqcdup/", histName, sf_tth, fout, fTT, "tth_flavorqcdUp", true);
TH1F* tth_flavorqcdDown = DC.readWriteHisto(fTH, "flavorqcddown/", histName, sf_tth, fout, fTT, "tth_flavorqcdDown", true);
TH1F* tth_timeptetaUp = DC.readWriteHisto(fTH, "timeptetaup/", histName, sf_tth, fout, fTT, "tth_timepteta_"+ year + "Up", true);
TH1F* tth_timeptetaDown = DC.readWriteHisto(fTH, "timeptetadown/", histName, sf_tth, fout, fTT, "tth_timepteta_"+ year + "Down", true);
TH1F* tth_jerhfUp = DC.readWriteHisto(fTH, "reljerhfup/", histName, sf_tth, fout, fTT, "tth_jerhfUp", true);
TH1F* tth_jerhfDown = DC.readWriteHisto(fTH, "reljerhfdown/", histName, sf_tth, fout, fTT, "tth_jerhfDown", true);
TH1F* tth_relptbbUp = DC.readWriteHisto(fTH, "relptbbup/", histName, sf_tth, fout, fTT, "tth_relptbbUp", true);
TH1F* tth_relptbbDown = DC.readWriteHisto(fTH, "relptbbdown/", histName, sf_tth, fout, fTT, "tth_relptbbDown", true);
TH1F* tth_relpthfUp = DC.readWriteHisto(fTH, "relpthfup/", histName, sf_tth, fout, fTT, "tth_relpthfUp", true);
TH1F* tth_relpthfDown = DC.readWriteHisto(fTH, "relpthfdown/", histName, sf_tth, fout, fTT, "tth_relpthfDown", true);
TH1F* tth_relstatecUp = DC.readWriteHisto(fTH, "relstatecup/", histName, sf_tth, fout, fTT, "tth_relstatec_" + year + "Up", true);
TH1F* tth_relstatecDown = DC.readWriteHisto(fTH, "relstatecdown/", histName, sf_tth, fout, fTT, "tth_relstatec_" + year + "Down", true);
TH1F* tth_absstatUp = DC.readWriteHisto(fTH, "absstatup/", histName, sf_tth, fout, fTT, "tth_absstat_" + year + "Up", true);
TH1F* tth_absstatDown = DC.readWriteHisto(fTH, "absstatdown/", histName, sf_tth, fout, fTT, "tth_absstat_" + year + "Down", true);
TH1F* tth_abssclUp = DC.readWriteHisto(fTH, "abssclup/", histName, sf_tth, fout, fTT, "tth_abssclUp", true);
TH1F* tth_abssclDown = DC.readWriteHisto(fTH, "absscldown/", histName, sf_tth, fout, fTT, "tth_abssclDown", true);
TH1F* tth_absmpfbUp = DC.readWriteHisto(fTH, "absmpfbup/", histName, sf_tth, fout, fTT, "tth_absmpfbUp", true);
TH1F* tth_absmpfbDown = DC.readWriteHisto(fTH, "absmpfbdown/", histName, sf_tth, fout, fTT, "tth_absmpfbDown", true);
TH1F* tth_fragUp = DC.readWriteHisto(fTH, "fragup/", histName, sf_tth, fout, fTT, "tth_fragUp", true);
TH1F* tth_fragDown = DC.readWriteHisto(fTH, "fragdown/", histName, sf_tth, fout, fTT, "tth_fragDown", true);
TH1F* tth_pudataMCUp = DC.readWriteHisto(fTH, "pudatamcup/", histName, sf_tth, fout, fTT, "tth_pudataMCUp", true);
TH1F* tth_pudataMCDown = DC.readWriteHisto(fTH, "pudatamcdown/", histName, sf_tth, fout, fTT, "tth_pudataMCDown", true);
TH1F* tth_relptec1Up = DC.readWriteHisto(fTH, "relptec1up/", histName, sf_tth, fout, fTT, "tth_relptec1_" + year + "Up", true);
TH1F* tth_relptec1Down = DC.readWriteHisto(fTH, "relptec1down/", histName, sf_tth, fout, fTT, "tth_relptec1_" + year + "Down", true);
TH1F* tth_relptec2Up = DC.readWriteHisto(fTH, "relptec2up/", histName, sf_tth, fout, fTT, "tth_relptec2_" + year + "Up", true);
TH1F* tth_relptec2Down = DC.readWriteHisto(fTH, "relptec2down/", histName, sf_tth, fout, fTT, "tth_relptec2_" + year + "Down", true);
TH1F* tth_reljerec1Up = DC.readWriteHisto(fTH, "reljerec1up/", histName, sf_tth, fout, fTT, "tth_reljerec1_" + year + "Up", true);
TH1F* tth_reljerec1Down = DC.readWriteHisto(fTH, "reljerec1down/", histName, sf_tth, fout, fTT, "tth_reljerec1_" + year + "Down", true);
TH1F* tth_reljerec2Up = DC.readWriteHisto(fTH, "reljerec2up/", histName, sf_tth, fout, fTT, "tth_reljerec2_" + year + "Up", true);
TH1F* tth_reljerec2Down = DC.readWriteHisto(fTH, "reljerec2down/", histName, sf_tth, fout, fTT, "tth_reljerec2_" + year + "Down", true);
TH1F* tth_puptrefUp = DC.readWriteHisto(fTH, "puptrefup/", histName, sf_tth, fout, fTT, "tth_puptrefUp", true);
TH1F* tth_puptrefDown = DC.readWriteHisto(fTH, "puptrefdown/", histName, sf_tth, fout, fTT, "tth_puptrefDown", true);
TH1F* tth_puptec1Up = DC.readWriteHisto(fTH, "puptec1up/", histName, sf_tth, fout, fTT, "tth_puptec1Up", true);
TH1F* tth_puptec1Down = DC.readWriteHisto(fTH, "puptec1down/", histName, sf_tth, fout, fTT, "tth_puptec1Down", true);
TH1F* tth_puptec2Up = DC.readWriteHisto(fTH, "puptec2up/", histName, sf_tth, fout, fTT, "tth_puptec2Up", true);
TH1F* tth_puptec2Down = DC.readWriteHisto(fTH, "puptec2down/", histName, sf_tth, fout, fTT, "tth_puptec2Down", true);
// B-tagging decorrelated systematics
TH1F* tth_bc_statUp = DC.readWriteHisto(fTH, "base_bc_stat_up/", histName, sf_tth, fout, fTT, "tth_bcstat_" + year + "_" + workingpoint + "Up", true);
TH1F* tth_bc_statDown = DC.readWriteHisto(fTH, "base_bc_stat_do/", histName, sf_tth, fout, fTT, "tth_bcstat_" + year + "_" + workingpoint + "Down", true);
TH1F* tth_lhemuFUp = DC.readWriteHisto(fTH, "base_bc_lhemuf_up/", histName, sf_tth, fout, fTT, "tth_lhemuF_"+ year + "_" + workingpoint + "Up", true);
TH1F* tth_lhemuFDown = DC.readWriteHisto(fTH, "base_bc_lhemuf_do/", histName, sf_tth, fout, fTT, "tth_lhemuF_"+ year + "_" + workingpoint + "Down", true);
TH1F* tth_lhemuRUp = DC.readWriteHisto(fTH, "base_lhemur_up/", histName, sf_tth, fout, fTT, "tth_lhemuR_"+ year + "_" + workingpoint + "Up", true);
TH1F* tth_lhemuRDown = DC.readWriteHisto(fTH, "base_lhemur_do/", histName, sf_tth, fout, fTT, "tth_lhemuR_"+ year + "_" + workingpoint + "Down", true);
TH1F* tth_extpUp = DC.readWriteHisto(fTH, "base_extp_up/", histName, sf_tth, fout, fTT, "tth_bcextp_" + year + "_" + workingpoint + "Up", true);
TH1F* tth_extpDown = DC.readWriteHisto(fTH, "base_extp_do/", histName, sf_tth, fout, fTT, "tth_bcextp_" + year + "_" + workingpoint + "Down", true);
TH1F* tth_intpUp = DC.readWriteHisto(fTH, "base_intp_up/", histName, sf_tth, fout, fTT, "tth_bcintp_"+ year + "_" + workingpoint + "Up", true);
TH1F* tth_intpDown = DC.readWriteHisto(fTH, "base_intp_do/", histName, sf_tth, fout, fTT, "tth_bcintp_"+ year + "_" + workingpoint + "Down", true);
TH1F* tth_xdycUp = DC.readWriteHisto(fTH, "base_xdyc_up/", histName, sf_tth, fout, fTT, "tth_bcxdyc_"+ year + "_" + workingpoint + "Up", true);
TH1F* tth_xdycDown = DC.readWriteHisto(fTH, "base_xdyc_do/", histName, sf_tth, fout, fTT, "tth_bcxdyc_"+ year + "_" + workingpoint + "Down", true);
TH1F* tth_xdybUp = DC.readWriteHisto(fTH, "base_xdyb_up/", histName, sf_tth, fout, fTT, "tth_bcxdyb_" + year + "_" + workingpoint + "Up", true);
TH1F* tth_xdybDown = DC.readWriteHisto(fTH, "base_xdyb_do/", histName, sf_tth, fout, fTT, "tth_bcxdyb_" + year + "_" + workingpoint + "Down", true);
TH1F* tth_xwjcUp = DC.readWriteHisto(fTH, "base_xwj_up/", histName, sf_tth, fout, fTT, "tth_bcxwjc_" + year + "_" + workingpoint + "Up", true);
TH1F* tth_xwjcDown = DC.readWriteHisto(fTH, "base_xwj_do/", histName, sf_tth, fout, fTT, "tth_bcxwjc_" + year + "_" + workingpoint + "Down", true);
TH1F* tth_muEffUp = DC.readWriteHisto(fTH, "base_muEff_up/", histName, sf_tth, fout, fTT, "tth_muEffUp", true);
TH1F* tth_muEffDown = DC.readWriteHisto(fTH, "base_muEff_do/", histName, sf_tth, fout, fTT, "tth_muEffDown", true);
TH1F* tth_singpiecalUp = DC.readWriteHisto(fTH, "/singpiecalup/", histName, sf_tth, fout, fTT, "tth_singpiecalUp", true);
TH1F* tth_singpiecalDown = DC.readWriteHisto(fTH, "/singpiecaldown/", histName, sf_tth, fout, fTT, "tth_singpiecalDown", true);
TH1F* tth_singpihcalUp = DC.readWriteHisto(fTH, "/singpihcalup/", histName, sf_tth, fout, fTT, "tth_singpihcalUp", true);
TH1F* tth_singpihcalDown = DC.readWriteHisto(fTH,"/singpihcaldown/", histName, sf_tth, fout, fTT, "tth_singpihcalDown", true);
TH1F* tth_relsampleUp = DC.readWriteHisto(fTH, "relsampleup/", histName, sf_tth, fout, fTT, "tth_relsample_" + year + "Up", true);
TH1F* tth_relsampleDown = DC.readWriteHisto(fTH, "relsampledown/", histName, sf_tth, fout, fTT, "tth_relsample_" + year + "Down", true);
TH1F* tth_relstatfsrUp = DC.readWriteHisto(fTH, "relstatfsrup/", histName, sf_tth, fout, fTT, "tth_relstatfsr_" + year + "Up", true);
TH1F* tth_relstatfsrDown = DC.readWriteHisto(fTH, "relstatfsrdown/", histName, sf_tth, fout, fTT, "tth_relstatfsr_" + year + "Down", true);
TH1F* tth_relfsrUp = DC.readWriteHisto(fTH, "relfsrup/", histName, sf_tth, fout, fTT, "tth_relfsrUp", true);
TH1F* tth_relfsrDown = DC.readWriteHisto(fTH, "relfsrdown/", histName, sf_tth, fout, fTT, "tth_relfsrDown", true);
TH1F* tth_relbalUp = DC.readWriteHisto(fTH, "relbalup/", histName, sf_tth, fout, fTT, "tth_relbalUp", true);
TH1F* tth_relbalDown = DC.readWriteHisto(fTH, "relbaldown/", histName, sf_tth, fout, fTT, "tth_relbalDown", true);
TH1F* tth_relstathfUp = DC.readWriteHisto(fTH, "relstathfup/", histName, sf_tth, fout, fTT, "tth_relstathf_"+ year + "Up", true);
TH1F* tth_relstathfDown = DC.readWriteHisto(fTH, "relstathfdown/", histName, sf_tth, fout, fTT, "tth_relstathf_" + year + "Down", true);
TH1F* tth_pdfUp = DC.readWriteHisto(fTH, "base_prefire_up/", histName, sf_tth, fout, fTT, "tth_pdfUp", true);
TH1F* tth_pdfDown = DC.readWriteHisto(fTH, "base_prefire_do/", histName, sf_tth, fout, fTT, "tth_pdfDown", true);
TH1F* tth_puptbbUp = DC.readWriteHisto(fTH, "puptbbup/", histName, sf_tth, fout, fTT, "tth_puptbbUp", true);
TH1F* tth_puptbbDown = DC.readWriteHisto(fTH, "puptbbdown/", histName, sf_tth, fout, fTT, "tth_puptbbDown", true);
TH1F* tth_reljerhfUp = DC.readWriteHisto(fTH, "reljerhfup/", histName, sf_tth, fout, fTT, "tth_reljerhfUp", true);
TH1F* tth_reljerhfDown = DC.readWriteHisto(fTH, "reljerhfdown/", histName, sf_tth, fout, fTT, "tth_reljerhfDown", true);
TH1F* tth_pupthfUp = DC.readWriteHisto(fTH, "pupthfup/", histName, sf_tth, fout, fTT, "tth_pupthfUp", true);
TH1F* tth_pupthfDown = DC.readWriteHisto(fTH, "pupthfdown/", histName, sf_tth, fout, fTT, "tth_pupthfDown", true);

// Assuming tth and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
  //double baseIntegral = tth->Integral();

normalizeHistogram(tth_bc_statUp, tth);
normalizeHistogram(tth_bc_statDown, tth);
normalizeHistogram(tth_fsrUp, tth);
normalizeHistogram(tth_fsrDown, tth);
normalizeHistogram(tth_isrUp, tth);
normalizeHistogram(tth_isrDown, tth);
// normalizeHistogram(tth_base_pdfUp, tth);
// normalizeHistogram(tth_base_pdfDown, tth);
// normalizeHistogram(tth_lhemuFUp, tth);
// normalizeHistogram(tth_lhemuFDown, tth);
// normalizeHistogram(tth_lhemuRUp, tth);
// normalizeHistogram(tth_lhemuRDown, tth);
// normalizeHistogram(tth_extpUp, tth);
// normalizeHistogram(tth_extpDown, tth);
// normalizeHistogram(tth_intpUp, tth);
// normalizeHistogram(tth_intpDown, tth);
// normalizeHistogram(tth_xdycUp, tth);
// normalizeHistogram(tth_xdycDown, tth);
// normalizeHistogram(tth_xdybUp, tth);
// normalizeHistogram(tth_xdybDown, tth);
// normalizeHistogram(tth_xwjcUp, tth);
// normalizeHistogram(tth_xwjcDown, tth);
  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  tth_bc_statUp->Write();
  tth_bc_statDown->Write();
  tth_fsrUp->Write();
  tth_fsrDown->Write();
  tth_isrUp->Write();
  tth_isrDown->Write();
//   tth_lhemuFUp->Write();
// tth_lhemuFDown->Write();
// tth_lhemuRUp->Write();
// tth_lhemuRDown->Write();
// tth_extpUp->Write();
// tth_extpDown->Write();
// tth_intpUp->Write();
// tth_intpDown->Write();
// tth_xdycUp->Write();
// tth_xdycDown->Write();
// tth_xdybUp->Write();
// tth_xdybDown->Write();
// tth_xwjcUp->Write();
// tth_xwjcDown->Write();
  // tth_base_pdfUp->Write();
  // tth_base_pdfDown->Write();




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
TH1F* ttz = DC.readWriteHisto(fTZ, "base/", histName, sf_ttz, fout, fTT, "ttz", true);
TH1F* ttz_JESUp = DC.readWriteHisto(fTZ, "base_JEC_up/", histName, sf_ttz, fout, fTT, "ttz_JESUp", true);
TH1F* ttz_JESDown = DC.readWriteHisto(fTZ, "base_JEC_do/", histName, sf_ttz, fout, fTT, "ttz_JESDown", true);
TH1F* ttz_PileupUp = DC.readWriteHisto(fTZ, "base_PUWeight_up/", histName, sf_ttz, fout, fTT, "ttz_PileupUp", true);
TH1F* ttz_PileupDown = DC.readWriteHisto(fTZ, "base_PUWeight_do/", histName, sf_ttz, fout, fTT, "ttz_PileupDown", true);
TH1F* ttz_JERUp = DC.readWriteHisto(fTZ, "jerup/", histName, sf_ttz, fout, fTT, "ttz_JER_"+ year + "Up", true);
TH1F* ttz_JERDown = DC.readWriteHisto(fTZ, "jerdown/", histName, sf_ttz, fout, fTT, "ttz_JER_"+ year + "Down", true);
TH1F* ttz_prefireUp = DC.readWriteHisto(fTZ, "base_prefire_up/", histName, sf_ttz, fout, fTT, "ttz_prefireUp", true);
TH1F* ttz_prefireDown = DC.readWriteHisto(fTZ, "base_prefire_do/", histName, sf_ttz, fout, fTT, "ttz_prefireDown", true);
TH1F* ttz_fsrUp = DC.readWriteHisto(fTZ, "base_fsr_up/", histName, sf_ttz, fout, fTT, "ttz_fsrUp", true);
TH1F* ttz_fsrDown = DC.readWriteHisto(fTZ, "base_fsr_do/", histName, sf_ttz, fout, fTT, "ttz_fsrDown", true);
TH1F* ttz_isrUp = DC.readWriteHisto(fTZ, "base_isr_up/", histName, sf_ttz, fout, fTT, "ttz_isrUp", true);
TH1F* ttz_isrDown = DC.readWriteHisto(fTZ, "base_isr_do/", histName, sf_ttz, fout, fTT, "ttz_isrDown", true);
TH1F* ttz_flavorqcdUp = DC.readWriteHisto(fTZ, "flavorqcdup/", histName, sf_ttz, fout, fTT, "ttz_flavorqcdUp", true);
TH1F* ttz_flavorqcdDown = DC.readWriteHisto(fTZ, "flavorqcddown/", histName, sf_ttz, fout, fTT, "ttz_flavorqcdDown", true);
TH1F* ttz_timeptetaUp = DC.readWriteHisto(fTZ, "timeptetaup/", histName, sf_ttz, fout, fTT, "ttz_timepteta_"+ year + "Up", true);
TH1F* ttz_timeptetaDown = DC.readWriteHisto(fTZ, "timeptetadown/", histName, sf_ttz, fout, fTT, "ttz_timepteta_"+ year + "Down", true);
TH1F* ttz_jerhfUp = DC.readWriteHisto(fTZ, "reljerhfup/", histName, sf_ttz, fout, fTT, "ttz_jerhfUp", true);
TH1F* ttz_jerhfDown = DC.readWriteHisto(fTZ, "reljerhfdown/", histName, sf_ttz, fout, fTT, "ttz_jerhfDown", true);
TH1F* ttz_relptbbUp = DC.readWriteHisto(fTZ, "relptbbup/", histName, sf_ttz, fout, fTT, "ttz_relptbbUp", true);
TH1F* ttz_relptbbDown = DC.readWriteHisto(fTZ, "relptbbdown/", histName, sf_ttz, fout, fTT, "ttz_relptbbDown", true);
TH1F* ttz_relpthfUp = DC.readWriteHisto(fTZ, "relpthfup/", histName, sf_ttz, fout, fTT, "ttz_relpthfUp", true);
TH1F* ttz_relpthfDown = DC.readWriteHisto(fTZ, "relpthfdown/", histName, sf_ttz, fout, fTT, "ttz_relpthfDown", true);
TH1F* ttz_relstatecUp = DC.readWriteHisto(fTZ, "relstatecup/", histName, sf_ttz, fout, fTT, "ttz_relstatec_" + year + "Up", true);
TH1F* ttz_relstatecDown = DC.readWriteHisto(fTZ, "relstatecdown/", histName, sf_ttz, fout, fTT, "ttz_relstatec_" + year + "Down", true);
TH1F* ttz_absstatUp = DC.readWriteHisto(fTZ, "absstatup/", histName, sf_ttz, fout, fTT, "ttz_absstat_" + year + "Up", true);
TH1F* ttz_absstatDown = DC.readWriteHisto(fTZ, "absstatdown/", histName, sf_ttz, fout, fTT, "ttz_absstat_" + year + "Down", true);
TH1F* ttz_abssclUp = DC.readWriteHisto(fTZ, "abssclup/", histName, sf_ttz, fout, fTT, "ttz_abssclUp", true);
TH1F* ttz_abssclDown = DC.readWriteHisto(fTZ, "absscldown/", histName, sf_ttz, fout, fTT, "ttz_abssclDown", true);
TH1F* ttz_absmpfbUp = DC.readWriteHisto(fTZ, "absmpfbup/", histName, sf_ttz, fout, fTT, "ttz_absmpfbUp", true);
TH1F* ttz_absmpfbDown = DC.readWriteHisto(fTZ, "absmpfbdown/", histName, sf_ttz, fout, fTT, "ttz_absmpfbDown", true);
TH1F* ttz_fragUp = DC.readWriteHisto(fTZ, "fragup/", histName, sf_ttz, fout, fTT, "ttz_fragUp", true);
TH1F* ttz_fragDown = DC.readWriteHisto(fTZ, "fragdown/", histName, sf_ttz, fout, fTT, "ttz_fragDown", true);
TH1F* ttz_pudataMCUp = DC.readWriteHisto(fTZ, "pudatamcup/", histName, sf_ttz, fout, fTT, "ttz_pudataMCUp", true);
TH1F* ttz_pudataMCDown = DC.readWriteHisto(fTZ, "pudatamcdown/", histName, sf_ttz, fout, fTT, "ttz_pudataMCDown", true);
TH1F* ttz_relptec1Up = DC.readWriteHisto(fTZ, "relptec1up/", histName, sf_ttz, fout, fTT, "ttz_relptec1_" + year + "Up", true);
TH1F* ttz_relptec1Down = DC.readWriteHisto(fTZ, "relptec1down/", histName, sf_ttz, fout, fTT, "ttz_relptec1_" + year + "Down", true);
TH1F* ttz_relptec2Up = DC.readWriteHisto(fTZ, "relptec2up/", histName, sf_ttz, fout, fTT, "ttz_relptec2_" + year + "Up", true);
TH1F* ttz_relptec2Down = DC.readWriteHisto(fTZ, "relptec2down/", histName, sf_ttz, fout, fTT, "ttz_relptec2_" + year + "Down", true);
TH1F* ttz_reljerec1Up = DC.readWriteHisto(fTZ, "reljerec1up/", histName, sf_ttz, fout, fTT, "ttz_reljerec1_" + year + "Up", true);
TH1F* ttz_reljerec1Down = DC.readWriteHisto(fTZ, "reljerec1down/", histName, sf_ttz, fout, fTT, "ttz_reljerec1_" + year + "Down", true);
TH1F* ttz_reljerec2Up = DC.readWriteHisto(fTZ, "reljerec2up/", histName, sf_ttz, fout, fTT, "ttz_reljerec2_" + year + "Up", true);
TH1F* ttz_reljerec2Down = DC.readWriteHisto(fTZ, "reljerec2down/", histName, sf_ttz, fout, fTT, "ttz_reljerec2_" + year + "Down", true);
TH1F* ttz_puptrefUp = DC.readWriteHisto(fTZ, "puptrefup/", histName, sf_ttz, fout, fTT, "ttz_puptrefUp", true);
TH1F* ttz_puptrefDown = DC.readWriteHisto(fTZ, "puptrefdown/", histName, sf_ttz, fout, fTT, "ttz_puptrefDown", true);
TH1F* ttz_puptec1Up = DC.readWriteHisto(fTZ, "puptec1up/", histName, sf_ttz, fout, fTT, "ttz_puptec1Up", true);
TH1F* ttz_puptec1Down = DC.readWriteHisto(fTZ, "puptec1down/", histName, sf_ttz, fout, fTT, "ttz_puptec1Down", true);
TH1F* ttz_puptec2Up = DC.readWriteHisto(fTZ, "puptec2up/", histName, sf_ttz, fout, fTT, "ttz_puptec2Up", true);
TH1F* ttz_puptec2Down = DC.readWriteHisto(fTZ, "puptec2down/", histName, sf_ttz, fout, fTT, "ttz_puptec2Down", true);
TH1F* ttz_bc_statUp = DC.readWriteHisto(fTZ, "base_bc_stat_up/", histName, sf_ttz, fout, fTT, "ttz_bcstat_" + year + "_" + workingpoint + "Up", true);
TH1F* ttz_bc_statDown = DC.readWriteHisto(fTZ, "base_bc_stat_do/", histName, sf_ttz, fout, fTT, "ttz_bcstat_" + year + "_" + workingpoint + "Down", true);
TH1F* ttz_lhemuFUp = DC.readWriteHisto(fTZ, "base_bc_lhemuf_up/", histName, sf_ttz, fout, fTT, "ttz_lhemuF_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttz_lhemuFDown = DC.readWriteHisto(fTZ, "base_bc_lhemuf_do/", histName, sf_ttz, fout, fTT, "ttz_lhemuF_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttz_lhemuRUp = DC.readWriteHisto(fTZ, "base_lhemur_up/", histName, sf_ttz, fout, fTT, "ttz_lhemuR_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttz_lhemuRDown = DC.readWriteHisto(fTZ, "base_lhemur_do/", histName, sf_ttz, fout, fTT, "ttz_lhemuR_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttz_extpUp = DC.readWriteHisto(fTZ, "base_extp_up/", histName, sf_ttz, fout, fTT, "ttz_bcextp_" + year + "_" + workingpoint + "Up", true);
TH1F* ttz_extpDown = DC.readWriteHisto(fTZ, "base_extp_do/", histName, sf_ttz, fout, fTT, "ttz_bcextp_" + year + "_" + workingpoint + "Down", true);
TH1F* ttz_intpUp = DC.readWriteHisto(fTZ, "base_intp_up/", histName, sf_ttz, fout, fTT, "ttz_bcintp_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttz_intpDown = DC.readWriteHisto(fTZ, "base_intp_do/", histName, sf_ttz, fout, fTT, "ttz_bcintp_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttz_xdycUp = DC.readWriteHisto(fTZ, "base_xdyc_up/", histName, sf_ttz, fout, fTT, "ttz_bcxdyc_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttz_xdycDown = DC.readWriteHisto(fTZ, "base_xdyc_do/", histName, sf_ttz, fout, fTT, "ttz_bcxdyc_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttz_xdybUp = DC.readWriteHisto(fTZ, "base_xdyb_up/", histName, sf_ttz, fout, fTT, "ttz_bcxdyb_" + year + "_" + workingpoint + "Up", true);
TH1F* ttz_xdybDown = DC.readWriteHisto(fTZ, "base_xdyb_do/", histName, sf_ttz, fout, fTT, "ttz_bcxdyb_" + year + "_" + workingpoint + "Down", true);
TH1F* ttz_xwjcUp = DC.readWriteHisto(fTZ, "base_xwj_up/", histName, sf_ttz, fout, fTT, "ttz_bcxwjc_" + year + "_" + workingpoint + "Up", true);
TH1F* ttz_xwjcDown = DC.readWriteHisto(fTZ, "base_xwj_do/", histName, sf_ttz, fout, fTT, "ttz_bcxwjc_" + year + "_" + workingpoint + "Down", true);
TH1F* ttz_muEffUp = DC.readWriteHisto(fTZ, "base_muEff_up/", histName, sf_ttz, fout, fTT, "ttz_muEffUp", true);
TH1F* ttz_muEffDown = DC.readWriteHisto(fTZ, "base_muEff_do/", histName, sf_ttz, fout, fTT, "ttz_muEffDown", true);
TH1F* ttz_singpiecalUp = DC.readWriteHisto(fTZ, "/singpiecalup/", histName, sf_ttz, fout, fTT, "ttz_singpiecalUp", true);
TH1F* ttz_singpiecalDown = DC.readWriteHisto(fTZ, "/singpiecaldown/", histName, sf_ttz, fout, fTT, "ttz_singpiecalDown", true);
TH1F* ttz_singpihcalUp = DC.readWriteHisto(fTZ, "/singpihcalup/", histName, sf_ttz, fout, fTT, "ttz_singpihcalUp", true);
TH1F* ttz_singpihcalDown = DC.readWriteHisto(fTZ,"/singpihcaldown/", histName, sf_ttz, fout, fTT, "ttz_singpihcalDown", true);
TH1F* ttz_relsampleUp = DC.readWriteHisto(fTZ, "relsampleup/", histName, sf_ttz, fout, fTT, "ttz_relsample_" + year + "Up", true);
TH1F* ttz_relsampleDown = DC.readWriteHisto(fTZ, "relsampledown/", histName, sf_ttz, fout, fTT, "ttz_relsample_" + year + "Down", true);
TH1F* ttz_relstatfsrUp = DC.readWriteHisto(fTZ, "relstatfsrup/", histName, sf_ttz, fout, fTT, "ttz_relstatfsr_" + year + "Up", true);
TH1F* ttz_relstatfsrDown = DC.readWriteHisto(fTZ, "relstatfsrdown/", histName, sf_ttz, fout, fTT, "ttz_relstatfsr_" + year + "Down", true);
TH1F* ttz_relfsrUp = DC.readWriteHisto(fTZ, "relfsrup/", histName, sf_ttz, fout, fTT, "ttz_relfsrUp", true);
TH1F* ttz_relfsrDown = DC.readWriteHisto(fTZ, "relfsrdown/", histName, sf_ttz, fout, fTT, "ttz_relfsrDown", true);
TH1F* ttz_relbalUp = DC.readWriteHisto(fTZ, "relbalup/", histName, sf_ttz, fout, fTT, "ttz_relbalUp", true);
TH1F* ttz_relbalDown = DC.readWriteHisto(fTZ, "relbaldown/", histName, sf_ttz, fout, fTT, "ttz_relbalDown", true);
TH1F* ttz_relstathfUp = DC.readWriteHisto(fTZ, "relstathfup/", histName, sf_ttz, fout, fTT, "ttz_relstathf_"+ year + "Up", true);
TH1F* ttz_relstathfDown = DC.readWriteHisto(fTZ, "relstathfdown/", histName, sf_ttz, fout, fTT, "ttz_relstathf_" + year + "Down", true);
TH1F* ttz_pdfUp = DC.readWriteHisto(fTZ, "base_prefire_up/", histName, sf_ttz, fout, fTT, "ttz_pdfUp", true);
TH1F* ttz_pdfDown = DC.readWriteHisto(fTZ, "base_prefire_do/", histName, sf_ttz, fout, fTT, "ttz_pdfDown", true);
TH1F* ttz_puptbbUp = DC.readWriteHisto(fTZ, "puptbbup/", histName, sf_ttz, fout, fTT, "ttz_puptbbUp", true);
TH1F* ttz_puptbbDown = DC.readWriteHisto(fTZ, "puptbbdown/", histName, sf_ttz, fout, fTT, "ttz_puptbbDown", true);
TH1F* ttz_reljerhfUp = DC.readWriteHisto(fTZ, "reljerhfup/", histName, sf_ttz, fout, fTT, "ttz_reljerhfUp", true);
TH1F* ttz_reljerhfDown = DC.readWriteHisto(fTZ, "reljerhfdown/", histName, sf_ttz, fout, fTT, "ttz_reljerhfDown", true);
TH1F* ttz_pupthfUp = DC.readWriteHisto(fTZ, "pupthfup/", histName, sf_ttz, fout, fTT, "ttz_pupthfUp", true);
TH1F* ttz_pupthfDown = DC.readWriteHisto(fTZ, "pupthfdown/", histName, sf_ttz, fout, fTT, "ttz_pupthfDown", true);
// Assuming ttz and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
  //double baseIntegral = ttz->Integral();


normalizeHistogram(ttz_bc_statUp, ttz);
normalizeHistogram(ttz_bc_statDown, ttz);
normalizeHistogram(ttz_fsrUp, ttz);
normalizeHistogram(ttz_fsrDown, ttz);
normalizeHistogram(ttz_isrUp, ttz);
normalizeHistogram(ttz_isrDown, ttz);
// normalizeHistogram(ttz_lhemuFUp, ttz);
// normalizeHistogram(ttz_lhemuFDown, ttz);
// normalizeHistogram(ttz_lhemuRUp, ttz);
// normalizeHistogram(ttz_lhemuRDown, ttz);
// normalizeHistogram(ttz_extpUp, ttz);
// normalizeHistogram(ttz_extpDown, ttz);
// normalizeHistogram(ttz_intpUp, ttz);
// normalizeHistogram(ttz_intpDown, ttz);
// normalizeHistogram(ttz_xdycUp, ttz);
// normalizeHistogram(ttz_xdycDown, ttz);
// normalizeHistogram(ttz_xdybUp, ttz);
// normalizeHistogram(ttz_xdybDown, ttz);
// normalizeHistogram(ttz_xwjcUp, ttz);
// normalizeHistogram(ttz_xwjcDown, ttz);
// normalizeHistogram(ttz_base_pdfUp, ttz);
// normalizeHistogram(ttz_base_pdfDown, ttz);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  ttz_bc_statUp->Write();
  ttz_bc_statDown->Write();
  ttz_fsrUp->Write();
  ttz_fsrDown->Write();
  ttz_isrUp->Write();
  ttz_isrDown->Write();
  ttz_lhemuFUp->Write();
// ttz_lhemuFDown->Write();
// ttz_lhemuRUp->Write();
// ttz_lhemuRDown->Write();
// ttz_extpUp->Write();
// ttz_extpDown->Write();
// ttz_intpUp->Write();
// ttz_intpDown->Write();
// ttz_xdycUp->Write();
// ttz_xdycDown->Write();
// ttz_xdybUp->Write();
// ttz_xdybDown->Write();
// ttz_xwjcUp->Write();
// ttz_xwjcDown->Write();

  // ttz_base_pdfUp->Write();
  // ttz_base_pdfDown->Write();




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
TH1F* ttw = DC.readWriteHisto(fTW, "base/", histName, sf_ttw, fout, fTT, "ttw", true);
TH1F* ttw_JESUp = DC.readWriteHisto(fTW, "base_JEC_up/", histName, sf_ttw, fout, fTT, "ttw_JESUp", true);
TH1F* ttw_JESDown = DC.readWriteHisto(fTW, "base_JEC_do/", histName, sf_ttw, fout, fTT, "ttw_JESDown", true);
TH1F* ttw_PileupUp = DC.readWriteHisto(fTW, "base_PUWeight_up/", histName, sf_ttw, fout, fTT, "ttw_PileupUp", true);
TH1F* ttw_PileupDown = DC.readWriteHisto(fTW, "base_PUWeight_do/", histName, sf_ttw, fout, fTT, "ttw_PileupDown", true);
TH1F* ttw_JERUp = DC.readWriteHisto(fTW, "jerup/", histName, sf_ttw, fout, fTT, "ttw_JER_"+ year + "Up", true);
TH1F* ttw_JERDown = DC.readWriteHisto(fTW, "jerdown/", histName, sf_ttw, fout, fTT, "ttw_JER_"+ year + "Down", true);
TH1F* ttw_prefireUp = DC.readWriteHisto(fTW, "base_prefire_up/", histName, sf_ttw, fout, fTT, "ttw_prefireUp", true);
TH1F* ttw_prefireDown = DC.readWriteHisto(fTW, "base_prefire_do/", histName, sf_ttw, fout, fTT, "ttw_prefireDown", true);
TH1F* ttw_fsrUp = DC.readWriteHisto(fTW, "base_fsr_up/", histName, sf_ttw, fout, fTT, "ttw_fsrUp", true);
TH1F* ttw_fsrDown = DC.readWriteHisto(fTW, "base_fsr_do/", histName, sf_ttw, fout, fTT, "ttw_fsrDown", true);
TH1F* ttw_isrUp = DC.readWriteHisto(fTW, "base_isr_up/", histName, sf_ttw, fout, fTT, "ttw_isrUp", true);
TH1F* ttw_isrDown = DC.readWriteHisto(fTW, "base_isr_do/", histName, sf_ttw, fout, fTT, "ttw_isrDown", true);
TH1F* ttw_flavorqcdUp = DC.readWriteHisto(fTW, "flavorqcdup/", histName, sf_ttw, fout, fTT, "ttw_flavorqcdUp", true);
TH1F* ttw_flavorqcdDown = DC.readWriteHisto(fTW, "flavorqcddown/", histName, sf_ttw, fout, fTT, "ttw_flavorqcdDown", true);
TH1F* ttw_timeptetaUp = DC.readWriteHisto(fTW, "timeptetaup/", histName, sf_ttw, fout, fTT, "ttw_timepteta_"+ year + "Up", true);
TH1F* ttw_timeptetaDown = DC.readWriteHisto(fTW, "timeptetadown/", histName, sf_ttw, fout, fTT, "ttw_timepteta_"+ year + "Down", true);
TH1F* ttw_jerhfUp = DC.readWriteHisto(fTW, "reljerhfup/", histName, sf_ttw, fout, fTT, "ttw_jerhfUp", true);
TH1F* ttw_jerhfDown = DC.readWriteHisto(fTW, "reljerhfdown/", histName, sf_ttw, fout, fTT, "ttw_jerhfDown", true);
TH1F* ttw_relptbbUp = DC.readWriteHisto(fTW, "relptbbup/", histName, sf_ttw, fout, fTT, "ttw_relptbbUp", true);
TH1F* ttw_relptbbDown = DC.readWriteHisto(fTW, "relptbbdown/", histName, sf_ttw, fout, fTT, "ttw_relptbbDown", true);
TH1F* ttw_relpthfUp = DC.readWriteHisto(fTW, "relpthfup/", histName, sf_ttw, fout, fTT, "ttw_relpthfUp", true);
TH1F* ttw_relpthfDown = DC.readWriteHisto(fTW, "relpthfdown/", histName, sf_ttw, fout, fTT, "ttw_relpthfDown", true);
TH1F* ttw_relstatecUp = DC.readWriteHisto(fTW, "relstatecup/", histName, sf_ttw, fout, fTT, "ttw_relstatec_" + year + "Up", true);
TH1F* ttw_relstatecDown = DC.readWriteHisto(fTW, "relstatecdown/", histName, sf_ttw, fout, fTT, "ttw_relstatec_" + year + "Down", true);
TH1F* ttw_absstatUp = DC.readWriteHisto(fTW, "absstatup/", histName, sf_ttw, fout, fTT, "ttw_absstat_" + year + "Up", true);
TH1F* ttw_absstatDown = DC.readWriteHisto(fTW, "absstatdown/", histName, sf_ttw, fout, fTT, "ttw_absstat_" + year + "Down", true);
TH1F* ttw_abssclUp = DC.readWriteHisto(fTW, "abssclup/", histName, sf_ttw, fout, fTT, "ttw_abssclUp", true);
TH1F* ttw_abssclDown = DC.readWriteHisto(fTW, "absscldown/", histName, sf_ttw, fout, fTT, "ttw_abssclDown", true);
TH1F* ttw_absmpfbUp = DC.readWriteHisto(fTW, "absmpfbup/", histName, sf_ttw, fout, fTT, "ttw_absmpfbUp", true);
TH1F* ttw_absmpfbDown = DC.readWriteHisto(fTW, "absmpfbdown/", histName, sf_ttw, fout, fTT, "ttw_absmpfbDown", true);
TH1F* ttw_fragUp = DC.readWriteHisto(fTW, "fragup/", histName, sf_ttw, fout, fTT, "ttw_fragUp", true);
TH1F* ttw_fragDown = DC.readWriteHisto(fTW, "fragdown/", histName, sf_ttw, fout, fTT, "ttw_fragDown", true);
TH1F* ttw_pudataMCUp = DC.readWriteHisto(fTW, "pudatamcup/", histName, sf_ttw, fout, fTT, "ttw_pudataMCUp", true);
TH1F* ttw_pudataMCDown = DC.readWriteHisto(fTW, "pudatamcdown/", histName, sf_ttw, fout, fTT, "ttw_pudataMCDown", true);
TH1F* ttw_relptec1Up = DC.readWriteHisto(fTW, "relptec1up/", histName, sf_ttw, fout, fTT, "ttw_relptec1_" + year + "Up", true);
TH1F* ttw_relptec1Down = DC.readWriteHisto(fTW, "relptec1down/", histName, sf_ttw, fout, fTT, "ttw_relptec1_" + year + "Down", true);
TH1F* ttw_relptec2Up = DC.readWriteHisto(fTW, "relptec2up/", histName, sf_ttw, fout, fTT, "ttw_relptec2_" + year + "Up", true);
TH1F* ttw_relptec2Down = DC.readWriteHisto(fTW, "relptec2down/", histName, sf_ttw, fout, fTT, "ttw_relptec2_" + year + "Down", true);
TH1F* ttw_reljerec1Up = DC.readWriteHisto(fTW, "reljerec1up/", histName, sf_ttw, fout, fTT, "ttw_reljerec1_" + year + "Up", true);
TH1F* ttw_reljerec1Down = DC.readWriteHisto(fTW, "reljerec1down/", histName, sf_ttw, fout, fTT, "ttw_reljerec1_" + year + "Down", true);
TH1F* ttw_reljerec2Up = DC.readWriteHisto(fTW, "reljerec2up/", histName, sf_ttw, fout, fTT, "ttw_reljerec2_" + year + "Up", true);
TH1F* ttw_reljerec2Down = DC.readWriteHisto(fTW, "reljerec2down/", histName, sf_ttw, fout, fTT, "ttw_reljerec2_" + year + "Down", true);
TH1F* ttw_puptrefUp = DC.readWriteHisto(fTW, "puptrefup/", histName, sf_ttw, fout, fTT, "ttw_puptrefUp", true);
TH1F* ttw_puptrefDown = DC.readWriteHisto(fTW, "puptrefdown/", histName, sf_ttw, fout, fTT, "ttw_puptrefDown", true);
TH1F* ttw_puptec1Up = DC.readWriteHisto(fTW, "puptec1up/", histName, sf_ttw, fout, fTT, "ttw_puptec1Up", true);
TH1F* ttw_puptec1Down = DC.readWriteHisto(fTW, "puptec1down/", histName, sf_ttw, fout, fTT, "ttw_puptec1Down", true);
TH1F* ttw_puptec2Up = DC.readWriteHisto(fTW, "puptec2up/", histName, sf_ttw, fout, fTT, "ttw_puptec2Up", true);
TH1F* ttw_puptec2Down = DC.readWriteHisto(fTW, "puptec2down/", histName, sf_ttw, fout, fTT, "ttw_puptec2Down", true);
// B-tagging decorrelated systematics
TH1F* ttw_bc_statUp = DC.readWriteHisto(fTW, "base_bc_stat_up/", histName, sf_ttw, fout, fTT, "ttw_bcstat_" + year + "_" + workingpoint + "Up", true);
TH1F* ttw_bc_statDown = DC.readWriteHisto(fTW, "base_bc_stat_do/", histName, sf_ttw, fout, fTT, "ttw_bcstat_" + year + "_" + workingpoint + "Down", true);
TH1F* ttw_lhemuFUp = DC.readWriteHisto(fTW, "base_bc_lhemuf_up/", histName, sf_ttw, fout, fTT, "ttw_lhemuF_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttw_lhemuFDown = DC.readWriteHisto(fTW, "base_bc_lhemuf_do/", histName, sf_ttw, fout, fTT, "ttw_lhemuF_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttw_lhemuRUp = DC.readWriteHisto(fTW, "base_lhemur_up/", histName, sf_ttw, fout, fTT, "ttw_lhemuR_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttw_lhemuRDown = DC.readWriteHisto(fTW, "base_lhemur_do/", histName, sf_ttw, fout, fTT, "ttw_lhemuR_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttw_extpUp = DC.readWriteHisto(fTW, "base_extp_up/", histName, sf_ttw, fout, fTT, "ttw_bcextp_" + year + "_" + workingpoint + "Up", true);
TH1F* ttw_extpDown = DC.readWriteHisto(fTW, "base_extp_do/", histName, sf_ttw, fout, fTT, "ttw_bcextp_" + year + "_" + workingpoint + "Down", true);
TH1F* ttw_intpUp = DC.readWriteHisto(fTW, "base_intp_up/", histName, sf_ttw, fout, fTT, "ttw_bcintp_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttw_intpDown = DC.readWriteHisto(fTW, "base_intp_do/", histName, sf_ttw, fout, fTT, "ttw_bcintp_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttw_xdycUp = DC.readWriteHisto(fTW, "base_xdyc_up/", histName, sf_ttw, fout, fTT, "ttw_bcxdyc_"+ year + "_" + workingpoint + "Up", true);
TH1F* ttw_xdycDown = DC.readWriteHisto(fTW, "base_xdyc_do/", histName, sf_ttw, fout, fTT, "ttw_bcxdyc_"+ year + "_" + workingpoint + "Down", true);
TH1F* ttw_xdybUp = DC.readWriteHisto(fTW, "base_xdyb_up/", histName, sf_ttw, fout, fTT, "ttw_bcxdyb_" + year + "_" + workingpoint + "Up", true);
TH1F* ttw_xdybDown = DC.readWriteHisto(fTW, "base_xdyb_do/", histName, sf_ttw, fout, fTT, "ttw_bcxdyb_" + year + "_" + workingpoint + "Down", true);
TH1F* ttw_xwjcUp = DC.readWriteHisto(fTW, "base_xwj_up/", histName, sf_ttw, fout, fTT, "ttw_bcxwjc_" + year + "_" + workingpoint + "Up", true);
TH1F* ttw_xwjcDown = DC.readWriteHisto(fTW, "base_xwj_do/", histName, sf_ttw, fout, fTT, "ttw_bcxwjc_" + year + "_" + workingpoint + "Down", true);
TH1F* ttw_muEffUp = DC.readWriteHisto(fTW, "base_muEff_up/", histName, sf_ttw, fout, fTT, "ttw_muEffUp", true);
TH1F* ttw_muEffDown = DC.readWriteHisto(fTW, "base_muEff_do/", histName, sf_ttw, fout, fTT, "ttw_muEffDown", true);
TH1F* ttw_singpiecalUp = DC.readWriteHisto(fTW, "/singpiecalup/", histName, sf_ttw, fout, fTT, "ttw_singpiecalUp", true);
TH1F* ttw_singpiecalDown = DC.readWriteHisto(fTW, "/singpiecaldown/", histName, sf_ttw, fout, fTT, "ttw_singpiecalDown", true);
TH1F* ttw_singpihcalUp = DC.readWriteHisto(fTW, "/singpihcalup/", histName, sf_ttw, fout, fTT, "ttw_singpihcalUp", true);
TH1F* ttw_singpihcalDown = DC.readWriteHisto(fTW,"/singpihcaldown/", histName, sf_ttw, fout, fTT, "ttw_singpihcalDown", true);
TH1F* ttw_relsampleUp = DC.readWriteHisto(fTW, "relsampleup/", histName, sf_ttw, fout, fTT, "ttw_relsample_" + year + "Up", true);
TH1F* ttw_relsampleDown = DC.readWriteHisto(fTW, "relsampledown/", histName, sf_ttw, fout, fTT, "ttw_relsample_" + year + "Down", true);
TH1F* ttw_relstatfsrUp = DC.readWriteHisto(fTW, "relstatfsrup/", histName, sf_ttw, fout, fTT, "ttw_relstatfsr_" + year + "Up", true);
TH1F* ttw_relstatfsrDown = DC.readWriteHisto(fTW, "relstatfsrdown/", histName, sf_ttw, fout, fTT, "ttw_relstatfsr_" + year + "Down", true);
TH1F* ttw_relfsrUp = DC.readWriteHisto(fTW, "relfsrup/", histName, sf_ttw, fout, fTT, "ttw_relfsrUp", true);
TH1F* ttw_relfsrDown = DC.readWriteHisto(fTW, "relfsrdown/", histName, sf_ttw, fout, fTT, "ttw_relfsrDown", true);
TH1F* ttw_relbalUp = DC.readWriteHisto(fTW, "relbalup/", histName, sf_ttw, fout, fTT, "ttw_relbalUp", true);
TH1F* ttw_relbalDown = DC.readWriteHisto(fTW, "relbaldown/", histName, sf_ttw, fout, fTT, "ttw_relbalDown", true);
 TH1F* ttw_relstathfUp = DC.readWriteHisto(fTW, "relstathfup/", histName, sf_ttw, fout, fTT, "ttw_relstathf_" + year + "Up", true);
TH1F* ttw_relstathfDown = DC.readWriteHisto(fTW, "relstathfdown/", histName, sf_ttw, fout, fTT, "ttw_relstathf_" + year + "Down", true);
// For ttw
TH1F* ttw_pdfUp = DC.readWriteHisto(fTW, "base_prefire_up/", histName, sf_ttw, fout, fTT, "ttw_pdfUp", true);
TH1F* ttw_pdfDown = DC.readWriteHisto(fTW, "base_prefire_do/", histName, sf_ttw, fout, fTT, "ttw_pdfDown", true);
TH1F* ttw_puptbbUp = DC.readWriteHisto(fTW, "puptbbup/", histName, sf_ttw, fout, fTT, "ttw_puptbbUp", true);
TH1F* ttw_puptbbDown = DC.readWriteHisto(fTW, "puptbbdown/", histName, sf_ttw, fout, fTT, "ttw_puptbbDown", true);
TH1F* ttw_reljerhfUp = DC.readWriteHisto(fTW, "reljerhfup/", histName, sf_ttw, fout, fTT, "ttw_reljerhfUp", true);
TH1F* ttw_reljerhfDown = DC.readWriteHisto(fTW, "reljerhfdown/", histName, sf_ttw, fout, fTT, "ttw_reljerhfDown", true);
TH1F* ttw_pupthfUp = DC.readWriteHisto(fTW, "pupthfup/", histName, sf_ttw, fout, fTT, "ttw_pupthfUp", true);
TH1F* ttw_pupthfDown = DC.readWriteHisto(fTW, "pupthfdown/", histName, sf_ttw, fout, fTT, "ttw_pupthfDown", true);
// Assuming ttw and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
  //double baseIntegral = ttw->Integral();

normalizeHistogram(ttw_bc_statUp, ttw);
normalizeHistogram(ttw_bc_statDown, ttw);
normalizeHistogram(ttw_fsrUp, ttw);
normalizeHistogram(ttw_fsrDown, ttw);
normalizeHistogram(ttw_isrUp, ttw);
normalizeHistogram(ttw_isrDown, ttw);
// normalizeHistogram(ttw_lhemuFUp, ttw);
// normalizeHistogram(ttw_lhemuFDown, ttw);
// normalizeHistogram(ttw_lhemuRUp, ttw);
// normalizeHistogram(ttw_lhemuRDown, ttw);
// normalizeHistogram(ttw_extpUp, ttw);
// normalizeHistogram(ttw_extpDown, ttw);
// normalizeHistogram(ttw_intpUp, ttw);
// normalizeHistogram(ttw_intpDown, ttw);
// normalizeHistogram(ttw_xdycUp, ttw);
// normalizeHistogram(ttw_xdycDown, ttw);
// normalizeHistogram(ttw_xdybUp, ttw);
// normalizeHistogram(ttw_xdybDown, ttw);
// normalizeHistogram(ttw_xwjcUp, ttw);
// normalizeHistogram(ttw_xwjcDown, ttw);
// normalizeHistogram(ttw_base_pdfUp, ttw);
// normalizeHistogram(ttw_base_pdfDown, ttw);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  ttw_bc_statUp->Write();
  ttw_bc_statDown->Write();
  ttw_fsrUp->Write();
  ttw_fsrDown->Write();
  ttw_isrUp->Write();
  ttw_isrDown->Write();
//   ttw_lhemuFUp->Write();
// ttw_lhemuFDown->Write();
// ttw_lhemuRUp->Write();
// ttw_lhemuRDown->Write();
// ttw_extpUp->Write();
// ttw_extpDown->Write();
// ttw_intpUp->Write();
// ttw_intpDown->Write();
// ttw_xdycUp->Write();
// ttw_xdycDown->Write();
// ttw_xdybUp->Write();
// ttw_xdybDown->Write();
// ttw_xwjcUp->Write();
// ttw_xwjcDown->Write();

  // ttw_base_pdfUp->Write();
  // ttw_base_pdfDown->Write();




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

TH1F* wjet = DC.readWriteHisto(fWJ, "base/", histName, sf_wjet, fout, fTT, "wjet", true);
TH1F* wjet_JESUp = DC.readWriteHisto(fWJ, "base_JEC_up/", histName, sf_wjet, fout, fTT, "wjet_JESUp", true);
TH1F* wjet_JESDown = DC.readWriteHisto(fWJ, "base_JEC_do/", histName, sf_wjet, fout, fTT, "wjet_JESDown", true);
TH1F* wjet_PileupUp = DC.readWriteHisto(fWJ, "base_PUWeight_up/", histName, sf_wjet, fout, fTT, "wjet_PileupUp", true);
TH1F* wjet_PileupDown = DC.readWriteHisto(fWJ, "base_PUWeight_do/", histName, sf_wjet, fout, fTT, "wjet_PileupDown", true);
TH1F* wjet_JERUp = DC.readWriteHisto(fWJ, "jerup/", histName, sf_wjet, fout, fTT, "wjet_JER_"+ year + "Up", true);
TH1F* wjet_JERDown = DC.readWriteHisto(fWJ, "jerdown/", histName, sf_wjet, fout, fTT, "wjet_JER_"+ year + "Down", true);
TH1F* wjet_prefireUp = DC.readWriteHisto(fWJ, "base_prefire_up/", histName, sf_wjet, fout, fTT, "wjet_prefireUp", true);
TH1F* wjet_prefireDown = DC.readWriteHisto(fWJ, "base_prefire_do/", histName, sf_wjet, fout, fTT, "wjet_prefireDown", true);
TH1F* wjet_fsrUp = DC.readWriteHisto(fWJ, "base_fsr_up/", histName, sf_wjet, fout, fTT, "wjet_fsrUp", true);
TH1F* wjet_fsrDown = DC.readWriteHisto(fWJ, "base_fsr_do/", histName, sf_wjet, fout, fTT, "wjet_fsrDown", true);
TH1F* wjet_isrUp = DC.readWriteHisto(fWJ, "base_isr_up/", histName, sf_wjet, fout, fTT, "wjet_isrUp", true);
TH1F* wjet_isrDown = DC.readWriteHisto(fWJ, "base_isr_do/", histName, sf_wjet, fout, fTT, "wjet_isrDown", true);
TH1F* wjet_flavorqcdUp = DC.readWriteHisto(fWJ, "flavorqcdup/", histName, sf_wjet, fout, fTT, "wjet_flavorqcdUp", true);
TH1F* wjet_flavorqcdDown = DC.readWriteHisto(fWJ, "flavorqcddown/", histName, sf_wjet, fout, fTT, "wjet_flavorqcdDown", true);
TH1F* wjet_timeptetaUp = DC.readWriteHisto(fWJ, "timeptetaup/", histName, sf_wjet, fout, fTT, "wjet_timepteta_"+ year + "Up", true);
TH1F* wjet_timeptetaDown = DC.readWriteHisto(fWJ, "timeptetadown/", histName, sf_wjet, fout, fTT, "wjet_timepteta_"+ year + "Down", true);
TH1F* wjet_jerhfUp = DC.readWriteHisto(fWJ, "reljerhfup/", histName, sf_wjet, fout, fTT, "wjet_jerhfUp", true);
TH1F* wjet_jerhfDown = DC.readWriteHisto(fWJ, "reljerhfdown/", histName, sf_wjet, fout, fTT, "wjet_jerhfDown", true);
TH1F* wjet_relptbbUp = DC.readWriteHisto(fWJ, "relptbbup/", histName, sf_wjet, fout, fTT, "wjet_relptbbUp", true);
TH1F* wjet_relptbbDown = DC.readWriteHisto(fWJ, "relptbbdown/", histName, sf_wjet, fout, fTT, "wjet_relptbbDown", true);
TH1F* wjet_relpthfUp = DC.readWriteHisto(fWJ, "relpthfup/", histName, sf_wjet, fout, fTT, "wjet_relpthfUp", true);
TH1F* wjet_relpthfDown = DC.readWriteHisto(fWJ, "relpthfdown/", histName, sf_wjet, fout, fTT, "wjet_relpthfDown", true);
TH1F* wjet_relstatecUp = DC.readWriteHisto(fWJ, "relstatecup/", histName, sf_wjet, fout, fTT, "wjet_relstatec_" + year + "Up", true);
TH1F* wjet_relstatecDown = DC.readWriteHisto(fWJ, "relstatecdown/", histName, sf_wjet, fout, fTT, "wjet_relstatec_" + year + "Down", true);
TH1F* wjet_absstatUp = DC.readWriteHisto(fWJ, "absstatup/", histName, sf_wjet, fout, fTT, "wjet_absstat_" + year + "Up", true);
TH1F* wjet_absstatDown = DC.readWriteHisto(fWJ, "absstatdown/", histName, sf_wjet, fout, fTT, "wjet_absstat_" + year + "Down", true);
TH1F* wjet_abssclUp = DC.readWriteHisto(fWJ, "abssclup/", histName, sf_wjet, fout, fTT, "wjet_abssclUp", true);
TH1F* wjet_abssclDown = DC.readWriteHisto(fWJ, "absscldown/", histName, sf_wjet, fout, fTT, "wjet_abssclDown", true);
TH1F* wjet_absmpfbUp = DC.readWriteHisto(fWJ, "absmpfbup/", histName, sf_wjet, fout, fTT, "wjet_absmpfbUp", true);
TH1F* wjet_absmpfbDown = DC.readWriteHisto(fWJ, "absmpfbdown/", histName, sf_wjet, fout, fTT, "wjet_absmpfbDown", true);
TH1F* wjet_fragUp = DC.readWriteHisto(fWJ, "fragup/", histName, sf_wjet, fout, fTT, "wjet_fragUp", true);
TH1F* wjet_fragDown = DC.readWriteHisto(fWJ, "fragdown/", histName, sf_wjet, fout, fTT, "wjet_fragDown", true);
TH1F* wjet_pudataMCUp = DC.readWriteHisto(fWJ, "pudatamcup/", histName, sf_wjet, fout, fTT, "wjet_pudataMCUp", true);
TH1F* wjet_pudataMCDown = DC.readWriteHisto(fWJ, "pudatamcdown/", histName, sf_wjet, fout, fTT, "wjet_pudataMCDown", true);
 TH1F* wjet_relptec1Up = DC.readWriteHisto(fWJ, "relptec1up/", histName, sf_wjet, fout, fTT, "wjet_relptec1_" + year + "Up", true);
TH1F* wjet_relptec1Down = DC.readWriteHisto(fWJ, "relptec1down/", histName, sf_wjet, fout, fTT, "wjet_relptec1_" + year + "Down", true);
TH1F* wjet_relptec2Up = DC.readWriteHisto(fWJ, "relptec2up/", histName, sf_wjet, fout, fTT, "wjet_relptec2_" + year + "Up", true);
TH1F* wjet_relptec2Down = DC.readWriteHisto(fWJ, "relptec2down/", histName, sf_wjet, fout, fTT, "wjet_relptec2_" + year + "Down", true);
TH1F* wjet_reljerec1Up = DC.readWriteHisto(fWJ, "reljerec1up/", histName, sf_wjet, fout, fTT, "wjet_reljerec1_" + year + "Up", true);
TH1F* wjet_reljerec1Down = DC.readWriteHisto(fWJ, "reljerec1down/", histName, sf_wjet, fout, fTT, "wjet_reljerec1_" + year + "Down", true);
TH1F* wjet_reljerec2Up = DC.readWriteHisto(fWJ, "reljerec2up/", histName, sf_wjet, fout, fTT, "wjet_reljerec2_" + year + "Up", true);
TH1F* wjet_reljerec2Down = DC.readWriteHisto(fWJ, "reljerec2down/", histName, sf_wjet, fout, fTT, "wjet_reljerec2_" + year + "Down", true);
TH1F* wjet_puptrefUp = DC.readWriteHisto(fWJ, "puptrefup/", histName, sf_wjet, fout, fTT, "wjet_puptrefUp", true);
TH1F* wjet_puptrefDown = DC.readWriteHisto(fWJ, "puptrefdown/", histName, sf_wjet, fout, fTT, "wjet_puptrefDown", true);
TH1F* wjet_puptec1Up = DC.readWriteHisto(fWJ, "puptec1up/", histName, sf_wjet, fout, fTT, "wjet_puptec1Up", true);
TH1F* wjet_puptec1Down = DC.readWriteHisto(fWJ, "puptec1down/", histName, sf_wjet, fout, fTT, "wjet_puptec1Down", true);
TH1F* wjet_puptec2Up = DC.readWriteHisto(fWJ, "puptec2up/", histName, sf_wjet, fout, fTT, "wjet_puptec2Up", true);
TH1F* wjet_puptec2Down = DC.readWriteHisto(fWJ, "puptec2down/", histName, sf_wjet, fout, fTT, "wjet_puptec2Down", true);
TH1F* wjet_bc_statUp = DC.readWriteHisto(fWJ, "base_bc_stat_up/", histName, sf_wjet, fout, fTT, "wjet_bcstat_" + year + "_" + workingpoint + "Up", true);
TH1F* wjet_bc_statDown = DC.readWriteHisto(fWJ, "base_bc_stat_do/", histName, sf_wjet, fout, fTT, "wjet_bcstat_" + year + "_" + workingpoint + "Down", true);
TH1F* wjet_lhemuFUp = DC.readWriteHisto(fWJ, "base_bc_lhemuf_up/", histName, sf_wjet, fout, fTT, "wjet_lhemuF_"+ year + "_" + workingpoint + "Up", true);
TH1F* wjet_lhemuFDown = DC.readWriteHisto(fWJ, "base_bc_lhemuf_do/", histName, sf_wjet, fout, fTT, "wjet_lhemuF_"+ year + "_" + workingpoint + "Down", true);
TH1F* wjet_lhemuRUp = DC.readWriteHisto(fWJ, "base_lhemur_up/", histName, sf_wjet, fout, fTT, "wjet_lhemuR_"+ year + "_" + workingpoint + "Up", true);
TH1F* wjet_lhemuRDown = DC.readWriteHisto(fWJ, "base_lhemur_do/", histName, sf_wjet, fout, fTT, "wjet_lhemuR_"+ year + "_" + workingpoint + "Down", true);
TH1F* wjet_extpUp = DC.readWriteHisto(fWJ, "base_extp_up/", histName, sf_wjet, fout, fTT, "wjet_bcextp_" + year + "_" + workingpoint + "Up", true);
TH1F* wjet_extpDown = DC.readWriteHisto(fWJ, "base_extp_do/", histName, sf_wjet, fout, fTT, "wjet_bcextp_" + year + "_" + workingpoint + "Down", true);
TH1F* wjet_intpUp = DC.readWriteHisto(fWJ, "base_intp_up/", histName, sf_wjet, fout, fTT, "wjet_bcintp_"+ year + "_" + workingpoint + "Up", true);
TH1F* wjet_intpDown = DC.readWriteHisto(fWJ, "base_intp_do/", histName, sf_wjet, fout, fTT, "wjet_bcintp_"+ year + "_" + workingpoint + "Down", true);
TH1F* wjet_xdycUp = DC.readWriteHisto(fWJ, "base_xdyc_up/", histName, sf_wjet, fout, fTT, "wjet_bcxdyc_"+ year + "_" + workingpoint + "Up", true);
TH1F* wjet_xdycDown = DC.readWriteHisto(fWJ, "base_xdyc_do/", histName, sf_wjet, fout, fTT, "wjet_bcxdyc_"+ year + "_" + workingpoint + "Down", true);
TH1F* wjet_xdybUp = DC.readWriteHisto(fWJ, "base_xdyb_up/", histName, sf_wjet, fout, fTT, "wjet_bcxdyb_" + year + "_" + workingpoint + "Up", true);
TH1F* wjet_xdybDown = DC.readWriteHisto(fWJ, "base_xdyb_do/", histName, sf_wjet, fout, fTT, "wjet_bcxdyb_" + year + "_" + workingpoint + "Down", true);
TH1F* wjet_xwjcUp = DC.readWriteHisto(fWJ, "base_xwj_up/", histName, sf_wjet, fout, fTT, "wjet_bcxwjc_" + year + "_" + workingpoint + "Up", true);
TH1F* wjet_xwjcDown = DC.readWriteHisto(fWJ, "base_xwj_do/", histName, sf_wjet, fout, fTT, "wjet_bcxwjc_" + year + "_" + workingpoint + "Down", true);
TH1F* wjet_muEffUp = DC.readWriteHisto(fWJ, "base_muEff_up/", histName, sf_wjet, fout, fTT, "wjet_muEffUp", true);
TH1F* wjet_muEffDown = DC.readWriteHisto(fWJ, "base_muEff_do/", histName, sf_wjet, fout, fTT, "wjet_muEffDown", true);
TH1F* wjet_singpiecalUp = DC.readWriteHisto(fWJ, "/singpiecalup/", histName, sf_wjet, fout, fTT, "wjet_singpiecalUp", true);
TH1F* wjet_singpiecalDown = DC.readWriteHisto(fWJ, "/singpiecaldown/", histName, sf_wjet, fout, fTT, "wjet_singpiecalDown", true);
TH1F* wjet_singpihcalUp = DC.readWriteHisto(fWJ, "/singpihcalup/", histName, sf_wjet, fout, fTT, "wjet_singpihcalUp", true);
TH1F* wjet_singpihcalDown = DC.readWriteHisto(fWJ,"/singpihcaldown/", histName, sf_wjet, fout, fTT, "wjet_singpihcalDown", true);
TH1F* wjet_relsampleUp = DC.readWriteHisto(fWJ, "relsampleup/", histName, sf_wjet, fout, fTT, "wjet_relsample_" + year + "Up", true);
TH1F* wjet_relsampleDown = DC.readWriteHisto(fWJ, "relsampledown/", histName, sf_wjet, fout, fTT, "wjet_relsample_" + year + "Down", true);
TH1F* wjet_relstatfsrUp = DC.readWriteHisto(fWJ, "relstatfsrup/", histName, sf_wjet, fout, fTT, "wjet_relstatfsr_" + year + "Up", true);
TH1F* wjet_relstatfsrDown = DC.readWriteHisto(fWJ, "relstatfsrdown/", histName, sf_wjet, fout, fTT, "wjet_relstatfsr_" + year + "Down", true);
TH1F* wjet_relfsrUp = DC.readWriteHisto(fWJ, "relfsrup/", histName, sf_wjet, fout, fTT, "wjet_relfsrUp", true);
TH1F* wjet_relfsrDown = DC.readWriteHisto(fWJ, "relfsrdown/", histName, sf_wjet, fout, fTT, "wjet_relfsrDown", true);
TH1F* wjet_relbalUp = DC.readWriteHisto(fWJ, "relbalup/", histName, sf_wjet, fout, fTT, "wjet_relbalUp", true);
TH1F* wjet_relbalDown = DC.readWriteHisto(fWJ, "relbaldown/", histName, sf_wjet, fout, fTT, "wjet_relbalDown", true);

 TH1F* wjet_relstathfUp = DC.readWriteHisto(fWJ, "relstathfup/", histName, sf_wjet, fout, fTT, "wjet_relstathf_" + year + "Up", true);
TH1F* wjet_relstathfDown = DC.readWriteHisto(fWJ, "relstathfdown/", histName, sf_wjet, fout, fTT, "wjet_relstathf_" + year + "Down", true);
 TH1F* wjet_pdfUp = DC.readWriteHisto(fWJ, "base_prefire_up/", histName, sf_wjet, fout, fTT, "wjet_pdfUp", true);
TH1F* wjet_pdfDown = DC.readWriteHisto(fWJ, "base_prefire_do/", histName, sf_wjet, fout, fTT, "wjet_pdfDown", true);
TH1F* wjet_puptbbUp = DC.readWriteHisto(fWJ, "puptbbup/", histName, sf_wjet, fout, fTT, "wjet_puptbbUp", true);
TH1F* wjet_puptbbDown = DC.readWriteHisto(fWJ, "puptbbdown/", histName, sf_wjet, fout, fTT, "wjet_puptbbDown", true);
TH1F* wjet_reljerhfUp = DC.readWriteHisto(fWJ, "reljerhfup/", histName, sf_wjet, fout, fTT, "wjet_reljerhfUp", true);
TH1F* wjet_reljerhfDown = DC.readWriteHisto(fWJ, "reljerhfdown/", histName, sf_wjet, fout, fTT, "wjet_reljerhfDown", true);
TH1F* wjet_pupthfUp = DC.readWriteHisto(fWJ, "pupthfup/", histName, sf_wjet, fout, fTT, "wjet_pupthfUp", true);
TH1F* wjet_pupthfDown = DC.readWriteHisto(fWJ, "pupthfdown/", histName, sf_wjet, fout, fTT, "wjet_pupthfDown", true);


  // Assuming wjet and all the systematic histograms are already filled and written
  // First, retrieve the integral of the base histogram
 //double baseIntegral_wjet = wjet->Integral();

normalizeHistogram(wjet_bc_statUp, wjet);
normalizeHistogram(wjet_bc_statDown, wjet);
normalizeHistogram(wjet_fsrUp, wjet);
normalizeHistogram(wjet_fsrDown, wjet);
normalizeHistogram(wjet_isrUp, wjet);
normalizeHistogram(wjet_isrDown, wjet);
// normalizeHistogram(wjet_lhemuFUp, wjet);
// normalizeHistogram(wjet_lhemuFDown, wjet);
// normalizeHistogram(wjet_lhemuRUp, wjet);
// normalizeHistogram(wjet_lhemuRDown, wjet);
// normalizeHistogram(wjet_extpUp, wjet);
// normalizeHistogram(wjet_extpDown, wjet);
// normalizeHistogram(wjet_intpUp, wjet);
// normalizeHistogram(wjet_intpDown, wjet);
// normalizeHistogram(wjet_xdycUp, wjet);
// normalizeHistogram(wjet_xdycDown, wjet);
// normalizeHistogram(wjet_xdybUp, wjet);
// normalizeHistogram(wjet_xdybDown, wjet);
// normalizeHistogram(wjet_xwjcUp, wjet);
// normalizeHistogram(wjet_xwjcDown, wjet);

//  fout->cd();
 
// wjet_lhemuFUp->Write();
// wjet_lhemuFDown->Write();
// wjet_lhemuRUp->Write();
// wjet_lhemuRDown->Write();
// wjet_extpUp->Write();
// wjet_extpDown->Write();
// wjet_intpUp->Write();
// wjet_intpDown->Write();
// wjet_xdycUp->Write();
// wjet_xdycDown->Write();
// wjet_xdybUp->Write();
// wjet_xdybDown->Write();
// wjet_xwjcUp->Write();
// wjet_xwjcDown->Write();
// normalizeHistogram(wjet_base_pdfUp, wjet);
// normalizeHistogram(wjet_base_pdfDo, wjet);

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
TH1F* zjet = DC.readWriteHisto(fDY, "base/", histName, sf_zjet, fout, fTT, "zjet", true);
TH1F* zjet_JESUp = DC.readWriteHisto(fDY, "base_JEC_up/", histName, sf_zjet, fout, fTT, "zjet_JESUp", true);
TH1F* zjet_JESDown = DC.readWriteHisto(fDY, "base_JEC_do/", histName, sf_zjet, fout, fTT, "zjet_JESDown", true);
TH1F* zjet_PileupUp = DC.readWriteHisto(fDY, "base_PUWeight_up/", histName, sf_zjet, fout, fTT, "zjet_PileupUp", true);
TH1F* zjet_PileupDown = DC.readWriteHisto(fDY, "base_PUWeight_do/", histName, sf_zjet, fout, fTT, "zjet_PileupDown", true);
TH1F* zjet_JERUp = DC.readWriteHisto(fDY, "jerup/", histName, sf_zjet, fout, fTT, "zjet_JER_"+ year + "Up", true);
TH1F* zjet_JERDown = DC.readWriteHisto(fDY, "jerdown/", histName, sf_zjet, fout, fTT, "zjet_JER_"+ year + "Down", true);
TH1F* zjet_prefireUp = DC.readWriteHisto(fDY, "base_prefire_up/", histName, sf_zjet, fout, fTT, "zjet_prefireUp", true);
TH1F* zjet_prefireDown = DC.readWriteHisto(fDY, "base_prefire_do/", histName, sf_zjet, fout, fTT, "zjet_prefireDown", true);
TH1F* zjet_fsrUp = DC.readWriteHisto(fDY, "base_fsr_up/", histName, sf_zjet, fout, fTT, "zjet_fsrUp", true);
TH1F* zjet_fsrDown = DC.readWriteHisto(fDY, "base_fsr_do/", histName, sf_zjet, fout, fTT, "zjet_fsrDown", true);
TH1F* zjet_isrUp = DC.readWriteHisto(fDY, "base_isr_up/", histName, sf_zjet, fout, fTT, "zjet_isrUp", true);
TH1F* zjet_isrDown = DC.readWriteHisto(fDY, "base_isr_do/", histName, sf_zjet, fout, fTT, "zjet_isrDown", true);
TH1F* zjet_flavorqcdUp = DC.readWriteHisto(fDY, "flavorqcdup/", histName, sf_zjet, fout, fTT, "zjet_flavorqcdUp", true);
TH1F* zjet_flavorqcdDown = DC.readWriteHisto(fDY, "flavorqcddown/", histName, sf_zjet, fout, fTT, "zjet_flavorqcdDown", true);
TH1F* zjet_timeptetaUp = DC.readWriteHisto(fDY, "timeptetaup/", histName, sf_zjet, fout, fTT, "zjet_timepteta_"+ year + "Up", true);
TH1F* zjet_timeptetaDown = DC.readWriteHisto(fDY, "timeptetadown/", histName, sf_zjet, fout, fTT, "zjet_timepteta_"+ year + "Down", true);
TH1F* zjet_jerhfUp = DC.readWriteHisto(fDY, "reljerhfup/", histName, sf_zjet, fout, fTT, "zjet_jerhfUp", true);
TH1F* zjet_jerhfDown = DC.readWriteHisto(fDY, "reljerhfdown/", histName, sf_zjet, fout, fTT, "zjet_jerhfDown", true);
TH1F* zjet_relptbbUp = DC.readWriteHisto(fDY, "relptbbup/", histName, sf_zjet, fout, fTT, "zjet_relptbbUp", true);
TH1F* zjet_relptbbDown = DC.readWriteHisto(fDY, "relptbbdown/", histName, sf_zjet, fout, fTT, "zjet_relptbbDown", true);
TH1F* zjet_relpthfUp = DC.readWriteHisto(fDY, "relpthfup/", histName, sf_zjet, fout, fTT, "zjet_relpthfUp", true);
TH1F* zjet_relpthfDown = DC.readWriteHisto(fDY, "relpthfdown/", histName, sf_zjet, fout, fTT, "zjet_relpthfDown", true);
TH1F* zjet_relstatecUp = DC.readWriteHisto(fDY, "relstatecup/", histName, sf_zjet, fout, fTT, "zjet_relstatec_" + year + "Up", true);
TH1F* zjet_relstatecDown = DC.readWriteHisto(fDY, "relstatecdown/", histName, sf_zjet, fout, fTT, "zjet_relstatec_" + year + "Down", true);
TH1F* zjet_absstatUp = DC.readWriteHisto(fDY, "absstatup/", histName, sf_zjet, fout, fTT, "zjet_absstat_" + year + "Up", true);
TH1F* zjet_absstatDown = DC.readWriteHisto(fDY, "absstatdown/", histName, sf_zjet, fout, fTT, "zjet_absstat_" + year + "Down", true);
TH1F* zjet_abssclUp = DC.readWriteHisto(fDY, "abssclup/", histName, sf_zjet, fout, fTT, "zjet_abssclUp", true);
TH1F* zjet_abssclDown = DC.readWriteHisto(fDY, "absscldown/", histName, sf_zjet, fout, fTT, "zjet_abssclDown", true);
TH1F* zjet_absmpfbUp = DC.readWriteHisto(fDY, "absmpfbup/", histName, sf_zjet, fout, fTT, "zjet_absmpfbUp", true);
TH1F* zjet_absmpfbDown = DC.readWriteHisto(fDY, "absmpfbdown/", histName, sf_zjet, fout, fTT, "zjet_absmpfbDown", true);
TH1F* zjet_fragUp = DC.readWriteHisto(fDY, "fragup/", histName, sf_zjet, fout, fTT, "zjet_fragUp", true);
TH1F* zjet_fragDown = DC.readWriteHisto(fDY, "fragdown/", histName, sf_zjet, fout, fTT, "zjet_fragDown", true);
TH1F* zjet_pudataMCUp = DC.readWriteHisto(fDY, "pudatamcup/", histName, sf_zjet, fout, fTT, "zjet_pudataMCUp", true);
TH1F* zjet_pudataMCDown = DC.readWriteHisto(fDY, "pudatamcdown/", histName, sf_zjet, fout, fTT, "zjet_pudataMCDown", true);
 TH1F* zjet_relptec1Up = DC.readWriteHisto(fDY, "relptec1up/", histName, sf_zjet, fout, fTT, "zjet_relptec1_" + year + "Up", true);
TH1F* zjet_relptec1Down = DC.readWriteHisto(fDY, "relptec1down/", histName, sf_zjet, fout, fTT, "zjet_relptec1_" + year + "Down", true);
TH1F* zjet_relptec2Up = DC.readWriteHisto(fDY, "relptec2up/", histName, sf_zjet, fout, fTT, "zjet_relptec2_" + year + "Up", true);
TH1F* zjet_relptec2Down = DC.readWriteHisto(fDY, "relptec2down/", histName, sf_zjet, fout, fTT, "zjet_relptec2_" + year + "Down", true);
TH1F* zjet_reljerec1Up = DC.readWriteHisto(fDY, "reljerec1up/", histName, sf_zjet, fout, fTT, "zjet_reljerec1_" + year + "Up", true);
TH1F* zjet_reljerec1Down = DC.readWriteHisto(fDY, "reljerec1down/", histName, sf_zjet, fout, fTT, "zjet_reljerec1_" + year + "Down", true);
TH1F* zjet_reljerec2Up = DC.readWriteHisto(fDY, "reljerec2up/", histName, sf_zjet, fout, fTT, "zjet_reljerec2_" + year + "Up", true);
TH1F* zjet_reljerec2Down = DC.readWriteHisto(fDY, "reljerec2down/", histName, sf_zjet, fout, fTT, "zjet_reljerec2_" + year + "Down", true);
TH1F* zjet_puptrefUp = DC.readWriteHisto(fDY, "puptrefup/", histName, sf_zjet, fout, fTT, "zjet_puptrefUp", true);
TH1F* zjet_puptrefDown = DC.readWriteHisto(fDY, "puptrefdown/", histName, sf_zjet, fout, fTT, "zjet_puptrefDown", true);
TH1F* zjet_puptec1Up = DC.readWriteHisto(fDY, "puptec1up/", histName, sf_zjet, fout, fTT, "zjet_puptec1Up", true);
TH1F* zjet_puptec1Down = DC.readWriteHisto(fDY, "puptec1down/", histName, sf_zjet, fout, fTT, "zjet_puptec1Down", true);
TH1F* zjet_puptec2Up = DC.readWriteHisto(fDY, "puptec2up/", histName, sf_zjet, fout, fTT, "zjet_puptec2Up", true);
TH1F* zjet_puptec2Down = DC.readWriteHisto(fDY, "puptec2down/", histName, sf_zjet, fout, fTT, "zjet_puptec2Down", true);
TH1F* zjet_bc_statUp = DC.readWriteHisto(fDY, "base_bc_stat_up/", histName, sf_zjet, fout, fTT, "zjet_bcstat_" + year + "_" + workingpoint + "Up", true);
TH1F* zjet_bc_statDown = DC.readWriteHisto(fDY, "base_bc_stat_do/", histName, sf_zjet, fout, fTT, "zjet_bcstat_" + year + "_" + workingpoint + "Down", true);
TH1F* zjet_lhemuFUp = DC.readWriteHisto(fDY, "base_bc_lhemuf_up/", histName, sf_zjet, fout, fTT, "zjet_lhemuF_"+ year + "_" + workingpoint + "Up", true);
TH1F* zjet_lhemuFDown = DC.readWriteHisto(fDY, "base_bc_lhemuf_do/", histName, sf_zjet, fout, fTT, "zjet_lhemuF_"+ year + "_" + workingpoint + "Down", true);
TH1F* zjet_lhemuRUp = DC.readWriteHisto(fDY, "base_lhemur_up/", histName, sf_zjet, fout, fTT, "zjet_lhemuR_"+ year + "_" + workingpoint + "Up", true);
TH1F* zjet_lhemuRDown = DC.readWriteHisto(fDY, "base_lhemur_do/", histName, sf_zjet, fout, fTT, "zjet_lhemuR_"+ year + "_" + workingpoint + "Down", true);
TH1F* zjet_extpUp = DC.readWriteHisto(fDY, "base_extp_up/", histName, sf_zjet, fout, fTT, "zjet_bcextp_" + year + "_" + workingpoint + "Up", true);
TH1F* zjet_extpDown = DC.readWriteHisto(fDY, "base_extp_do/", histName, sf_zjet, fout, fTT, "zjet_bcextp_" + year + "_" + workingpoint + "Down", true);
TH1F* zjet_intpUp = DC.readWriteHisto(fDY, "base_intp_up/", histName, sf_zjet, fout, fTT, "zjet_bcintp_"+ year + "_" + workingpoint + "Up", true);
TH1F* zjet_intpDown = DC.readWriteHisto(fDY, "base_intp_do/", histName, sf_zjet, fout, fTT, "zjet_bcintp_"+ year + "_" + workingpoint + "Down", true);
TH1F* zjet_xdycUp = DC.readWriteHisto(fDY, "base_xdyc_up/", histName, sf_zjet, fout, fTT, "zjet_bcxdyc_"+ year + "_" + workingpoint + "Up", true);
TH1F* zjet_xdycDown = DC.readWriteHisto(fDY, "base_xdyc_do/", histName, sf_zjet, fout, fTT, "zjet_bcxdyc_"+ year + "_" + workingpoint + "Down", true);
TH1F* zjet_xdybUp = DC.readWriteHisto(fDY, "base_xdyb_up/", histName, sf_zjet, fout, fTT, "zjet_bcxdyb_" + year + "_" + workingpoint + "Up", true);
TH1F* zjet_xdybDown = DC.readWriteHisto(fDY, "base_xdyb_do/", histName, sf_zjet, fout, fTT, "zjet_bcxdyb_" + year + "_" + workingpoint + "Down", true);
TH1F* zjet_xwjcUp = DC.readWriteHisto(fDY, "base_xwj_up/", histName, sf_zjet, fout, fTT, "zjet_bcxwjc_" + year + "_" + workingpoint + "Up", true);
TH1F* zjet_xwjcDown = DC.readWriteHisto(fDY, "base_xwj_do/", histName, sf_zjet, fout, fTT, "zjet_bcxwjc_" + year + "_" + workingpoint + "Down", true);
TH1F* zjet_muEffUp = DC.readWriteHisto(fDY, "base_muEff_up/", histName, sf_zjet, fout, fTT, "zjet_muEffUp", true);
TH1F* zjet_muEffDown = DC.readWriteHisto(fDY, "base_muEff_do/", histName, sf_zjet, fout, fTT, "zjet_muEffDown", true);
TH1F* zjet_singpiecalUp = DC.readWriteHisto(fDY, "/singpiecalup/", histName, sf_zjet, fout, fTT, "zjet_singpiecalUp", true);
TH1F* zjet_singpiecalDown = DC.readWriteHisto(fDY, "/singpiecaldown/", histName, sf_zjet, fout, fTT, "zjet_singpiecalDown", true);
TH1F* zjet_singpihcalUp = DC.readWriteHisto(fDY, "/singpihcalup/", histName, sf_zjet, fout, fTT, "zjet_singpihcalUp", true);
TH1F* zjet_singpihcalDown = DC.readWriteHisto(fDY,"/singpihcaldown/", histName, sf_zjet, fout, fTT, "zjet_singpihcalDown", true);
TH1F* zjet_relsampleUp = DC.readWriteHisto(fDY, "relsampleup/", histName, sf_zjet, fout, fTT, "zjet_relsample_" + year + "Up", true);
TH1F* zjet_relsampleDown = DC.readWriteHisto(fDY, "relsampledown/", histName, sf_zjet, fout, fTT, "zjet_relsample_" + year + "Down", true);
TH1F* zjet_relstatfsrUp = DC.readWriteHisto(fDY, "relstatfsrup/", histName, sf_zjet, fout, fTT, "zjet_relstatfsr_" + year + "Up", true);
TH1F* zjet_relstatfsrDown = DC.readWriteHisto(fDY, "relstatfsrdown/", histName, sf_zjet, fout, fTT, "zjet_relstatfsr_" + year + "Down", true);
TH1F* zjet_relfsrUp = DC.readWriteHisto(fDY, "relfsrup/", histName, sf_zjet, fout, fTT, "zjet_relfsrUp", true);
TH1F* zjet_relfsrDown = DC.readWriteHisto(fDY, "relfsrdown/", histName, sf_zjet, fout, fTT, "zjet_relfsrDown", true);
TH1F* zjet_relbalUp = DC.readWriteHisto(fDY, "relbalup/", histName, sf_zjet, fout, fTT, "zjet_relbalUp", true);
TH1F* zjet_relbalDown = DC.readWriteHisto(fDY, "relbaldown/", histName, sf_zjet, fout, fTT, "zjet_relbalDown", true);
TH1F* zjet_relstathfUp = DC.readWriteHisto(fDY, "relstathfup/", histName, sf_zjet, fout, fTT, "zjet_relstathf_" + year + "Up", true);
TH1F* zjet_relstathfDown = DC.readWriteHisto(fDY, "relstathfdown/", histName, sf_zjet, fout, fTT, "zjet_relstathf_" + year + "Down", true);
TH1F* zjet_pdfUp = DC.readWriteHisto(fDY, "base_prefire_up/", histName, sf_zjet, fout, fTT, "zjet_pdfUp", true);
TH1F* zjet_pdfDown = DC.readWriteHisto(fDY, "base_prefire_do/", histName, sf_zjet, fout, fTT, "zjet_pdfDown", true);
TH1F* zjet_puptbbUp = DC.readWriteHisto(fDY, "puptbbup/", histName, sf_zjet, fout, fTT, "zjet_puptbbUp", true);
TH1F* zjet_puptbbDown = DC.readWriteHisto(fDY, "puptbbdown/", histName, sf_zjet, fout, fTT, "zjet_puptbbDown", true);
TH1F* zjet_reljerhfUp = DC.readWriteHisto(fDY, "reljerhfup/", histName, sf_zjet, fout, fTT, "zjet_reljerhfUp", true);
TH1F* zjet_reljerhfDown = DC.readWriteHisto(fDY, "reljerhfdown/", histName, sf_zjet, fout, fTT, "zjet_reljerhfDown", true);
TH1F* zjet_pupthfUp = DC.readWriteHisto(fDY, "pupthfup/", histName, sf_zjet, fout, fTT, "zjet_pupthfUp", true);
TH1F* zjet_pupthfDown = DC.readWriteHisto(fDY, "pupthfdown/", histName, sf_zjet, fout, fTT, "zjet_pupthfDown", true);

// For stop
// double baseIntegral_zjet = zjet->Integral();

normalizeHistogram(zjet_bc_statUp, zjet);
normalizeHistogram(zjet_bc_statDown, zjet);
normalizeHistogram(zjet_fsrUp, zjet);
normalizeHistogram(zjet_fsrDown, zjet);
normalizeHistogram(zjet_isrUp, zjet);
normalizeHistogram(zjet_isrDown, zjet);
// normalizeHistogram(zjet_lhemuFUp, zjet);
// normalizeHistogram(zjet_lhemuFDown, zjet);
// normalizeHistogram(zjet_lhemuRUp, zjet);
// normalizeHistogram(zjet_lhemuRDown, zjet);
// normalizeHistogram(zjet_extpUp, zjet);
// normalizeHistogram(zjet_extpDown, zjet);
// normalizeHistogram(zjet_intpUp, zjet);
// normalizeHistogram(zjet_intpDown, zjet);
// normalizeHistogram(zjet_xdycUp, zjet);
// normalizeHistogram(zjet_xdycDown, zjet);
// normalizeHistogram(zjet_xdybUp, zjet);
// normalizeHistogram(zjet_xdybDown, zjet);
// normalizeHistogram(zjet_xwjcUp, zjet);
// normalizeHistogram(zjet_xwjcDown, zjet);
// normalizeHistogram(zjet_base_pdfUp, zjet);
// normalizeHistogram(zjet_base_pdfDo, zjet);
  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  zjet_bc_statUp->Write();
  zjet_bc_statDown->Write();
  zjet_fsrUp->Write();
  zjet_fsrDown->Write();
  zjet_isrUp->Write();
  zjet_isrDown->Write();
  zjet_lhemuFUp->Write();
// zjet_lhemuFDown->Write();
// zjet_lhemuRUp->Write();
// zjet_lhemuRDown->Write();
// zjet_extpUp->Write();
// zjet_extpDown->Write();
// zjet_intpUp->Write();
// zjet_intpDown->Write();
// zjet_xdycUp->Write();
// zjet_xdycDown->Write();
// zjet_xdybUp->Write();
// zjet_xdybDown->Write();
// zjet_xwjcUp->Write();
// zjet_xwjcDown->Write();
  // zjet_base_pdfUp->Write();
  // zjet_base_pdfDo->Write();


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

TH1F* stop = DC.readWriteHisto(fST, "base/", histName, sf_stop, fout, fTT, "stop", true);
TH1F* stop_JESUp = DC.readWriteHisto(fST, "base_JEC_up/", histName, sf_stop, fout, fTT, "stop_JESUp", true);
TH1F* stop_JESDown = DC.readWriteHisto(fST, "base_JEC_do/", histName, sf_stop, fout, fTT, "stop_JESDown", true);
TH1F* stop_PileupUp = DC.readWriteHisto(fST, "base_PUWeight_up/", histName, sf_stop, fout, fTT, "stop_PileupUp", true);
TH1F* stop_PileupDown = DC.readWriteHisto(fST, "base_PUWeight_do/", histName, sf_stop, fout, fTT, "stop_PileupDown", true);
TH1F* stop_JERUp = DC.readWriteHisto(fST, "jerup/", histName, sf_stop, fout, fTT, "stop_JER_"+ year + "Up", true);
TH1F* stop_JERDown = DC.readWriteHisto(fST, "jerdown/", histName, sf_stop, fout, fTT, "stop_JER_"+ year + "Down", true);
TH1F* stop_prefireUp = DC.readWriteHisto(fST, "base_prefire_up/", histName, sf_stop, fout, fTT, "stop_prefireUp", true);
TH1F* stop_prefireDown = DC.readWriteHisto(fST, "base_prefire_do/", histName, sf_stop, fout, fTT, "stop_prefireDown", true);
TH1F* stop_fsrUp = DC.readWriteHisto(fST, "base_fsr_up/", histName, sf_stop, fout, fTT, "stop_fsrUp", true);
TH1F* stop_fsrDown = DC.readWriteHisto(fST, "base_fsr_do/", histName, sf_stop, fout, fTT, "stop_fsrDown", true);
TH1F* stop_isrUp = DC.readWriteHisto(fST, "base_isr_up/", histName, sf_stop, fout, fTT, "stop_isrUp", true);
TH1F* stop_isrDown = DC.readWriteHisto(fST, "base_isr_do/", histName, sf_stop, fout, fTT, "stop_isrDown", true);
TH1F* stop_flavorqcdUp = DC.readWriteHisto(fST, "flavorqcdup/", histName, sf_stop, fout, fTT, "stop_flavorqcdUp", true);
TH1F* stop_flavorqcdDown = DC.readWriteHisto(fST, "flavorqcddown/", histName, sf_stop, fout, fTT, "stop_flavorqcdDown", true);
TH1F* stop_timeptetaUp = DC.readWriteHisto(fST, "timeptetaup/", histName, sf_stop, fout, fTT, "stop_timepteta_"+ year + "Up", true);
TH1F* stop_timeptetaDown = DC.readWriteHisto(fST, "timeptetadown/", histName, sf_stop, fout, fTT, "stop_timepteta_"+ year + "Down", true);
TH1F* stop_jerhfUp = DC.readWriteHisto(fST, "reljerhfup/", histName, sf_stop, fout, fTT, "stop_jerhfUp", true);
TH1F* stop_jerhfDown = DC.readWriteHisto(fST, "reljerhfdown/", histName, sf_stop, fout, fTT, "stop_jerhfDown", true);
TH1F* stop_relptbbUp = DC.readWriteHisto(fST, "relptbbup/", histName, sf_stop, fout, fTT, "stop_relptbbUp", true);
TH1F* stop_relptbbDown = DC.readWriteHisto(fST, "relptbbdown/", histName, sf_stop, fout, fTT, "stop_relptbbDown", true);
TH1F* stop_relpthfUp = DC.readWriteHisto(fST, "relpthfup/", histName, sf_stop, fout, fTT, "stop_relpthfUp", true);
TH1F* stop_relpthfDown = DC.readWriteHisto(fST, "relpthfdown/", histName, sf_stop, fout, fTT, "stop_relpthfDown", true);
TH1F* stop_relstatecUp = DC.readWriteHisto(fST, "relstatecup/", histName, sf_stop, fout, fTT, "stop_relstatec_" + year + "Up", true);
TH1F* stop_relstatecDown = DC.readWriteHisto(fST, "relstatecdown/", histName, sf_stop, fout, fTT, "stop_relstatec_" + year + "Down", true);
TH1F* stop_absstatUp = DC.readWriteHisto(fST, "absstatup/", histName, sf_stop, fout, fTT, "stop_absstat_" + year + "Up", true);
TH1F* stop_absstatDown = DC.readWriteHisto(fST, "absstatdown/", histName, sf_stop, fout, fTT, "stop_absstat_" + year + "Down", true);
TH1F* stop_abssclUp = DC.readWriteHisto(fST, "abssclup/", histName, sf_stop, fout, fTT, "stop_abssclUp", true);
TH1F* stop_abssclDown = DC.readWriteHisto(fST, "absscldown/", histName, sf_stop, fout, fTT, "stop_abssclDown", true);
TH1F* stop_absmpfbUp = DC.readWriteHisto(fST, "absmpfbup/", histName, sf_stop, fout, fTT, "stop_absmpfbUp", true);
TH1F* stop_absmpfbDown = DC.readWriteHisto(fST, "absmpfbdown/", histName, sf_stop, fout, fTT, "stop_absmpfbDown", true);
TH1F* stop_fragUp = DC.readWriteHisto(fST, "fragup/", histName, sf_stop, fout, fTT, "stop_fragUp", true);
TH1F* stop_fragDown = DC.readWriteHisto(fST, "fragdown/", histName, sf_stop, fout, fTT, "stop_fragDown", true);
TH1F* stop_pudataMCUp = DC.readWriteHisto(fST, "pudatamcup/", histName, sf_stop, fout, fTT, "stop_pudataMCUp", true);
TH1F* stop_pudataMCDown = DC.readWriteHisto(fST, "pudatamcdown/", histName, sf_stop, fout, fTT, "stop_pudataMCDown", true);
TH1F* stop_relptec1Up = DC.readWriteHisto(fST, "relptec1up/", histName, sf_stop, fout, fTT, "stop_relptec1_" + year + "Up", true);
TH1F* stop_relptec1Down = DC.readWriteHisto(fST, "relptec1down/", histName, sf_stop, fout, fTT, "stop_relptec1_" + year + "Down", true);

TH1F* stop_relptec2Up = DC.readWriteHisto(fST, "relptec2up/", histName, sf_stop, fout, fTT, "stop_relptec2_" + year + "Up", true);
TH1F* stop_relptec2Down = DC.readWriteHisto(fST, "relptec2down/", histName, sf_stop, fout, fTT, "stop_relptec2_" + year + "Down", true);
TH1F* stop_reljerec1Up = DC.readWriteHisto(fST, "reljerec1up/", histName, sf_stop, fout, fTT, "stop_reljerec1_" + year + "Up", true);
TH1F* stop_reljerec1Down = DC.readWriteHisto(fST, "reljerec1down/", histName, sf_stop, fout, fTT, "stop_reljerec1_" + year + "Down", true);

TH1F* stop_reljerec2Up = DC.readWriteHisto(fST, "reljerec2up/", histName, sf_stop, fout, fTT, "stop_reljerec2_" + year + "Up", true);
TH1F* stop_reljerec2Down = DC.readWriteHisto(fST, "reljerec2down/", histName, sf_stop, fout, fTT, "stop_reljerec2_" + year + "Down", true);
TH1F* stop_puptrefUp = DC.readWriteHisto(fST, "puptrefup/", histName, sf_stop, fout, fTT, "stop_puptrefUp", true);
TH1F* stop_puptrefDown = DC.readWriteHisto(fST, "puptrefdown/", histName, sf_stop, fout, fTT, "stop_puptrefDown", true);
TH1F* stop_puptec1Up = DC.readWriteHisto(fST, "puptec1up/", histName, sf_stop, fout, fTT, "stop_puptec1Up", true);
TH1F* stop_puptec1Down = DC.readWriteHisto(fST, "puptec1down/", histName, sf_stop, fout, fTT, "stop_puptec1Down", true);
TH1F* stop_puptec2Up = DC.readWriteHisto(fST, "puptec2up/", histName, sf_stop, fout, fTT, "stop_puptec2Up", true);
TH1F* stop_puptec2Down = DC.readWriteHisto(fST, "puptec2down/", histName, sf_stop, fout, fTT, "stop_puptec2Down", true);
TH1F* stop_bc_statUp = DC.readWriteHisto(fST, "base_bc_stat_up/", histName, sf_stop, fout, fTT, "stop_bcstat_" + year + "_" + workingpoint + "Up", true);
TH1F* stop_bc_statDown = DC.readWriteHisto(fST, "base_bc_stat_do/", histName, sf_stop, fout, fTT, "stop_bcstat_" + year + "_" + workingpoint + "Down", true);
TH1F* stop_lhemuFUp = DC.readWriteHisto(fST, "base_bc_lhemuf_up/", histName, sf_stop, fout, fTT, "stop_lhemuF_"+ year + "_" + workingpoint + "Up", true);
TH1F* stop_lhemuFDown = DC.readWriteHisto(fST, "base_bc_lhemuf_do/", histName, sf_stop, fout, fTT, "stop_lhemuF_"+ year + "_" + workingpoint + "Down", true);
TH1F* stop_lhemuRUp = DC.readWriteHisto(fST, "base_lhemur_up/", histName, sf_stop, fout, fTT, "stop_lhemuR_"+ year + "_" + workingpoint + "Up", true);
TH1F* stop_lhemuRDown = DC.readWriteHisto(fST, "base_lhemur_do/", histName, sf_stop, fout, fTT, "stop_lhemuR_"+ year + "_" + workingpoint + "Down", true);
TH1F* stop_extpUp = DC.readWriteHisto(fST, "base_extp_up/", histName, sf_stop, fout, fTT, "stop_bcextp_" + year + "_" + workingpoint + "Up", true);
TH1F* stop_extpDown = DC.readWriteHisto(fST, "base_extp_do/", histName, sf_stop, fout, fTT, "stop_bcextp_" + year + "_" + workingpoint + "Down", true);
TH1F* stop_intpUp = DC.readWriteHisto(fST, "base_intp_up/", histName, sf_stop, fout, fTT, "stop_bcintp_"+ year + "_" + workingpoint + "Up", true);
TH1F* stop_intpDown = DC.readWriteHisto(fST, "base_intp_do/", histName, sf_stop, fout, fTT, "stop_bcintp_"+ year + "_" + workingpoint + "Down", true);
TH1F* stop_xdycUp = DC.readWriteHisto(fST, "base_xdyc_up/", histName, sf_stop, fout, fTT, "stop_bcxdyc_"+ year + "_" + workingpoint + "Up", true);
TH1F* stop_xdycDown = DC.readWriteHisto(fST, "base_xdyc_do/", histName, sf_stop, fout, fTT, "stop_bcxdyc_"+ year + "_" + workingpoint + "Down", true);
TH1F* stop_xdybUp = DC.readWriteHisto(fST, "base_xdyb_up/", histName, sf_stop, fout, fTT, "stop_bcxdyb_" + year + "_" + workingpoint + "Up", true);
TH1F* stop_xdybDown = DC.readWriteHisto(fST, "base_xdyb_do/", histName, sf_stop, fout, fTT, "stop_bcxdyb_" + year + "_" + workingpoint + "Down", true);
TH1F* stop_xwjcUp = DC.readWriteHisto(fST, "base_xwj_up/", histName, sf_stop, fout, fTT, "stop_bcxwjc_" + year + "_" + workingpoint + "Up", true);
TH1F* stop_xwjcDown = DC.readWriteHisto(fST, "base_xwj_do/", histName, sf_stop, fout, fTT, "stop_bcxwjc_" + year + "_" + workingpoint + "Down", true);
TH1F* stop_muEffUp = DC.readWriteHisto(fST, "base_muEff_up/", histName, sf_stop, fout, fTT, "stop_muEffUp", true);
TH1F* stop_muEffDown = DC.readWriteHisto(fST, "base_muEff_do/", histName, sf_stop, fout, fTT, "stop_muEffDown", true);
TH1F* stop_singpiecalUp = DC.readWriteHisto(fST, "/singpiecalup/", histName, sf_stop, fout, fTT, "stop_singpiecalUp", true);
TH1F* stop_singpiecalDown = DC.readWriteHisto(fST, "/singpiecaldown/", histName, sf_stop, fout, fTT, "stop_singpiecalDown", true);
TH1F* stop_singpihcalUp = DC.readWriteHisto(fST, "/singpihcalup/", histName, sf_stop, fout, fTT, "stop_singpihcalUp", true);
TH1F* stop_singpihcalDown = DC.readWriteHisto(fST,"/singpihcaldown/", histName, sf_stop, fout, fTT, "stop_singpihcalDown", true);
TH1F* stop_relsampleUp = DC.readWriteHisto(fST, "relsampleup/", histName, sf_stop, fout, fTT, "stop_relsample_" + year + "Up", true);
TH1F* stop_relsampleDown = DC.readWriteHisto(fST, "relsampledown/", histName, sf_stop, fout, fTT, "stop_relsample_" + year + "Down", true);
TH1F* stop_relstatfsrUp = DC.readWriteHisto(fST, "relstatfsrup/", histName, sf_stop, fout, fTT, "stop_relstatfsr_" + year + "Up", true);
TH1F* stop_relstatfsrDown = DC.readWriteHisto(fST, "relstatfsrdown/", histName, sf_stop, fout, fTT, "stop_relstatfsr_" + year + "Down", true);
TH1F* stop_relfsrUp = DC.readWriteHisto(fST, "relfsrup/", histName, sf_stop, fout, fTT, "stop_relfsrUp", true);
TH1F* stop_relfsrDown = DC.readWriteHisto(fST, "relfsrdown/", histName, sf_stop, fout, fTT, "stop_relfsrDown", true);
TH1F* stop_relbalUp = DC.readWriteHisto(fST, "relbalup/", histName, sf_stop, fout, fTT, "stop_relbalUp", true);
TH1F* stop_relbalDown = DC.readWriteHisto(fST, "relbaldown/", histName, sf_stop, fout, fTT, "stop_relbalDown", true);
TH1F* stop_relstathfUp = DC.readWriteHisto(fST, "relstathfup/", histName, sf_stop, fout, fTT, "stop_relstathf_"+ year + "Up", true);
TH1F* stop_relstathfDown = DC.readWriteHisto(fST, "relstathfdown/", histName, sf_stop, fout, fTT, "stop_relstathf_" + year + "Down", true);
TH1F* stop_pdfUp = DC.readWriteHisto(fST, "base_prefire_up/", histName, sf_stop, fout, fTT, "stop_pdfUp", true);
TH1F* stop_pdfDown = DC.readWriteHisto(fST, "base_prefire_do/", histName, sf_stop, fout, fTT, "stop_pdfDown", true);
TH1F* stop_puptbbUp = DC.readWriteHisto(fST, "puptbbup/", histName, sf_stop, fout, fTT, "stop_puptbbUp", true);
TH1F* stop_puptbbDown = DC.readWriteHisto(fST, "puptbbdown/", histName, sf_stop, fout, fTT, "stop_puptbbDown", true);
TH1F* stop_reljerhfUp = DC.readWriteHisto(fST, "reljerhfup/", histName, sf_stop, fout, fTT, "stop_reljerhfUp", true);
TH1F* stop_reljerhfDown = DC.readWriteHisto(fST, "reljerhfdown/", histName, sf_stop, fout, fTT, "stop_reljerhfDown", true);
TH1F* stop_pupthfUp = DC.readWriteHisto(fST, "pupthfup/", histName, sf_stop, fout, fTT, "stop_pupthfUp", true);
TH1F* stop_pupthfDown = DC.readWriteHisto(fST, "pupthfdown/", histName, sf_stop, fout, fTT, "stop_pupthfDown", true);

// For vv
normalizeHistogram(stop_bc_statUp, stop);
normalizeHistogram(stop_bc_statDown, stop);
normalizeHistogram(stop_fsrUp, stop);
normalizeHistogram(stop_fsrDown, stop);
normalizeHistogram(stop_isrUp, stop);
normalizeHistogram(stop_isrDown, stop);
// normalizeHistogram(stop_lhemuFUp, stop);
// normalizeHistogram(stop_lhemuFDown, stop);
// normalizeHistogram(stop_lhemuRUp, stop);
// normalizeHistogram(stop_lhemuRDown, stop);
// normalizeHistogram(stop_extpUp, stop);
// normalizeHistogram(stop_extpDown, stop);
// normalizeHistogram(stop_intpUp, stop);
// normalizeHistogram(stop_intpDown, stop);
// normalizeHistogram(stop_xdycUp, stop);
// normalizeHistogram(stop_xdycDown, stop);
// normalizeHistogram(stop_xdybUp, stop);
// normalizeHistogram(stop_xdybDown, stop);
// normalizeHistogram(stop_xwjcUp, stop);
// normalizeHistogram(stop_xwjcDown, stop);
// normalizeHistogram(stop_base_pdfUp, stop);
// normalizeHistogram(stop_base_pdfDo, stop);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  stop_bc_statUp->Write();
  stop_bc_statDown->Write();
  stop_fsrUp->Write();
  stop_fsrDown->Write();
  stop_isrUp->Write();
  stop_isrDown->Write();
  stop_lhemuFUp->Write();
// stop_lhemuFDown->Write();
// stop_lhemuRUp->Write();
// stop_lhemuRDown->Write();
// stop_extpUp->Write();
// stop_extpDown->Write();
// stop_intpUp->Write();
// stop_intpDown->Write();
// stop_xdycUp->Write();
// stop_xdycDown->Write();
// stop_xdybUp->Write();
// stop_xdybDown->Write();
// stop_xwjcUp->Write();
// stop_xwjcDown->Write();
 //  stop_base_pdfUp->Write();
//   stop_base_pdfDo->Write();
// 
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
TH1F* vv = DC.readWriteHisto(fVV, "base/", histName, sf_vv, fout, fTT, "vv", true);
TH1F* vv_JESUp = DC.readWriteHisto(fVV, "base_JEC_up/", histName, sf_vv, fout, fTT, "vv_JESUp", true);
TH1F* vv_JESDown = DC.readWriteHisto(fVV, "base_JEC_do/", histName, sf_vv, fout, fTT, "vv_JESDown", true);
TH1F* vv_PileupUp = DC.readWriteHisto(fVV, "base_PUWeight_up/", histName, sf_vv, fout, fTT, "vv_PileupUp", true);
TH1F* vv_PileupDown = DC.readWriteHisto(fVV, "base_PUWeight_do/", histName, sf_vv, fout, fTT, "vv_PileupDown", true);
TH1F* vv_JERUp = DC.readWriteHisto(fVV, "jerup/", histName, sf_vv, fout, fTT, "vv_JER_"+ year + "Up", true);
TH1F* vv_JERDown = DC.readWriteHisto(fVV, "jerdown/", histName, sf_vv, fout, fTT, "vv_JER_"+ year + "Down", true);
TH1F* vv_prefireUp = DC.readWriteHisto(fVV, "base_prefire_up/", histName, sf_vv, fout, fTT, "vv_prefireUp", true);
TH1F* vv_prefireDown = DC.readWriteHisto(fVV, "base_prefire_do/", histName, sf_vv, fout, fTT, "vv_prefireDown", true);
TH1F* vv_fsrUp = DC.readWriteHisto(fVV, "base_fsr_up/", histName, sf_vv, fout, fTT, "vv_fsrUp", true);
TH1F* vv_fsrDown = DC.readWriteHisto(fVV, "base_fsr_do/", histName, sf_vv, fout, fTT, "vv_fsrDown", true);
TH1F* vv_isrUp = DC.readWriteHisto(fVV, "base_isr_up/", histName, sf_vv, fout, fTT, "vv_isrUp", true);
TH1F* vv_isrDown = DC.readWriteHisto(fVV, "base_isr_do/", histName, sf_vv, fout, fTT, "vv_isrDown", true);
TH1F* vv_flavorqcdUp = DC.readWriteHisto(fVV, "flavorqcdup/", histName, sf_vv, fout, fTT, "vv_flavorqcdUp", true);
TH1F* vv_flavorqcdDown = DC.readWriteHisto(fVV, "flavorqcddown/", histName, sf_vv, fout, fTT, "vv_flavorqcdDown", true);
TH1F* vv_timeptetaUp = DC.readWriteHisto(fVV, "timeptetaup/", histName, sf_vv, fout, fTT, "vv_timepteta_"+ year + "Up", true);
TH1F* vv_timeptetaDown = DC.readWriteHisto(fVV, "timeptetadown/", histName, sf_vv, fout, fTT, "vv_timepteta_"+ year + "Down", true);
TH1F* vv_jerhfUp = DC.readWriteHisto(fVV, "reljerhfup/", histName, sf_vv, fout, fTT, "vv_jerhfUp", true);
TH1F* vv_jerhfDown = DC.readWriteHisto(fVV, "reljerhfdown/", histName, sf_vv, fout, fTT, "vv_jerhfDown", true);
TH1F* vv_relptbbUp = DC.readWriteHisto(fVV, "relptbbup/", histName, sf_vv, fout, fTT, "vv_relptbbUp", true);
TH1F* vv_relptbbDown = DC.readWriteHisto(fVV, "relptbbdown/", histName, sf_vv, fout, fTT, "vv_relptbbDown", true);
TH1F* vv_relpthfUp = DC.readWriteHisto(fVV, "relpthfup/", histName, sf_vv, fout, fTT, "vv_relpthfUp", true);
TH1F* vv_relpthfDown = DC.readWriteHisto(fVV, "relpthfdown/", histName, sf_vv, fout, fTT, "vv_relpthfDown", true);
TH1F* vv_relstatecUp = DC.readWriteHisto(fVV, "relstatecup/", histName, sf_vv, fout, fTT, "vv_relstatec_" + year + "Up", true);
TH1F* vv_relstatecDown = DC.readWriteHisto(fVV, "relstatecdown/", histName, sf_vv, fout, fTT, "vv_relstatec_" + year + "Down", true);
TH1F* vv_absstatUp = DC.readWriteHisto(fVV, "absstatup/", histName, sf_vv, fout, fTT, "vv_absstat_" + year + "Up", true);
TH1F* vv_absstatDown = DC.readWriteHisto(fVV, "absstatdown/", histName, sf_vv, fout, fTT, "vv_absstat_" + year + "Down", true);
TH1F* vv_abssclUp = DC.readWriteHisto(fVV, "abssclup/", histName, sf_vv, fout, fTT, "vv_abssclUp", true);
TH1F* vv_abssclDown = DC.readWriteHisto(fVV, "absscldown/", histName, sf_vv, fout, fTT, "vv_abssclDown", true);
TH1F* vv_absmpfbUp = DC.readWriteHisto(fVV, "absmpfbup/", histName, sf_vv, fout, fTT, "vv_absmpfbUp", true);
TH1F* vv_absmpfbDown = DC.readWriteHisto(fVV, "absmpfbdown/", histName, sf_vv, fout, fTT, "vv_absmpfbDown", true);
TH1F* vv_fragUp = DC.readWriteHisto(fVV, "fragup/", histName, sf_vv, fout, fTT, "vv_fragUp", true);
TH1F* vv_fragDown = DC.readWriteHisto(fVV, "fragdown/", histName, sf_vv, fout, fTT, "vv_fragDown", true);
TH1F* vv_pudataMCUp = DC.readWriteHisto(fVV, "pudatamcup/", histName, sf_vv, fout, fTT, "vv_pudataMCUp", true);
TH1F* vv_pudataMCDown = DC.readWriteHisto(fVV, "pudatamcdown/", histName, sf_vv, fout, fTT, "vv_pudataMCDown", true);
TH1F* vv_relptec1Up = DC.readWriteHisto(fVV, "relptec1up/", histName, sf_vv, fout, fTT, "vv_relptec1_" + year + "Up", true);
TH1F* vv_relptec1Down = DC.readWriteHisto(fVV, "relptec1down/", histName, sf_vv, fout, fTT, "vv_relptec1_" + year + "Down", true);
TH1F* vv_relptec2Up = DC.readWriteHisto(fVV, "relptec2up/", histName, sf_vv, fout, fTT, "vv_relptec2_" + year + "Up", true);
TH1F* vv_relptec2Down = DC.readWriteHisto(fVV, "relptec2down/", histName, sf_vv, fout, fTT, "vv_relptec2_" + year + "Down", true);
TH1F* vv_reljerec1Up = DC.readWriteHisto(fVV, "reljerec1up/", histName, sf_vv, fout, fTT, "vv_reljerec1_" + year + "Up", true);
TH1F* vv_reljerec1Down = DC.readWriteHisto(fVV, "reljerec1down/", histName, sf_vv, fout, fTT, "vv_reljerec1_" + year + "Down", true);
TH1F* vv_reljerec2Up = DC.readWriteHisto(fVV, "reljerec2up/", histName, sf_vv, fout, fTT, "vv_reljerec2_" + year + "Up", true);
TH1F* vv_reljerec2Down = DC.readWriteHisto(fVV, "reljerec2down/", histName, sf_vv, fout, fTT, "vv_reljerec2_" + year + "Down", true);
TH1F* vv_puptrefUp = DC.readWriteHisto(fVV, "puptrefup/", histName, sf_vv, fout, fTT, "vv_puptrefUp", true);
TH1F* vv_puptrefDown = DC.readWriteHisto(fVV, "puptrefdown/", histName, sf_vv, fout, fTT, "vv_puptrefDown", true);
TH1F* vv_puptec1Up = DC.readWriteHisto(fVV, "puptec1up/", histName, sf_vv, fout, fTT, "vv_puptec1Up", true);
TH1F* vv_puptec1Down = DC.readWriteHisto(fVV, "puptec1down/", histName, sf_vv, fout, fTT, "vv_puptec1Down", true);
TH1F* vv_puptec2Up = DC.readWriteHisto(fVV, "puptec2up/", histName, sf_vv, fout, fTT, "vv_puptec2Up", true);
TH1F* vv_puptec2Down = DC.readWriteHisto(fVV, "puptec2down/", histName, sf_vv, fout, fTT, "vv_puptec2Down", true);
TH1F* vv_bc_statUp = DC.readWriteHisto(fVV, "base_bc_stat_up/", histName, sf_vv, fout, fTT, "vv_bcstat_" + year + "_" + workingpoint + "Up", true);
TH1F* vv_bc_statDown = DC.readWriteHisto(fVV, "base_bc_stat_do/", histName, sf_vv, fout, fTT, "vv_bcstat_" + year + "_" + workingpoint + "Down", true);
TH1F* vv_lhemuFUp = DC.readWriteHisto(fVV, "base_bc_lhemuf_up/", histName, sf_vv, fout, fTT, "vv_lhemuF_"+ year + "_" + workingpoint + "Up", true);
TH1F* vv_lhemuFDown = DC.readWriteHisto(fVV, "base_bc_lhemuf_do/", histName, sf_vv, fout, fTT, "vv_lhemuF_"+ year + "_" + workingpoint + "Down", true);
TH1F* vv_lhemuRUp = DC.readWriteHisto(fVV, "base_lhemur_up/", histName, sf_vv, fout, fTT, "vv_lhemuR_"+ year + "_" + workingpoint + "Up", true);
TH1F* vv_lhemuRDown = DC.readWriteHisto(fVV, "base_lhemur_do/", histName, sf_vv, fout, fTT, "vv_lhemuR_"+ year + "_" + workingpoint + "Down", true);
TH1F* vv_extpUp = DC.readWriteHisto(fVV, "base_extp_up/", histName, sf_vv, fout, fTT, "vv_bcextp_" + year + "_" + workingpoint + "Up", true);
TH1F* vv_extpDown = DC.readWriteHisto(fVV, "base_extp_do/", histName, sf_vv, fout, fTT, "vv_bcextp_" + year + "_" + workingpoint + "Down", true);
TH1F* vv_intpUp = DC.readWriteHisto(fVV, "base_intp_up/", histName, sf_vv, fout, fTT, "vv_bcintp_"+ year + "_" + workingpoint + "Up", true);
TH1F* vv_intpDown = DC.readWriteHisto(fVV, "base_intp_do/", histName, sf_vv, fout, fTT, "vv_bcintp_"+ year + "_" + workingpoint + "Down", true);
TH1F* vv_xdycUp = DC.readWriteHisto(fVV, "base_xdyc_up/", histName, sf_vv, fout, fTT, "vv_bcxdyc_"+ year + "_" + workingpoint + "Up", true);
TH1F* vv_xdycDown = DC.readWriteHisto(fVV, "base_xdyc_do/", histName, sf_vv, fout, fTT, "vv_bcxdyc_"+ year + "_" + workingpoint + "Down", true);
TH1F* vv_xdybUp = DC.readWriteHisto(fVV, "base_xdyb_up/", histName, sf_vv, fout, fTT, "vv_bcxdyb_" + year + "_" + workingpoint + "Up", true);
TH1F* vv_xdybDown = DC.readWriteHisto(fVV, "base_xdyb_do/", histName, sf_vv, fout, fTT, "vv_bcxdyb_" + year + "_" + workingpoint + "Down", true);
TH1F* vv_xwjcUp = DC.readWriteHisto(fVV, "base_xwj_up/", histName, sf_vv, fout, fTT, "vv_bcxwjc_" + year + "_" + workingpoint + "Up", true);
TH1F* vv_xwjcDown = DC.readWriteHisto(fVV, "base_xwj_do/", histName, sf_vv, fout, fTT, "vv_bcxwjc_" + year + "_" + workingpoint + "Down", true);
TH1F* vv_muEffUp = DC.readWriteHisto(fVV, "base_muEff_up/", histName, sf_vv, fout, fTT, "vv_muEffUp", true);
TH1F* vv_muEffDown = DC.readWriteHisto(fVV, "base_muEff_do/", histName, sf_vv, fout, fTT, "vv_muEffDown", true);
TH1F* vv_singpiecalUp = DC.readWriteHisto(fVV, "/singpiecalup/", histName, sf_vv, fout, fTT, "vv_singpiecalUp", true);
TH1F* vv_singpiecalDown = DC.readWriteHisto(fVV, "/singpiecaldown/", histName, sf_vv, fout, fTT, "vv_singpiecalDown", true);
TH1F* vv_singpihcalUp = DC.readWriteHisto(fVV, "/singpihcalup/", histName, sf_vv, fout, fTT, "vv_singpihcalUp", true);
TH1F* vv_singpihcalDown = DC.readWriteHisto(fVV,"/singpihcaldown/", histName, sf_vv, fout, fTT, "vv_singpihcalDown", true);
TH1F* vv_relsampleUp = DC.readWriteHisto(fVV, "relsampleup/", histName, sf_vv, fout, fTT, "vv_relsample_" + year + "Up", true);
TH1F* vv_relsampleDown = DC.readWriteHisto(fVV, "relsampledown/", histName, sf_vv, fout, fTT, "vv_relsample_" + year + "Down", true);
TH1F* vv_relstatfsrUp = DC.readWriteHisto(fVV, "relstatfsrup/", histName, sf_vv, fout, fTT, "vv_relstatfsr_" + year + "Up", true);
TH1F* vv_relstatfsrDown = DC.readWriteHisto(fVV, "relstatfsrdown/", histName, sf_vv, fout, fTT, "vv_relstatfsr_" + year + "Down", true);
 TH1F* vv_relfsrUp = DC.readWriteHisto(fVV, "relfsrup/", histName, sf_vv, fout, fTT, "vv_relfsrUp", true);
TH1F* vv_relfsrDown = DC.readWriteHisto(fVV, "relfsrdown/", histName, sf_vv, fout, fTT, "vv_relfsrDown", true);
TH1F* vv_relbalUp = DC.readWriteHisto(fVV, "relbalup/", histName, sf_vv, fout, fTT, "vv_relbalUp", true);
TH1F* vv_relbalDown = DC.readWriteHisto(fVV, "relbaldown/", histName, sf_vv, fout, fTT, "vv_relbalDown", true);
TH1F* vv_relstathfUp = DC.readWriteHisto(fVV, "relstathfup/", histName, sf_vv, fout, fTT, "vv_relstathf_" + year + "Up", true);
TH1F* vv_relstathfDown = DC.readWriteHisto(fVV, "relstathfdown/", histName, sf_vv, fout, fTT, "vv_relstathf_" + year + "Down", true);
TH1F* vv_pdfUp = DC.readWriteHisto(fVV, "base_prefire_up/", histName, sf_vv, fout, fTT, "vv_pdfUp", true);
TH1F* vv_pdfDown = DC.readWriteHisto(fVV, "base_prefire_do/", histName, sf_vv, fout, fTT, "vv_pdfDown", true);
TH1F* vv_puptbbUp = DC.readWriteHisto(fVV, "puptbbup/", histName, sf_vv, fout, fTT, "vv_puptbbUp", true);
TH1F* vv_puptbbDown = DC.readWriteHisto(fVV, "puptbbdown/", histName, sf_vv, fout, fTT, "vv_puptbbDown", true);
TH1F* vv_reljerhfUp = DC.readWriteHisto(fVV, "reljerhfup/", histName, sf_vv, fout, fTT, "vv_reljerhfUp", true);
TH1F* vv_reljerhfDown = DC.readWriteHisto(fVV, "reljerhfdown/", histName, sf_vv, fout, fTT, "vv_reljerhfDown", true);
TH1F* vv_pupthfUp = DC.readWriteHisto(fVV, "pupthfup/", histName, sf_vv, fout, fTT, "vv_pupthfUp", true);
TH1F* vv_pupthfDown = DC.readWriteHisto(fVV, "pupthfdown/", histName, sf_vv, fout, fTT, "vv_pupthfDown", true);
  
normalizeHistogram(vv_bc_statUp, vv);
normalizeHistogram(vv_bc_statDown, vv);
normalizeHistogram(vv_fsrUp, vv);
normalizeHistogram(vv_fsrDown, vv);
normalizeHistogram(vv_isrUp, vv);
normalizeHistogram(vv_isrDown, vv);
// normalizeHistogram(vv_lhemuFUp, vv);
// normalizeHistogram(vv_lhemuFDown, vv);
// normalizeHistogram(vv_lhemuRUp, vv);
// normalizeHistogram(vv_lhemuRDown, vv);
// normalizeHistogram(vv_extpUp, vv);
// normalizeHistogram(vv_extpDown, vv);
// normalizeHistogram(vv_intpUp, vv);
// normalizeHistogram(vv_intpDown, vv);
// normalizeHistogram(vv_xdycUp, vv);
// normalizeHistogram(vv_xdycDown, vv);
// normalizeHistogram(vv_xdybUp, vv);
// normalizeHistogram(vv_xdybDown, vv);
// normalizeHistogram(vv_xwjcUp, vv);
// normalizeHistogram(vv_xwjcDown, vv);
// normalizeHistogram(vv_base_pdfUp, vv);
// normalizeHistogram(vv_base_pdfDo, vv);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  vv_bc_statUp->Write();
  vv_bc_statDown->Write();
  vv_fsrUp->Write();
  vv_fsrDown->Write();
  vv_isrUp->Write();
  vv_isrDown->Write();
//   vv_lhemuFUp->Write();
// vv_lhemuFDown->Write();
// vv_lhemuRUp->Write();
// vv_lhemuRDown->Write();
// vv_extpUp->Write();
// vv_extpDown->Write();
// vv_intpUp->Write();
// vv_intpDown->Write();
// vv_xdycUp->Write();
// vv_xdycDown->Write();
// vv_xdybUp->Write();
// vv_xdybDown->Write();
// vv_xwjcUp->Write();
// vv_xwjcDown->Write();
  // vv_base_pdfUp->Write();
  // vv_base_pdfDo->Write();



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

  //   TH1F* qcd_dd = DC.readWriteHisto(fQCD_dd, "", qhist, sf_qcd, fout, fQCD_dd, "qcd", true);

TString wpShort;
if (workingpoint == "ExcTight") {
    wpShort = "ExcT";
} else if (workingpoint == "ExcMedium") {
    wpShort = "ExcM";
} else if (workingpoint == "ExcLoose") {
    wpShort = "ExcL";
}

// Construct the qhist1 string with the selected working point
TString qhist1 = "_ct_" + wpShort + "_mjj_"+ channelName;
TString qhist1Down = "_ct_" + wpShort + "_mjj_" + channelName + "_down";
TString qhist1Up = "_ct_" + wpShort + "_mjj_" + channelName + "_up";
 
     TH1F* qcd_dd = DC.readWriteHisto(fQCD, "base/", histName, sf_qcd, fout, fQCD, "qcd", true);
     TH1F* qcd_ddDown = DC.readWriteHisto(fQCD, "QCDddUp/", histName, sf_qcd, fout, fQCD, "qcd_qcddd_" +channelName+"_"+year+"_"+workingpoint +"Down", true);
     TH1F* qcd_ddUp = DC.readWriteHisto(fQCD, "QCDddDown/", histName, sf_qcd, fout, fQCD, "qcd_qcddd_" +channelName+"_"+year+"_"+workingpoint + "Up", true);
     // double stat_unc_qcd = DC.getStatUnc(qcd_dd, 0);
  // // cout<<"qcd stat unc: "<<stat_unc_qcd<<endl;
  // // cout<<"qcd = "<<qcd_dd->Integral()<<endl;
  // double qcd_unc = DC.getSysUncQcd(fData, fTT, fST, fWJ, fDY,  fVV, histSubDir_+"/", histName, false);
   
  //Data
  double sf_data = 1.0; //should be 1, always
//  TH1F* data_obs = DC.readWriteHisto(fData, baseDir+"/"+histSubDir, histName, sf_data, fout, fData, "data_obs", true);
  TH1F* data_obs = DC.readWriteHisto(fData, "base/", histName, sf_data, fout, fTT, "data_obs", true);
  cout<<"data_obs================: "<<data_obs->Integral()<<endl;

//wh
  double sf_wh = 1.0; 
TH1F* wh = DC.readWriteHisto(fWH, "base/", histName, sf_wh, fout, fTT, label, true);
TH1F* wh_JESUp = DC.readWriteHisto(fWH, "base_JEC_up/", histName, sf_wh, fout, fTT, label + "_JESUp", true);
TH1F* wh_JESDown = DC.readWriteHisto(fWH, "base_JEC_do/", histName, sf_wh, fout, fTT, label + "_JESDown", true);
TH1F* wh_PileupUp = DC.readWriteHisto(fWH, "base_PUWeight_up/", histName, sf_wh, fout, fTT, label + "_PileupUp", true);
TH1F* wh_PileupDown = DC.readWriteHisto(fWH, "base_PUWeight_do/", histName, sf_wh, fout, fTT, label + "_PileupDown", true);
TH1F* wh_JERUp = DC.readWriteHisto(fWH, "jerup/", histName, sf_wh, fout, fTT, label + "_JER_"+ year + "Up", true);
TH1F* wh_JERDown = DC.readWriteHisto(fWH, "jerdown/", histName, sf_wh, fout, fTT, label + "_JER_"+ year + "Down", true);
TH1F* wh_prefireUp = DC.readWriteHisto(fWH, "base_prefire_up/", histName, sf_wh, fout, fTT, label + "_prefireUp", true);
TH1F* wh_prefireDown = DC.readWriteHisto(fWH, "base_prefire_do/", histName, sf_wh, fout, fTT, label + "_prefireDown", true);
TH1F* wh_fsrUp = DC.readWriteHisto(fWH, "base_fsr_up/", histName, sf_wh, fout, fTT, label + "_fsrUp", true);
TH1F* wh_fsrDown = DC.readWriteHisto(fWH, "base_fsr_do/", histName, sf_wh, fout, fTT, label + "_fsrDown", true);
TH1F* wh_isrUp = DC.readWriteHisto(fWH, "base_isr_up/", histName, sf_wh, fout, fTT, label + "_isrUp", true);
TH1F* wh_isrDown = DC.readWriteHisto(fWH, "base_isr_do/", histName, sf_wh, fout, fTT, label + "_isrDown", true);
TH1F* wh_flavorqcdUp = DC.readWriteHisto(fWH, "flavorqcdup/", histName, sf_wh, fout, fTT, label + "_flavorqcdUp", true);
TH1F* wh_flavorqcdDown = DC.readWriteHisto(fWH, "flavorqcddown/", histName, sf_wh, fout, fTT, label + "_flavorqcdDown", true);
TH1F* wh_timeptetaUp = DC.readWriteHisto(fWH, "timeptetaup/", histName, sf_wh, fout, fTT, label + "_timepteta_"+ year + "Up", true);
TH1F* wh_timeptetaDown = DC.readWriteHisto(fWH, "timeptetadown/", histName, sf_wh, fout, fTT, label + "_timepteta_"+ year + "Down", true);
TH1F* wh_jerhfUp = DC.readWriteHisto(fWH, "reljerhfup/", histName, sf_wh, fout, fTT, label + "_jerhfUp", true);
TH1F* wh_jerhfDown = DC.readWriteHisto(fWH, "reljerhfdown/", histName, sf_wh, fout, fTT, label + "_jerhfDown", true);
TH1F* wh_relptbbUp = DC.readWriteHisto(fWH, "relptbbup/", histName, sf_wh, fout, fTT, label + "_relptbbUp", true);
TH1F* wh_relptbbDown = DC.readWriteHisto(fWH, "relptbbdown/", histName, sf_wh, fout, fTT, label + "_relptbbDown", true);
TH1F* wh_relpthfUp = DC.readWriteHisto(fWH, "relpthfup/", histName, sf_wh, fout, fTT, label + "_relpthfUp", true);
TH1F* wh_relpthfDown = DC.readWriteHisto(fWH, "relpthfdown/", histName, sf_wh, fout, fTT, label + "_relpthfDown", true);
TH1F* wh_relstatecUp = DC.readWriteHisto(fWH, "relstatecup/", histName, sf_wh, fout, fTT, label + "_relstatec_" + year + "Up", true);
TH1F* wh_relstatecDown = DC.readWriteHisto(fWH, "relstatecdown/", histName, sf_wh, fout, fTT, label + "_relstatec_" + year + "Down", true);
TH1F* wh_absstatUp = DC.readWriteHisto(fWH, "absstatup/", histName, sf_wh, fout, fTT, label + "_absstat_" + year + "Up", true);
TH1F* wh_absstatDown = DC.readWriteHisto(fWH, "absstatdown/", histName, sf_wh, fout, fTT, label + "_absstat_" + year + "Down", true);
TH1F* wh_abssclUp = DC.readWriteHisto(fWH, "abssclup/", histName, sf_wh, fout, fTT, label + "_abssclUp", true);
TH1F* wh_abssclDown = DC.readWriteHisto(fWH, "absscldown/", histName, sf_wh, fout, fTT, label + "_abssclDown", true);
TH1F* wh_absmpfbUp = DC.readWriteHisto(fWH, "absmpfbup/", histName, sf_wh, fout, fTT, label + "_absmpfbUp", true);
TH1F* wh_absmpfbDown = DC.readWriteHisto(fWH, "absmpfbdown/", histName, sf_wh, fout, fTT, label + "_absmpfbDown", true);
TH1F* wh_fragUp = DC.readWriteHisto(fWH, "fragup/", histName, sf_wh, fout, fTT, label + "_fragUp", true);
TH1F* wh_fragDown = DC.readWriteHisto(fWH, "fragdown/", histName, sf_wh, fout, fTT, label + "_fragDown", true);
TH1F* wh_pudataMCUp = DC.readWriteHisto(fWH, "pudatamcup/", histName, sf_wh, fout, fTT, label + "_pudataMCUp", true);
TH1F* wh_pudataMCDown = DC.readWriteHisto(fWH, "pudatamcdown/", histName, sf_wh, fout, fTT, label + "_pudataMCDown", true);
TH1F* wh_relptec1Up = DC.readWriteHisto(fWH, "relptec1up/", histName, sf_wh, fout, fTT, label + "_relptec1_" + year + "Up", true);
TH1F* wh_relptec1Down = DC.readWriteHisto(fWH, "relptec1down/", histName, sf_wh, fout, fTT, label + "_relptec1_" + year + "Down", true);
TH1F* wh_relptec2Up = DC.readWriteHisto(fWH, "relptec2up/", histName, sf_wh, fout, fTT, label + "_relptec2_" + year + "Up", true);
TH1F* wh_relptec2Down = DC.readWriteHisto(fWH, "relptec2down/", histName, sf_wh, fout, fTT, label + "_relptec2_" + year + "Down", true);
TH1F* wh_reljerec1Up = DC.readWriteHisto(fWH, "reljerec1up/", histName, sf_wh, fout, fTT, label + "_reljerec1_" + year + "Up", true);
TH1F* wh_reljerec1Down = DC.readWriteHisto(fWH, "reljerec1down/", histName, sf_wh, fout, fTT, label + "_reljerec1_" + year + "Down", true);
TH1F* wh_reljerec2Up = DC.readWriteHisto(fWH, "reljerec2up/", histName, sf_wh, fout, fTT, label + "_reljerec2_" + year + "Up", true);
TH1F* wh_reljerec2Down = DC.readWriteHisto(fWH, "reljerec2down/", histName, sf_wh, fout, fTT, label + "_reljerec2_" + year + "Down", true);
TH1F* wh_puptrefUp = DC.readWriteHisto(fWH, "puptrefup/", histName, sf_wh, fout, fTT, label + "_puptrefUp", true);
TH1F* wh_puptrefDown = DC.readWriteHisto(fWH, "puptrefdown/", histName, sf_wh, fout, fTT, label + "_puptrefDown", true);
TH1F* wh_puptec1Up = DC.readWriteHisto(fWH, "puptec1up/", histName, sf_wh, fout, fTT, label + "_puptec1Up", true);
TH1F* wh_puptec1Down = DC.readWriteHisto(fWH, "puptec1down/", histName, sf_wh, fout, fTT, label + "_puptec1Down", true);
TH1F* wh_puptec2Up = DC.readWriteHisto(fWH, "puptec2up/", histName, sf_wh, fout, fTT, label + "_puptec2Up", true);
TH1F* wh_puptec2Down = DC.readWriteHisto(fWH, "puptec2down/", histName, sf_wh, fout, fTT, label + "_puptec2Down", true);
TH1F* wh_bc_statUp = DC.readWriteHisto(fWH, "base_bc_stat_up/", histName, sf_wh, fout, fTT, label + "_bcstat_" + year + "_" + workingpoint + "Up", true);
TH1F* wh_bc_statDown = DC.readWriteHisto(fWH, "base_bc_stat_do/", histName, sf_wh, fout, fTT,label + "_bcstat_" + year + "_" + workingpoint + "Down", true);
TH1F* wh_lhemuFUp = DC.readWriteHisto(fWH, "base_bc_lhemuf_up/", histName, sf_wh, fout, fTT, label + "_lhemuF_"+ year + "_" + workingpoint + "Up", true);
TH1F* wh_lhemuFDown = DC.readWriteHisto(fWH, "base_bc_lhemuf_do/", histName, sf_wh, fout, fTT, label + "_lhemuF_"+ year + "_" + workingpoint + "Down", true);
TH1F* wh_lhemuRUp = DC.readWriteHisto(fWH, "base_lhemur_up/", histName, sf_wh, fout, fTT, label + "_lhemuR_"+ year + "_" + workingpoint + "Up", true);
TH1F* wh_lhemuRDown = DC.readWriteHisto(fWH, "base_lhemur_do/", histName, sf_wh, fout, fTT, label + "_lhemuR_"+ year + "_" + workingpoint + "Down", true);
TH1F* wh_extpUp = DC.readWriteHisto(fWH, "base_extp_up/", histName, sf_wh, fout, fTT, label + "_bcextp_" + year + "_" + workingpoint + "Up", true);
TH1F* wh_extpDown = DC.readWriteHisto(fWH, "base_extp_do/", histName, sf_wh, fout, fTT, label + "_bcextp_" + year + "_" + workingpoint + "Down", true);
TH1F* wh_intpUp = DC.readWriteHisto(fWH, "base_intp_up/", histName, sf_wh, fout, fTT, label + "_bcintp_"+ year + "_" + workingpoint + "Up", true);
TH1F* wh_intpDown = DC.readWriteHisto(fWH, "base_intp_do/", histName, sf_wh, fout, fTT, label + "_bcintp_"+ year + "_" + workingpoint + "Down", true);
TH1F* wh_xdycUp = DC.readWriteHisto(fWH, "base_xdyc_up/", histName, sf_wh, fout, fTT, label + "_bcxdyc_"+ year + "_" + workingpoint + "Up", true);
TH1F* wh_xdycDown = DC.readWriteHisto(fWH, "base_xdyc_do/", histName, sf_wh, fout, fTT, label + "_bcxdyc_"+ year + "_" + workingpoint + "Down", true);
TH1F* wh_xdybUp = DC.readWriteHisto(fWH, "base_xdyb_up/", histName, sf_wh, fout, fTT, label + "_bcxdyb_" + year + "_" + workingpoint + "Up", true);
TH1F* wh_xdybDown = DC.readWriteHisto(fWH, "base_xdyb_do/", histName, sf_wh, fout, fTT, label + "_bcxdyb_" + year + "_" + workingpoint + "Down", true);
TH1F* wh_xwjcUp = DC.readWriteHisto(fWH, "base_xwj_up/", histName, sf_wh, fout, fTT, label + "_bcxwjc_" + year + "_" + workingpoint + "Up", true);
TH1F* wh_xwjcDown = DC.readWriteHisto(fWH, "base_xwj_do/", histName, sf_wh, fout, fTT, label + "_bcxwjc_" + year + "_" + workingpoint + "Down", true);
TH1F* wh_muEffUp = DC.readWriteHisto(fWH, "base_muEff_up/", histName, sf_wh, fout, fTT, label + "_muEffUp", true);
TH1F* wh_muEffDown = DC.readWriteHisto(fWH, "base_muEff_do/", histName, sf_wh, fout, fTT, label + "_muEffDown", true);
TH1F* wh_singpiecalUp = DC.readWriteHisto(fWH, "singpiecalup/", histName, sf_wh, fout, fTT, label + "_singpiecalUp", true);
TH1F* wh_singpiecalDown = DC.readWriteHisto(fWH, "singpiecaldown/", histName, sf_wh, fout, fTT, label + "_singpiecalDown", true);
TH1F* wh_singpihcalUp = DC.readWriteHisto(fWH, "singpihcalup/", histName, sf_wh, fout, fTT, label + "_singpihcalUp", true);
TH1F* wh_singpihcalDown = DC.readWriteHisto(fWH, "singpihcaldown/", histName, sf_wh, fout, fTT, label + "_singpihcalDown", true);
TH1F* wh_relsampleUp = DC.readWriteHisto(fWH, "relsampleup/", histName, sf_wh, fout, fTT, label + "_relsample_" + year + "Up", true);
TH1F* wh_relsampleDown = DC.readWriteHisto(fWH, "relsampledown/", histName, sf_wh, fout, fTT, label + "_relsample_" + year + "Down", true);
TH1F* wh_relstatfsrUp = DC.readWriteHisto(fWH, "relstatfsrup/", histName, sf_wh, fout, fTT, label + "_relstatfsr_" + year + "Up", true);
TH1F* wh_relstatfsrDown = DC.readWriteHisto(fWH, "relstatfsrdown/", histName, sf_wh, fout, fTT, label + "_relstatfsr_" + year + "Down", true);
TH1F* wh_relfsrUp = DC.readWriteHisto(fWH, "relfsrup/", histName, sf_wh, fout, fTT, label + "_relfsrUp", true);
TH1F* wh_relfsrDown = DC.readWriteHisto(fWH, "relfsrdown/", histName, sf_wh, fout, fTT, label + "_relfsrDown", true);
TH1F* wh_relbalUp = DC.readWriteHisto(fWH, "relbalup/", histName, sf_wh, fout, fTT, label + "_relbalUp", true);
 TH1F* wh_relbalDown = DC.readWriteHisto(fWH, "relbaldown/", histName, sf_wh, fout, fTT, label + "_relbalDown", true);
TH1F* wh_relstathfUp = DC.readWriteHisto(fWH, "relstathfup/", histName, sf_wh, fout, fTT, label + "_relstathf_" + year + "Up", true);
TH1F* wh_relstathfDown = DC.readWriteHisto(fWH, "relstathfdown/", histName, sf_wh, fout, fTT, label + "_relstathf_" + year + "Down", true);
TH1F* wh_pdfUp = DC.readWriteHisto(fWH, "base_prefire_up/", histName, sf_wh, fout, fTT, label +"_pdfUp", true);
TH1F* wh_pdfDown = DC.readWriteHisto(fWH, "base_prefire_do/", histName, sf_wh, fout, fTT, label +"_pdfDown", true);
TH1F* wh_puptbbUp = DC.readWriteHisto(fWH, "puptbbup/", histName, sf_wh, fout, fTT, label + "_puptbbUp", true);
TH1F* wh_puptbbDown = DC.readWriteHisto(fWH, "puptbbdown/", histName, sf_wh, fout, fTT, label + "_puptbbDown", true);
TH1F* wh_reljerhfUp = DC.readWriteHisto(fWH, "reljerhfup/", histName, sf_wh, fout, fTT, label + "_reljerhfUp", true);
TH1F* wh_reljerhfDown = DC.readWriteHisto(fWH, "reljerhfdown/", histName, sf_wh, fout, fTT, label + "_reljerhfDown", true);
TH1F* wh_pupthfUp = DC.readWriteHisto(fWH, "pupthfup/", histName, sf_wh, fout, fTT, label + "_pupthfUp", true);
TH1F* wh_pupthfDown = DC.readWriteHisto(fWH, "pupthfdown/", histName, sf_wh, fout, fTT, label + "_pupthfDown", true);
TH1F* wh_topPtUp = DC.readWriteHisto(fWH, "base_topPt_up/", histName, sf_wh, fout, fTT, label + "_topPtUp", true);
TH1F* wh_topPtDown = DC.readWriteHisto(fWH, "base_topPt_do/", histName, sf_wh, fout, fTT, label + "_topPtDown", true);
 
normalizeHistogram(wh_bc_statUp, wh);
normalizeHistogram(wh_bc_statDown, wh);
normalizeHistogram(wh_fsrUp, wh);
normalizeHistogram(wh_fsrDown, wh);
normalizeHistogram(wh_isrUp, wh);
normalizeHistogram(wh_isrDown, wh);
// normalizeHistogram(wh_lhemuFUp, wh);
// normalizeHistogram(wh_lhemuFDown, wh);
// normalizeHistogram(wh_lhemuRUp, wh);
// normalizeHistogram(wh_lhemuRDown, wh);
// normalizeHistogram(wh_extpUp, wh);
// normalizeHistogram(wh_extpDown, wh);
// normalizeHistogram(wh_intpUp, wh);
// normalizeHistogram(wh_intpDown, wh);
// normalizeHistogram(wh_xdycUp, wh);
// normalizeHistogram(wh_xdycDown, wh);
// normalizeHistogram(wh_xdybUp, wh);
// normalizeHistogram(wh_xdybDown, wh);
// normalizeHistogram(wh_xwjcUp, wh);
// normalizeHistogram(wh_xwjcDown, wh);
// normalizeHistogram(wh_base_pdfUp, wh);
// normalizeHistogram(wh_base_pdfDo, wh);

  // After normalization, you may want to write the normalized histograms back to the file or use them in your analysis
  fout->cd();  // Assuming fout is the output file and already open
  wh_bc_statUp->Write();
  wh_bc_statDown->Write();
  wh_fsrUp->Write();
  wh_fsrDown->Write();
  wh_isrUp->Write();
  wh_isrDown->Write();
//   wh_lhemuFUp->Write();
// wh_lhemuFDown->Write();
// wh_lhemuRUp->Write();
// wh_lhemuRDown->Write();
// wh_extpUp->Write();
// wh_extpDown->Write();
// wh_intpUp->Write();
// wh_intpDown->Write();
// wh_xdycUp->Write();
// wh_xdycDown->Write();
// wh_xdybUp->Write();
// wh_xdybDown->Write();
// wh_xwjcUp->Write();
// wh_xwjcDown->Write();
  // wh_base_pdfUp->Write();
  // wh_base_pdfDo->Write();


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
  char* c = new char[220];
  in.open("MyTemplateDataCard.txt");
  //create output data card for 13 TeV
  string outDataCard = "datacard_hcs_2018_WH.txt";
  string histName_str(histSubDir_+TString("_")+histName+workingpoint);
  if(isMuChannel) outDataCard = "datacard_hcs_2018_mu_"+histName_str+"_WH%d.txt"; 
  else outDataCard = "datacard_hcs_2018_ele_"+histName_str+"_WH%d.txt";
  ofstream out(Form(outDataCard.c_str(), mass));
  out.precision(8);

  time_t secs=time(0);
  tm *t=localtime(&secs);
 while (in.good()){
    in.getline(c,220,'\n');
    if (in.good()){
      string line(c);
      if(line.find("Date")!=string::npos){
        string day = string(Form("%d",t->tm_mday));
        string month = string(Form("%d",t->tm_mon+1));
        string year = string(Form("%d",t->tm_year+1220));
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
        line.replace( line.find("XXX") , 3 , string(TString("Shapes_hcs_2018_")+channelName+TString("_")+histSubDir_+TString("_")+workingpoint+histName+TString("_")+label));
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
	    << space << ttg->Integral()
	    << space << ttw->Integral()
	    << space << ttz->Integral()
	    << space << tth->Integral()
            << space << wjet->Integral()
            << space << zjet->Integral()
            << space << stop->Integral()
            << space << vv->Integral()
	    << space << qcd_dd->Integral()
            << endl;
      }
    else if (line.find("CMS_Pileup") != string::npos) {
      DC.replaceSystematicUnc(line,wh, wh_PileupUp, wh_PileupDown, ttbar, ttbar_PileupUp, ttbar_PileupDown, wjet, wjet_PileupUp, wjet_PileupDown, zjet, zjet_PileupUp, zjet_PileupDown, stop, stop_PileupUp, stop_PileupDown, vv, vv_PileupUp, vv_PileupDown, ttw, ttw_PileupUp, ttw_PileupDown, ttz, ttz_PileupUp, ttz_PileupDown, ttg, ttg_PileupUp, ttg_PileupDown, tth, tth_PileupUp, tth_PileupDown, out);
    }
    else if (line.find("CMS_scale_j") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_JESUp, wh_JESDown, ttbar, ttbar_JESUp, ttbar_JESDown, wjet, wjet_JESUp, wjet_JESDown, zjet, zjet_JESUp, zjet_JESDown, stop, stop_JESUp, stop_JESDown, vv, vv_JESUp, vv_JESDown, ttw, ttw_JESUp, ttw_JESDown, ttz, ttz_JESUp, ttz_JESDown, ttg, ttg_JESUp, ttg_JESDown, tth, tth_JESUp, tth_JESDown, out);
    }
    else if (line.find("CMS_res_j") != string::npos) {
      DC.replaceSystematicUnc(line,wh, wh_JERUp, wh_JERDown, ttbar, ttbar_JERUp, ttbar_JERDown, wjet, wjet_JERUp, wjet_JERDown, zjet, zjet_JERUp, zjet_JERDown, stop, stop_JERUp, stop_JERDown, vv, vv_JERUp, vv_JERDown,ttw, ttw_JERUp, ttw_JERDown, ttz, ttz_JERUp, ttz_JERDown, ttg, ttg_JERUp, ttg_JERDown, tth, tth_JERUp, tth_JERDown, out);
    }
    else if (line.find("CMS_timepteta") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_timeptetaUp, wh_timeptetaDown, ttbar, ttbar_timeptetaUp, ttbar_timeptetaDown, wjet, wjet_timeptetaUp, wjet_timeptetaDown, zjet, zjet_timeptetaUp, zjet_timeptetaDown, stop, stop_timeptetaUp, stop_timeptetaDown, vv, vv_timeptetaUp, vv_timeptetaDown, ttw, ttw_timeptetaUp, ttw_timeptetaDown, ttz, ttz_timeptetaUp, ttz_timeptetaDown, ttg, ttg_timeptetaUp, ttg_timeptetaDown, tth, tth_timeptetaUp, tth_timeptetaDown, out);
    }
    else if (line.find("CMS_jerhf") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_jerhfUp, wh_jerhfDown, ttbar, ttbar_jerhfUp, ttbar_jerhfDown, wjet, wjet_jerhfUp, wjet_jerhfDown, zjet, zjet_jerhfUp, zjet_jerhfDown, stop, stop_jerhfUp, stop_jerhfDown, vv, vv_jerhfUp, vv_jerhfDown,ttw, ttw_jerhfUp, ttw_jerhfDown, ttz, ttz_jerhfUp, ttz_jerhfDown, ttg, ttg_jerhfUp, ttg_jerhfDown, tth, tth_jerhfUp, tth_jerhfDown, out);
    }
    else if (line.find("CMS_relptbb") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_relptbbUp, wh_relptbbDown, ttbar, ttbar_relptbbUp, ttbar_relptbbDown, wjet, wjet_relptbbUp, wjet_relptbbDown, zjet, zjet_relptbbUp, zjet_relptbbDown, stop, stop_relptbbUp, stop_relptbbDown, vv, vv_relptbbUp, vv_relptbbDown,ttw, ttw_relptbbUp, ttw_relptbbDown, ttz, ttz_relptbbUp, ttz_relptbbDown, ttg, ttg_relptbbUp, ttg_relptbbDown, tth, tth_relptbbUp, tth_relptbbDown, out);
    }
    else if (line.find("CMS_relpthf") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_relpthfUp, wh_relpthfDown, ttbar, ttbar_relpthfUp, ttbar_relpthfDown, wjet, wjet_relpthfUp, wjet_relpthfDown, zjet, zjet_relpthfUp, zjet_relpthfDown, stop, stop_relpthfUp, stop_relpthfDown, vv, vv_relpthfUp, vv_relpthfDown,ttw, ttw_relpthfUp, ttw_relpthfDown, ttz, ttz_relpthfUp, ttz_relpthfDown, ttg, ttg_relpthfUp, ttg_relpthfDown, tth, tth_relpthfUp, tth_relpthfDown, out);
    }
    else if (line.find("CMS_relstatec_" + year) != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_relstatecUp, wh_relstatecDown, ttbar, ttbar_relstatecUp, ttbar_relstatecDown, wjet, wjet_relstatecUp, wjet_relstatecDown, zjet, zjet_relstatecUp, zjet_relstatecDown, stop, stop_relstatecUp, stop_relstatecDown, vv, vv_relstatecUp, vv_relstatecDown,ttw, ttw_relstatecUp, ttw_relstatecDown, ttz, ttz_relstatecUp, ttz_relstatecDown, ttg, ttg_relstatecUp, ttg_relstatecDown, tth, tth_relstatecUp, tth_relstatecDown,out);
    }
    else if (line.find("CMS_absstat") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_absstatUp, wh_absstatDown, ttbar, ttbar_absstatUp, ttbar_absstatDown, wjet, wjet_absstatUp, wjet_absstatDown, zjet, zjet_absstatUp, zjet_absstatDown, stop, stop_absstatUp, stop_absstatDown, vv, vv_absstatUp, vv_absstatDown, ttw, ttw_absstatUp, ttw_absstatDown, ttz, ttz_absstatUp, ttz_absstatDown, ttg, ttg_absstatUp, ttg_absstatDown, tth, tth_absstatUp, tth_absstatDown, out);
    }
    else if (line.find("CMS_absscl") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_abssclUp, wh_abssclDown, ttbar, ttbar_abssclUp, ttbar_abssclDown, wjet, wjet_abssclUp, wjet_abssclDown, zjet, zjet_abssclUp, zjet_abssclDown, stop, stop_abssclUp, stop_abssclDown, vv, vv_abssclUp, vv_abssclDown,ttw, ttw_abssclUp, ttw_abssclDown, ttz, ttz_abssclUp, ttz_abssclDown, ttg, ttg_abssclUp, ttg_abssclDown, tth, tth_abssclUp, tth_abssclDown, out);
    }
    else if (line.find("CMS_absmpfb") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_absmpfbUp, wh_absmpfbDown, ttbar, ttbar_absmpfbUp, ttbar_absmpfbDown, wjet, wjet_absmpfbUp, wjet_absmpfbDown, zjet, zjet_absmpfbUp, zjet_absmpfbDown, stop, stop_absmpfbUp, stop_absmpfbDown, vv, vv_absmpfbUp, vv_absmpfbDown,ttw, ttw_absmpfbUp, ttw_absmpfbDown, ttz, ttz_absmpfbUp, ttz_absmpfbDown, ttg, ttg_absmpfbUp, ttg_absmpfbDown, tth, tth_absmpfbUp, tth_absmpfbDown, out);
    }
    else if (line.find("CMS_lhemuF") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_lhemuFUp, wh_lhemuFDown, ttbar, ttbar_lhemuFUp, ttbar_lhemuFDown, wjet, wjet_lhemuFUp, wjet_lhemuFDown, zjet, zjet_lhemuFUp, zjet_lhemuFDown, stop, stop_lhemuFUp, stop_lhemuFDown, vv, vv_lhemuFUp, vv_lhemuFDown,  ttw, ttw_lhemuFUp, ttw_lhemuFDown, ttz, ttz_lhemuFUp, ttz_lhemuFDown, ttg, ttg_lhemuFUp, ttg_lhemuFDown, tth, tth_lhemuFUp, tth_lhemuFDown,out);
    }
    else if (line.find("CMS_lhemuR") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_lhemuRUp, wh_lhemuRDown, ttbar, ttbar_lhemuRUp, ttbar_lhemuRDown, wjet, wjet_lhemuRUp, wjet_lhemuRDown, zjet, zjet_lhemuRUp, zjet_lhemuRDown, stop, stop_lhemuRUp, stop_lhemuRDown, vv, vv_lhemuRUp, vv_lhemuRDown,ttw, ttw_lhemuRUp, ttw_lhemuRDown, ttz, ttz_lhemuRUp, ttz_lhemuRDown, ttg, ttg_lhemuRUp, ttg_lhemuRDown, tth, tth_lhemuRUp, tth_lhemuRDown, out);
    }
    else if (line.find("CMS_frag") != string::npos) {
      DC.replaceSystematicUnc(line,wh, wh_fragUp, wh_fragDown, ttbar, ttbar_fragUp, ttbar_fragDown, wjet, wjet_fragUp, wjet_fragDown, zjet, zjet_fragUp, zjet_fragDown, stop, stop_fragUp, stop_fragDown, vv, vv_fragUp, vv_fragDown,ttw, ttw_fragUp, ttw_fragDown, ttz, ttz_fragUp, ttz_fragDown, ttg, ttg_fragUp, ttg_fragDown, tth, tth_fragUp, tth_fragDown, out);
    }
    else if (line.find("CMS_pudataMC") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_pudataMCUp, wh_pudataMCDown, ttbar, ttbar_pudataMCUp, ttbar_pudataMCDown, wjet, wjet_pudataMCUp, wjet_pudataMCDown, zjet, zjet_pudataMCUp, zjet_pudataMCDown, stop, stop_pudataMCUp, stop_pudataMCDown, vv, vv_pudataMCUp, vv_pudataMCDown, ttw, ttw_pudataMCUp, ttw_pudataMCDown, ttz, ttz_pudataMCUp, ttz_pudataMCDown, ttg, ttg_pudataMCUp, ttg_pudataMCDown, tth, tth_pudataMCUp, tth_pudataMCDown,out);
    }
    else if (line.find("CMS_relptec2") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_relptec2Up, wh_relptec2Down, ttbar, ttbar_relptec2Up, ttbar_relptec2Down, wjet, wjet_relptec2Up, wjet_relptec2Down, zjet, zjet_relptec2Up, zjet_relptec2Down, stop, stop_relptec2Up, stop_relptec2Down, vv, vv_relptec2Up, vv_relptec2Down,ttw, ttw_relptec2Up, ttw_relptec2Down, ttz, ttz_relptec2Up, ttz_relptec2Down, ttg, ttg_relptec2Up, ttg_relptec2Down, tth, tth_relptec2Up, tth_relptec2Down,  out);
    }
    else if (line.find("CMS_flavorqcd") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_flavorqcdUp, wh_flavorqcdDown, ttbar, ttbar_flavorqcdUp, ttbar_flavorqcdDown, wjet, wjet_flavorqcdUp, wjet_flavorqcdDown, zjet, zjet_flavorqcdUp, zjet_flavorqcdDown, stop, stop_flavorqcdUp, stop_flavorqcdDown, vv, vv_flavorqcdUp, vv_flavorqcdDown,ttw, ttw_flavorqcdUp, ttw_flavorqcdDown, ttz, ttz_flavorqcdUp, ttz_flavorqcdDown, ttg, ttg_flavorqcdUp, ttg_flavorqcdDown, tth, tth_flavorqcdUp, tth_flavorqcdDown,out);
    }
    else if (line.find("CMS_bcextp_2018") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_extpUp, wh_extpDown, ttbar, ttbar_extpUp, ttbar_extpDown, wjet, wjet_extpUp, wjet_extpDown, zjet, zjet_extpUp, zjet_extpDown, stop, stop_extpUp, stop_extpDown, vv, vv_extpUp, vv_extpDown,ttw, ttw_extpUp, ttw_extpDown, ttz, ttz_extpUp, ttz_extpDown, ttg, ttg_extpUp, ttg_extpDown, tth, tth_extpUp, tth_extpDown,out);
    }
    else if (line.find("CMS_bcintp_2018") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_intpUp, wh_intpDown, ttbar, ttbar_intpUp, ttbar_intpDown, wjet, wjet_intpUp, wjet_intpDown, zjet, zjet_intpUp, zjet_intpDown, stop, stop_intpUp, stop_intpDown, vv, vv_intpUp, vv_intpDown,ttw, ttw_intpUp, ttw_intpDown, ttz, ttz_intpUp, ttz_intpDown, ttg, ttg_intpUp, ttg_intpDown, tth, tth_intpUp, tth_intpDown, out);
    }
    else if (line.find("CMS_bclhemuf") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_lhemuFUp, wh_lhemuFDown, ttbar, ttbar_lhemuFUp, ttbar_lhemuFDown, wjet, wjet_lhemuFUp, wjet_lhemuFDown, zjet, zjet_lhemuFUp, zjet_lhemuFDown, stop, stop_lhemuFUp, stop_lhemuFDown, vv, vv_lhemuFUp, vv_lhemuFDown,ttw, ttw_lhemuFUp, ttw_lhemuFDown, ttz, ttz_lhemuFUp, ttz_lhemuFDown, ttg, ttg_lhemuFUp, ttg_lhemuFDown, tth, tth_lhemuFUp, tth_lhemuFDown, out);
    }
    else if (line.find("CMS_bclhemur") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_lhemuRUp, wh_lhemuRDown, ttbar, ttbar_lhemuRUp, ttbar_lhemuRDown, wjet, wjet_lhemuRUp, wjet_lhemuRDown, zjet, zjet_lhemuRUp, zjet_lhemuRDown, stop, stop_lhemuRUp, stop_lhemuRDown, vv, vv_lhemuRUp, vv_lhemuRDown,ttw, ttw_lhemuRUp, ttw_lhemuRDown, ttz, ttz_lhemuRUp, ttz_lhemuRDown, ttg, ttg_lhemuRUp, ttg_lhemuRDown, tth, tth_lhemuRUp, tth_lhemuRDown, out);
    }
    else if (line.find("CMS_bcstat_2018") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_bc_statUp, wh_bc_statDown, ttbar, ttbar_bc_statUp, ttbar_bc_statDown, wjet, wjet_bc_statUp, wjet_bc_statDown, zjet, zjet_bc_statUp, zjet_bc_statDown, stop, stop_bc_statUp, stop_bc_statDown, vv, vv_bc_statUp, vv_bc_statDown, ttw, ttw_bc_statUp, ttw_bc_statDown, ttz, ttz_bc_statUp, ttz_bc_statDown, ttg, ttg_bc_statUp, ttg_bc_statDown, tth, tth_bc_statUp, tth_bc_statDown, out);
    }
    else if (line.find("CMS_bcxdyb") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_xdybUp, wh_xdybDown, ttbar, ttbar_xdybUp, ttbar_xdybDown, wjet, wjet_xdybUp, wjet_xdybDown, zjet, zjet_xdybUp, zjet_xdybDown, stop, stop_xdybUp, stop_xdybDown, vv, vv_xdybUp, vv_xdybDown,ttw, ttw_xdybUp, ttw_xdybDown, ttz, ttz_xdybUp, ttz_xdybDown, ttg, ttg_xdybUp, ttg_xdybDown, tth, tth_xdybUp, tth_xdybDown, out);
    }
    else if (line.find("CMS_bcxdyc") != string::npos) {
      DC.replaceSystematicUnc(line, wh, wh_xdycUp, wh_xdycDown, ttbar, ttbar_xdycUp, ttbar_xdycDown, wjet, wjet_xdycUp, wjet_xdycDown, zjet, zjet_xdycUp, zjet_xdycDown, stop, stop_xdycUp, stop_xdycDown, vv, vv_xdycUp, vv_xdycDown,ttw, ttw_xdycUp, ttw_xdycDown, ttz, ttz_xdycUp, ttz_xdycDown, ttg, ttg_xdycUp, ttg_xdycDown, tth, tth_xdycUp, tth_xdycDown, out);
    }
// else if (line.find("CMS_ttbar_cp5") != string::npos) {
//   DC.replaceSystematicUnc(line, wh, wh_cp5Up, wh_cp5Down, ttbar, ttbar_cp5Up, ttbar_cp5Down, wjet, wjet_cp5Up, wjet_cp5Down, zjet, zjet_cp5Up, zjet_cp5Down, stop, stop_cp5Up, stop_cp5Down, vv, vv_cp5Up, vv_cp5Down, ttw, ttw_cp5Up, ttw_cp5Down, ttz, ttz_cp5Up, ttz_cp5Down, ttg, ttg_cp5Up, ttg_cp5Down, tth, tth_cp5Up, tth_cp5Down, out);
// }

// else if (line.find("CMS_ttbar_hdamp") != string::npos) {
//   DC.replaceSystematicUnc(line, wh, wh_hdampUp, wh_hdampDown, ttbar, ttbar_hdampUp, ttbar_hdampDown, wjet, wjet_hdampUp, wjet_hdampDown, zjet, zjet_hdampUp, zjet_hdampDown, stop, stop_hdampUp, stop_hdampDown, vv, vv_hdampUp, vv_hdampDown, ttw, ttw_hdampUp, ttw_hdampDown, ttz, ttz_hdampUp, ttz_hdampDown, ttg, ttg_hdampUp, ttg_hdampDown, tth, tth_hdampUp, tth_hdampDown, out);
// }

// else if (line.find("CMS_ttbar_mtop") != string::npos) {
//   DC.replaceSystematicUnc(line, wh, wh_mtopUp, wh_mtopDown, ttbar, ttbar_mtopUp, ttbar_mtopDown, wjet, wjet_mtopUp, wjet_mtopDown, zjet, zjet_mtopUp, zjet_mtopDown, stop, stop_mtopUp, stop_mtopDown, vv, vv_mtopUp, vv_mtopDown, ttw, ttw_mtopUp, ttw_mtopDown, ttz, ttz_mtopUp, ttz_mtopDown, ttg, ttg_mtopUp, ttg_mtopDown, tth, tth_mtopUp, tth_mtopDown, out);
// }

    // else if (line.find("CMS_bcxwjc") != string::npos) {
    //   DC.replaceSystematicUnc(line, wh, wh_base_xwjcUp, wh_base_xwjcDown, ttbar, ttbar_base_xwjcUp, ttbar_base_xwjcDown, wjet, wjet_base_xwjcUp, wjet_base_xwjcDown, zjet, zjet_base_xwjcUp, zjet_base_xwjcDown, stop, stop_base_xwjcUp, stop_base_xwjcDown, vv, vv_base_xwjcUp, vv_base_xwjcDown, out);
    // }
    // else if (line.find("CMS_frag") != string::npos) {
    //   DC.replaceSystematicUnc(line, wh, wh_fragUp, wh_fragDown, ttbar, ttbar_fragUp, ttbar_fragDown, wjet, wjet_fragUp, wjet_fragDown, zjet, zjet_fragUp, zjet_fragDown, stop, stop_fragUp, stop_fragDown, vv, vv_fragUp, vv_fragDown, out);
    // }
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
  //  out<<"qcdrate1 rateParam * qcd 1.01 [0.0,6.0]"<<endl;
  out << "qcdrate_"<<channelName<<"_" << year << "_" << workingpoint << " rateParam * qcd 1.01 [0.0,30.0]" << endl;

  out.close();
  in.close();
  fout->Close();
}

void MyHPlusDataCardMaker_lowmass(TString inFileDir="/afs/cern.ch/work/s/savarghe/NewJEC/2018/mu/A/transformedHistosLowMass/ExcTight/mass40/",
			    TString histSubDir_="KinFit",
			      TString histName="bdt_output",
			      TString channelName="mu",
			      int mass=40,
			      TString label="WH40",
			      TString hPlusFileName="hist_HplusM40_2018_mu.root")
{

  MyHPlusDataCardMakerMini(inFileDir, histSubDir_, histName, channelName, mass, label, hPlusFileName);                                                            
  //  MyHPlusDataCardMakerNano(inFileDir, histSubDir_, histName, channelName, mass, label, hPlusFileName);


}
