def define_weight(df, scenario):
    """
    Define the weight variable depending on the specified scenario.
    :param df: DataFrame to define the weight on.
    :param scenario: The scenario for which the weight is defined (e.g., 'nominal', 'JEC_up', 'PUWeight_Do').
    :return: DataFrame with the weight defined.
    """
    weight_expression = "float(sampleWeight * wt_ratio"

    if scenario == "base":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight)"
    elif scenario == "JEC_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_jes_Up)"
    elif scenario == "JEC_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_jes_Do)"
    elif scenario == "PUWeight_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight_Do * muEffWeight * bcTagWeight_pu_Do)"
    elif scenario == "PUWeight_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight_Up * muEffWeight * bcTagWeight_pu_Up)"
    elif scenario == "prefire_up":
        weight_expression += "*puJetIDWeight * prefireWeight_Up * PUWeight * muEffWeight * bcTagWeight)"
    elif scenario == "prefire_do":
        weight_expression += "*puJetIDWeight * prefireWeight_Do * PUWeight * muEffWeight * bcTagWeight)"
    elif scenario == "muEff_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight_Do * bcTagWeight_muid_Do)"
    elif scenario == "muEff_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight_Up * bcTagWeight_muid_Up)"
    elif scenario == "bc_stat_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_stat_Up)"
    elif scenario == "bc_lhemuf_down":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_lhemuf_Do)"
    elif scenario == "bc_lhemuf_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight_Up * bcTagWeight_lhemuf_Up)"
    elif scenario == "lhemur_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_lhemur_Up)"
    elif scenario == "lhemur_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_lhemur_Do)"
    elif scenario == "isr_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_isr_Up * ISRweight_Up)"
    elif scenario == "isr_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_isr_Do * ISRweight_Do)"
    elif scenario == "fsr_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_fsr_Up * FSRweight_Up)"
    elif scenario == "fsr_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_fsr_Do * FSRweight_Do)"
    elif scenario == "xdy_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_xdy_Up)"
    elif scenario == "xdy_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_xdy_Do)"
    elif scenario == "xdyc_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_xdyc_Up)"
    elif scenario == "xdyc_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_xdyc_Do)"
    elif scenario == "intp_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_intp_Up)"
    elif scenario == "intp_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_intp_Do)"
    elif scenario == "extp_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_extp_Up)"
    elif scenario == "extp_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_extp_Do)"
    elif scenario == "xwj_up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_xwj_Up)"
    elif scenario == "bfrag_do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_bfrag_Do)"
    elif scenario == "bfrag_Up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight_bfrag_Up)"
    elif scenario == "pdf_Up":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight * pdfweight_Up)"
    elif scenario == "pdf_Do":
        weight_expression += "*puJetIDWeight * prefireWeight * PUWeight * muEffWeight * bcTagWeight * pdfweight_Do)"
    else:
        raise ValueError(f"Unknown scenario: {scenario}")

    return df.Define("Weight", weight_expression)

