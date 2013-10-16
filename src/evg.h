#ifndef EVG_H
#define EVG_H

#include "TFile.h"
#include "TTree.h"
#include <vector>

class evg {
  
private:
  TFile    *fFile;
  TTree    *fTree;
  int       fNEvents;
  int       fEventID;
  double    fThetaXZ;
  double    fThetaYZ;
  int       fTrueFibers[1024];
  int       fSimFibers[1024];
  
public:
  evg();
  evg(std::string fname, int n_events);
  ~evg();


  void SaveFile();
};

#endif
