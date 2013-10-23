
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
#include "TVector3.h"
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
  double            fThetaXZ;
  double            fThetaYZ;
  int               fTrueFibers[1024];
  int               fSimFibers[1024];
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
  void MakeLine();
  void RunEvents();
  void SaveFile();



  void OldRunEvents();
  void OldMultiplex(int fiberid, std::vector<int> *ids);
  bool OldIntersection(double fx, double fy, double fz,
		    bool yzView, double tx, double ty, double tz,
		    double thetaxz, double thetayz,
		    double sigma_x, double sigma_y, double sigma_z);  
  int OldGetFiberInView(int irow, int ifiber, bool YZview);

};

#endif
