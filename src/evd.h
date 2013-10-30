
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
  int               fSelectedEventID;
  double            fSlopeXZ;
  double            fSlopeYZ;
  double            fYintXZ;
  double            fYintYZ;
  TF1              *LineXZ;
  TF1              *LineYZ;
  TApplication     *fApp;

public:
  evd();
  ~evd();
  void InitData(std::string file_name, int event_number);
  void RawDumpTrue();
  void RawDumpSim();
  void DrawTrue(int argc, char *argv[]);
};

#endif
