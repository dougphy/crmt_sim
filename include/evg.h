//////////////////////////////////////////////////////////////////////
/// \file evg.h
/// \brief A class which describes a set of events (generator)
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#ifndef EVG_H
#define EVG_H

#include "TFile.h"
#include "TTree.h"
#include "Line.h"
#include "TestVolume.h"
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

namespace ev {

  class evg {
  
  protected:
  
    bool                               fOriginUniformDist; ///< on/off uniform dist for starting x,y
    bool                               fOriginDefined; ///< on/off defined starting x,y
    bool                               fAngleZenithDefined; ///< on/off zenith angle defined
    bool                               fAngleZenithCosSq; ///< on/off zenith angle cos2(theta)
    bool                               fAngleZenithGaussian; ///< on/off zenith angle gaussian
    bool                               fAnglePolarDefined; ///< on/off polar angle defined
    bool                               fAnglePolarUniform; ///< on/off polar angle uniform
    double                             fOriginUniformDistMin; ///< origin uniform starting dist min
    double                             fOriginUniformDistMax; ///< origin uniform starting dist max
    double                             fOriginDefinedX; ///< origin defined x value
    double                             fOriginDefinedY; ///< origin defined y value
    double                             fAngleZenithDefinedValue; ///< zenith angle defined value
    double                             fAngleZenithGaussianCenter; ///< zenith angle gaussian dist center
    double                             fAngleZenithGaussianSigma; ///< zenith angle gaussian dist sigma 
    double                             fAnglePolarDefinedValue; ///< polar defined value
    double                             fAnglePolarUniformMin; ///< polar uniform min
    double                             fAnglePolarUniformMax; ///< polar uniform max
    double                             fGap; ///< detector gap
    unsigned int                       fNEvents; ///< number of events
    TFile                             *fFile; ///< ROOT file
    TTree                             *fTree; ///< simulation tree
    int                                fEventID; ///< event ID for each event
    double                             fInitialX; ///< initial x for each event
    double                             fInitialY; ///< initial y for each event
    double                             fInitialZ; ///< initial z for each event
    double                             fTraj[3]; ///< trajectory unit vector (x,y,z)
    double                             fTheta; ///< zenith angle theta
    double                             fPhi; ///< polar angle phi
    double                             fSlopeXZ; ///< xz projection line slope
    double                             fSlopeYZ; ///< yz projection line slope
    double                             fYintXZ; ///< xz projection line y-int
    double                             fYintYZ; ///< yz projection line y-int
    double                             fAngleXZ; ///< xz projection angle from planar zenith
    double                             fAngleYZ; ///< yz projection angle from planar zenith
    double                             fAngleXZ_RF; ///< xz projection angle from planar zenith reco form
    double                             fAngleYZ_RF; ///< yz projection angle from planar zenith reco form
    bool                               fCoincidence; ///< coincidence through detector bool
    bool                               fTrueMod0[256]; ///< mod0 array of hits
    bool                               fTrueMod1[256]; ///< mod1 array of hits
    bool                               fTrueMod2[256]; ///< mod2 array of hits
    bool                               fTrueMod3[256]; ///< mod3 array of hits
    bool                               fSimMod0[256]; ///< mod0 array of hits (multiplexed)
    bool                               fSimMod1[256]; ///< mod1 array of hits (multiplexed)
    bool                               fSimMod2[256]; ///< mod2 array of hits (multiplexed)
    bool                               fSimMod3[256]; ///< mod3 array of hits (multiplexed)
    bool                               fPinsArray0[32];
    bool                               fPinsArray1[32];
    bool                               fPinsArray2[32];
    bool                               fPinsArray3[32];
    std::vector< std::pair<int,int> >  fRemapFiberTop; ///< pairs connecting fiber to pixel (top pmt)
    std::vector< std::pair<int,int> >  fRemapFiberBot; ///< pairs connecting fiber to pixel (bottom pmt)
    std::vector< std::pair<int,int> >  fPixelToPinTop; ///< pairs connecting pixel to pin (top pmt)
    std::vector< std::pair<int,int> >  fPixelToPinBot; ///< pairs connecting pixel to pin (bottom pmt)
    TTree                             *fTreeMod0; ///< tree for mod0 pixels and pins
    TTree                             *fTreeMod1; ///< tree for mod1 pixels and pins
    TTree                             *fTreeMod2; ///< tree for mod2 pixels and pins
    TTree                             *fTreeMod3; ///< tree for mod3 pixels and pins
    std::vector<int>                   fPinsMod0;
    std::vector<int>                   fPinsMod1;
    std::vector<int>                   fPinsMod2;
    std::vector<int>                   fPinsMod3;
    std::vector<int>                   fHitPixelsTop0; ///< contains hit pixel ids (mod0 top pmt)
    std::vector<int>                   fHitPixelsBot0; ///< contains hit pixel ids (mod0 bottom pmt)
    std::vector<int>                   fHitPixelsTop1; ///< contains hit pixel ids (mod1 top pmt)
    std::vector<int>                   fHitPixelsBot1; ///< contains hit pixel ids (mod1 bottom pmt)
    std::vector<int>                   fHitPixelsTop2; ///< contains hit pixel ids (mod2 top pmt)
    std::vector<int>                   fHitPixelsBot2; ///< contains hit pixel ids (mod2 bottom pmt)
    std::vector<int>                   fHitPixelsTop3; ///< contains hit pixel ids (mod3 top pmt)
    std::vector<int>                   fHitPixelsBot3; ///< contains hit pixel ids (mod3 bottom pmt)
    std::vector<int>                   fHitPinsTop0; ///< contains hit pin ids (mod0 top pmt)
    std::vector<int>                   fHitPinsBot0; ///< contains hit pin ids (mod0 bottom pmt)
    std::vector<int>                   fHitPinsTop1; ///< contains hit pin ids (mod1 top pmt)
    std::vector<int>                   fHitPinsBot1; ///< contains hit pin ids (mod1 bottom pmt)
    std::vector<int>                   fHitPinsTop2; ///< contains hit pin ids (mod2 top pmt)
    std::vector<int>                   fHitPinsBot2; ///< contains hit pin ids (mod2 bottom pmt)
    std::vector<int>                   fHitPinsTop3; ///< contains hit pin ids (mod3 top pmt)
    std::vector<int>                   fHitPinsBot3; ///< contains hit pin ids (mod3 bottom pmt)
    std::map<int, std::vector<int> >   fFiberCouplingMap;
  
