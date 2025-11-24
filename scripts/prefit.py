#!/usr/bin/env python3
# Usage:
#   python3 PlotFit.py --year 2016|2017|2018|Run2
#
# - Stack order (bottom->top): VV, Z/#gamma+jets, W+jets, QCD, Single t, ttX, ttbar+jets
# - X-axis shown is the bin index; labels are transformed to (bin*10 + 20)
#   labels every 2 bins -> 20, 40, ..., 160 (170 at the far end)
# - Minor subticks at half-bin (so 5 GeV when 1 bin == 10 GeV)
# - Legend: two columns
# - Uses existing adaptive binning from Combine (no rebin)

import ROOT
import ctypes
import os
import argparse

from ROOT import TFile, THStack, TCanvas, TLegend, TF1, TGraphAsymmErrors, TPaveText, TGaxis, TLatex

ROOT.gROOT.SetBatch(True)

# --- Config ---
isSaveHisto = True
BASE_DIR  = "/afs/cern.ch/work/s/savarghe/private/Combine_newbin/CMSSW_14_1_0_pre4/src/HiggsAnalysis/CombinedLimit/Limit"
CHAN_NAME = "hcs_13TeV"

# ---------- Style ----------
def paveText(x1, y1, x2, y2, textAlign=12, textSize=0.04, textColor=1, textAngle=0, textFont=42):
    pt = TPaveText(x1, y1, x2, y2, "NDC")
    pt.SetTextAlign(textAlign); pt.SetTextSize(textSize); pt.SetTextColor(textColor)
    pt.SetTextAngle(textAngle); pt.SetTextFont(textFont); pt.SetFillStyle(0); pt.SetBorderSize(0)
    return pt

def setTDRStyle():
    ROOT.gStyle.SetOptStat(0); ROOT.gStyle.SetOptTitle(0)
    ROOT.gStyle.SetPadLeftMargin(0.16); ROOT.gStyle.SetPadRightMargin(0.04)
    ROOT.gStyle.SetPadTopMargin(0.09);  ROOT.gStyle.SetPadBottomMargin(0.12)
    ROOT.gStyle.SetTitleXOffset(1.1);   ROOT.gStyle.SetTitleYOffset(1.6)
    ROOT.gStyle.SetTitleSize(0.05, "X"); ROOT.gStyle.SetTitleSize(0.05, "Y")
    ROOT.gStyle.SetLabelSize(0.05, "X"); ROOT.gStyle.SetLabelSize(0.05, "Y")
    ROOT.gStyle.SetLegendBorderSize(0);  ROOT.gStyle.SetLegendFont(42); ROOT.gStyle.SetLegendTextSize(0.028)

# ---------- Helpers ----------
def get_hist(file_handle, dir_name, chName, process, tag):
    h = file_handle.Get(f"{dir_name}/{chName}/{process}")
    if not h:
        raise ValueError(f"[{tag}] Missing hist: {dir_name}/{chName}/{process}")
    h = h.Clone(f"{process}_{tag}")
    h.SetDirectory(0)
    h.Sumw2()
    return h

def getSummedHistos(file_dict, chName, process):
    h_total = None
    for year, f in file_dict.items():
        dir_name = "shapes_prefit" if process.startswith("WH") else "shapes_prefit"
        h = get_hist(f, dir_name, chName, process, year)
        if h_total is None:
            h_total = h.Clone()
        else:
            h_total.Add(h)
    return h_total

def convertGraphToHistMatching(graph, template_hist, name="data_hist"):
    """Map TGraphAsymmErrors to TH1 with same binning as template_hist."""
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

def getCombinedDataHistogram(file_dict, chName, template_hMC):
    h_total = None
    for year, f in file_dict.items():
        g = f.Get(f"shapes_prefit/{chName}/data")
        if not g:
            raise ValueError(f"[{year}] Missing data graph: shapes_prefit/{chName}/data")
        h = convertGraphToHistMatching(g, template_hMC, name=f"data_hist_{year}")
        if h_total is None:
            h_total = h.Clone()
        else:
            h_total.Add(h)
    return h_total

