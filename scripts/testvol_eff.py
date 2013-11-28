#!/usr/bin/env python

import ROOT
import sys

the_file = ROOT.TFile(sys.argv[1],'read')
the_tree = the_file.Get('SimulationTree')

total = 0
frac  = 0

for event in the_tree:
    if event.TVCoincidence == 1:
        if event.Coincidence == 1:
            frac = frac + 1
        total = total + 1

print '---------------------'
print 'Det coincidence / TV coincidence'
print frac,'/',total
efficiency = float(frac)/float(total)
print 'Efficiency =',efficiency
print '---------------------'
