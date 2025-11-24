#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <sstream>  // For std::ostringstream
using namespace std;

class MyHPlusDataCardMaker{
  public:

  TH1F* getHisto(TFile *inRootFile, TString histPath, TString histName, TFile* fTT, double sf=1.0);
  //  TH1F* readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TFile *fTT, TString outHistName,  bool isWrite = false, double min_thres = 0, bool isNeffThreshold = false);
  TH1F* readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TFile *fTT, TString outHistName,  bool isWrite, bool isNorm, TH1F *hBase);
  
  double getBTagUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown);
  double getStatUnc(TH1F* hCentral, double sError = 0.0);
  double getConservativeUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown);
  pair<float,float> getConservativeUncPair(TH1F *hCentral, TH1F* hUp, TH1F* hDown);
  double getUncExL(TH1F* yLyMyT, TH1F* yLyMnT, TH1F* yLnMyT, TH1F* yLnMnT);
  double getUncExM(TH1F* yMyT, TH1F* yMnT);
  double getQcdSF(TString baseIsoDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName);
  double getQcdDD(TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf=1.0);
  double getSysUncQcd(TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF);
  TH1F* trimHisto(TH1F* hist, TString histName, int binWidth, int xMin, int xMax);
 TH1F* trimHistoNano(TH1F* hist, TString histName, float binWidth, float xMin, float xMax);
  void replaceSystematicUnc(std::string& line, TH1F* wh, TH1F* whUp, TH1F* whDown, TH1F* ttbar, TH1F* ttbarUp, TH1F* ttbarDown, TH1F* wjet, TH1F* wjetUp, TH1F* wjetDown, TH1F* zjet, TH1F* zjetUp, TH1F* zjetDown, TH1F* stop, TH1F* stopUp, TH1F* stopDown, TH1F* vv, TH1F* vvUp, TH1F* vvDown,TH1F* ttg, TH1F* ttgUp, TH1F* ttgDown , TH1F* ttw, TH1F* ttwUp, TH1F* ttwDown, TH1F* ttz, TH1F* ttzUp, TH1F* ttzDown,TH1F* tth, TH1F* tthUp, TH1F* tthDown, std::ofstream& out);
  private:
  double dont_use;
};

