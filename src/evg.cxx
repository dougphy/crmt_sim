
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
  std::string name = "output/"+file_name;
  fNEvents  = n_events;
  fFile     = new TFile(name.c_str(),"RECREATE");
  fTree     = new TTree("SimulationTree","SimulationTree");
  fTree->Branch("EventID",    &fEventID,    "EventID/I");
  fTree->Branch("Gap",        &fGap,        "Gap/D");
  fTree->Branch("InitialX",   &fInitialX,   "InitialX/D");
  fTree->Branch("InitialY",   &fInitialY,   "InitialY/D");
  fTree->Branch("InitialZ",   &fInitialZ,   "InitialZ/D");
  fTree->Branch("Phi",        &fPhi,        "Phi/D");
  fTree->Branch("Theta",      &fTheta,      "Theta/D");
  fTree->Branch("AngleXZ",    &fAngleXZ,    "AngleXZ/D");
  fTree->Branch("AngleYZ",    &fAngleYZ,    "AngleYZ/D");
  fTree->Branch("SlopeXZ",    &fSlopeXZ,    "SlopeXZ/D");
  fTree->Branch("SlopeYZ",    &fSlopeYZ,    "SlopeYZ/D");
  fTree->Branch("YintXZ",     &fYintXZ,     "YintXZ/D");
  fTree->Branch("YintYZ",     &fYintYZ,     "YintYZ/D");
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
  if (param_vec[4] == 0)   { fAngleZenithGaussian = false; }
  else                     { fAngleZenithGaussian = true;  }
  if (param_vec[5] == 0)   { fAnglePolarDefined   = false; }
  else                     { fAnglePolarDefined   = true;  }
  if (param_vec[6] == 0)   { fAnglePolarUniform   = false; }
  else                     { fAnglePolarUniform   = true;  }
  fOriginUniformDistMin      = param_vec[7];
  fOriginUniformDistMax      = param_vec[8];
  fOriginDefinedX            = param_vec[9];
  fOriginDefinedY            = param_vec[10];
  fAngleZenithDefinedValue   = param_vec[11]*PI/180.;
  fAngleZenithGaussianCenter = param_vec[12]*PI/180.;
  fAngleZenithGaussianSigma  = param_vec[13]*PI/180.;
  fAnglePolarDefinedValue    = param_vec[14]*PI/180.;
  fAnglePolarUniformMin      = param_vec[15]*PI/180.;
  fAnglePolarUniformMax      = param_vec[16]*PI/180.;
  fGap                       = param_vec[17];
}

// __________________________________________________________________

void evg::CheckParameters()
{
  std::cout << "fOriginUniformDist         = " << fOriginUniformDist << "\n";
  std::cout << "fOriginDefined             = " << fOriginDefined << "\n";
  std::cout << "fAngleZenithDefined        = " << fAngleZenithDefined << "\n";
  std::cout << "fAngleZenithCosSq          = " << fAngleZenithCosSq << "\n";
  std::cout << "fAngleZenithGaussian       = " << fAngleZenithGaussian << "\n";
  std::cout << "fAnglePolarDefined         = " << fAnglePolarDefined << "\n";
  std::cout << "fAnglePolarUniform         = " << fAnglePolarUniform << "\n";
  std::cout << "fOriginUniformDistMin      = " << fOriginUniformDistMin << "\n";
  std::cout << "fOriginUniformDistMax      = " << fOriginUniformDistMax << "\n";
  std::cout << "fOriginDefinedX            = " << fOriginDefinedX << "\n";
  std::cout << "fOriginDefinedY            = " << fOriginDefinedY << "\n";
  std::cout << "fAngleZenithDefinedValue   = " << fAngleZenithDefinedValue << "\n";
  std::cout << "fAngleZenithGaussianCenter = " << fAngleZenithGaussianCenter << "\n";
  std::cout << "fAngleZenithGaussianSigma  = " << fAngleZenithGaussianSigma << "\n";
  std::cout << "fAnglePolarDefinedValue    = " << fAnglePolarDefinedValue << "\n";
  std::cout << "fAnglePolarUniformMin      = " << fAnglePolarUniformMin << "\n";
  std::cout << "fAnglePolarUniformMax      = " << fAnglePolarUniformMax << "\n";
  std::cout << "fGap                       = " << fGap << "\n";
}

// __________________________________________________________________

