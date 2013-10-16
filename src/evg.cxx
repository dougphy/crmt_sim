
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy evg methods ________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#include <map>
#include <vector>
#include <cmath>
#include "evg.h"

#define PI 3.14159

evg::evg() {}  // Default constructor -- not used

// __________________________________________________________________

evg::evg(std::string file_name, int n_events)
{
  fNEvents  = n_events;
  fFile     = new TFile(file_name.c_str(),"RECREATE");
  fTree     = new TTree("SimulationTree","SimulationTree");
  fTree->Branch("EventID",    &fEventID,    "EventID/I");
  fTree->Branch("ThetaXZ",    &fThetaXZ,    "ThetaXZ/D");
  fTree->Branch("ThetaYZ",    &fThetaYZ,    "ThetaYZ/D");
  fTree->Branch("TrueFibers",  fTrueFibers, "TrueFibers[1024]/I");
  fTree->Branch("SimFibers",   fSimFibers,  "SimFibers[1024]/I");
}

// __________________________________________________________________

evg::~evg() {} // Default destructor

// __________________________________________________________________

void evg::Multiplex(int fiberid, std::vector<int> *ids)
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

bool evg::Intersection(double fx, double fy, double fz,
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

int evg::GetFiberInView(int irow, int ifiber, bool YZview)
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

void evg::SaveFile()
{
  fTree->Write();
  fFile->Close();
}
