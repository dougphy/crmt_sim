
// __________________________________________________________________
// __________________________________________________________________
// _______ crmt evd class ___________________________________________
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
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TEllipse.h"
#include "TBox.h"

class evd {

private:
  TFile            *fFile;
  TTree            *fTree;
  TTree            *fVolTree;
  double            fGap;
  int               fSelectedEventID;
  double            fInitialX;
  double            fInitialY;
  double            fInitialZ;
  double            fPhi;
  double            fTheta;
  double            fAngleXZ;
  double            fAngleYZ;
  double            fSlopeXZ;
  double            fSlopeYZ;
  double            fYintXZ;
  double            fYintYZ;
  bool              fTrueMod0[256];
  bool              fTrueMod1[256];
  bool              fTrueMod2[256];
  bool              fTrueMod3[256];
  bool              fSimMod0[256];
  bool              fSimMod1[256];
  bool              fSimMod2[256];
  bool              fSimMod3[256];
  TApplication     *fApp;
  TGraph           *fAll0;
  TGraph           *fAll1;
  TGraph           *fAll2;
  TGraph           *fAll3;
  TMultiGraph      *fTMGXZ;
  TMultiGraph      *fTMGYZ;
  bool              fTVOn;
  bool              fTVChecker;
  double            fTVCenter[3];
  double            fTVRadius;
  double            fTVLength;
  double            fTVWidth;
  double            fTVHeight;
  TEllipse         *fEllipseXZ;
  TEllipse         *fEllipseYZ;
  TBox             *fBoxXZ;
  TBox             *fBoxYZ;

public:
  evd();
  ~evd();
  void InitFile(const std::string file_name, int event_number);
  void RawDumpTrue();
  void RawDumpSim();
  void SetupTVs();
  void InitAllGraphs();
  void DrawTrue(int argc, char *argv[]);
  void DrawSim(int argc, char *argv[]);
};

#endif
