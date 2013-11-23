#!/usr/bin/env python

import sys
import math
import os
from ROOT import TFile, TTree, TH1D, gROOT, gStyle, kRed, TCanvas, TLegend, TPaveText

gROOT.SetStyle('DStyle')
gStyle.SetOptStat(0)

lof  = [x for x in os.listdir('../../../acp_data/') if x.endswith('.root')]
lof.sort()
lotf = [TFile('../../../acp_data//%s' % f_name,'read') for f_name in lof]
lott = [p.Get('SimulationTree') for p in lotf]
nbins = 90

histlist_all = [TH1D('all_h_gap%d' % int(gap_name[3:7]),';Angle (deg);Events/Degree',nbins,90,180) for gap_name in lof]
histlist_hit = [TH1D('hit_h_gap%d' % int(gap_name[3:7]),';Angle (deg);Events/Degree',nbins,90,180) for gap_name in lof]
histlist_acp = [TH1D('acp_h_gap%d' % int(gap_name[3:7]),';Angle (deg);Acceptance/Degree',nbins,90,180) for gap_name in lof]


for x in range(len(lott)):
    for ev in lott[x]:
        histlist_all[x].Fill(ev.Theta*180/math.pi)
        if ev.Coincidence == 1:
            histlist_hit[x].Fill(ev.Theta*180/math.pi)

for x in range(len(histlist_all)):
    for bins in range(histlist_all[x].GetNbinsX()):
        all_value  = histlist_all[x].GetBinContent(bins+1)
        hit_value  = histlist_hit[x].GetBinContent(bins+1)
        difference = math.fabs(hit_value - all_value)
        if all_value == 0:
            filler = 1
        else:
            filler = difference / all_value
        histlist_acp[x].SetBinContent(bins+1,math.fabs(1-filler))

c_com = TCanvas()
histlist_all[0].Draw()
histlist_hit[0].Draw('same')
c_acp = TCanvas()
histlist_acp[0].Draw()

histlist_acp[0].SetFillColor(kRed+4)
histlist_acp[1].SetFillColor(kRed+3)
histlist_acp[2].SetFillColor(kRed+2)
histlist_acp[3].SetFillColor(kRed+1)
histlist_acp[4].SetFillColor(kRed)
histlist_acp[5].SetFillColor(kRed-1)
histlist_acp[6].SetFillColor(kRed-2)
histlist_acp[7].SetFillColor(kRed-3)
histlist_acp[8].SetFillColor(kRed-4)
histlist_acp[9].SetFillColor(kRed-5)
histlist_acp[10].SetFillColor(kRed-6)
histlist_acp[0].SetLineColor(kRed+4)
histlist_acp[1].SetLineColor(kRed+3)
histlist_acp[2].SetLineColor(kRed+2)
histlist_acp[3].SetLineColor(kRed+1)
histlist_acp[4].SetLineColor(kRed)
histlist_acp[5].SetLineColor(kRed-1)
histlist_acp[6].SetLineColor(kRed-2)
histlist_acp[7].SetLineColor(kRed-3)
histlist_acp[8].SetLineColor(kRed-4)
histlist_acp[9].SetLineColor(kRed-5)
histlist_acp[10].SetLineColor(kRed-6)

c_fun = TCanvas()
for j in histlist_acp:
    j.SetLineWidth(1)
    j.GetXaxis().CenterTitle()
    j.GetYaxis().CenterTitle()
    j.SetLineWidth(0)
    j.SetFillStyle(1001)
    if histlist_acp.index(j) == 0:
        j.Draw()
    else:
        j.Draw('same')


tit = TPaveText(0.21,0.80,0.46,0.86,'brNDC')
tit.SetFillColor(0)
tit.SetBorderSize(0)
tit.SetTextFont(63)
tit.SetTextSize(20)
tit.AddText('UT#muT Gap Acceptance')

leg = TLegend(0.16,0.35,0.45,0.78)
leg.SetFillColor(0)
leg.SetTextSize(14)
leg.SetTextFont(63)
counter = 0
for gap_name in lof:
    leg.AddEntry(histlist_acp[counter],'%d mm' % int(gap_name[3:7]),'f')
    counter = counter + 1

leg.Draw('same')
tit.Draw('same')
c_fun.SetTickx()
c_fun.SetTicky()
c_fun.RedrawAxis()
c_fun.Update()
c_fun.Modified()
raw_input('')
