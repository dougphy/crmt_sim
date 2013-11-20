from ROOT import TFile, TTree, TH1D, gROOT, gStyle, kRed, TCanvas
import math

gROOT.SetStyle('DStyle')
gStyle.SetOptStat(0)


the_file = TFile('afile.root','read')
the_tree = the_file.Get('SimulationTree')

n_bins = 180

h_all = TH1D('h_all',';Angle (degrees);Events/.5 Degree',n_bins,90,180)
h_hit = TH1D('h_hit',';Angle (degrees);Events/.5 Degree',n_bins,90,180)



h_all.SetLineColor(kRed)

for e in the_tree:
    fillit = e.Theta*180/math.pi
    h_all.Fill(fillit)
    if e.Coincidence == 1:
        h_hit.Fill(fillit)

h_acp = TH1D('h_acp',';Angle (degrees);Acceptance',n_bins,90,180)

for bins in range(h_all.GetNbinsX()):
    all_value = h_all.GetBinContent(bins+1)
    hit_value = h_hit.GetBinContent(bins+1)
    difference = math.fabs(hit_value - all_value)
    if all_value == 0:
        filler = 1
    else:
        filler = difference / all_value
    h_acp.SetBinContent(bins+1,math.fabs(1-filler))


'''
scaler_all = 1/h_all.Integral()
scaler_hit = 1/h_hit.Integral()
h_all.Scale(scaler_all)
h_hit.Scale(scaler_hit)
'''

c1 = TCanvas()
h_all.Draw()
h_hit.Draw('same')

h_acp.SetMarkerStyle(8)
c2 = TCanvas()
h_acp.Draw()
