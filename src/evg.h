#ifndef EVG_H
#define EVG_H

#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <string>

class evg {
  
private:
  TFile            *fFile;
  TTree            *fTree;
  int               fNEvents;
  int               fEventID;
  double            fThetaXZ;
  double            fThetaYZ;
  int               fTrueFibers[1024];
  int               fSimFibers[1024];
  std::vector<int>  fIDs;
  
public:
  evg();
  evg(std::string fname, int n_events);
  ~evg();
  void Multiplex(int fiberid, std::vector<int> *ids);
  bool Intersection(double fx, double fy, double fz,
		    bool yzView, double tx, double ty, double tz,
		    double thetaxz, double thetayz,
		    double sigma_x, double sigma_y, double sigma_z);  
  int GetFiberInView(int irow, int ifiber, bool YZview);
  void SaveFile();
};

#endif
