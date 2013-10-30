
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy evg methods ________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include "evg.h"
#include "Line.h"
#include "Module.h"
#include "TRandom.h"
#include "TF1.h"

#define PI 3.1415926536

evg::evg() {}

// __________________________________________________________________

evg::evg(std::string file_name, int n_events)
{
  fNEvents  = n_events;
  fFile     = new TFile(file_name.c_str(),"RECREATE");
  fTree     = new TTree("SimulationTree","SimulationTree");
  fTree->Branch("EventID",    &fEventID,    "EventID/I");
  fTree->Branch("InitialX",   &fInitialX,   "InitialX/D");
  fTree->Branch("InitialY",   &fInitialY,   "InitialY/D");
  fTree->Branch("InitialZ",   &fInitialZ,   "InitialZ/D");
  fTree->Branch("Phi",        &fPhi,        "Phi/D");
  fTree->Branch("Theta",      &fTheta,      "Theta/D");
  fTree->Branch("AngleXZ",    &fAngleXZ,    "AngleXZ/D");
  fTree->Branch("AngleYZ",    &fAngleYZ,    "AngleYZ/D");
  fTree->Branch("SlopeXZ",    &fSlopeXZ,    "SlopeXZ/D");
  fTree->Branch("SlopeYZ",    &fSlopeYZ,    "SlopeYZ/D");
  fTree->Branch("Traj",        fTraj,       "Traj[3]/D");
  fTree->Branch("TrueMod0",    fTrueMod0,   "TrueMod0[256]/I");
  fTree->Branch("TrueMod1",    fTrueMod1,   "TrueMod1[256]/I");
  fTree->Branch("TrueMod2",    fTrueMod2,   "TrueMod2[256]/I");
  fTree->Branch("TrueMod3",    fTrueMod3,   "TrueMod3[256]/I");
  fTree->Branch("SimMod0",     fSimMod0,    "SimMod0[256]/I");
  fTree->Branch("SimMod1",     fSimMod1,    "SimMod1[256]/I");
  fTree->Branch("SimMod2",     fSimMod2,    "SimMod2[256]/I");
  fTree->Branch("SimMod3",     fSimMod3,    "SimMod3[256]/I");
}

// __________________________________________________________________

evg::~evg() {}

// __________________________________________________________________

void evg::ReadParameters()
{
  fConfigFile.open("Parameters.cfg");
  std::string label;
  double param;
  std::vector<double> param_vec;
  param_vec.reserve(20);
  while (fConfigFile >> label >> param)
    param_vec.push_back(param);
  if (param_vec[0] == 0)   { fOriginUniformDist   = false; }
  else                     { fOriginUniformDist   = true;  }
  if (param_vec[1] == 0)   { fOriginDefined       = false; }
  else                     { fOriginDefined       = true;  }
  if (param_vec[2] == 0)   { fAngleZenithDefined  = false; }
  else                     { fAngleZenithDefined  = true;  }
  if (param_vec[3] == 0)   { fAngleZenithCosSq    = false; }
  else                     { fAngleZenithCosSq    = true;  }
  if (param_vec[4] == 0)   { fAnglePolarDefined   = false; }
  else                     { fAnglePolarDefined   = true;  }
  if (param_vec[5] == 0)   { fAnglePolarUniform   = false; }
  else                     { fAnglePolarUniform   = true;  }
  fOriginUniformDistMin    = param_vec[6];
  fOriginUniformDistMax    = param_vec[7];
  fOriginDefinedX          = param_vec[8];
  fOriginDefinedY          = param_vec[9];
  fAngleZenithDefinedValue = param_vec[10]*PI/180.;
  fAnglePolarDefinedValue  = param_vec[11]*PI/180.;
  fAnglePolarUniformMin    = param_vec[12]*PI/180.;
  fAnglePolarUniformMax    = param_vec[13]*PI/180.;
  fGap                     = param_vec[14];
}

// __________________________________________________________________

