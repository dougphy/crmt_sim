#!/usr/bin/env python

import sys
import math
from ROOT import TFile, TTree, TH1D, gROOT, gStyle, kRed, TCanvas, kGreen, TLegend, TPaveText

gROOT.SetStyle('DStyle')
gStyle.SetOptStat(0)

file_name = sys.argv[1]
the_file = TFile(file_name,'read')
the_tree = the_file.Get('SimulationTree')
n_bins = 90
h_all = TH1D('h_all',';Angle (degrees);Events/Degree',n_bins,90,180)
h_hit = TH1D('h_hit',';Angle (degrees);Events/Degree',n_bins,90,180)
h_acp = TH1D('h_acp',';Angle (degrees);Acceptance/Degree',n_bins,90,180)
h_all.SetLineColor(kGreen+2)
h_all.GetXaxis().CenterTitle()
h_hit.GetXaxis().CenterTitle()
h_all.GetYaxis().CenterTitle()
h_hit.GetYaxis().CenterTitle()

for e in the_tree:
    fillit = e.Theta*180/math.pi
    h_all.Fill(fillit)
    if e.Coincidence == 1:
        h_hit.Fill(fillit)

for bins in range(h_all.GetNbinsX()):
    all_value = h_all.GetBinContent(bins+1)
    hit_value = h_hit.GetBinContent(bins+1)
    difference = math.fabs(hit_value - all_value)
    if all_value == 0:
        filler = 1
    else:
        filler = difference / all_value
    h_acp.SetBinContent(bins+1,math.fabs(1-filler))

c1 = TCanvas()
tl = TLegend(.15,.785,.45,.9)
tl.SetBorderSize(0)
tl.SetFillColor(0)
tl.SetTextSize(16)
tl.SetTextFont(63)
tl.AddEntry(h_all,'All events','l')
tl.AddEntry(h_hit,'Coincidence','l')

tit = TPaveText(.5,.785,.7,.9,'brNDC')
tit.SetTextSize(20)
tit.SetTextFont(63)
tit.SetBorderSize(0)
tit.SetFillColor(0)
tit.AddText('300 mm gap')
c1.SetTickx()
c1.SetTicky()
h_all.Draw()
h_hit.Draw('same')
tl.Draw('same')
tit.Draw('same')

h_acp.SetMarkerStyle(8)
c2 = TCanvas()
h_acp.Draw()

raw_input('')
