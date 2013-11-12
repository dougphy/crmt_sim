
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
#include <algorithm>
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
  fTree->Branch("EventID",     &fEventID,    "EventID/I");
  fTree->Branch("Gap",         &fGap,        "Gap/D");
  fTree->Branch("InitialX",    &fInitialX,   "InitialX/D");
  fTree->Branch("InitialY",    &fInitialY,   "InitialY/D");
  fTree->Branch("InitialZ",    &fInitialZ,   "InitialZ/D");
  fTree->Branch("Phi",         &fPhi,        "Phi/D");
  fTree->Branch("Theta",       &fTheta,      "Theta/D");
  fTree->Branch("AngleXZ",     &fAngleXZ,    "AngleXZ/D");
  fTree->Branch("AngleYZ",     &fAngleYZ,    "AngleYZ/D");
  fTree->Branch("SlopeXZ",     &fSlopeXZ,    "SlopeXZ/D");
  fTree->Branch("SlopeYZ",     &fSlopeYZ,    "SlopeYZ/D");
  fTree->Branch("YintXZ",      &fYintXZ,     "YintXZ/D");
  fTree->Branch("YintYZ",      &fYintYZ,     "YintYZ/D");
  fTree->Branch("Traj",         fTraj,       "Traj[3]/D");
  fTree->Branch("TrueMod0",     fTrueMod0,   "TrueMod0[256]/I");
  fTree->Branch("TrueMod1",     fTrueMod1,   "TrueMod1[256]/I");
  fTree->Branch("TrueMod2",     fTrueMod2,   "TrueMod2[256]/I");
  fTree->Branch("TrueMod3",     fTrueMod3,   "TrueMod3[256]/I");
  fTree->Branch("SimMod0",      fSimMod0,    "SimMod0[256]/I");
  fTree->Branch("SimMod1",      fSimMod1,    "SimMod1[256]/I");
  fTree->Branch("SimMod2",      fSimMod2,    "SimMod2[256]/I");
  fTree->Branch("SimMod3",      fSimMod3,    "SimMod3[256]/I");

  fTreeMod0 = new TTree("Mod0Tree","Mod0Tree");
  fTreeMod1 = new TTree("Mod1Tree","Mod1Tree");
  fTreeMod2 = new TTree("Mod2Tree","Mod2Tree");
  fTreeMod3 = new TTree("Mod3Tree","Mod3Tree");

  fTreeMod0->Branch("HitPixelsTop0",&fHitPixelsTop0);
  fTreeMod0->Branch("HitPinsTop0",  &fHitPinsTop0);
  fTreeMod0->Branch("HitPixelsBot0",&fHitPixelsBot0);
  fTreeMod0->Branch("HitPinsBot0",  &fHitPinsBot0);

  fTreeMod1->Branch("HitPixelsTop1",&fHitPixelsTop1);
  fTreeMod1->Branch("HitPinsTop1",  &fHitPinsTop1);
  fTreeMod1->Branch("HitPixelsBot1",&fHitPixelsBot1);
  fTreeMod1->Branch("HitPinsBot1",  &fHitPinsBot1);

  fTreeMod2->Branch("HitPixelsTop2",&fHitPixelsTop2);
  fTreeMod2->Branch("HitPinsTop2",  &fHitPinsTop2);
  fTreeMod2->Branch("HitPixelsBot2",&fHitPixelsBot2);
  fTreeMod2->Branch("HitPinsBot2",  &fHitPinsBot2);

  fTreeMod3->Branch("HitPixelsTop3",&fHitPixelsTop3);
  fTreeMod3->Branch("HitPinsTop3",  &fHitPinsTop3);
  fTreeMod3->Branch("HitPixelsBot3",&fHitPixelsBot3);
  fTreeMod3->Branch("HitPinsBot3",  &fHitPinsBot3);

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
  if (param_vec[0] == 0)     { fOriginUniformDist   = false; }
  else                       { fOriginUniformDist   = true;  }
  if (param_vec[1] == 0)     { fOriginDefined       = false; }
  else                       { fOriginDefined       = true;  }
  if (param_vec[2] == 0)     { fAngleZenithDefined  = false; }
  else                       { fAngleZenithDefined  = true;  }
  if (param_vec[3] == 0)     { fAngleZenithCosSq    = false; }
  else                       { fAngleZenithCosSq    = true;  }
  if (param_vec[4] == 0)     { fAngleZenithGaussian = false; }
  else                       { fAngleZenithGaussian = true;  }
  if (param_vec[5] == 0)     { fAnglePolarDefined   = false; }
  else                       { fAnglePolarDefined   = true;  }
  if (param_vec[6] == 0)     { fAnglePolarUniform   = false; }
  else                       { fAnglePolarUniform   = true;  }
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
  InitFiberPixelPinPairs();
  geo::Module *Mod0 = new geo::Module(0,fGap);
  geo::Module *Mod1 = new geo::Module(1,fGap);
  geo::Module *Mod2 = new geo::Module(2,fGap);
  geo::Module *Mod3 = new geo::Module(3,fGap);
  std::map<int, std::pair<double,double> > Mod0Loc = Mod0->GetMap();
  std::map<int, std::pair<double,double> > Mod1Loc = Mod1->GetMap();
  std::map<int, std::pair<double,double> > Mod2Loc = Mod2->GetMap();
  std::map<int, std::pair<double,double> > Mod3Loc = Mod3->GetMap();
  std::map<int, std::pair<double,double> >::iterator FiberItr;

  double InitialZ = 330 + fGap;
  for ( int i = 0; i < fNEvents; i++ ) {
    geo::Line *Mu = new geo::Line();
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
    fTraj[0] = Mu->Tx();
    fTraj[1] = Mu->Ty();
    fTraj[2] = Mu->Tz();
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
    SimHitsToPixels();

    fTreeMod0->Fill();
    fTreeMod1->Fill();
    fTreeMod2->Fill();
    fTreeMod3->Fill();
    
    fTree->Fill();
    
    ClearVecs();
  } // For fNEvents loop
  fTree->Write();
  fTreeMod0->Write();
  fTreeMod1->Write();
  fTreeMod2->Write();
  fTreeMod3->Write();
  fFile->Close();
}