void evg::CheckParameters()
{
  std::cout << "fOriginUniformDist       = " << fOriginUniformDist << "\n";
  std::cout << "fOriginDefined           = " << fOriginDefined << "\n";
  std::cout << "fAngleZenithDefined      = " << fAngleZenithDefined << "\n";
  std::cout << "fAngleZenithCosSq        = " << fAngleZenithCosSq << "\n";
  std::cout << "fAnglePolarDefined       = " << fAnglePolarDefined << "\n";
  std::cout << "fAnglePolarUniform       = " << fAnglePolarUniform << "\n";
  std::cout << "fOriginUniformDistMin    = " << fOriginUniformDistMin << "\n";
  std::cout << "fOriginUniformDistMax    = " << fOriginUniformDistMax << "\n";
  std::cout << "fOriginDefinedX          = " << fOriginDefinedX << "\n";
  std::cout << "fOriginDefinedY          = " << fOriginDefinedY << "\n";
  std::cout << "fAngleZenithDefinedValue = " << fAngleZenithDefinedValue << "\n";
  std::cout << "fAnglePolarDefinedValue  = " << fAnglePolarDefinedValue << "\n";
  std::cout << "fAnglePolarUniformMin    = " << fAnglePolarUniformMin << "\n";
  std::cout << "fAnglePolarUniformMax    = " << fAnglePolarUniformMax << "\n";
  std::cout << "fGap                     = " << fGap << "\n";
}

// __________________________________________________________________

void evg::RunEvents()
{
  Module *Mod0 = new Module(0,fGap);
  Module *Mod1 = new Module(1,fGap);
  Module *Mod2 = new Module(2,fGap);
  Module *Mod3 = new Module(3,fGap);
  std::map<int, std::pair<double,double> > Mod0Loc = Mod0->GetMap();
  std::map<int, std::pair<double,double> > Mod1Loc = Mod1->GetMap();
  std::map<int, std::pair<double,double> > Mod2Loc = Mod2->GetMap();
  std::map<int, std::pair<double,double> > Mod3Loc = Mod3->GetMap();

  double InitialZ = 330 + fGap;
  for ( int i = 0; i < fNEvents; i++ ) {
    Line *Mu = new Line();
    fInitialZ = InitialZ;
    if ( fOriginUniformDist ) {
      gRandom->SetSeed(0);
      fInitialX = gRandom->Uniform(fOriginUniformDistMin,fOriginUniformDistMax);
      fInitialY = gRandom->Uniform(fOriginUniformDistMin,fOriginUniformDistMax);
    }
    else if ( fOriginDefined ) {
      fInitialX = fOriginDefinedX;
      fInitialY = fOriginDefinedY;
    }
    else {
      std::cout << "Muon origin definition malfunction." << std::endl;
    }
    Mu->SetInitialPos(fInitialX,fInitialY,fInitialZ);
    if ( fAngleZenithDefined )
      fTheta = fAngleZenithDefinedValue;
    else if ( fAngleZenithCosSq ) {
      std::cout << "Not using yet" << std::endl;
      fTheta = fAngleZenithDefinedValue;
    }
    else {
      std::cout << "Muon zenith angle definition malfunction." << std::endl;
    }
    if ( fAnglePolarDefined ) {
      fPhi = fAnglePolarDefinedValue;
    }
    else if ( fAnglePolarUniform ) {
      fPhi = gRandom->Uniform(fAnglePolarUniformMin,fAnglePolarUniformMax);
    }
    else {
      std::cout << "Muon polar angle definition malfunction" << std::endl;
    }
    Mu->SetLinePropertiesFromPhiTheta(fPhi,fTheta);
    fAngleXZ = Mu->AngleXZ();
    fAngleYZ = Mu->AngleYZ();

    fSlopeXZ = Mu->SlopeXZ();
    fSlopeYZ = Mu->SlopeYZ();


    fTree->Fill();
  } // For fNEvents loop
  fTree->Write();
  fFile->Close();
}









