#!/usr/bin/env python

import sys
import ROOT

the_file = ROOT.TFile(sys.argv[1],'read')
the_tree = the_file.Get('SimulationTree')

for entry in the_tree:
    print entry.EventID, entry.IdentifierHit[0], entry.IdentifierHit[1],entry.IdentifierHit[2],entry.IdentifierHit[3]