def UNCGRAPH(hist, isRatio):
    n = hist.GetNbinsX()
    g = ROOT.TGraphAsymmErrors(n)
    for i in range(1, n + 1):
        x = hist.GetBinCenter(i)
        y = hist.GetBinContent(i)
        ex = 0.5 * hist.GetBinWidth(i)
        ey = 1.5*hist.GetBinError(i)
        if isRatio:
            val = 1.0
            e = (ey / y) if y != 0 else 0.0
            g.SetPoint(i - 1, x, val)
            g.SetPointError(i - 1, ex, ex, e, e)
        else:
            g.SetPoint(i - 1, x, y)
            g.SetPointError(i - 1, ex, ex, ey, ey)
    return g

# -------- Axis overlay: variable binning labels --------
def draw_variable_mass_axis(pad, hist, title="m_{jj} [GeV]", label_step=1):
    """
    Draw custom axis for variable binning:
      - Labels at multiples of `label_step` (20, 40, ..., 160, 170).
      - Subticks at 10 GeV (half of widest bins).
    """
    pad.cd()
    pad.Update()

    ax = hist.GetXaxis()
    nb = ax.GetNbins()
    x_min = ax.GetBinLowEdge(1)
    x_max = ax.GetBinUpEdge(nb)
    y0 = pad.GetUymin()
    yline = y0 + (pad.GetUymax() - y0) * 0.001

    # Axis ticks
    axis_ticks = TGaxis(x_min, yline, x_max, yline,
                        x_min, x_max, nb*100, "")
    axis_ticks.SetLabelSize(0.0)
    axis_ticks.SetTickLength(0.08)
    axis_ticks.SetLineColor(ROOT.kBlack)
    axis_ticks.Draw()

    # Draw labels at 20,40,...,160,170
    lab = TLatex()
    lab.SetTextFont(42)
    lab.SetTextSize(0.15)
    lab.SetTextAlign(21)
    y_text = y0 + (pad.GetUymax() - y0) * 0.15

    for i in range(1, nb+1):
        lo = int(round(ax.GetBinLowEdge(i)))
        hi = int(round(ax.GetBinUpEdge(i)))
        if lo % label_step == 0:
            lab.DrawLatex(lo, y_text, str(lo))
        if hi == 170:  # ensure last edge is shown
            lab.DrawLatex(hi, y_text, "170")

    # Subticks every 10 GeV
    for val in range(30, 170, 10):
        line = ROOT.TLine(val, y0, val, y0 - 0.03*(pad.GetUymax()-y0))
        line.SetLineWidth(1)
        line.Draw()

    # Axis title
    title_latex = TLatex()
    title_latex.SetTextFont(42)
    title_latex.SetTextSize(0.20)
    title_latex.SetTextAlign(22)
    title_latex.DrawLatex((x_min+x_max)/2.0, y0 - 0.12*(pad.GetUymax()-y0), title)

# -------- Axis overlay: ticks per bin, half-bin subticks, labels = bin*10 + 20 --------
def draw_index_axis_with_mass_labels(pad, hist, title="m_{jj} [GeV]", label_every=2, label_last_170=False):
    """
    Use when histogram x-axis is BIN INDEX (0..N-1).
    - Primary ticks: each bin edge (1 bin == 10 GeV)
    - Minor ticks: half-bin (-> 5 GeV)
    - Labels: every 'label_every' bins, text = bin*10 + 20
    """
    pad.cd()
    pad.Update()

    ax = hist.GetXaxis()
    nb = hist.GetNbinsX()
    x_min = ax.GetBinLowEdge(1)
    x_max = ax.GetBinUpEdge(nb)
    y0 = pad.GetUymin()
    yline = y0 + (pad.GetUymax() - y0) * 0.001  # avoid clipping

    # Primary divisions per bin; 1 secondary per primary (half-bin subtick)
    NDIV_BIN_WITH_HALF = nb*100 + 1*5 + 0
    axis_ticks = TGaxis(x_min, yline, x_max, yline, x_min, x_max, NDIV_BIN_WITH_HALF, "")
    axis_ticks.SetLabelSize(0.0)   # draw custom labels below
    axis_ticks.SetTickLength(0.08)
    axis_ticks.SetLineColor(ROOT.kBlack)
    axis_ticks.Draw()

    # Custom numeric labels
    lab = TLatex()
    lab.SetTextFont(42)
    lab.SetTextSize(0.10)
    lab.SetTextAlign(21)  # centered
    y_text = y0 + (pad.GetUymax() - y0) * 0.06

    # Labels at bin indices i = 0, 2, 4, ...
    for i in range(nb):
        if i % label_every != 0:
            continue
        label_val = i * 5 + 20
        x_at = x_min + i  # axis is bin-index units
        lab.DrawLatex(x_at, y_text, str(label_val))

    # Optional: label the last upper edge as 170
    if label_last_170:
        lab.DrawLatex(x_max, y_text, "170")

    # Axis title is already drawn by the histogram itself (ratio GetXaxis title)

