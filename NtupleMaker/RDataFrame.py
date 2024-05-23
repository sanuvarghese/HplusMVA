import ROOT
from optparse import OptionParser
import sys
import os
from helper import *

from new_syst import *

'''
parser = OptionParser()
parser.add_option('--channel', type='string', default='mu', choices=['mu', 'ele'],
                  help='Select the channel: mu (muon) or ele (electron). Default is mu.')
parser.add_option('--region', type='string', default='A', help='Define the region for the analysis. Default is A.')

(opts, args) = parser.parse_args()

# Check if the required number of arguments (FileName and Scenario) is provided
if len(args) < 2:
    print("Usage: script.py <FileName> <Scenario>")
    sys.exit(1)

# Assign the first argument to FileName and the second argument to Scenario
FileName = str(args[0])
scenario = str(args[1])

# Accessing options
channel = opts.channel
region = opts.region

print(f"File: {FileName}, Scenario: {scenario}, Channel: {channel}, Region: {region}")
'''
# Define the valid choices for --region
VALID_REGIONS = ['A', 'B', 'C', 'D']

#outputdir = "

def check_region(option, opt, value, parser):
    if value not in VALID_REGIONS:
        raise OptionParser.OptionValueError(f"Invalid value for --region. Valid choices are: {', '.join(VALID_REGIONS)}")
    setattr(parser.values, option.dest, value)

parser = OptionParser()
parser.add_option('--channel', type='choice', choices=['mu', 'ele'], default='mu',
                  help='Select the channel: mu (muon) or ele (electron). Default is mu.')
parser.add_option('--region', type='string', default='A',
                  help='Define the region for the analysis. Default is A.')
parser.set_default('region', 'A')
parser.set_default('channel', 'mu')

(opts, args) = parser.parse_args()

# Check if the required number of arguments (FileName and Scenario) is provided
if len(args) < 2:
    print("Usage: script.py <FileName> <Scenario>")
    sys.exit(1)

FileName = str(args[0])
scenario = str(args[1])

# Accessing options
channel = opts.channel
region = opts.region

print(f"File: {FileName}, Scenario: {scenario}, Channel: {channel}, Region: {region}")

# Further processing with FileName, scenario, channel, and region


ROOT.EnableImplicitMT(4)

df = ROOT.RDataFrame("Kinfit_Reco","root::///eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/pre/Combined_all/"+FileName+".root")

variables = ["Weight","mjj","CvsL_j2","CvsL_j1","CvsB_j1","CvsB_j2","pt_b1","pt_j1","pt_j2","pt_b2","mbb","dPhi_j1j2","dPhi_j1b1","CTopVar","CvsL_b1","CvsB_b1","CvsL_b2","DelR_j1j2","DelR_j1b2","pt_l","ht_b1b2j1j2","DelR_j2b1","dPhi_lb2","m_b1b2j1j2lv","chisq"]

# Usage example
#scenario = "PUWeight_do"  # or "nominal", "JEC_up", etc.

columns = ROOT.std.vector["string"](variables)

# Assuming filter_events_* functions are already defined

# Example for the channel and region conditions
if channel == "mu" and region == "A":
    df = filter_events_mu(df)
elif channel == "mu" and region == "B":
    df = filter_events_muB(df)
elif channel == "mu" and region == "C":
    df = filter_events_muC(df)
elif channel == "mu" and region == "D":
    df = filter_events_muD(df)
elif channel == "ele" and region == "A":
    df = filter_events_ele(df)
elif channel == "ele" and region == "B":
    df = filter_events_eleB(df)
elif channel == "ele" and region == "C":
    df = filter_events_eleC(df)
elif channel == "ele" and region == "D":
    df = filter_events_eleD(df)

df = define_variables(df, scenario)


# if scenario == "base":
#     df.Filter("rdfentry_ % 1 == 0").Snapshot("KinFit", FileName+"_2018_mu.root", columns)
# else:
#     df.Filter("rdfentry_ % 1 == 0").Snapshot("KinFit", FileName+"_"+scenario+"_2018_mu.root", columns)

# Assume outputDir is your custom output directory path
outputDir = "/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/Full_Ntuples/" + channel + "/Base/" + region

#outputDir = "/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/Full_Ntuples/" + channel + "/" +"baseNtuples/" + region
 
# Check if the output directory exists, and create it if it doesn't
if not os.path.exists(outputDir):
    os.makedirs(outputDir)


# Ensure the output directory ends with a slash for proper path concatenation
if not outputDir.endswith('/'):
    outputDir += '/'

if scenario == "base":
    outputFile = outputDir + FileName + "_2018_mu.root"
    df.Filter("rdfentry_ % 1 == 0").Snapshot("KinFit", outputFile, columns)
else:
    outputFile = outputDir + FileName + "_" + scenario + "_2018_mu.root"
    df.Filter("rdfentry_ % 1 == 0").Snapshot("KinFit", outputFile, columns)

