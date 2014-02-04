#!/usr/bin/env python

import sys
import math
import os
from ROOT import TFile, TTree, TH1D, gROOT, gStyle, kRed, TCanvas, TLegend, TPaveText

the_file = TFile(sys.argv[1],'read')
the_tree = the_file.Get('SimulationTree')

hist_all = TH1D('hist_all',';Zenith Angle;Events/Degree',90,90,180)
hist_acp = TH1D('hist_acp',';Zenith Angle;Events/Degree',90,90,180)

for entry in the_tree:
    hist_all.Fill(entry.Theta*180/math.pi)
    if entry.IdentifierHit[0] == True and entry.IdentifierHit[1] == True and entry.IdentifierHit[2] == True and entry.IdentifierHit[3] == True:
        hist_acp.Fill(entry.Theta*180/math.pi)

print 'Efficiency:',hist_acp.Integral()/hist_all.Integral()

hist_all.Draw()
hist_acp.Draw('same')

raw_input('')