// -----------------
// -----------------
// -----------------
// ALL THE OLD STUFF 
// -----------------
// -----------------
// -----------------
/*
void evg::OldRunEvents()
{
  double z_start = 310 + fGap;
  double x_start, y_start, thetaXZ, thetaYZ, theta, phi;

  double m1_z[4];
  m1_z[0] = 162.8;
  m1_z[1] = 198.4;
  m1_z[2] = 234.0;
  m1_z[3] = 269.6;

  bool on_fibers_xz[8][64];
  bool on_fibers_yz[6][64];

  int count_xz = 0;
  int count_yz = 0;

  int irow, icolumn, jrow;
  bool YZview, YZview2;
  double strip_z;

  std::vector<int> ids;
  double fiber_x, fiber_y, fiber_z;
  int ifiber_in_view;
  int kfiber_in_view;

  double FibLoc[1024][4] = {0};
  for (int ifiber = 0; ifiber < 1024; ifiber++) {
    irow = (int)((double)ifiber/64);
    fiber_z = m1_z[3] - irow*(fScintGap + fScintHeight);
    YZview = false;
    if (irow < 4 || (irow > 7 && irow < 12))
      YZview = true;
    icolumn = ifiber - irow*64;
    if(YZview) {
      fiber_x = 0.0;
      fiber_y = -32.0*fScintWidth + icolumn*fScintWidth;
      
      if (irow == 1) {
        fiber_y += 3.333;
        fiber_z += fGap;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 9) {
        fiber_y += 3.333;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
        
      }
      else if (irow == 3) {
        fiber_y -= 3.333;
        fiber_z += fGap;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 11) {
        fiber_y -= 3.333;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 0) {
        fiber_z += fGap;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow==2) {                     
        fiber_z += fGap;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 8) {
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 10) {
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }          
    }
    else {
      fiber_y = 0.0;
      fiber_x = - 32*fScintWidth + icolumn*fScintWidth;
      if (irow == 5) {
        fiber_x += 3.333;
        fiber_z += fGap;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow==13) {
        fiber_x += 3.333;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 7) {
        fiber_x -= 3.333;
        fiber_z += fGap;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 15) {
        fiber_x -= 3.333;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 4) {
        fiber_z += fGap;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 6) {
        fiber_z += fGap;
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 12) {
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
      else if (irow == 14) {
        FibLoc[ifiber][0] = ifiber;
        FibLoc[ifiber][1] = fiber_x;
        FibLoc[ifiber][2] = fiber_y;
        FibLoc[ifiber][3] = fiber_z;
      }
    }
  }
  double yz_max;
  int event_count = 0;
  while ( event_count < fNEvents ){
    fEventID = event_count;
    if (fOriginUniformDist) {
      gRandom->SetSeed(0);
      x_start = gRandom->Uniform(fOriginUniformDistXmin,fOriginUniformDistXmax);
      y_start = gRandom->Uniform(fOriginUniformDistYmin,fOriginUniformDistYmax);
    }
    else if (fOriginDefined) {
      x_start = fOriginDefinedX;
      y_start = fOriginDefinedY;
    }
    else
      std::cout << "Something went wrong with the origin choice" << std::endl;
    
    if (fAnglesGaussian) { 
      gRandom->SetSeed(0);
      thetaXZ = gRandom->Gaus(fAnglesGaussianCenter,fAnglesGaussianSigma);
      yz_max = asin(sqrt(1.-pow(sin(thetaXZ/180.*PI),2)))*180./PI;
      thetaYZ = yz_max + 1;
      while ( fabs(thetaXZ) > yz_max ) {
	thetaYZ = gRandom->Gaus(fAnglesGaussianCenter,fAnglesGaussianSigma);
      }
    }
    else if (fAnglesCosineSq) {
      thetaYZ = -1*fAnglesDefinedX;
      thetaXZ = -1*fAnglesDefinedY;
    }
    else if (fAnglesUniformDist) {
      gRandom->SetSeed(0);
      thetaXZ = gRandom->Uniform(fAnglesUniformDistXmin,fAnglesUniformDistXmax);
      thetaYZ = gRandom->Uniform(fAnglesUniformDistYmin,fAnglesUniformDistYmax);
    }
    else 
      std::cout << "Something went wrong with the angle choice" << std::endl;

    fInitialX = x_start;
    fInitialY = y_start;
    fInitialZ = z_start;
    fTraj[0]  = sin(thetaYZ*PI/180.);
    fTraj[1]  = sin(thetaXZ*PI/180.);
    fTraj[2]  = sqrt(1-pow(fTraj[0],2)-pow(fTraj[1],2));
    fThetaYZ  = -thetaXZ; // Not a typo -- will fix this later
    fThetaXZ  = -thetaYZ; // Not a typo -- will fix this later

    for (int kfiber = 0; kfiber < 1024; kfiber++) {
      jrow = (int)((double)kfiber/64.);
      YZview2 = false;
      
      if ( jrow < 4 || ( jrow > 7 && jrow < 12 ) )
	YZview2 = true;
      if(OldIntersection(FibLoc[kfiber][1],FibLoc[kfiber][2],FibLoc[kfiber][3],
		      YZview2,x_start,y_start,z_start,thetaXZ,thetaYZ,
		      fScintWidth,fScintWidth,fScintHeight)) {
	fTrueFibers[kfiber] = true;
	ids.clear();
	OldMultiplex(kfiber, &ids);
	for (int j = 0; j < ids.size(); j++) {
	  kfiber_in_view = OldGetFiberInView(jrow,ids[j],YZview2);
	  fSimFibers[ids[j]] = true;
	}
      }
    }
    fTree->Fill();
    event_count++;

    for (int ii = 0; ii < 1024; ii++) {
      fTrueFibers[ii] = 0;
      fSimFibers[ii]  = 0;
    }
    fThetaXZ  = 0;
    fThetaYZ  = 0;
    fInitialX = 0;
    fTraj[0]  = 0;
    fTraj[1]  = 0;
    fTraj[2]  = 0;
  }
}

void evg::OldMultiplex(int fiberid, std::vector<int> *ids)
{
  int r_num, c_num;
  r_num = (int)((double)fiberid/64.0);
  c_num = fiberid - r_num*64;

  int b_num  = (int)((double)r_num/4.0);
  int r_type = r_num - b_num*4;

  int octuple_index = (int)((double)c_num/8.0);
  int first_col = octuple_index*8;

  int local_fiber_id;

  switch(r_type) {
  case 0: {
    for ( int icol = 0; icol < 8; icol++ ) {
      local_fiber_id = r_num*64 + first_col + icol;
      ids->push_back(local_fiber_id);
    }
    break;
  }
  case 1: {
    int delta_col = c_num - first_col;
    for (int icol = 0; icol < 8; icol++) {
      local_fiber_id = r_num + delta_col + icol*8;
      ids->push_back(local_fiber_id);
    }
    break;
  }
  case 2: {
    int delta_col = c_num - first_col;
    for (int icol = 0; icol < 8; icol++) {
      local_fiber_id = r_num + delta_col + icol*8;
      ids->push_back(local_fiber_id);
    }
    break;
  }
  case 3: {
    int delta_col = c_num - first_col;
    for (int icol = 0; icol < 8; icol++) {
      local_fiber_id = r_num + delta_col + icol*8;
      ids->push_back(local_fiber_id);
    }
    break;
  }
  }
  return;
}

// __________________________________________________________________

bool evg::OldIntersection(double fx, double fy, double fz,
		       bool yzView, double tx, double ty, double tz,
		       double thetaxz, double thetayz,
		       double sigma_x, double sigma_y, double sigma_z)
{
  double TrajX = sin(thetayz*PI/180.);
  double TrajY = sin(thetaxz*PI/180.);
  double TrajZ = sqrt(1-pow(TrajX,2)-pow(TrajY,2));

  double top_edge, bottom_edge;
  top_edge    = fz + sigma_z/2;
  bottom_edge = fz - sigma_z/2;

  if(yzView) {
    double left_edge  = fy - sigma_y/2.;
    double right_edge = fy + sigma_y/2.;
    double slope      = TrajZ/TrajY;
    double left_z     = tz + (left_edge-ty)*slope;
    double right_z    = tz + (right_edge-ty)*slope;
    double top_z, bottom_z;
    if (left_z > right_z) {
      top_z = left_z;
      bottom_z = right_z;
    }
    else {
      top_z = right_z;
      bottom_z = left_z;
    }
    if (top_edge < bottom_z)
      return false;
    if (bottom_edge > top_z)
      return false;
    return true;
  }
  double left_edge   = fx - sigma_x/2.;
  double right_edge  = fx + sigma_x/2.;
  double slope       = TrajZ/TrajX;
  double left_z      = tz + (left_edge-tx)*slope;
  double right_z     = tz + (right_edge-tx)*slope;
  double top_z, bottom_z;
  if (left_z > right_z) {
    top_z = left_z;
    bottom_z = right_z;
  }
  else {
    top_z = right_z;
    bottom_z = left_z;
  }
  if (top_edge < bottom_z)
    return false;
  if (bottom_edge > top_z)
    return false;
  return true;
}

// __________________________________________________________________

int evg::OldGetFiberInView(int irow, int ifiber, bool YZview)
{
  int imodule = (int)((double)irow/4.);
  int ifiber_in_view = ifiber;
  if (YZview) {
    if ( imodule == 2 )
      ifiber_in_view -= 64*4;
  }
  else {
    ifiber_in_view -= 64*4;
    if ( imodule == 3)
      ifiber_in_view -= 64*4;
  }
  return ifiber_in_view;
}

*/