// __________________________________________________________________

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

// __________________________________________________________________

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

// __________________________________________________________________

void evg::InitFiberPixelPinPairs()
{
  std::ifstream ftp_top;
  std::ifstream ftp_bot;
  std::ifstream ptp_top;
  std::ifstream ptp_bot;

  std::ifstream in_file;
  int left, right;
  in_file.open("config/remap_fibers_top.dat");
  while (in_file >> left >> right)
    fRemapFiberTop.push_back(std::make_pair(left,right));
  in_file.close();
  in_file.open("config/remap_fibers_bot.dat");
  while (in_file >> left >> right)
    fRemapFiberBot.push_back(std::make_pair(left,right));
  in_file.close();
  in_file.open("config/pixel_to_pin_top.dat");
  while (in_file >> left >> right)
    fPixelToPinTop.push_back(std::make_pair(left,right));
  in_file.close();
  in_file.open("config/pixel_to_pin_bot.dat");
  while (in_file >> left >> right)
    fPixelToPinBot.push_back(std::make_pair(left,right));
}

// __________________________________________________________________

void evg::SimHitsToPixels()
{
  for ( int i = 0; i < 256; i++ ) {
    if ( i < 128) {
      if ( fSimMod0[i] == 1 )
	for ( auto entry : fRemapFiberTop )
	  if ( entry.first == i )
	    fHitPixelsTop0.push_back(entry.second);
    }    
    else {
      if ( fSimMod0[i] == 1 )
	for ( auto entry : fRemapFiberBot )
	  if ( entry.first == i )
	    fHitPixelsBot0.push_back(entry.second);
    }      
  }
 
  for ( int i = 0; i < 256; i++ ) {
    if ( i < 128) {
      if ( fSimMod1[i] == 1 )
	for ( auto entry : fRemapFiberTop )
	  if ( entry.first == i )
	    fHitPixelsTop1.push_back(entry.second);
    }    
    else {
      if ( fSimMod1[i] == 1 )
	for ( auto entry : fRemapFiberBot )
	  if ( entry.first == i )
	    fHitPixelsBot1.push_back(entry.second);
    }      
  }

  for ( int i = 0; i < 256; i++ ) {
    if ( i < 128) {
      if ( fSimMod2[i] == 1 )
	for ( auto entry : fRemapFiberTop )
	  if ( entry.first == i )
	    fHitPixelsTop2.push_back(entry.second);
    }    
    else {
      if ( fSimMod2[i] == 1 )
	for ( auto entry : fRemapFiberBot )
	  if ( entry.first == i )
	    fHitPixelsBot2.push_back(entry.second);
    }      
  }

  for ( int i = 0; i < 256; i++ ) {
    if ( i < 128) {
      if ( fSimMod3[i] == 1 )
	for ( auto entry : fRemapFiberTop )
	  if ( entry.first == i )
	    fHitPixelsTop3.push_back(entry.second);
    }    
    else {
      if ( fSimMod3[i] == 1 )
	for ( auto entry : fRemapFiberBot )
	  if ( entry.first == i )
	    fHitPixelsBot3.push_back(entry.second);
    }      
  }

 
}
// __________________________________________________________________

void evg::PixelsToPins()
{

}

void evg::ClearVecs()
{
  fHitPixelsTop0.clear();
  fHitPixelsBot0.clear();
  fHitPixelsTop1.clear();
  fHitPixelsBot1.clear();
  fHitPixelsTop2.clear();
  fHitPixelsBot2.clear();
  fHitPixelsTop3.clear();
  fHitPixelsBot3.clear();

  fHitPinsTop0.clear();
  fHitPinsBot0.clear();
  fHitPinsTop1.clear();
  fHitPinsBot1.clear();
  fHitPinsTop2.clear();
  fHitPinsBot2.clear();
  fHitPinsTop3.clear();
  fHitPinsBot3.clear();
}
