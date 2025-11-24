#!/usr/bin/env python3
# Usage:
#   python3 PlotFit_Var_Remap.py --file /path/to/CombinedAll/fitDiagnosticsTest.root --cats ExcLoose,ExcMedium --var CTop
# Supported vars: CTop (cos#theta* in [-1,1]), CvsL_j1 (0..1), pT_b1 (0..200), pT_j1 (-3.14..3.14)

import ROOT
import os
import argparse
import ctypes
from ROOT import TFile, THStack, TCanvas, TLegend, TF1, TGraphAsymmErrors, TLatex
import math
ROOT.gROOT.SetBatch(True)

# --- Config ---
isSaveHisto = True
# BASE_DIR = "/afs/cern.ch/work/s/savarghe/private/Combine_newbin/CMSSW_14_1_0_pre4/src/HiggsAnalysis/CombinedLimit/Limit/VarHisto/Combined/"
#var1 = args.var
BASE_DIR = "/afs/cern.ch/work/s/savarghe/private/Combine_newbin/CMSSW_14_1_0_pre4/src/HiggsAnalysis/CombinedLimit/Limit/VarHisto/Combined/"
CHAN_NAME = "hcs_13TeV"
#os.path.join(BASE_DIR, args.var, "fitDiagnostics.root")

# ---------- Style ----------
def setTDRStyle():
    ROOT.gStyle.SetOptStat(0); ROOT.gStyle.SetOptTitle(0)
    ROOT.gStyle.SetPadLeftMargin(0.16); ROOT.gStyle.SetPadRightMargin(0.04)
    ROOT.gStyle.SetPadTopMargin(0.09);  ROOT.gStyle.SetPadBottomMargin(0.12)
    ROOT.gStyle.SetTitleXOffset(1.1);   ROOT.gStyle.SetTitleYOffset(1.6)
    ROOT.gStyle.SetTitleSize(0.05, "X"); ROOT.gStyle.SetTitleSize(0.05, "Y")
    ROOT.gStyle.SetLabelSize(0.05, "X"); ROOT.gStyle.SetLabelSize(0.05, "Y")
    ROOT.gStyle.SetLegendBorderSize(0);  ROOT.gStyle.SetLegendFont(42); ROOT.gStyle.SetLegendTextSize(0.050)

# ---------- Helpers ----------

def get_hist(file_handle, dir_name, chName, process, tag):
    h = file_handle.Get(f"{dir_name}/{chName}/{process}")
    if not h:
        raise ValueError(f"[{tag}] Missing hist: {dir_name}/{chName}/{process}")
    h = h.Clone(f"{process}_{tag}")
    h.SetDirectory(0)
    if hasattr(h, 'GetSumw2N') and h.GetSumw2N() == 0:
        h.Sumw2()
    return h


def convertGraphToHistMatching(graph, template_hist, name="data_hist"):
    if not isinstance(graph, ROOT.TGraphAsymmErrors):
        raise ValueError("Input data is not a TGraphAsymmErrors")
    ax = template_hist.GetXaxis()
    nb = ax.GetNbins()
    import array as _array
    edges = [ax.GetBinLowEdge(1)] + [ax.GetBinUpEdge(i) for i in range(1, nb+1)]
    arr = _array.array('d', edges)
    h = ROOT.TH1F(name, name, nb, arr)
    h.Sumw2()
    x = ctypes.c_double(); y = ctypes.c_double()
    for i in range(graph.GetN()):
        graph.GetPoint(i, x, y)
        if hasattr(graph, "GetErrorYlow") and hasattr(graph, "GetErrorYhigh"):
            ey = 0.5 * (graph.GetErrorYlow(i) + graph.GetErrorYhigh(i))
        elif hasattr(graph, "GetErrorY"):
            ey = graph.GetErrorY(i)
        else:
            ey = 0.0
        ib = h.FindBin(x.value)
        h.SetBinContent(ib, h.GetBinContent(ib) + y.value)
        old = h.GetBinError(ib)
        h.SetBinError(ib, (old*old + ey*ey) ** 0.5)
    h.SetDirectory(0)
    return h


