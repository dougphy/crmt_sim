#!/usr/bin/env python

import ROOT
import sys

the_file = ROOT.TFile(sys.argv[1],'read')
vol_tree = the_file.Get('TestVolumeTree')
sim_tree = the_file.Get('SimulationTree')

counter = 0
for ev in sim_tree:
    if ev.TVCoincidence == 1:
        print counter, ev.TVCoincidence
    counter = counter + 1
