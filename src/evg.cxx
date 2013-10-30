
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
  std::map<int, std::pair<double,double> >::iterator FiberItr;
  
  double InitialZ = 330 + fGap;
  for ( int i = 0; i < fNEvents; i++ ) {
    std::cout << "*******************" << std::endl;
    std::cout << "*******************" << std::endl;
    std::cout << "* EVENT NUMBER " << i << std::endl;
    std::cout << "*******************" << std::endl;
    std::cout << "*******************" << std::endl;

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
    fYintXZ  = Mu->YintXZ();
    fYintYZ  = Mu->YintYZ();
    
    for ( FiberItr = Mod0Loc.begin(); FiberItr != Mod0Loc.end(); FiberItr++ ) {
      if ( Intersection((*FiberItr).second.first,(*FiberItr).second.second,
			fSlopeYZ,fYintYZ) ) {
	std::cout << (*FiberItr).first << "Hit!" << std::endl;
	fTrueMod0[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod0[(*FiberItr).first] = 0;
      }
    }
    
    for ( FiberItr = Mod1Loc.begin(); FiberItr != Mod1Loc.end(); FiberItr++ ) {
      if ( Intersection((*FiberItr).second.first,(*FiberItr).second.second,
			fSlopeXZ,fYintXZ) ) {
	std::cout << (*FiberItr).first << " Hit!" << std::endl;
	fTrueMod1[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod1[(*FiberItr).first] = 0;
      }
    }

    for ( FiberItr = Mod2Loc.begin(); FiberItr != Mod2Loc.end(); FiberItr++ ) {
      if ( Intersection((*FiberItr).second.first,(*FiberItr).second.second,
			fSlopeYZ,fYintYZ) ) {
	std::cout << (*FiberItr).first << "Hit!" << std::endl;
	fTrueMod2[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod2[(*FiberItr).first] = 0;
      }
    }
    
    for ( FiberItr = Mod3Loc.begin(); FiberItr != Mod3Loc.end(); FiberItr++ ) {
      if ( Intersection((*FiberItr).second.first,(*FiberItr).second.second,
			fSlopeXZ,fYintXZ) ) {
	std::cout << (*FiberItr).first << " Hit!" << std::endl;
	fTrueMod3[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod3[(*FiberItr).first] = 0;
      }
    }


    fTree->Fill();
  } // For fNEvents loop
  fTree->Write();
  fFile->Close();
}


bool evg::Intersection(double FibI, double FibJ, double Slope, double Yint)
{
  double   LineLeftLocation_v = fSlopeYZ*(FibI - fScintWidth/2.0) + fYintYZ;
  double  LineRightLocation_v = fSlopeYZ*(FibI + fScintWidth/2.0) + fYintYZ;
  double            TopEdge_v = FibJ + fScintHeight/2.0;
  double         BottomEdge_v = FibJ - fScintHeight/2.0;
  double           LeftEdge_h = FibI - fScintWidth/2.0;
  double          RightEdge_h = FibI + fScintWidth/2.0;


  return false;
}



