
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
#include "evg.h"

class evd : public evg {

private:
  int               fSelectedEventID;
  double            fSlopeXZ;
  double            fSloptYZ;
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