def getDataHist_prefit(f, chName, template_hMC=None):
    obj = f.Get(f"shapes_prefit/{chName}/data")
    if not obj:
        raise ValueError(f"Missing data object: shapes_prefit/{chName}/data")
    if isinstance(obj, ROOT.TH1):
        h = obj.Clone("data_prefit")
        h.SetDirectory(0)
        h.Sumw2()
        return h
    if isinstance(obj, ROOT.TGraphAsymmErrors):
        if template_hMC is None:
            raise ValueError("template_hMC must be provided to convert TGraphAsymmErrors to TH1")
        h = convertGraphToHistMatching(obj, template_hMC, name="data_prefit")
        return h
    raise TypeError(f"Unsupported data object type: {type(obj)}")


def UNCGRAPH(hist, isRatio):
    n = hist.GetNbinsX()
    g = ROOT.TGraphAsymmErrors(n)
    for i in range(1, n + 1):
        x = hist.GetBinCenter(i)
        y = hist.GetBinContent(i)
        ex = 0.5 * hist.GetBinWidth(i)
        ey = 0.5*hist.GetBinError(i)
        if isRatio:
            val = 1.0
            e = (ey / y) if y != 0 else 0.0
                # --- Apply maximum uncertainty cap of 20% ---
            e = min(e, 0.20)

            g.SetPoint(i - 1, x, val)
            g.SetPointError(i - 1, ex, ex, e, e)
        else:
            g.SetPoint(i - 1, x, y)
            g.SetPointError(i - 1, ex, ex, ey, ey)
    return g

# ---------- Variable remapping ----------

VAR_BINS = {
    'CTop':    {'nb': 20, 'xmin': -1.0,   'xmax': 1.0,   'xlabel': 'cos #theta*'},
    'CvsL_j1': {'nb': 20, 'xmin':  0.0,   'xmax': 1.0,   'xlabel': 'CvsL^{leading light jet}'},
    'pT_b1':   {'nb': 15, 'xmin':  0.0,   'xmax': 225.0, 'xlabel': 'p_{T}^{bjet from hadronic top decay} [GeV]'},
    'pT_j1':   {'nb': 15, 'xmin':  0.0,   'xmax': 225.0, 'xlabel': 'p_{T}^{leading light jet} [GeV]'},
    }



def remap_hist_to_var(h_in, var_name, name_suffix=""):
    """Remap an input histogram into `VAR_BINS[var_name]` binning and return a new TH1F."""
    if var_name not in VAR_BINS:
        raise KeyError(f"Unknown var: {var_name}")
    nb_new = VAR_BINS[var_name]['nb']
    xmin = VAR_BINS[var_name]['xmin']
    xmax = VAR_BINS[var_name]['xmax']
    title = h_in.GetTitle()
    new_name = h_in.GetName() + ("_var" if name_suffix=="" else f"_{name_suffix}")
    h_new = ROOT.TH1F(new_name, title, nb_new, xmin, xmax)
    if hasattr(h_new, 'GetSumw2N') and h_new.GetSumw2N() == 0:
        h_new.Sumw2()
    nb_old = h_in.GetNbinsX()
    old_xmin = h_in.GetXaxis().GetBinLowEdge(1)
    old_xmax = h_in.GetXaxis().GetBinUpEdge(nb_old)
    if old_xmax == old_xmin:
        return h_new
    for i in range(1, nb_old+1):
        c = h_in.GetBinContent(i)
        e = h_in.GetBinError(i)
        xcenter = h_in.GetXaxis().GetBinCenter(i)
        # normalize old center to 0..1 then map to new range
        frac = (xcenter - old_xmin) / (old_xmax - old_xmin)
        new_x = xmin + frac * (xmax - xmin)
        ib_new = h_new.FindBin(new_x)
        oldc = h_new.GetBinContent(ib_new); olde = h_new.GetBinError(ib_new)
        h_new.SetBinContent(ib_new, oldc + c)
        h_new.SetBinError(ib_new, (olde*olde + e*e) ** 0.5)
    h_new.SetDirectory(0)
    return h_new