void evg::RunEvents()
{
  InitCoupleMap();
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
    else if ( fAngleZenithGaussian ) {
      gRandom->SetSeed(0);
      fTheta = fabs(gRandom->Gaus(fAngleZenithGaussianCenter,
				  fAngleZenithGaussianSigma));
    }
    else {
      std::cout << "Muon zenith angle definition malfunction." << std::endl;
    }
    if ( fAnglePolarDefined ) {
      fPhi = fAnglePolarDefinedValue;
    }
    else if ( fAnglePolarUniform ) {
      gRandom->SetSeed(0);
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
	fTrueMod0[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod0[(*FiberItr).first] = 0;
      }
    }
    
    for ( FiberItr = Mod1Loc.begin(); FiberItr != Mod1Loc.end(); FiberItr++ ) {
      if ( Intersection((*FiberItr).second.first,(*FiberItr).second.second,
			fSlopeXZ,fYintXZ) ) {
	fTrueMod1[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod1[(*FiberItr).first] = 0;
      }
    }

    for ( FiberItr = Mod2Loc.begin(); FiberItr != Mod2Loc.end(); FiberItr++ ) {
      if ( Intersection((*FiberItr).second.first,(*FiberItr).second.second,
			fSlopeYZ,fYintYZ) ) {
	fTrueMod2[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod2[(*FiberItr).first] = 0;
      }
    }
    
    for ( FiberItr = Mod3Loc.begin(); FiberItr != Mod3Loc.end(); FiberItr++ ) {
      if ( Intersection((*FiberItr).second.first,(*FiberItr).second.second,
			fSlopeXZ,fYintXZ) ) {
	fTrueMod3[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod3[(*FiberItr).first] = 0;
      }
    }

    Multiplex();

    fTree->Fill();
  } // For fNEvents loop
  fTree->Write();
  fFile->Close();
  }


bool evg::Intersection(double FibI, double FibJ, double Slope, double Yint)
{
  double           LeftEdge_h = FibI - fScintWidth/2.0;
  double          RightEdge_h = FibI + fScintWidth/2.0;
  double   LineLeftLocation_v = Slope*LeftEdge_h  + Yint;
  double  LineRightLocation_v = Slope*RightEdge_h + Yint;
  double            TopEdge_v = FibJ + fScintHeight/2.0;
  double         BottomEdge_v = FibJ - fScintHeight/2.0;
  double           LineXTop_h = (TopEdge_v - Yint)/Slope;
  double           LineXBot_h = (BottomEdge_v - Yint)/Slope;
  
  if ( (LineLeftLocation_v < TopEdge_v) && (LineLeftLocation_v > BottomEdge_v) )
    return true;
  if ( (LineRightLocation_v < TopEdge_v) && (LineRightLocation_v > BottomEdge_v) )
    return true;
  if ( (LineXTop_h < RightEdge_h) && (LineXTop_h > LeftEdge_h) )
    return true;
  if ( (LineXBot_h < RightEdge_h) && (LineXBot_h > LeftEdge_h) )
    return true;
  return false;
}

void evg::InitCoupleMap()
{
  std::ifstream CouplingFile;
  CouplingFile.open("config/coupled_fibers.dat");
  int f0, f1, f2, f3, f4, f5, f6, f7;
  int counter = 0;
  while ( CouplingFile >> f0 >> f1 >> f2
	  >> f3 >> f4 >> f5 >> f6 >> f7 ) {
    fFiberCouplingMap[counter].push_back(f0);
    fFiberCouplingMap[counter].push_back(f1);
    fFiberCouplingMap[counter].push_back(f2);
    fFiberCouplingMap[counter].push_back(f3);
    fFiberCouplingMap[counter].push_back(f4);
    fFiberCouplingMap[counter].push_back(f5);
    fFiberCouplingMap[counter].push_back(f6);
    fFiberCouplingMap[counter].push_back(f7);
    counter++;
  }

}

void evg::Multiplex()
{
  std::vector<int> Hits0;
  std::vector<int> Hits1;
  std::vector<int> Hits2;
  std::vector<int> Hits3;
  
  for ( int i = 0; i < 256; i++ ) {
    fSimMod0[i] = 0;
    fSimMod1[i] = 0;
    fSimMod2[i] = 0;
    fSimMod3[i] = 0;
  }

  for ( int i = 0; i < 256; i++ ) {
    if ( fTrueMod0[i] == 1 )
      Hits0.push_back(i);
  }
  for ( int i = 0; i < 256; i++ ) {
    if ( fTrueMod1[i] == 1 )
      Hits1.push_back(i);
  }
  for ( int i = 0; i < 256; i++ ) {
    if ( fTrueMod2[i] == 1 )
      Hits2.push_back(i);
  }
  for ( int i = 0; i < 256; i++ ) {
    if ( fTrueMod3[i] == 1 )
      Hits3.push_back(i);
  }

  for ( auto iMap : fFiberCouplingMap ) {
    for ( auto hit : Hits0 )
      if ( std::find(iMap.second.begin(),iMap.second.end(),hit) != iMap.second.end() )
	for ( int i = 0; i < iMap.second.size(); i++ )
	  fSimMod0[iMap.second[i]] = 1;
    for ( auto hit : Hits1 )
      if ( std::find(iMap.second.begin(),iMap.second.end(),hit) != iMap.second.end() )
	for ( int i = 0; i < iMap.second.size(); i++ )
	  fSimMod1[iMap.second[i]] = 1;
    for ( auto hit : Hits2 )
      if ( std::find(iMap.second.begin(),iMap.second.end(),hit) != iMap.second.end() )
	for ( int i = 0; i < iMap.second.size(); i++ )
	  fSimMod2[iMap.second[i]] = 1;
    for ( auto hit : Hits3 )
      if ( std::find(iMap.second.begin(),iMap.second.end(),hit) != iMap.second.end() )
	for ( int i = 0; i < iMap.second.size(); i++ )
	  fSimMod3[iMap.second[i]] = 1;
  }
  
}
