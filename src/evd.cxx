
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy evd methods ________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#include <iostream>
#include "TH2I.h"
#include "TCanvas.h"
#include "evd.h"
#include "Module.h"

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

