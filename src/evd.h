
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy evd class __________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#ifndef EVD_H
#define EVD_H

#include <iostream>
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"

class evd {

private:
  TFile            *fFile;
  TTree            *fTree;
  double            fGap;
  int               fSelectedEventID;
  double            fPhi;
  double            fTheta;
  double            fAngleXZ;
  double            fAngleYZ;
  double            fSlopeXZ;
  double            fSlopeYZ;
  double            fYintXZ;
  double            fYintYZ;
  TApplication     *fApp;
  int               fTrueMod0[256];
  int               fTrueMod1[256];
  int               fTrueMod2[256];
  int               fTrueMod3[256];
  int               fSimMod0[256];
  int               fSimMod1[256];
  int               fSimMod2[256];
  int               fSimMod3[256];

public:
  evd();
  ~evd();
  void InitFile(std::string file_name, int event_number);
  void RawDumpTrue();
  void RawDumpSim();
  void DrawTrue(int argc, char *argv[]);
  void DrawSim(int argc, char *argv[]);
  std::string MakeString(double value);
};

#endif