    double                             fScintWidth  = 10.4; ///< scintillator width
    double                             fScintHeight = 30.8; ///< scintillator height 
    double                             fScintLength = 650.0; ///< scintillator length
    double                             fStripShift  = 3.333; ///< shift for rows
    double                             fScintGap    = 4.8; ///< gap between rows
    double                             fModGap      = 6.4; ///< gap between modules
    const double                       PI           = 4*atan(1.); ///< pi = 3.14159....
  
    TTree                             *fTestVolumeTree; ///< test volume tree
    geo::TestVolume                   *fTestVolume;  ///< test volume object
    std::string                        fTVType; ///< test volume type
    bool                               fTestVolumeOnOff; ///< test volume on/off
    bool                               fTVCoincidence; ///< test volume coincidence bool
    bool                               fTVOn; ///< test volume on/off (needed repeat)
    double                             fTVCenter[3]; ///< test volume center (x,y,z)
    double                             fTVRadius; ///< test volume radius
    double                             fTVLength; ///< test volume length
    double                             fTVWidth; ///< test volume width
    double                             fTVHeight; ///< test volume height
  
  public:

    /// Default constructor
    evg();

    /// Used constructor (name for file, # events)
    evg(const std::string& fname, unsigned int n_events);

    /// Virtual destructor
    virtual ~evg();
  
    /// Reads parameter file (Parameters.cfg)
    void ReadParameters();

    /// Prints current parameters (from Parameters.cfg)
    void CheckParameters();

    /// Runs the events (loops # events time)
    void RunEvents();

    /// Checks to see if line intersected through extrusion cross section
    inline bool Intersection(double FibI, double FibJ, const geo::Line *function,
			     bool view_xz, double gap, int type);

    /// Initialized map of coupled fibers (reads file from config directory)
    inline void InitCoupleMap();

    /// Multiplex the true hits
    inline void Multiplex();

    /// Initialize the fiber to pixel and pixel to pin pairs
    inline void InitFiberPixelPinPairs();

    /// Generates hit pixels from the simulated fibers
    inline void SimHitsToPixels();

    /// Generates hit pins from the hit pixels
    inline void PixelsToPins();

    /// Clears vectors which hold hits for each event
    inline void ClearVecs();  

    /// Checks for intersection through spherical test volume in both planes
    inline bool SphereIntersect(const geo::Line *line, const geo::TestVolume *vol);

    /// Checks for intersection through box test volume in both planes
    inline bool BoxIntersect(const geo::Line *line, const geo::TestVolume *vol);

  };
}

#endif
