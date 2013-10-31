
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
#include "TMultiGraph.h"

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
  TGraphErrors *Graph0 = new TGraphErrors();
  Graph0->SetMarkerStyle(8);
  TGraphErrors *Graph1 = new TGraphErrors();
  Graph1->SetMarkerStyle(8);
  TGraphErrors *Graph2 = new TGraphErrors();
  Graph2->SetMarkerStyle(8);
  TGraphErrors *Graph3 = new TGraphErrors();
  Graph3->SetMarkerStyle(8);

  int counter = 0;
  for ( int i = 0; i < 256; i++ ) {
    if ( fTrueMod0[i] == 1 ) {
      Graph0->SetPoint(counter,Mod0[i].first,Mod0[i].second);
      counter++;
    }
    else {
      continue;
    }
  }
  counter = 0;
  for ( int i = 0; i < 256; i++ ) {
    if ( fTrueMod1[i] == 1 ) {
      Graph1->SetPoint(counter,Mod1[i].first,Mod1[i].second);
      counter++;
    }
    else {
      continue;
    }
  }
  counter = 0;
  for ( int i = 0; i < 256; i++ ) {
    if ( fTrueMod2[i] == 1 ) {
      Graph2->SetPoint(counter,Mod2[i].first,Mod2[i].second);
      counter++;
    }
    else {
      continue;
    }
  }
  counter = 0;
  for ( int i = 0; i < 256; i++ ) {
    if ( fTrueMod3[i] == 1 ) {
      Graph3->SetPoint(counter,Mod3[i].first,Mod3[i].second);
      counter++;
    }
    else {
      continue;
    }
  }

  TMultiGraph *TMGXZ = new TMultiGraph();
  TMGXZ->Add(Graph1);
  TMGXZ->Add(Graph3);
  TMultiGraph *TMGYZ = new TMultiGraph();
  TMGYZ->Add(Graph0);
  TMGYZ->Add(Graph2);
  TF1 *LineXZ = new TF1("LineXZ","pol1",0,660);
  TF1 *LineYZ = new TF1("LineYZ","pol1",0,660);
  LineXZ->SetParameters(fYintXZ,fSlopeXZ);
  LineYZ->SetParameters(fYintYZ,fSlopeYZ);

  fApp = new TApplication("app",&argc,argv);
  TCanvas *can = new TCanvas();
  can->Divide(2,1);

  can->cd(1);
  TMGXZ->Draw("AP");
  LineXZ->Draw("same");

  can->cd(2);
  TMGYZ->Draw("AP");
  LineYZ->Draw("same");

  fApp->Run();

}
