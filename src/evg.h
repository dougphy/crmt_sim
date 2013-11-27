
// __________________________________________________________________
// __________________________________________________________________
// _______ crmt evg class ___________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

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

class evg {
  
protected:
  
  bool                               fOriginUniformDist;
  bool                               fOriginDefined;
  bool                               fAngleZenithDefined;
  bool                               fAngleZenithCosSq;
  bool                               fAngleZenithGaussian;
  bool                               fAnglePolarDefined;
  bool                               fAnglePolarUniform;
  double                             fOriginUniformDistMin;
  double                             fOriginUniformDistMax;
  double                             fOriginDefinedX;
  double                             fOriginDefinedY;
  double                             fAngleZenithDefinedValue;
  double                             fAngleZenithGaussianCenter;
  double                             fAngleZenithGaussianSigma;
  double                             fAnglePolarDefinedValue;
  double                             fAnglePolarUniformMin;
  double                             fAnglePolarUniformMax;
  double                             fGap;
  int                                fNEvents;
  TFile                             *fFile;
  TTree                             *fTree;
  int                                fEventID;
  double                             fInitialX;
  double                             fInitialY;
  double                             fInitialZ;
  double                             fTraj[3];
  double                             fTheta;
  double                             fPhi;
  double                             fSlopeXZ;
  double                             fSlopeYZ;
  double                             fYintXZ;
  double                             fYintYZ;
  double                             fAngleXZ;
  double                             fAngleYZ;
  double                             fAngleXZ_RF;
  double                             fAngleYZ_RF;
  bool                               fCoincidence;
  bool                               fTrueMod0[256];
  bool                               fTrueMod1[256];
  bool                               fTrueMod2[256];
  bool                               fTrueMod3[256];
  bool                               fSimMod0[256];
  bool                               fSimMod1[256];
  bool                               fSimMod2[256];
  bool                               fSimMod3[256];
  std::vector< std::pair<int,int> >  fRemapFiberTop;
  std::vector< std::pair<int,int> >  fRemapFiberBot;
  std::vector< std::pair<int,int> >  fPixelToPinTop;
  std::vector< std::pair<int,int> >  fPixelToPinBot;
  TTree                             *fTreeMod0;
  TTree                             *fTreeMod1;
  TTree                             *fTreeMod2;
  TTree                             *fTreeMod3;
  std::vector<int>                   fHitPixelsTop0;
  std::vector<int>                   fHitPixelsBot0;
  std::vector<int>                   fHitPixelsTop1;
  std::vector<int>                   fHitPixelsBot1;
  std::vector<int>                   fHitPixelsTop2;
  std::vector<int>                   fHitPixelsBot2;
  std::vector<int>                   fHitPixelsTop3;
  std::vector<int>                   fHitPixelsBot3;
  std::vector<int>                   fHitPinsTop0;
  std::vector<int>                   fHitPinsBot0;
  std::vector<int>                   fHitPinsTop1;
  std::vector<int>                   fHitPinsBot1;
  std::vector<int>                   fHitPinsTop2;
  std::vector<int>                   fHitPinsBot2;
  std::vector<int>                   fHitPinsTop3;
  std::vector<int>                   fHitPinsBot3;
  std::map<int, std::vector<int> >   fFiberCouplingMap;
  
  double                             fScintWidth  = 10.4;
  double                             fScintHeight = 30.8;
  double                             fScintLength = 650.0;
  double                             fStripShift  = 3.333;
  double                             fScintGap    = 4.8;
  double                             fModGap      = 6.4;
  const double                       PI           = 4*atan(1.);
  
  TTree                             *fTestVolumeTree;
  geo::TestVolume                   *fTestVolume;
  std::string                        fTVType;
  bool                               fTestVolumeOnOff;
  bool                               fTVCoincidence;
  double                             fTVCenter[3];
  double                             fTVRadius;
  double                             fTVLength;
  double                             fTVWidth;
  double                             fTVHeight;
  
public:

  evg();
  evg(std::string fname, int n_events);
  ~evg();
  void ReadParameters();
  void CheckParameters();
  void RunEvents();
  bool Intersection(double FibI, double FibJ, geo::Line *function,
		     bool view_xz, double gap, int type);
  void InitCoupleMap();
  void Multiplex();
  void InitFiberPixelPinPairs();
  void SimHitsToPixels();
  void PixelsToPins();
  void ClearVecs();

  bool SphereIntersect(geo::Line *line, geo::TestVolume *vol);
  bool BoxIntersect(geo::Line *line, geo::TestVolume *vol);

};

#endif