# -------- Axis overlay: custom bin-to-mass mapping --------
def draw_mass_axis_custom(pad, hist, title="", label_every=3, force_last=True):
    """
    Draw an x-axis with the correct custom bin-to-mass mapping,
    but only label every Nth bin to avoid crowding.
    """
    pad.cd()
    pad.Update()

    bin_labels = [
        20, 30, 35, 40, 45, 50, 55, 60,
        65, 70, 75, 80, 85, 90, 95, 100,
        105, 110, 115, 120, 125, 130, 135, 140,
        150, 160, 170
    ]

    nb = hist.GetNbinsX()
    x_min = hist.GetXaxis().GetBinLowEdge(1)
    x_max = hist.GetXaxis().GetBinUpEdge(nb)
    y0 = pad.GetUymin()
    yline = y0 + (pad.GetUymax() - y0) * 0.001

    # Axis ticks only
    axis_ticks = TGaxis(x_min, yline, x_max, yline,
                        x_min, x_max, nb*100, "")
    axis_ticks.SetLabelSize(0.0)
    axis_ticks.SetTickLength(0.08)
    axis_ticks.SetLineColor(ROOT.kBlack)
    axis_ticks.Draw()

    # Labels (sparse)
    lab = TLatex()
    lab.SetTextFont(42)
    lab.SetTextSize(0.08)
    lab.SetTextAlign(21)
    y_text = y0 - 0.14*(pad.GetUymax()-y0)

    for ibin, mass in enumerate(bin_labels):
        if ibin % label_every == 0 or (force_last and ibin == len(bin_labels)-1):
            x = hist.GetXaxis().GetBinCenter(ibin+1)
            lab.DrawLatex(x-0.5, y_text, str(mass))

    # Axis title
    title_latex = TLatex()
    title_latex.SetTextFont(42)
    title_latex.SetTextSize(0.10)
    title_latex.SetTextAlign(22)
    title_latex.DrawLatex((x_min+x_max)/2.0, y0 - 0.40*(pad.GetUymax()-y0), title)

