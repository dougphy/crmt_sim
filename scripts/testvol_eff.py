#!/usr/bin/env python

import ROOT
import sys

the_file = ROOT.TFile(sys.argv[1],'read')
the_tree = the_file.Get('SimulationTree')
vol_tree = the_file.Get('TestVolumeTree')

for info in vol_tree:
    tv_type   = info.TVType
    tv_center = info.TVCenter
    tv_radius = info.TVRadius
    tv_length = info.TVLength
    tv_width  = info.TVWidth
    tv_height = info.TVHeight

total = 0
frac  = 0

for event in the_tree:
    if event.TVCoincidence == 1:
        if event.Coincidence == 1:
            frac = frac + 1
        total = total + 1

print 'Type:',tv_type
if tv_type == 'sphere':
    print 'Radius = ',tv_radius
if tv_type == 'box':
    print 'Length, width, height = ',tv_length,tv_width,tv_height
print 'Det coincidence / TV coincidence'
print frac,'/',total
efficiency = float(frac)/float(total)
print 'Efficiency =',efficiency
