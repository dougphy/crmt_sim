
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy evg methods ________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "evg.h"
#include "Line.h"
#include "Module.h"
#include "TRandom.h"
#include "TF1.h"

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
  fTree->Branch("AngleXZ_RF",  &fAngleXZ_RF, "AngleXZ_RF/D");
  fTree->Branch("AngleYZ_RF",  &fAngleYZ_RF, "AngleYZ_RF/D");
  fTree->Branch("SlopeXZ",     &fSlopeXZ,    "SlopeXZ/D");
  fTree->Branch("SlopeYZ",     &fSlopeYZ,    "SlopeYZ/D");
  fTree->Branch("YintXZ",      &fYintXZ,     "YintXZ/D");
  fTree->Branch("YintYZ",      &fYintYZ,     "YintYZ/D");
  fTree->Branch("Coincidence", &fCoincidence,"Conincidence/O");
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

evg::~evg()
{
  delete fTreeMod0;
  delete fTreeMod1;
  delete fTreeMod2;
  delete fTreeMod3;
  delete fTree;
  delete fFile;
}


// __________________________________________________________________

void evg::ReadParameters()
{
  std::ifstream ConfigFile;
  ConfigFile.open("Parameters.cfg");
  std::string label;
  double param;
  std::vector<double> param_vec;
  param_vec.reserve(20);
  while (ConfigFile >> label >> param)
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
  ConfigFile.close();
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
  std::cout << PI << std::endl;
  InitCoupleMap();
  InitFiberPixelPinPairs();
  gRandom->SetSeed(0);
  geo::Module *Mod0 = new geo::Module(0,fGap);
  geo::Module *Mod1 = new geo::Module(1,fGap);
  geo::Module *Mod2 = new geo::Module(2,fGap);
  geo::Module *Mod3 = new geo::Module(3,fGap);
  std::map<int, std::pair<double,double> > Mod0Loc = Mod0->GetMap();
  std::map<int, std::pair<double,double> > Mod1Loc = Mod1->GetMap();
  std::map<int, std::pair<double,double> > Mod2Loc = Mod2->GetMap();
  std::map<int, std::pair<double,double> > Mod3Loc = Mod3->GetMap();
  std::map<int, std::pair<double,double> >::iterator FiberItr;

  TF1 *cossq = new TF1("cossq","cos(x)*cos(x)",PI/2.,PI);
  for ( int ev = 0; ev < fNEvents; ev++ ) {
    geo::Line *Muon = new geo::Line();
    double InitialZ = 542 + fGap;
    fInitialZ = InitialZ;
    if ( fOriginUniformDist ) {
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
    Muon->SetInitialPos(fInitialX,fInitialY,fInitialZ);
    if ( fAngleZenithDefined )
      fTheta = fAngleZenithDefinedValue;
    else if ( fAngleZenithCosSq ) {
      fTheta = cossq->GetRandom();
    }
    else if ( fAngleZenithGaussian ) {
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
      fPhi = gRandom->Uniform(fAnglePolarUniformMin,fAnglePolarUniformMax);
    }
    else {
      std::cout << "Muon polar angle definition malfunction" << std::endl;
    }
    
    Muon->SetLinePropertiesFromPhiTheta(fPhi,fTheta);
    fAngleXZ = Muon->AngleXZ();
    fAngleYZ = Muon->AngleYZ();
    if ( fAngleXZ > 0 )
      fAngleXZ_RF = PI - fAngleXZ;
    if ( fAngleXZ < 0 )
      fAngleXZ_RF = fabs(fAngleXZ) - PI;
    if ( fAngleYZ > 0 )
      fAngleYZ_RF = PI - fAngleYZ;
    if ( fAngleYZ < 0 )
      fAngleYZ_RF = fabs(fAngleYZ) - PI;
    fTraj[0] = Muon->Tx();
    fTraj[1] = Muon->Ty();
    fTraj[2] = Muon->Tz();
    fSlopeXZ = Muon->SlopeXZ();
    fSlopeYZ = Muon->SlopeYZ();
    fYintXZ  = Muon->YintXZ();
    fYintYZ  = Muon->YintYZ();
    
    for ( FiberItr = Mod0Loc.begin(); FiberItr != Mod0Loc.end(); FiberItr++ ) {
      if ( Intersection2((*FiberItr).second.first,(*FiberItr).second.second,
			 Muon,false,fGap,0) ) {
	fTrueMod0[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod0[(*FiberItr).first] = 0;
      }
    }
    
    for ( FiberItr = Mod1Loc.begin(); FiberItr != Mod1Loc.end(); FiberItr++ ) {
      if ( Intersection2((*FiberItr).second.first,(*FiberItr).second.second,
			 Muon,true,fGap,1) ) {
	fTrueMod1[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod1[(*FiberItr).first] = 0;
      }
    }
    
    for ( FiberItr = Mod2Loc.begin(); FiberItr != Mod2Loc.end(); FiberItr++ ) {
      if ( Intersection2((*FiberItr).second.first,(*FiberItr).second.second,
			 Muon,false,fGap,2) ) {
	fTrueMod2[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod2[(*FiberItr).first] = 0;
      }
    }
    
    for ( FiberItr = Mod3Loc.begin(); FiberItr != Mod3Loc.end(); FiberItr++ ) {
      if ( Intersection2((*FiberItr).second.first,(*FiberItr).second.second,
			 Muon,true,fGap,3) ) {
	fTrueMod3[(*FiberItr).first] = 1;
      }
      else {
	fTrueMod3[(*FiberItr).first] = 0;
      }
    }

    int top_counter = 0;
    for ( int i = 0; i < 64; i++ )
      if ( fTrueMod0[i] == 1 )
	top_counter += 1;
    int bot_counter = 0;
    for ( int i = 192; i < 256; i++ )
      if ( fTrueMod3[i] == 1 )
	bot_counter += 1;
    
    bool yz_through_bottom_square = false;
    double horiz_check = (0.0 - Muon->YintYZ())/(Muon->SlopeYZ());
    if ( horiz_check > 0 && horiz_check < 640 )
      yz_through_bottom_square = true;

    fCoincidence = true;
    if ( bot_counter == 0 || top_counter == 0 || !yz_through_bottom_square ) {
      fCoincidence = false;
      for ( int i = 0; i < 256; i++ ) {
	fTrueMod0[i] = 0;
	fTrueMod1[i] = 0;
	fTrueMod2[i] = 0;
	fTrueMod3[i] = 0;
      }
    }
    
    Multiplex();
    SimHitsToPixels();
    PixelsToPins();
    fTreeMod0->Fill();
    fTreeMod1->Fill();
    fTreeMod2->Fill();
    fTreeMod3->Fill();
    fTree->Fill();
    
    ClearVecs();
  }
  fTree->Write();
  fTreeMod0->Write();
  fTreeMod1->Write();
  fTreeMod2->Write();
  fTreeMod3->Write();
  fFile->Close();
}

// __________________________________________________________________

bool evg::Intersection2(double FibI, double FibJ, geo::Line *function, 
			bool view_xz, double gap, int type) {

  double Slope, Yint, Slope_perp, Yint_perp;
  if ( view_xz ) {
    Slope      = function->SlopeXZ();
    Yint       = function->YintXZ();
    Slope_perp = function->SlopeYZ();
    Yint_perp  = function->YintYZ();
    
  }
  else { 
    Slope      = function->SlopeYZ();
    Yint       = function->YintYZ();
    Slope_perp = function->SlopeXZ();
    Yint_perp  = function->YintXZ();
  }
  
  double           LeftEdge_h = FibI - fScintWidth/2.0;
  double          RightEdge_h = FibI + fScintWidth/2.0;
  double   LineLeftLocation_v = Slope*LeftEdge_h + Yint;
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

// __________________________________________________________________

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
  for ( auto entry : fHitPixelsTop0 )
    for ( auto link : fPixelToPinTop )
      if ( link.second ==entry )
	fHitPinsTop0.push_back(link.first);

  for ( auto entry : fHitPixelsBot0 )
    for ( auto link : fPixelToPinBot )
      if ( link.second ==entry )
	fHitPinsBot0.push_back(link.first);

  for ( auto entry : fHitPixelsTop1 )
    for ( auto link : fPixelToPinTop )
      if ( link.second ==entry )
	fHitPinsTop1.push_back(link.first);

  for ( auto entry : fHitPixelsBot1 )
    for ( auto link : fPixelToPinBot )
      if ( link.second ==entry )
	fHitPinsBot1.push_back(link.first);

  for ( auto entry : fHitPixelsTop2 )
    for ( auto link : fPixelToPinTop )
      if ( link.second ==entry )
	fHitPinsTop2.push_back(link.first);

  for ( auto entry : fHitPixelsBot2 )
    for ( auto link : fPixelToPinBot )
      if ( link.second ==entry )
	fHitPinsBot2.push_back(link.first);

  for ( auto entry : fHitPixelsTop3 )
    for ( auto link : fPixelToPinTop )
      if ( link.second ==entry )
	fHitPinsTop3.push_back(link.first);

  for ( auto entry : fHitPixelsBot3 )
    for ( auto link : fPixelToPinBot )
      if ( link.second ==entry )
	fHitPinsBot3.push_back(link.first);
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
