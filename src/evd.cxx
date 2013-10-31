
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy evd methods ________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#include <iostream>
#include "TGraphErrors.h"
#include "TF1.h"
#include "TCanvas.h"
#include "evd.h"
#include "Module.h"

evd::evd() {}

evd::~evd() {}

void evd::InitFile(std::string file_name, int event_number)
{
  fFile = new TFile(file_name.c_str());
  fTree = (TTree*)fFile->Get("SimulationTree");
  fTree->SetBranchAddress("SlopeXZ",  &fSlopeXZ);
  fTree->SetBranchAddress("SlopeYZ",  &fSlopeYZ);
  fTree->SetBranchAddress("YintXZ",   &fYintXZ);
  fTree->SetBranchAddress("YintYZ",   &fYintYZ);
  fTree->SetBranchAddress("TrueMod0",  fTrueMod0);
  fTree->SetBranchAddress("TrueMod1",  fTrueMod1);
  fTree->SetBranchAddress("TrueMod2",  fTrueMod2);
  fTree->SetBranchAddress("TrueMod3",  fTrueMod3);
  fTree->SetBranchAddress("SimMod0",   fSimMod0);
  fTree->SetBranchAddress("SimMod1",   fSimMod1);
  fTree->SetBranchAddress("SimMod2",   fSimMod2);
  fTree->SetBranchAddress("SimMod3",   fSimMod3);
  fTree->SetBranchAddress("Gap",      &fGap);
  fSelectedEventID = event_number;
}

void evd::RawDumpTrue()
{
  fTree->GetEntry(fSelectedEventID);
  for ( int i = 0; i < 256; i++ ) 
    std::cout << "Module 0 -- " << i << " " << fTrueMod0[i] << std::endl;
  for ( int i = 0; i < 256; i++ ) 
    std::cout << "Module 1 -- " << i << " " << fTrueMod1[i] << std::endl;
  for ( int i = 0; i < 256; i++ ) 
    std::cout << "Module 2 -- " << i << " " << fTrueMod2[i] << std::endl;
  for ( int i = 0; i < 256; i++ ) 
    std::cout << "Module 3 -- " << i << " " << fTrueMod3[i] << std::endl;
}

void evd::RawDumpSim()
{
  fTree->GetEntry(fSelectedEventID);
  for ( int i = 0; i < 256; i++ ) 
    std::cout << "Module 0 -- " << i << " " << fSimMod0[i] << std::endl;
  for ( int i = 0; i < 256; i++ ) 
    std::cout << "Module 1 -- " << i << " " << fSimMod1[i] << std::endl;
  for ( int i = 0; i < 256; i++ ) 
    std::cout << "Module 2 -- " << i << " " << fSimMod2[i] << std::endl;
  for ( int i = 0; i < 256; i++ ) 
    std::cout << "Module 3 -- " << i << " " << fSimMod3[i] << std::endl;
}

void evd::DrawTrue(int argc, char *argv[])
{
  fTree->GetEntry(fSelectedEventID);
  double gap = fGap;
  Module *mod0 = new Module(0,gap);
  Module *mod1 = new Module(1,gap);
  Module *mod2 = new Module(2,gap);
  Module *mod3 = new Module(3,gap);
  std::map<int, std::pair<double,double> > Mod0 = mod0->GetMap();
  std::map<int, std::pair<double,double> > Mod1 = mod1->GetMap();
  std::map<int, std::pair<double,double> > Mod2 = mod2->GetMap();
  std::map<int, std::pair<double,double> > Mod3 = mod3->GetMap();
}