//----------------------------------------//
//Variuos functions
//----------------------------------------//
TH1F*  MyHPlusDataCardMaker:: getHisto(TFile *inRootFile, TString histPath, TString histName, TFile *fTT, double sf=1.0){
  TH1F* hist;
  TString fullPath = histPath+histName;
  string exception_msg (inRootFile->GetName()+TString("/")+fullPath+", does not exist");
  try{
    if(!(inRootFile->Get(fullPath)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    ///cout<<"WARNING:"<<e<<endl;
  }
  try{
    if(!(fTT->Get(fullPath)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"\033[01;31mERROR: \033[0m"<<e<< endl;
    exit(0);
  }
  if(!(inRootFile->Get(fullPath))){
    hist = (TH1F*)(fTT->Get(fullPath))->Clone(histName);
    hist->Reset();
  }else hist = (TH1F*)(inRootFile->Get(fullPath))->Clone(histName);
  hist->Scale(sf);
  return hist;
}

TH1F* MyHPlusDataCardMaker::readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TFile *fTT, TString outHistName, bool isWrite = false, bool isNorm = false, TH1F *hBase = 0x0) {
    TH1F* hist = (TH1F*) getHisto(inFile, histPath, inHistName, fTT)->Clone(outHistName);
    hist->Scale(sf);
    //hist->Rebin(2);
    TH1F* trimmedHist = trimHistoNano(hist, outHistName, 5., 20., 170.);
    //        trimmedHist->Rebin(2);
    if (outHistName.Contains("CMS_stat_")) {
        string hname = outHistName.Data();
        string binnum = "";
        if (hname.find("Up") != string::npos) {
            binnum = hname.substr(hname.find_last_of("_") + 1, hname.find_last_of("Up") - hname.find_last_of("_") - 1 );
        }
        if (hname.find("Down") != string::npos) {
            binnum = hname.substr(hname.find_last_of("_") + 1, hname.find_last_of("Do") - hname.find_last_of("_") - 1 );
        }
        int ibin = atoi(binnum.c_str());
        TH1F* trimmedHist_Temp = (TH1F *)trimmedHist->Clone("temp");
        if (hname.find("Up") != string::npos) {
            float error = trimmedHist->GetBinError(ibin);
            float up_val = trimmedHist->GetBinContent(ibin) + error;
            up_val = (up_val > 0.0) ? up_val : 1e-3; // Ensure non-zero content
            trimmedHist_Temp->SetBinContent(ibin, up_val);
            trimmedHist_Temp->SetBinError(ibin, error);
        }
        if (hname.find("Down") != string::npos) {
            float error = trimmedHist->GetBinError(ibin);
            float down_val = trimmedHist->GetBinContent(ibin) - error;
            down_val = (down_val > 0.0) ? down_val : 1e-3; // Ensure non-zero content
            error = (down_val > 0.0) ? error : 0.0;
            trimmedHist_Temp->SetBinContent(ibin, down_val);
            trimmedHist_Temp->SetBinError(ibin, error);
        }
        trimmedHist = (TH1F *)trimmedHist_Temp->Clone(outHistName);
        delete trimmedHist_Temp;
    }

    if (isNorm) {
        if (!hBase) {
            trimmedHist->Scale(1.0 / trimmedHist->Integral());
        } else {
            if (trimmedHist->Integral() > 0.) trimmedHist->Scale(hBase->Integral() / trimmedHist->Integral());
        }
    }

    if (isWrite) {
        outFile->cd();
        trimmedHist->Write(outHistName);
    }

    return trimmedHist;
}


/*
TH1F* MyHPlusDataCardMaker::trimHistoNano(TH1F* hist, TString histName, float binWidth, float xMin, float xMax){
  int nBin = TMath::Nint((xMax-xMin)/binWidth);
    TH1F* newHisto = new TH1F(histName, histName, nBin, xMin, xMax);
    int initX = TMath::Nint(xMin/binWidth);
    int lastX = TMath::Nint(xMax/binWidth);
    for(int i = initX; i<lastX; i++){
      double binVal = hist->GetBinContent(i);
      double binErr = hist->GetBinError(i);
      int i_new = i - initX;
      newHisto->SetBinContent(i_new, binVal);
      newHisto->SetBinError(i_new, binErr);
    }
    return newHisto;
}
*/

// TH1F* MyHPlusDataCardMaker::trimHistoNano(TH1F* hist, TString histName, float binWidth, float xMin, float xMax) {
//     int nBins = TMath::Nint((xMax - xMin) / binWidth);
//     TH1F* newHisto = new TH1F(histName, histName, nBins, xMin, xMax);

//     int initX = TMath::Nint(xMin / hist->GetBinWidth(1));  // Use the original histogram's bin width for indexing
//     int lastX = TMath::Nint(xMax / hist->GetBinWidth(1));   // Adjust indexing based on the original histogram's bin width

//     for (int i = initX; i < lastX; ++i) {
//         double binVal = hist->GetBinContent(i);
//         double binErr = hist->GetBinError(i);
//         int i_new = i - initX;  // Adjust for the new histogram's bin index
//            // Set content to 1e-6 for empty bins
//         if (binVal == 0) {
//             binVal = 1e-3;
//             binErr = 0.0;
//         }

// 	newHisto->SetBinContent(i_new, binVal);
//         newHisto->SetBinError(i_new, binErr);
//     }
//     return newHisto;
// }
TH1F* MyHPlusDataCardMaker::trimHistoNano(TH1F* hist, TString histName, float binWidth, float xMin, float xMax) {
    // Number of original bins
    int nBins = TMath::Nint((xMax - xMin) / binWidth);
    if (nBins < 9) {
        std::cerr << "Error: Need at least 9 bins to merge first 2 and last 6 bins." << std::endl;
        return nullptr;
    }

    // Step 1: Fill temporary histogram with fixed binning
    TH1F* tmpHisto = new TH1F("tmp", "tmp", nBins, xMin, xMax);

    int initX = hist->FindBin(xMin);
    int lastX = hist->FindBin(xMax) - 1;
    for (int i = initX; i <= lastX; ++i) {
        double binCenter = hist->GetBinCenter(i);
        double binVal = hist->GetBinContent(i);
        double binErr = hist->GetBinError(i);

        int i_new = tmpHisto->FindBin(binCenter);
        if (binVal == 0) {
            binVal = 1e-3;
            binErr = 0.0;
        }
        tmpHisto->SetBinContent(i_new, binVal);
        tmpHisto->SetBinError(i_new, binErr);
    }

    // Step 2: Compute new bin edges
    int nKeep = nBins - 8;     // bins to keep in the middle
    int nFinalBins = 1 /*first 2 merged*/ + nKeep + 3 /*last 6 merged into 3*/;
    std::vector<double> binEdges;

    // First merged bin (first 2 bins)
    binEdges.push_back(tmpHisto->GetBinLowEdge(1));                         // Start at first bin low edge
    binEdges.push_back(tmpHisto->GetBinLowEdge(3));                         // End after merging 2 bins

    // Middle bins (copied as-is)
    for (int i = 3; i <= 2 + nKeep; ++i)
        binEdges.push_back(tmpHisto->GetBinLowEdge(i + 1));                 // Add upper edge of each kept bin

    // Last 3 merged bins (each merging 2 original bins)
    for (int j = 1; j <= 3; ++j) {
        int idx = 2 + nKeep + 2 * j;
        binEdges.push_back(tmpHisto->GetBinLowEdge(idx + 1));
    }

    // Step 3: Create new histogram with new binning
    TH1F* newHisto = new TH1F(histName, histName, nFinalBins, &binEdges[0]);

    // Step 4: Fill new histogram
    int binIdx = 1;

    // First merged bin (1+2)
    {
        double c1 = tmpHisto->GetBinContent(1);
        double e1 = tmpHisto->GetBinError(1);
        double c2 = tmpHisto->GetBinContent(2);
        double e2 = tmpHisto->GetBinError(2);

        newHisto->SetBinContent(binIdx, c1 + c2);
        newHisto->SetBinError(binIdx, std::sqrt(e1 * e1 + e2 * e2));
        ++binIdx;
    }

    // Middle bins (kept as-is)
    for (int i = 3; i <= 2 + nKeep; ++i, ++binIdx) {
        newHisto->SetBinContent(binIdx, tmpHisto->GetBinContent(i));
        newHisto->SetBinError(binIdx, tmpHisto->GetBinError(i));
    }

    // Last 3 merged bins
    for (int j = 0; j < 3; ++j, ++binIdx) {
        int i1 = 2 + nKeep + 2 * j + 1;
        int i2 = i1 + 1;
        double c1 = tmpHisto->GetBinContent(i1);
        double e1 = tmpHisto->GetBinError(i1);
        double c2 = tmpHisto->GetBinContent(i2);
        double e2 = tmpHisto->GetBinError(i2);

        newHisto->SetBinContent(binIdx, c1 + c2);
        newHisto->SetBinError(binIdx, std::sqrt(e1 * e1 + e2 * e2));
    }

    delete tmpHisto;
    return newHisto;
}


// TH1F* MyHPlusDataCardMaker::trimHistoNano(TH1F* hist, TString histName, float binWidth, float xMin, float xMax) {
//     // Number of bins for the temporary histogram
//     int nBins = TMath::Nint((xMax - xMin) / binWidth);
//     TH1F* tmpHisto = new TH1F("tmp", "tmp", nBins, xMin, xMax);

//     // Fill the temporary histogram
//     int initX = hist->FindBin(xMin);       // First bin within xMin
//     int lastX = hist->FindBin(xMax) - 1;   // Last bin within xMax
//     for (int i = initX; i <= lastX; ++i) {
//         double binCenter = hist->GetBinCenter(i);
//         double binVal = hist->GetBinContent(i);
//         double binErr = hist->GetBinError(i);

//         int i_new = tmpHisto->FindBin(binCenter);
//         if (binVal == 0) {
//             binVal = 1e-3;
//             binErr = 0.0;
//         }
//         tmpHisto->SetBinContent(i_new, binVal);
//         tmpHisto->SetBinError(i_new, binErr);
//     }

//     // Prepare new bin edges: last bin will be wider (merging last two bins)
//     int nMerged = nBins - 1;
//     std::vector<double> binEdges;
//     for (int i = 1; i <= nBins - 1; ++i) // binLowEdge(1) ... binLowEdge(nBins-1)
//         binEdges.push_back(tmpHisto->GetBinLowEdge(i));
//     // Add upper edge of the *last* bin (so last bin covers both previous bins)
//     binEdges.push_back(tmpHisto->GetBinLowEdge(nBins) + tmpHisto->GetBinWidth(nBins));

//     // Create the final histogram with merged bins
//     TH1F* newHisto = new TH1F(histName, histName, nMerged, &binEdges[0]);

//     // Copy all but last bin
//     for (int i = 1; i <= nMerged - 1; ++i) {
//         newHisto->SetBinContent(i, tmpHisto->GetBinContent(i));
//         newHisto->SetBinError(i, tmpHisto->GetBinError(i));
//     }
//     // Merge last two bins
//     double c_last = tmpHisto->GetBinContent(nBins);
//     double e_last = tmpHisto->GetBinError(nBins);
//     double c_2last = tmpHisto->GetBinContent(nBins - 1);
//     double e_2last = tmpHisto->GetBinError(nBins - 1);

//     newHisto->SetBinContent(nMerged, c_last + c_2last);
//     newHisto->SetBinError(nMerged, std::sqrt(e_last*e_last + e_2last*e_2last));

//     delete tmpHisto;
//     return newHisto;
// }


// TH1F* MyHPlusDataCardMaker::trimHistoNano(TH1F* hist, TString histName, float binWidth, float xMin, float xMax) {
//     // Number of bins for the new histogram
//     int nBins = TMath::Nint((xMax - xMin) / binWidth);
//     TH1F* newHisto = new TH1F(histName, histName, nBins, xMin, xMax);

//     // Find the corresponding bin indices in the original histogram
//     int initX = hist->FindBin(xMin);       // First bin within xMin
//     int lastX = hist->FindBin(xMax) - 1;  // Last bin within xMax

//     // Loop over the bins within the specified range
//     for (int i = initX; i <= lastX; ++i) {
//         double binCenter = hist->GetBinCenter(i);
//         double binVal = hist->GetBinContent(i);
//         double binErr = hist->GetBinError(i);

//         // Map the bin center to the new histogram
//         int i_new = newHisto->FindBin(binCenter);

//         // Set content to 1e-6 for empty bins
//         if (binVal ==0) {
//             binVal = 1e-3;
//             binErr = 0.0;
//         }

	
//         // Set content and error in the new histogram
//         newHisto->SetBinContent(i_new, binVal);
//         newHisto->SetBinError(i_new, binErr);
//     }

//     return newHisto;
// }

//get normalised uncertainity
double MyHPlusDataCardMaker::getBTagUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown){
  return 1 + max(fabs(hUp->Integral() - hCentral->Integral()), fabs(hCentral->Integral() - hDown->Integral()))/hCentral->Integral();
}

//get statistical uncertainity
double MyHPlusDataCardMaker::getStatUnc(TH1F* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;
  return statUnc;
}

double MyHPlusDataCardMaker::getConservativeUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown){
  double maxUp = -1.;
  double maxDown = -1.;
  for(int ibin=1;ibin<=hCentral->GetNbinsX();ibin++){
    double upBin = TMath::Abs(hUp->GetBinContent(ibin));
    double downBin = TMath::Abs(hDown->GetBinContent(ibin));
    double baseBin = TMath::Abs(hCentral->GetBinContent(ibin));
    double fracBase = baseBin/hCentral->Integral(); //to avoid edge bins that contains less than 1% of total yield
    if(TMath::AreEqualAbs(upBin,0.0,1.e-5) or TMath::AreEqualAbs(downBin,0.0,1.e-5) or TMath::AreEqualAbs(baseBin,0.0,1.e-5) or fracBase<0.01) continue;
    double ratioUp = (baseBin>upBin) ?  upBin/baseBin : baseBin/upBin;
    double ratioDown = (baseBin>downBin) ?  downBin/baseBin : baseBin/downBin;
    double fracUp = 1.0 - ratioUp;
    double fracDown = 1.0 - ratioDown;
    maxUp = max(fracUp,maxUp);
    maxDown = max(fracDown,maxDown);
  }
  return 1 + max(maxUp, maxDown);

  //return std::round(result * 100) / 100;
}

pair<float,float> MyHPlusDataCardMaker::getConservativeUncPair(TH1F *hCentral, TH1F* hUp, TH1F* hDown){
  double maxUp = -1.;
  double maxDown = -1.;
  for(int ibin=1;ibin<=hCentral->GetNbinsX();ibin++){
    double upBin = TMath::Abs(hUp->GetBinContent(ibin));
    double downBin = TMath::Abs(hDown->GetBinContent(ibin));
    double baseBin = TMath::Abs(hCentral->GetBinContent(ibin));
    if(TMath::AreEqualAbs(upBin,0.0,1.e-5) or TMath::AreEqualAbs(downBin,0.0,1.e-5) or TMath::AreEqualAbs(baseBin,0.0,1.e-5)) continue;
    double ratioUp = (baseBin>upBin) ?  upBin/baseBin : baseBin/upBin;
    double ratioDown = (baseBin>downBin) ?  downBin/baseBin : baseBin/downBin;
    double fracUp = 1.0 - ratioUp;
    double fracDown = 1.0 - ratioDown;
    maxUp = max(fracUp,maxUp);
    maxDown = max(fracDown,maxDown);
  }
  maxUp /= 1.0;
  maxDown /= 1.0;
  return std::make_pair(1 + maxUp, 1 + maxDown);
}


TH1F* MyHPlusDataCardMaker::trimHisto(TH1F* hist, TString histName, int binWidth, int xMin, int xMax){
  double nBin = 6*binWidth;
    TH1F* newHisto = new TH1F(histName, histName, nBin, xMin, xMax);
    double initX = 1;
    double lastX = 31;
    for(int i = initX; i<lastX; i++){
      double binVal = hist->GetBinContent(i);
      double binErr = hist->GetBinError(i);
      int i_new = i- initX+1;
      newHisto->SetBinContent(i_new, binVal);
      newHisto->SetBinError(i_new, binErr);
    }
    return newHisto;
}

double MyHPlusDataCardMaker::getUncExL(TH1F* yLyMyT, TH1F* yLyMnT, TH1F* yLnMyT, TH1F* yLnMnT){
  double m_yLyMyT = yLyMyT->GetMean();
  double m_yLyMnT = yLyMnT->GetMean();
  double m_yLnMyT = yLnMyT->GetMean();
  double m_yLnMnT = yLnMnT->GetMean();
  vector<double> vecExL;
  vecExL.push_back(m_yLyMyT);
  vecExL.push_back(m_yLyMnT);
  vecExL.push_back(m_yLnMyT);
  vecExL.push_back(m_yLnMnT);
  auto it_min = min_element(std::begin(vecExL), std::end(vecExL));
  auto it_max = max_element(std::begin(vecExL), std::end(vecExL));
  double min = *it_min;
  double max = *it_max;
  double unc = max/min;
  //--------------------
  //double tmp_budh = unc -1;
  //unc = 1+ 2*tmp_budh;
  //--------------------
  return (min>0 && max>0)?unc:1.0;
}

double MyHPlusDataCardMaker::getUncExM(TH1F* yMyT, TH1F* yMnT){
  double m_yMyT = yMyT->GetMean();
  double m_yMnT = yMnT->GetMean();
  vector<double> vecExM;
  vecExM.push_back(m_yMyT);
  vecExM.push_back(m_yMnT);
  auto it_min = min_element(std::begin(vecExM), std::end(vecExM));
  auto it_max = max_element(std::begin(vecExM), std::end(vecExM));
  double min = *it_min;
  double max = *it_max;
  double unc = max/min;
  //--------------------
  //double tmp_budh = unc -1;
  //unc = 1+ 2*tmp_budh;
  //--------------------
  return (min>0 && max>0)?unc:1.0;
}

// qcd SF for data-driven QCD
double MyHPlusDataCardMaker::getQcdSF(TString baseIsoDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName){
  //RegionC = LowMET, Iso
  TH1F* hVV_RegC = getHisto(fVV,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hDY_RegC = getHisto(fDY,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hWJ_RegC = getHisto(fWJ,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hST_RegC = getHisto(fST,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hTT_RegC = getHisto(fTT,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hMC_RegC = (TH1F*)hVV_RegC->Clone("hAllMC_RegC");
  hMC_RegC->Add(hDY_RegC);
  hMC_RegC->Add(hWJ_RegC);
  hMC_RegC->Add(hST_RegC);
  hMC_RegC->Add(hTT_RegC);
  TH1F* hData_RegC= getHisto(fData, baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  //RegionD = LowMET, NonIso
  TH1F* hVV_RegD = getHisto(fVV,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hDY_RegD = getHisto(fDY,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hWJ_RegD = getHisto(fWJ,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hST_RegD = getHisto(fST,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hTT_RegD = getHisto(fTT,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hMC_RegD = (TH1F*)hVV_RegD->Clone("hAllMC_RegD");
  hMC_RegD->Add(hDY_RegD);
  hMC_RegD->Add(hWJ_RegD);
  hMC_RegD->Add(hST_RegD);
  hMC_RegD->Add(hTT_RegD);
  TH1F* hData_RegD=  getHisto(fData, baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hDiffC = (TH1F*)hData_RegC->Clone("hDiffC");
  hDiffC->Add(hMC_RegC, -1);
  //If binContent < 0, set it to 0
  for(int ibin=1; ibin<hDiffC->GetNbinsX(); ibin++){
    double binCont = hDiffC->GetBinContent(ibin);
    if(binCont<0){
      hDiffC->SetBinContent(ibin, 0);
      //hDiffC->SetBinError(ibin, 0);
    }
  }
  TH1F* hDiffD = (TH1F*)hData_RegD->Clone("hDiffD");
  hDiffD->Add(hMC_RegD, -1);
  for(int ibin=1; ibin<hDiffD->GetNbinsX(); ibin++){
    double binCont = hDiffD->GetBinContent(ibin);
    if(binCont<0){
      hDiffD->SetBinContent(ibin, 0);
      //hDiffD->SetBinError(ibin, 0);
    }
  }
  double intDiffC   = hDiffC->Integral();
  double intDiffD   = hDiffD->Integral();
  double ratioDiffDC = intDiffD/intDiffC;
  return ratioDiffDC;
}

double MyHPlusDataCardMaker::getQcdDD(TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf=1.0){
  TH1F* hVV = getHisto(fVV,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hDY = getHisto(fDY,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hWJ = getHisto(fWJ,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hST = getHisto(fST,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hTT = getHisto(fTT,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hData= getHisto(fData, baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hOtherMC = (TH1F*)hVV->Clone("hOtherMC");
  hOtherMC->Add(hDY);
  hOtherMC->Add(hST);
  hOtherMC->Add(hWJ);
  hOtherMC->Add(hTT);
  TH1F* hQCD = (TH1F*)hData->Clone(histName);
  hQCD->Add(hOtherMC, -1);
  //If binContent < 0, set it to 0
  for(int ibin=1; ibin<hQCD->GetNbinsX(); ibin++){
    double binCont = hQCD->GetBinContent(ibin);
    if(binCont<0){
      hQCD->SetBinContent(ibin, 0);
      //hQCD->SetBinError(ibin, 0);
    }
  }
  hQCD->Scale(qcd_sf);
  return hQCD->Integral();
}

double MyHPlusDataCardMaker::getSysUncQcd(TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF){
  double sf_baseIsoDir = getQcdSF("baseLowMET", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
  double qcd_baseIsoDir = getQcdDD("base", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseIsoDir);
  double sf_baseShiftedIsoDir = getQcdSF("baseIso20LowMET", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
  double qcd_baseShiftedIsoDir = getQcdDD("baseIso20HighMET", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseShiftedIsoDir);
  double sf_unc = abs(sf_baseIsoDir - sf_baseShiftedIsoDir)/sf_baseIsoDir;
  double qcd_unc = abs(qcd_baseIsoDir - qcd_baseShiftedIsoDir)/qcd_baseIsoDir;
  cout<<"-------------------------------------"<<endl;
  cout<<"sf_baseIsoDir 	      = "<<sf_baseIsoDir<<endl;
  cout<<"sf_baseShiftedIsoDir = "<<sf_baseShiftedIsoDir<<endl;
  cout<<"sf_unc               = "<<sf_unc<<endl;
  cout<<"qcd_baseIsoDir 	   = "<<qcd_baseIsoDir<<endl;
  cout<<"qcd_baseShiftedIsoDir = "<<qcd_baseShiftedIsoDir<<endl;
  cout<<"qcd_unc               = "<<qcd_unc<<endl;
  cout<<"-------------------------------------"<<endl;
  double unc = 0.0;
  if(isUncSF) unc = sf_unc;
  else unc = qcd_unc;
  return 1+unc;
}

/* void MyHPlusDataCardMaker::replaceSystematicUnc(std::string& line, TH1F* wh, TH1F* whUp, TH1F* whDown, TH1F* ttbar, TH1F* ttbarUp, TH1F* ttbarDown, TH1F* wjet, TH1F* wjetUp, TH1F* wjetDown, TH1F* zjet, TH1F* zjetUp, TH1F* zjetDown, TH1F* stop, TH1F* stopUp, TH1F* stopDown, TH1F* vv, TH1F* vvUp, TH1F* vvDown, std::ofstream& out) { */
/*   float unc_wh = (wh->Integral() > 0) ? getBTagUnc(wh, whUp, whDown) : 1.00; */
/*   line.replace(line.find("HHHH"), 4, std::to_string(unc_wh)); */

/*   float unc_ttbar = (ttbar->Integral() > 0) ? getBTagUnc(ttbar, ttbarUp, ttbarDown) : 1.00; */
/*   line.replace(line.find("TTTT"), 4, std::to_string(unc_ttbar)); */

/*   float unc_wjet = (wjet->Integral() > 0) ? getBTagUnc(wjet, wjetUp, wjetDown) : 1.00; */
/*   line.replace(line.find("WWWW"), 4, std::to_string(unc_wjet)); */

/*   float unc_zjet = (zjet->Integral() > 0) ? getBTagUnc(zjet, zjetUp, zjetDown) : 1.00; */
/*   line.replace(line.find("DDDD"), 4, std::to_string(unc_zjet)); */

/*   float unc_stop = (stop->Integral() > 0) ? getBTagUnc(stop, stopUp, stopDown) : 1.00; */
/*   line.replace(line.find("SSSS"), 4, std::to_string(unc_stop)); */

/*   float unc_vv = (vv->Integral() > 0) ? getBTagUnc(vv, vvUp, vvDown) : 1.00; */
/*   line.replace(line.find("VVVV"), 4, std::to_string(unc_vv)); */

/*   out << line << std::endl; */
/* } */

void MyHPlusDataCardMaker::replaceSystematicUnc(std::string& line, TH1F* wh, TH1F* whUp, TH1F* whDown, TH1F* ttbar, TH1F* ttbarUp, TH1F* ttbarDown, TH1F* wjet, TH1F* wjetUp, TH1F* wjetDown, TH1F* zjet, TH1F* zjetUp, TH1F* zjetDown, TH1F* stop, TH1F* stopUp, TH1F* stopDown, TH1F* vv, TH1F* vvUp, TH1F* vvDown,TH1F* ttg, TH1F* ttgUp, TH1F* ttgDown , TH1F* ttw, TH1F* ttwUp, TH1F* ttwDown, TH1F* ttz, TH1F* ttzUp, TH1F* ttzDown,TH1F* tth, TH1F* tthUp, TH1F* tthDown, std::ofstream& out) {
  auto replaceUncertainty = [&](TH1F* hist, TH1F* histUp, TH1F* histDown, const std::string& tag) {
    if (!hist) return; // Ensure the histogram exists
    float unc = (hist->Integral() > 0) ? getConservativeUnc(hist, histUp, histDown) : 1.00;
    
    // Using a stringstream to format the float with two decimal places
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << unc;
    std::string unc_str = stream.str();  // Convert the stream into a string


auto pos = line.find(tag);
    if (pos != std::string::npos) {
      line.replace(pos, 4, unc_str);
    }
  };

  replaceUncertainty(wh, whUp, whDown, "HHHH");
  replaceUncertainty(ttbar, ttbarUp, ttbarDown, "TTTT");
  replaceUncertainty(wjet, wjetUp, wjetDown, "WWWW");
  replaceUncertainty(zjet, zjetUp, zjetDown, "DDDD");
  replaceUncertainty(stop, stopUp, stopDown, "SSSS");
  replaceUncertainty(vv, vvUp, vvDown, "VVVV");
  replaceUncertainty(ttg, ttgUp, ttgDown, "TTGG");
  replaceUncertainty(ttw, ttwUp, ttwDown, "TTWW");
  replaceUncertainty(ttz, ttzUp, ttzDown, "TTZZ");
  replaceUncertainty(tth, tthUp, tthDown, "TTHH");

  out << line << std::endl; // Write the modified line to the output file
}
