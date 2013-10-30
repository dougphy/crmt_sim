
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy evd methods ________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#include <iostream>
#include "TH2I.h"
#include "TCanvas.h"
#include "evg.h"
#include "evd.h"

evd::evd() {}

evd::~evd() {}

void evd::InitData(std::string file_name, int event_number)
{
  
  fFile = new TFile(file_name.c_str());
  fTree = (TTree*)fFile->Get("SimulationTree");
  fTree->SetBranchAddress("SlopeXZ",&fSlopeXZ);
  fTree->SetBranchAddress("SlopeYZ",&fSlopeYZ);
  fTree->SetBranchAddress("YintXZ", &fYintXZ);
  fTree->SetBranchAddress("YintYZ", &fYintYZ);
  //fTree->SetBranchAddress("SimFibers",&fSimFibers);
  //fTree->SetBranchAddress("TrueFibers",&fTrueFibers);
  fSelectedEventID = event_number;
  
}

void evd::RawDumpSim()
{
  /*
  for ( int i = 0; i < 1024; i++ ) {
    fTree->GetEntry(fSelectedEventID);
    if ( fSimFibers[i] > 0 )
      std::cout << "Fiber " << i << " " << fSimFibers[i] << std::endl;
  }
  */
}

void evd::RawDumpTrue()
{
  /*
  for ( int i = 0; i < 1024; i++ ) {
    fTree->GetEntry(fSelectedEventID);
    if ( fTrueFibers[i] > 0 )
      std::cout << "Fiber " << i << " " << fTrueFibers[i] << std::endl;
  }
  */
}

void evd::DrawTrue(int argc, char *argv[])
{
  /*
  fApp = new TApplication("ex",&argc,argv);
  double half_x, half_y;
  half_x = 32*1.04;
  half_y = 3.08*8;
  TH2I *h = new TH2I("h",";x;y",64,-half_x,half_x,16,-half_y,half_y);
  h->Draw();
  fApp->Run();
  */
}
