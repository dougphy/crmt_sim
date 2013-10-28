
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
  // event options from config file
  std::ifstream     fConfigFile;
  
  bool fOriginUniformDist;
  bool fOriginDefined;
  bool fAngleZenithDefined;
  bool fAngleZenithCosSq;
  bool fAnglePolarDefined;
  bool fAnglePolarUniform;

  double fOriginUniformDistMin;
  double fOriginUniformDistMax;
  double fOriginDefinedX;
  double fOriginDefinedY;

  double fAngleZenithDefinedValue;
  double fAnglePolarDefinedValue;
  double fAnglePolarUniformMin;
  double fAnglePolarUniformMax;

  double            fGap;

  int               fNEvents;
  // Attributes of the events
  TFile            *fFile;
  TTree            *fTree;
  int               fEventID;
  double            fInitialX;
  double            fInitialY;
  double            fInitialZ;
  double            fTraj[3];
  double            fTheta;
  double            fPhi;
  double            fAngleXZ;
  double            fAngleYZ;
  int               fTrueMod0[256];
  int               fTrueMod1[256];
  int               fTrueMod2[256];
  int               fTrueMod3[256];
  int               fSimMod0[256];
  int               fSimMod1[256];
  int               fSimMod2[256];
  int               fSimMod3[256];
  // Attributes of the detector
  const double      fScintWidth  = 10.4;
  const double      fScintHeight = 30.8;
  const double      fScintLength = 650.0;
  const double      fStripShift  = 3.333;
  const double      fScintGap    = 4.8;
  const double      fModGap      = 6.4;
  
public:
  evg();
  evg(std::string fname, int n_events);
  ~evg();
  void ReadParameters();
  void CheckParameters();
  void RunEvents();
  void SaveFile();

};

#endif
