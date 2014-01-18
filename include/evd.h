//////////////////////////////////////////////////////////////////////
/// \class evd
/// \file evd.h
/// \brief A class which describes a single event display.
///        inherits some variables from gen::evg  
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#ifndef EVD_H
#define EVD_H

#include <iostream>
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TEllipse.h"
#include "TBox.h"
#include "evg.h"

namespace ev {

  class evd : public ev::evg {

  private:
    TFile            *fFile; ///< file to be read
    TTree            *fTree; ///< simulation tree to read simulation info
    TTree            *fVolTree; ///< test volume tree to read test volume info
    int               fSelectedEventID; ///< event to display id#
    double            fGap; ///< gap for event
    bool              fCoincidence; ///< coincidence check
    double            fInitialX; ///< initial x
    double            fInitialY; ///< initial y
    TApplication     *fApp; ///< ROOT application to draw with X11
    TGraph           *fAll0; ///< contains all points for mod0
    TGraph           *fAll1; ///< contains all points for mod1
    TGraph           *fAll2; ///< contains all points for mod2
    TGraph           *fAll3; ///< contains all points for mod3
    TMultiGraph      *fTMGXZ; ///< contains points for xz plane
    TMultiGraph      *fTMGYZ; ///< contains points for yz plane
    bool              fTVChecker; ///< checks for a test volume
    TEllipse         *fEllipseXZ; ///< ellipse object to draw sphere projection xz
    TEllipse         *fEllipseYZ; ///< ellipse object to draw sphere projection yz
    TBox             *fBoxXZ; ///< box object to draw box projection xz
    TBox             *fBoxYZ; ///< box object to draw box projection yz

  public:

    /// Default constructor
    evd();

    /// Virtual destructor
    virtual ~evd();

    /// Initialized file to read event from
    void InitFile(const std::string& file_name, unsigned int event_number);

    /// Dump raw hit fibers
    void RawDumpTrue();

    /// Dump raw hit simulated fibers (multiplexed)
    void RawDumpSim();

    /// Sets up test volume info
    void SetupTVs();
    
    /// Initialized the graphs which draw all points
    void InitAllGraphs();

    /// Draws the true event display
    void DrawTrue(int argc, char *argv[]);

    /// Draws the simulated event display (multiplxed)
    void DrawSim(int argc, char *argv[]);
  };
}

#endif