def define_variables(df, scenario):
    """
    Define the variables which shall be used for training, including weights depending on the scenario.
    """
    df = define_weight(df, scenario)
    
    return (df.Define("mjj", "Compute_mjj(jetChadPt, jetChadEta, jetChadPhi, jetChadEnergy, jetShadPt, jetShadEta, jetShadPhi, jetShadEnergy)")
             .Define("CvsL_j2", "float(sjhadCvsLdisc)")
             .Define("CvsL_j1", "float(cjhadCvsLdisc)")
             .Define("CvsB_j1", "float(cjhadCvsBdisc)")
             .Define("CvsB_j2", "float(sjhadCvsBdisc)")
             .Define("pt_b1", "jetBhadPt")
             .Define("pt_j1", "jetChadPt")
             .Define("pt_j2", "jetShadPt")
             .Define("pt_b2", "jetBlepPt")
             .Define("mbb", "Compute_mjj(jetBhadPt, jetBhadEta, jetBhadPhi, jetBhadEnergy, jetBlepPt, jetBlepEta, jetBlepPhi, jetBlepEnergy)")
             .Define("dPhi_j1j2", "DeltaPhi(jetChadPhi, jetShadPhi)")
             .Define("dPhi_j1b1", "DeltaPhi(jetChadPhi, jetBhadPhi)")
             .Define("cjet", "Helper::add_p4(jetChadPt, jetChadEta, jetChadPhi, jetChadEnergy)")
             .Define("sjet", "Helper::add_p4(jetShadPt, jetShadEta, jetShadPhi, jetShadEnergy)")
             .Define("Higgs", "cjet + sjet")
             .Define("bjet_H", "Helper::add_p4(jetBhadPt, jetBhadEta, jetBhadPhi, jetBhadEnergy)")
             .Define("bjet_l", "Helper::add_p4(jetBlepPt, jetBlepEta, jetBlepPhi, jetBlepEnergy)")
             .Define("TopHadron", "bjet_H + Higgs")
             .Define("CTopVar", "float(Helper::CosVector_test(cjet, sjet, cjet, TopHadron, sjet, cjhadCvsLdisc, sjhadCvsLdisc))")
             .Define("CvsL_b1", "float(bjhadCvsLdisc)")
             .Define("CvsB_b1", "float(bjhadCvsBdisc)")
             .Define("CvsL_b2", "float(bjlepCvsLdisc)")
             .Define("DelR_j1j2", "float(sqrt(pow(dPhi_j1j2, 2) + pow((jetChadEta - jetShadEta), 2)))")
             .Define("dPhi_j1b2", "DeltaPhi(jetChadPhi, jetBlepPhi)")
             .Define("DelR_j1b2", "float(sqrt(pow(dPhi_j1b2, 2) + pow((jetChadEta - jetBlepEta), 2)))")
             .Define("pt_l", "lepPt")
             .Define("ht_b1b2j1j2", "float((TopHadron + bjet_l).Pt())")
             .Define("m_b1b2j1j2lv", "float((bjet_H + bjet_l + Higgs).M())")
             .Define("lep", "Helper::add_p4(lepPt, lepEta, lepPhi, lepEnergy)")
             .Define("dPhi_lb2", "DeltaPhi(lepPhi, jetBlepPhi)")
             .Define("dPhi_j2b1", "DeltaPhi(jetShadPhi, jetBhadPhi)")
             .Define("DelR_j2b1", "float(sqrt(pow(dPhi_j2b1, 2) + pow((jetShadEta - jetBhadEta), 2)))")
             .Define("MET", "sqrt(pow(metPx, 2) + pow(metPy, 2))")
             .Define("met_phi", "metPhi(metPx, metPy)")
             .Define("dPhi_lv", "DeltaPhi(lepPhi, met_phi)")
             .Define("chisq", "float(chi2)"))

def filter_events_mu(df):
    """
    Reduce initial dataset to only events which shall be used for training
    """
    return df.Filter("singleMu==1", "mu channel")\
             .Filter("muonIsoCut==1","Isolation of mus")\
             .Filter("isLowMET==0","MET cut")

def filter_events_ele(df):
    """
    Reduce initial dataset to only events which shall be used for training
    """
    return df.Filter("singleEle==1", "mu channel")\
             .Filter("electronIsoCut==1","Isolation of ele")\
             .Filter("isLowMET==0","MET cut")

def filter_events_muA(df):
    """
    Reduce initial dataset to only events which shall be used for training
    """
    return df.Filter("singleMu==1", "mu channel")\
             .Filter("muonIsoCut==1","Isolation of mus")\
             .Filter("isLowMET==0","MET cut")

def filter_events_muB(df):
    """
    Reduce initial dataset to only events which shall be used for training
    """
    return df.Filter("singleMu==1", "mu channel")\
             .Filter("muonIsoCut==0","Isolation of mus")\
             .Filter("isLowMET==0","MET cut")

def filter_events_muC(df):
    """
    Reduce initial dataset to only events which shall be used for training
    """
    return df.Filter("singleMu==1", "mu channel")\
             .Filter("muonIsoCut==0","Isolation of mus")\
             .Filter("isLowMET==1","MET cut")

def filter_events_muD(df):
    """
    Reduce initial dataset to only events which shall be used for training
    """
    return df.Filter("singleMu==1", "mu channel")\
             .Filter("muonIsoCut==1","Isolation of mus")\
             .Filter("isLowMET==1","MET cut")

def filter_events_eleB(df):
    """
    Reduce initial dataset to only events which shall be used for training in scenario eleB.
    """
    return (df.Filter("singleEle == 1", "ele channel")
              .Filter("electronIsoCut == 0", "Isolation of eles")
              .Filter("isLowMET == 0", "MET cut"))

def filter_events_eleC(df):
    """
    Reduce initial dataset to only events which shall be used for training in scenario eleC.
    """
    return (df.Filter("singleEle == 1", "ele channel")
              .Filter("electronIsoCut == 0", "Isolation of eles")
              .Filter("isLowMET == 1", "MET cut"))

def filter_events_eleD(df):
    """
    Reduce initial dataset to only events which shall be used for training in scenario eleD.
    """
    return (df.Filter("singleEle == 1", "ele channel")
              .Filter("electronIsoCut == 1", "Isolation of eles")
              .Filter("isLowMET == 1", "MET cut"))
