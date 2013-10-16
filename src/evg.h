#ifndef EVG_H
#define EVG_H

#include "TFile.h"
#include "TTree.h"

class evg {

private:
  TFile    *fFile;
  TTree    *fTree;
  int       fNEvents;

public:
  evg();
  evg(std::string fname, int n_events);
  ~evg();
};

#endif
