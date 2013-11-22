#!/usr/bin/env python

import sys
from ROOT import TFile, TTree, TH2D, TCanvas, gROOT, TPaveText, gStyle
import math


def fixit(alist):
    for o in alist:
        o.GetXaxis().CenterTitle()
        o.GetYaxis().CenterTitle()

gROOT.SetStyle('DStyle')
gStyle.SetOptStat(0)
the_file = TFile(sys.argv[1],'read')
the_tree = the_file.Get('SimulationTree')

h_all = TH2D('h_all',';Zenith;Polar',90,90,180,360,0,360)
h_hit = TH2D('h_hit',';Zenith;Polar',90,90,180,360,0,360)
hist_list = [h_all,h_hit]
fixit(hist_list)

counter = 0
for ev in the_tree:
    h_all.Fill(ev.Theta*180/math.pi,ev.Phi*180/math.pi)
    if ev.Conincidence > 0:
        h_hit.Fill(ev.Theta*180/math.pi,ev.Phi*180/math.pi)
    counter = counter + 1
    fgap = ev.Gap

tit = TPaveText(.23,.47,.50,.78,'brNDC')
tit.SetTextSize(20)
tit.SetTextFont(63)
tit.SetBorderSize(0)
tit.SetFillColor(0)
tit.AddText('Acceptance vs. spherical')
tit.AddText('angles combined')
tit.AddText(str(fgap)+' cm Gap')
tit.AddText('(uniform muon origin)')
print counter
c1 = TCanvas()
h_all.Draw('colz')

c2 = TCanvas()
h_hit.Draw('colz')
tit.Draw('same')
raw_input('')
