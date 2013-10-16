#include <map>
#include <vector>
#include "evg.h"

evg::evg() {}  // Default constructor -- not used

evg::evg(std::string file_name, int n_events)
{
  fNEvents  = n_events;
  fFile     = new TFile(file_name.c_str(),"RECREATE");
  fTree     = new TTree("SimulationTree","SimulationTree");
  fTree->Branch("EventID",   &fEventID,  "EventID/I");
  fTree->Branch("ThetaXZ",   &fThetaXZ,  "ThetaXZ/D");
  fTree->Branch("ThetaYZ",   &fThetaYZ,  "ThetaYZ/D");
  fTree->Branch("TrueFibers",fTrueFibers,"TrueFibers[1024]/I");
  fTree->Branch("SimFibers",fSimFibers,  "SimFibers[1024]/I");
}

evg::~evg() {} // Default destructor


void evg::SaveFile()
{
  fTree->Write();
  fFile->Close();
}