# ---------- Plotting: variable ----------

def example_stack_from_combined(root_file_path, chLabel, var_name):
    f = TFile.Open(root_file_path)
    if not f or f.IsZombie():
        raise IOError(f"Could not open: {root_file_path}")

    if var_name not in VAR_BINS:
        raise KeyError(f"Unsupported variable: {var_name}")

    setTDRStyle()
    c1 = TCanvas("c1", "", 800, 800)
    pad1 = ROOT.TPad("pad1", "pad1", 0, 0.35, 1, 1.0)
    pad2 = ROOT.TPad("pad2", "pad2", 0, 0.0, 1, 0.35)
    pad1.SetTickx(1)
    pad1.SetTicky(1)
    pad2.SetTickx(1)
    pad2.SetTicky(1)
    pad1.SetBottomMargin(0.02)
    pad2.SetTopMargin(0.08)
    pad2.SetBottomMargin(0.35)
    pad1.Draw()
    pad2.Draw()

    pad1.cd()

    # --- MC components (from shapes_prefit in combined file) ---
    hTT   = get_hist(f, "shapes_prefit", CHAN_NAME, "ttbar", "combined")
    hST   = get_hist(f, "shapes_prefit", CHAN_NAME, "stop", "combined")
    hQCD  = get_hist(f, "shapes_prefit", CHAN_NAME, "qcd", "combined")
    hWjet = get_hist(f, "shapes_prefit", CHAN_NAME, "wjet", "combined")
    hDY   = get_hist(f, "shapes_prefit", CHAN_NAME, "zjet", "combined")
    hVV   = get_hist(f, "shapes_prefit", CHAN_NAME, "vv", "combined")
    hTTG  = get_hist(f, "shapes_prefit", CHAN_NAME, "ttg", "combined")
    hTTH  = get_hist(f, "shapes_prefit", CHAN_NAME, "tth", "combined")
    hTTV  = get_hist(f, "shapes_prefit", CHAN_NAME, "ttw", "combined")
    hTTZ  = get_hist(f, "shapes_prefit", CHAN_NAME, "ttz", "combined")

    hMC = f.Get(f"shapes_prefit/{CHAN_NAME}/total_background")
    if hMC and not hMC.IsZombie():
        hMC = hMC.Clone("total_background_combined"); hMC.SetDirectory(0);
        if hasattr(hMC, 'GetSumw2N') and hMC.GetSumw2N() == 0:
            hMC.Sumw2()
    else:
        hMC = hTT.Clone("total_bkg_combined")
        if hasattr(hMC, 'GetSumw2N') and hMC.GetSumw2N() == 0:
            hMC.Sumw2()
        for hh in [hST, hQCD, hWjet, hDY, hVV, hTTG, hTTH, hTTV, hTTZ]:
            hMC.Add(hh)

    hSig  = get_hist(f, "shapes_prefit", CHAN_NAME, "WH120", "combined")
    hSig.Scale(0.01 * 5)

    # Normalize signal to background yield
    bkgIntegral = hMC.Integral()
    sigIntegral = hSig.Integral()
    if sigIntegral > 0:
        norm_factor = bkgIntegral / sigIntegral
        hSig.Scale(norm_factor)

    # Data
    hData = getDataHist_prefit(f, CHAN_NAME, hMC)

    # Remap histograms to chosen variable binning
    hTT  = remap_hist_to_var(hTT, var_name, "ttbar")
    hST  = remap_hist_to_var(hST, var_name, "stop")
    hQCD = remap_hist_to_var(hQCD, var_name, "qcd")
    hWjet= remap_hist_to_var(hWjet, var_name, "wjet")
    hDY  = remap_hist_to_var(hDY, var_name, "zjet")
    hVV  = remap_hist_to_var(hVV, var_name, "vv")
    hTTG = remap_hist_to_var(hTTG, var_name, "ttg")
    hTTH = remap_hist_to_var(hTTH, var_name, "tth")
    hTTV = remap_hist_to_var(hTTV, var_name, "ttw")
    hTTZ = remap_hist_to_var(hTTZ, var_name, "ttz")
    hMC  = remap_hist_to_var(hMC, var_name, "total_bkg")
    hSig = remap_hist_to_var(hSig, var_name, "WH120")
    hData= remap_hist_to_var(hData, var_name, "data")

    hTTX = hTTG.Clone("hTTX"); hTTX.Add(hTTH); hTTX.Add(hTTV); hTTX.Add(hTTZ)
    hOthers = hTTX.Clone("hOthers"); hOthers.Add(hVV); hOthers.Add(hDY); hOthers.Add(hWjet)

    colors = {
        "Z/gamma+jets": ROOT.TColor.GetColor("#009E73"),
        "W+jets":ROOT.TColor.GetColor("#F0E442"),
        "QCD":   ROOT.TColor.GetColor("#E69F00"),
        "Single t": ROOT.TColor.GetColor("#56B4E9"),
        "ttX":   ROOT.TColor.GetColor("#CC79A7"),
        "ttbar+jets": ROOT.TColor.GetColor("#0072B2"),
        "Others": ROOT.TColor.GetColor("#999999"),
    }

    stack = THStack("stack", "")
    draw_list = [
        ("ttbar+jets",     hTT),
        ("Single t",       hST),
        ("QCD",            hQCD),
        ("Others",         hOthers),
    ]

    for label, h in draw_list:
        col = colors[label]
        h.SetFillColor(col)
        h.SetLineColor(ROOT.kBlack)
        h.SetLineWidth(1)
        stack.Add(h)

    stack.Draw("HIST")
    stack.GetYaxis().SetTitle("Events / bin")
    stack.GetXaxis().SetTitle(VAR_BINS[var_name]['xlabel'])
    stack.GetXaxis().SetLabelSize(0)
    stack.GetXaxis().SetTitleSize(0.18)
    stack.GetXaxis().SetRangeUser(VAR_BINS[var_name]['xmin'], VAR_BINS[var_name]['xmax'])
    stack.SetMaximum(2.0 * max(stack.GetMaximum(), 1.0))

    UncBand = UNCGRAPH(hMC, isRatio=False)
    UncBand.SetFillColor(ROOT.kGreen+2)
    UncBand.SetFillStyle(3008)

    hSig.SetLineColor(ROOT.kRed); hSig.SetLineStyle(2); hSig.SetLineWidth(3); hSig.SetFillColor(0); hSig.Draw("HISTSAME")
    hData.SetMarkerStyle(20); hData.SetMarkerSize(1.2); hData.SetLineColor(ROOT.kBlack); hData.Draw("EP SAME")

    leg = TLegend(0.43, 0.46, 0.85, 0.90)
    leg.SetBorderSize(0); leg.SetFillStyle(0); leg.SetTextFont(42); leg.SetNColumns(2)
    leg.AddEntry(hData, "Data", "PE")
    leg.AddEntry(hST,  "Single t",        "F")
    leg.AddEntry(hTT,  "t#bar{t} + jets", "F")
    leg.AddEntry(hQCD, "QCD",             "F")
    leg.AddEntry(hOthers,  "Others",              "F")
    leg.AddEntry(UncBand, "Total unc.",   "F")
    leg.AddEntry(hSig, "m_{H^{+}} = 120 GeV (normalized to bkg)", "L")
    leg.Draw()

    cmsText = ROOT.TPaveText(0.18, 0.82, 0.4, 0.87, "NDC")
    cmsText.SetTextAlign(12); cmsText.SetTextSize(0.06); cmsText.SetTextColor(1)
    cmsText.SetTextFont(42); cmsText.SetFillStyle(0); cmsText.SetBorderSize(0)
    cmsText.AddText("#bf{CMS}")
    cmsText.Draw()

    lumi_label = "138 fb^{-1} (13 TeV)"
    lumiText = ROOT.TPaveText(0.7, 0.92, 0.9, 0.96, "NDC")
    lumiText.SetTextAlign(12); lumiText.SetTextSize(0.055); lumiText.SetTextFont(42); lumiText.SetFillStyle(0); lumiText.SetBorderSize(0)
    lumiText.AddText(lumi_label)
    lumiText.Draw()

    latexMuJets = ROOT.TLatex(); latexMuJets.SetNDC(); latexMuJets.SetTextFont(42); latexMuJets.SetTextSize(0.05); latexMuJets.SetTextAlign(13)
    latexMuJets.DrawLatex(0.19, 0.78, "Pre-Fit")

    # ---- Ratio pad ----
    c1.cd(); pad2.cd()
    ratio = hData.Clone("ratio");
    ratio.Divide(hMC)
    nb = ratio.GetNbinsX()
    for ib in range(1, nb+1):
        data_val = hData.GetBinContent(ib)
        if data_val > 0:
            ratio.SetBinError(ib, math.sqrt(data_val) / data_val)
        else:
            ratio.SetBinError(ib, 0.0)

    ratio.GetYaxis().SetTitle("Data/Pred")
    ratio.GetYaxis().SetTitleSize(0.10); ratio.GetYaxis().SetLabelSize(0.10); ratio.GetYaxis().SetTitleOffset(0.6);
    ratio.GetXaxis().SetTitleOffset(1.4); ratio.GetXaxis().SetTitle(VAR_BINS[var_name]['xlabel']); ratio.GetXaxis().SetTitleSize(0.12); ratio.GetXaxis().SetLabelSize(0.10); ratio.GetYaxis().SetNdivisions(502); ratio.SetMinimum(0.6); ratio.SetMaximum(1.4)
    ratio.Draw("EP")

    UncBand_Ratio = UNCGRAPH(hMC, isRatio=True)
    UncBand_Ratio.SetFillColorAlpha(ROOT.kGreen+2, 0.5); UncBand_Ratio.SetFillStyle(3008); UncBand_Ratio.Draw("E2 SAME")
    ratio.Draw("E SAME")
    line = TF1("line", "1", ratio.GetXaxis().GetBinLowEdge(1), ratio.GetXaxis().GetBinUpEdge(ratio.GetXaxis().GetNbins()))
    line.SetLineColor(ROOT.kRed); line.Draw("SAME")

    ROOT.gPad.RedrawAxis()

    if isSaveHisto:
        os.makedirs("output", exist_ok=True)
        base_filename = f"output/{var_name}_prefit_combined"
        c1.SaveAs(base_filename + ".pdf")
        root_filename = base_filename + ".root"
        out_file = ROOT.TFile(root_filename, "RECREATE")
        c1.Write()
        out_file.Close()
        c1.Close()

    f.Close()


def MyPostFitPlot(single_root_file, var_name='CTop'):
#    for cat in category_list:
     example_stack_from_combined(single_root_file, "#mu + jets", var_name)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Prefit plotting for variables from CombinedAll fitDiagnostics (shapes_prefit)")
    parser.add_argument("--file", default= None, help="Path to fitDiagnosticsTest.root (CombinedAll)")
    #parser.add_argument("--cats", default="ExcLoose,ExcMedium,ExcTight", help="Comma-separated categories to plot")
    parser.add_argument("--var", default="CTop", help="Variable to plot: CTop, CvsL_j1, pT_b1, pT_j1")
    args = parser.parse_args()
    # cats = [c.strip() for c in args.cats.split(",") if c.strip()]
    # MyPostFitPlot(args.file, cats, args.var)
    file_path = args.file if args.file else os.path.join(BASE_DIR, args.var, "fitDiagnosticsTest.root")
#    cats = [c.strip() for c in args.cats.split(",") if c.strip()]
    MyPostFitPlot(file_path,  args.var)