# ---------- Plotting ----------
def example_stack(year_key, category, chLabel):
    years = ["2016", "2017", "2018"] if year_key == "Run2" else [year_key]
    files = {}
    for y in years:
        path = f"{BASE_DIR}/muon{y}/{category}/fitDiagnosticsTest.root"
        f = TFile.Open(path)
        if not f or f.IsZombie():
            raise IOError(f"Could not open: {path}")
        files[y] = f

    setTDRStyle()
    c1 = TCanvas("c1", "", 800, 800)
    pad1 = ROOT.TPad("pad1", "pad1", 0, 0.35, 1, 1.0)
    pad2 = ROOT.TPad("pad2", "pad2", 0, 0.0, 1, 0.35)
    pad1.SetBottomMargin(0.02)
    pad2.SetTopMargin(0.02)
    pad2.SetBottomMargin(0.35)
    pad1.Draw()
    pad2.Draw()

    pad1.cd()
    pad1.SetLogy()

    # --- MC components (sum across years) ---
    hTT   = getSummedHistos(files, CHAN_NAME, "ttbar")
    hST   = getSummedHistos(files, CHAN_NAME, "stop")
    hQCD  = getSummedHistos(files, CHAN_NAME, "qcd")
    hWjet = getSummedHistos(files, CHAN_NAME, "wjet")
    hDY   = getSummedHistos(files, CHAN_NAME, "zjet")
    hVV   = getSummedHistos(files, CHAN_NAME, "vv")
    hTTG  = getSummedHistos(files, CHAN_NAME, "ttg")
    hTTH  = getSummedHistos(files, CHAN_NAME, "tth")
    hTTV  = getSummedHistos(files, CHAN_NAME, "ttw")
    hTTZ  = getSummedHistos(files, CHAN_NAME, "ttz")
    hMC   = getSummedHistos(files, CHAN_NAME, "total_background")
    hSig  = getSummedHistos(files, CHAN_NAME, "WH120")
    hSig.Scale(0.01 * 50)  # BR scaling

    # ttX
    hTTX = hTTG.Clone("hTTX"); hTTX.Add(hTTH); hTTX.Add(hTTV); hTTX.Add(hTTZ)

    # Color-blind friendly
    colors = {
        "vv":    ROOT.TColor.GetColor("#999999"),
        "zjet":  ROOT.TColor.GetColor("#009E73"),
        "wjet":  ROOT.TColor.GetColor("#F0E442"),
        "qcd":   ROOT.TColor.GetColor("#E69F00"),
        "stop":  ROOT.TColor.GetColor("#56B4E9"),
        "ttx":   ROOT.TColor.GetColor("#CC79A7"),
        "ttbar": ROOT.TColor.GetColor("#0072B2"),
    }

    # Stack order (bottom -> top)
    draw_list = [
        ("vv",    hVV),
        ("zjet",  hDY),
        ("wjet",  hWjet),
        ("qcd",   hQCD),
        ("stop",  hST),
        ("ttx",   hTTX),
        ("ttbar", hTT),
    ]
    stack = THStack("stack", "")
    for label, h in draw_list:
        col = colors[label]
        h.SetFillColor(col); h.SetLineColor(col); h.SetLineWidth(1)
        stack.Add(h)

    stack.Draw("HIST")
    ytitle = hMC.GetYaxis().GetTitle() if hMC.GetYaxis().GetTitle() else "Events / bin"
    #stack.GetYaxis().SetTitle(ytitle)
    stack.GetYaxis().SetTitle("Events / bin")
    stack.GetXaxis().SetLabelSize(0)  # hide top-pad x labels
    stack.SetMinimum(1.0)
    stack.SetMaximum(100000 * max(stack.GetMaximum(), 1.0))

    # Uncertainty band
    UncBand = UNCGRAPH(hMC, isRatio=False)
    UncBand.SetFillColor(ROOT.kGreen+2)
    UncBand.SetFillStyle(3008)
    UncBand.Draw("E2 same")

    # Signal + Data
    hSig.SetLineColor(ROOT.kRed); hSig.SetLineStyle(2); hSig.SetLineWidth(3); hSig.SetFillColor(0); hSig.Draw("HISTSAME")
    hData = getCombinedDataHistogram(files, CHAN_NAME, hMC)
    hData.SetMarkerStyle(20); hData.SetMarkerSize(1.2); hData.SetLineColor(ROOT.kBlack); hData.Draw("EP SAME")

    # Legend (two columns)
    leg = TLegend(0.60, 0.48, 0.96, 0.90)
    leg.SetBorderSize(0); leg.SetFillStyle(0); leg.SetTextFont(42); leg.SetNColumns(2)
    leg.AddEntry(hData, "Data", "PE")
    leg.AddEntry(hTT,  "t#bar{t} + jets", "F")
    leg.AddEntry(hST,  "Single t",        "F")
    leg.AddEntry(hQCD, "QCD",             "F")
    leg.AddEntry(hWjet,"W + jets",        "F")
    leg.AddEntry(hDY,  "Z/#gamma + jets", "F")
    leg.AddEntry(hTTX, "ttX",             "F")
    leg.AddEntry(hVV,  "VV",              "F")
    leg.AddEntry(UncBand, "Total unc.",   "F")
    leg.AddEntry(hSig, "m_{H^{+}} = 120 GeV (B = 0.01)", "L")
    leg.Draw()

    # CMS & lumi
    cmsText = paveText(0.18, 0.91, 0.4, 0.96, textSize=0.06); cmsText.AddText("#bf{CMS} #it{Preliminary}"); cmsText.Draw()
    # lumiText = paveText(0.6, 0.91, 0.9, 0.96, textSize=0.05); lumiText.AddText("138 fb^{-1} (13 TeV)" if year_key=="Run2" else f"Year: {year_key} (13 TeV)"); lumiText.Draw()
    if year_key == "Run2":
        lumi_label = "138 fb^{-1} (13 TeV)"
    elif year_key == "2018":
        lumi_label = "59.8 fb^{-1} (13 TeV)"
    elif year_key == "2017":
        lumi_label = "41.5 fb^{-1} (13 TeV)"
    elif year_key == "2016":
        lumi_label = "36.3 fb^{-1} (13 TeV)"
    else:
        lumi_label = f"Year: {year_key} (13 TeV)"

    lumiText = paveText(0.6, 0.91, 0.9, 0.96, textSize=0.05)
    lumiText.AddText(lumi_label)
    lumiText.Draw()

    # Channel label
    latexMuJets = ROOT.TLatex(); latexMuJets.SetNDC(); latexMuJets.SetTextFont(62); latexMuJets.SetTextSize(0.045); latexMuJets.SetTextAlign(13)
    latexMuJets.DrawLatex(0.20, 0.83, "#mu + jets,")
    latexBDT = ROOT.TLatex(); latexBDT.SetNDC(); latexBDT.SetTextFont(42); latexBDT.SetTextSize(0.045); latexBDT.SetTextAlign(13)
    bdt_cat = category.replace("Exc", "").capitalize(); latexBDT.DrawLatex(0.32, 0.83, f"BDT {bdt_cat}")

    # ---- Ratio pad ----
    c1.cd(); pad2.cd()
    ratio = hData.Clone("ratio"); ratio.Divide(hMC)
    nb = ratio.GetNbinsX()
    for i in range(1, nb+1):
        D  = hData.GetBinContent(i)
        eD = hData.GetBinError(i)
        M  = hMC.GetBinContent(i)
        if M > 0:
            ratio.SetBinContent(i, D / M)
            ratio.SetBinError(i,   eD / M)
        else:
            ratio.SetBinContent(i, 0.0)
            ratio.SetBinError(i,   0.0)
    ratio.GetYaxis().SetTitle("Data/Pred")
    ratio.GetYaxis().SetTitleSize(0.10); ratio.GetYaxis().SetLabelSize(0.06); ratio.GetYaxis().SetTitleOffset(0.6)
    ratio.GetXaxis().SetTitle("m_{jj} [GeV]"); ratio.GetXaxis().SetTitleSize(0.10); ratio.GetXaxis().SetLabelSize(0.0)  # we overlay custom labels
    ratio.GetYaxis().SetNdivisions(504); ratio.SetMinimum(0.4); ratio.SetMaximum(1.6)
    ratio.Draw("EP")

    UncBand_Ratio = UNCGRAPH(hMC, isRatio=True)
    UncBand_Ratio.SetFillColorAlpha(ROOT.kGreen+2, 0.5); UncBand_Ratio.SetFillStyle(3008); UncBand_Ratio.Draw("E2 SAME")
    ratio.Draw("E SAME")
    line = TF1("line", "1", ratio.GetXaxis().GetBinLowEdge(1), ratio.GetXaxis().GetBinUpEdge(ratio.GetXaxis().GetNbins()))
    line.SetLineColor(ROOT.kRed); line.Draw("SAME")

    # ---- Overlay bin-index axis with transformed mass labels (bin*10 + 20) ----
    pad2.Update()
    #draw_index_axis_with_mass_labels(pad2, ratio, title="m_{jj} [GeV]", label_every=2, label_last_170=False)
    #draw_variable_mass_axis(pad2, ratio, title="m_{jj} [GeV]", label_step=20)
    draw_mass_axis_custom(pad2, ratio, title="")

    ROOT.gPad.RedrawAxis()

    if isSaveHisto:
        os.makedirs("output", exist_ok=True)
        out_tag = year_key
        c1.SaveAs(f"output/mjj_prefit_{out_tag}_{category}_mu.pdf")
        c1.SaveAs(f"output/mjj_prefit_{out_tag}_{category}_mu.png")
        c1.Close()

    # Close files
    for f in files.values():
        f.Close()

def MyPostFitPlot(year_key):
    for cat in ["ExcLoose", "ExcMedium", "ExcTight"]:
        example_stack(year_key, cat, "#mu + jets")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Post-fit plotting with transformed mass labels (bin*10+20)")
    parser.add_argument("--year", required=True, choices=["2016", "2017", "2018", "Run2"],
                        help="Year (2016, 2017, 2018) or Run2 for combined")
    args = parser.parse_args()
    MyPostFitPlot(args.year)
