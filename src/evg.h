
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
#include <vector>
#include <string>
#include <fstream>

class evg {
  
protected:
  
  std::ifstream     fConfigFile;
  
  bool fOriginUniformDist;
  bool fOriginDefined;

  bool fAngleZenithDefined;
  bool fAngleZenithCosSq;
  bool fAngleZenithGaussian;

  bool fAnglePolarDefined;
  bool fAnglePolarUniform;

  double fOriginUniformDistMin;
  double fOriginUniformDistMax;
  double fOriginDefinedX;
  double fOriginDefinedY;

  double fAngleZenithDefinedValue;
  double fAngleZenithGaussianCenter;
  double fAngleZenithGaussianSigma;
  double fAnglePolarDefinedValue;
  double fAnglePolarUniformMin;
  double fAnglePolarUniformMax;

  double            fGap;

  int               fNEvents;
  TFile            *fFile;
  TTree            *fTree;
  int               fEventID;
  double            fInitialX;
  double            fInitialY;
  double            fInitialZ;
  double            fTraj[3];
  double            fTheta;
  double            fPhi;
  double            fSlopeXZ;
  double            fSlopeYZ;
  double            fYintXZ;
  double            fYintYZ;
  double            fAngleXZ;
  double            fAngleYZ;
  int               fTrueMod3[256];
  int               fSimMod3[256];
  // Attributes of the detector
  double            fScintWidth  = 10.4;
  double            fScintHeight = 30.8;
  double            fScintLength = 650.0;
  double            fStripShift  = 3.333;
  double            fScintGap    = 4.8;
  double            fModGap      = 6.4;
  std::map<int, std::vector<int> > fFiberCouplingMap;
public:
  evg();
  evg(std::string fname, int n_events);
  ~evg();
  void ReadParameters();
  void CheckParameters();
  void RunEvents();
  bool Intersection(double FibI, double FibJ, double Slope, double Yint);
  void InitCoupleMap();
  void Multiplex();

};

#endif
