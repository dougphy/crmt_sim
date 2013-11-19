
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy evg class __________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#ifndef EVG_H
#define EVG_H

#include "TFile.h"
#include "TTree.h"
#include "Line.h"
#include <vector>
#include <string>
#include <fstream>

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
  int                                fTrueMod0[256];
  int                                fTrueMod1[256];
  int                                fTrueMod2[256];
  int                                fTrueMod3[256];
  int                                fSimMod0[256];
  int                                fSimMod1[256];
  int                                fSimMod2[256];
  int                                fSimMod3[256];
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
  double                             fScintWidth  = 10.4;
  double                             fScintHeight = 30.8;
  double                             fScintLength = 650.0;
  double                             fStripShift  = 3.333;
  double                             fScintGap    = 4.8;
  double                             fModGap      = 6.4;
  std::map<int, std::vector<int> >   fFiberCouplingMap;

public:

  evg();
  evg(std::string fname, int n_events);
  ~evg();
  void ReadParameters();
  void CheckParameters();
  void RunEvents();
  bool Intersection(double FibI, double FibJ, double Slope, double Yint);
  bool Intersection2(double FibI, double FibJ, geo::Line *function, bool view_xz, double gap, int type);
  void InitCoupleMap();
  void Multiplex();
  void InitFiberPixelPinPairs();
  void SimHitsToPixels();
  void PixelsToPins();
  void ClearVecs();
};

#endif
