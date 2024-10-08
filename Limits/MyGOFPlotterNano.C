#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include <cstring>

#include "TMath.h"
#include "TFile.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TGraphPainter.h"
#include "TMultiGraph.h"
#include "TTree.h"

#include "TPaveText.h"
#include "TStyle.h"
#include "TArrow.h"
#include "TText.h"

using namespace std;

string doubleToStr(double val){
  ostringstream convert;
  string result("");
  convert <<std::setprecision(4)<<val;
  result = convert.str();
  return result;
}

TPaveText * paveText(double minX, double minY, double maxX, double maxY, int lineColor, int fillColor, int size, int style, int font ){
  TPaveText *pt = new TPaveText(minX, minY, maxX, maxY, "brNDC"); // good_v1
  pt->SetBorderSize(size);
  pt->SetFillColor(fillColor);
  pt->SetFillStyle(style);
  pt->SetLineColor(lineColor);
  pt->SetTextFont(font);
  return pt;
}

void gofPlotter(TString CHANNEL="mu", TString CAT= "Cat1_Inc", TString MASS="90"){
  gStyle->SetOptStat(0);
  
  //TString inFileDir = "limit/"+CHANNEL+"/"+CAT+"/Mass"+MASS;
  TString inFileDir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit/local/UL_2016_muUnBlinded_mu-ele-Blinded/"+CHANNEL+"/"+CAT+"/Mass"+MASS;

  //----------------------------------
  // GOF files from toys
  //----------------------------------
  TString inFileToy = "higgsCombine_hcs_13TeV_toy_"+CHANNEL+"_"+CAT+".GoodnessOfFit.mH"+MASS+".root";
  TFile *fileToy = new TFile(inFileDir+"/"+inFileToy, "READ");
  if(fileToy->IsZombie()){
    cout << "Cannot open GOF toys file "+inFileDir+"/"+inFileToy << endl;
    //continue;
  }
  //Tree
  TTree* treeToy = (TTree*)fileToy->Get("limit");
  cout << "treeToy=  " << treeToy->GetEntries() << endl;
  //Hist
  TH1F *histToy = new TH1F("histToy", "histToy", 100, 0., 250.);
  histToy->SetLineWidth(2);
  //histToy->SetTitle(Form("Goodness of Fit for %s",save_tag.Data()));
  histToy->SetTitle("");
  //histToy->GetYaxis()->SetRangeUser(0.05, yMax);
  //histToy->GetXaxis()->SetRangeUser(xMin, 170);
  histToy->GetXaxis()->SetTitle("q_{GoF,saturated}");
  histToy->GetYaxis()->SetTitleOffset(1.00);
  histToy->GetXaxis()->SetTitleOffset(1.10);
  histToy->GetYaxis()->SetTitle("Number of Toys");
  histToy->GetYaxis()->CenterTitle();
  histToy->GetYaxis()->SetTitleSize(0.05);
  histToy->GetXaxis()->SetTitleSize(0.04);
  histToy->GetXaxis()->SetLabelSize(0.04);
  histToy->GetYaxis()->SetLabelSize(0.04);
  histToy->SetLineColor(kViolet -5);
  //treeToy->Draw("limit>>histToy");
  double limit;
  TBranch *br_limit = 0 ;
  treeToy->SetBranchAddress("limit", &limit, &br_limit);  
  for(int ievent=0;ievent<treeToy->GetEntries();ievent++){
    treeToy->GetEntry(ievent);
    histToy->Fill(limit);
  }
  // TCanvas *c1 = new TCanvas("c1","c1");
  // histToy->Draw();

  //----------------------------------
  // GOF files from data
  //----------------------------------
  TString inFileData = "higgsCombine_hcs_13TeV_data_"+CHANNEL+"_"+CAT+".GoodnessOfFit.mH"+MASS+".root";
  TFile *fileData = new TFile(inFileDir+"/"+inFileData, "READ");
  if(fileData->IsZombie()){
    cout << "Cannot open GOF data file "+inFileDir+"/"+inFileData << endl;
    //continue;
  }

  //Tree
  TTree* treeData = (TTree*)fileData->Get("limit");
  TH1F *histData = new TH1F("histData", "histData", 100, 0., 250.);
  histData->SetLineColor(kOrange+7);
  histData->SetLineWidth(2);
  treeData->SetBranchAddress("limit", &limit, &br_limit);  
  for(int ievent=0;ievent<treeData->GetEntries();ievent++){
    treeData->GetEntry(ievent);
    histData->Fill(limit);
  }
  //treeData->Draw("limit>>histData");
  //histData->Draw("same");

  TLegend* leg = new TLegend(0.5329513,0.628692,0.7335244,0.8797468,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  TString meanToy = TString(doubleToStr(histToy->GetMean()))+" #pm "+ TString(doubleToStr(histToy->GetStdDev()));
  TString legToy = "#splitline{Expected from 1000 Toys}{(Mean ="+meanToy+")}";
  leg->AddEntry(histToy, legToy,"L");
  TString legData = "#splitline{Observed}{("+TString(doubleToStr(histData->GetMean()))+")}";
  leg->AddEntry(histData,legData,"L");

  TCanvas *can = new TCanvas();
  can->cd();
  // gPad->SetBottomMargin(0.15);
  // gPad->SetLeftMargin(0.15);
  histToy->Draw();
  histData->Draw("same");
  TArrow *ar = new TArrow(histData->GetMean(),3.0,histData->GetMean(),30,0.08,"<|");
  ar->SetLineWidth(4);
  ar->SetLineColor(kGreen -6);
  ar->SetFillColor(kOrange +7);
  ar->Draw("same");
  //ar->Draw();

  leg->Draw();
  cout << "histData->GetMean():  " << histData->GetMean() << endl;
  cout << "histToy->GetMean():  " << histToy->GetMean() << endl;
 
  //Pavetext
  TPaveText *pt = paveText(0.20,0.9554,0.82,0.9562, 0, 19, 1, 0, 132);
  pt->SetTextSize(0.07);
  TText *text = pt->AddText("#sqrt{s} = 13 TeV, 35.9 fb^{-1},        #mu + jets(Cat1)");
  pt->Draw();
  TPaveText *cct = paveText(0.25,0.85,0.45,0.85, 0, 19, 1, 0, 132);
  cct->SetTextSize(0.06);
  cct->AddText("m_{H^{+}} = "+MASS+" GeV");
  cct->Draw();
  
  // //TString outDir = "limit/"+CHANNEL+"/"+CAT+"/Mass"+MASS;
  // //TString inFileDir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit/local/UL_2016_muUnBlinded_mu-ele-Blinded/"+CHANNEL+"/"+CAT+"/Mass"+MASS;

  TString outFile = "GOF_"+CHANNEL+"_"+CAT+"_"+MASS;
  //c1->SaveAs(inFileDir+"/"+outFile+".pdf");
  can->SaveAs(inFileDir+"/"+outFile+".pdf");
  
  delete fileData;
}

int MyGOFPlotterNano(){
  //gofPlotter("mu_ele","Cat3_cTagEx","80");
  // gofPlotter("mu_ele","Cat3_cTagEx","90");
  // gofPlotter("mu_ele","Cat3_cTagEx","100");
  // gofPlotter("mu_ele","Cat3_cTagEx","120");
  // gofPlotter("mu_ele","Cat3_cTagEx","140");
  // gofPlotter("mu_ele","Cat3_cTagEx","150");
  // gofPlotter("mu_ele","Cat3_cTagEx","155");
  // gofPlotter("mu_ele","Cat3_cTagEx","160");
  gofPlotter("mu","Cat1_Inc","80");
  gofPlotter("mu","Cat1_Inc","90");
  gofPlotter("mu","Cat1_Inc","100");
  gofPlotter("mu","Cat1_Inc","110");
  gofPlotter("mu","Cat1_Inc","120");
  gofPlotter("mu","Cat1_Inc","130");
  gofPlotter("mu","Cat1_Inc","140");
  gofPlotter("mu","Cat1_Inc","150");
  gofPlotter("mu","Cat1_Inc","155");
  gofPlotter("mu","Cat1_Inc","160");
  return true;
}
