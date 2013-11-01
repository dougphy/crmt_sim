
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy evd methods ________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#include <iostream>
#include <sstream>
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "evd.h"
#include "Module.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TPaveText.h"
#include "TStyle.h"
#include "TPad.h"

evd::evd() {}

evd::~evd() {}

void evd::InitFile(std::string file_name, int event_number)
{
  fFile = new TFile(file_name.c_str());
  fTree = (TTree*)fFile->Get("SimulationTree");
  fTree->SetBranchAddress("AngleXZ",  &fAngleXZ);
  fTree->SetBranchAddress("AngleYZ",  &fAngleYZ);
  fTree->SetBranchAddress("Phi",      &fPhi);
  fTree->SetBranchAddress("Theta",    &fTheta);
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
  TGraph *Graph0 = new TGraph();
  Graph0->SetMarkerColor(kBlue);
  Graph0->SetMarkerStyle(8);
  TGraph *Graph1 = new TGraph();
  Graph1->SetMarkerStyle(8);
  Graph1->SetMarkerColor(kBlue);
  TGraph *Graph2 = new TGraph();
  Graph2->SetMarkerStyle(8);
  Graph2->SetMarkerColor(kBlue);
  TGraph *Graph3 = new TGraph();
  Graph3->SetMarkerStyle(8);
  Graph3->SetMarkerColor(kBlue);

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
  
  TGraph *All0 = new TGraph(); All0->SetMarkerStyle(7);
  TGraph *All1 = new TGraph(); All1->SetMarkerStyle(7);
  TGraph *All2 = new TGraph(); All2->SetMarkerStyle(7);
  TGraph *All3 = new TGraph(); All3->SetMarkerStyle(7);
  
  counter = 0;
  for ( auto fib : Mod0 ) {
    All0->SetPoint(counter,fib.second.first,fib.second.second);
    counter++;
  }
  counter = 0;
  for ( auto fib : Mod1 ) {
    All1->SetPoint(counter,fib.second.first,fib.second.second);
    counter++;
  }
  counter = 0;
  for ( auto fib : Mod2 ) {
    All2->SetPoint(counter,fib.second.first,fib.second.second);
    counter++;
  }
  counter = 0;
  for ( auto fib : Mod3 ) {
    All3->SetPoint(counter,fib.second.first,fib.second.second);
    counter++;
  }
  
  TGraph *HolderXZ = new TGraph();
  TGraph *HolderYZ = new TGraph();
  HolderXZ->SetMarkerColor(kWhite);
  HolderYZ->SetMarkerColor(kWhite);
  HolderXZ->SetPoint(0,0,0);
  HolderXZ->SetPoint(1,0,550+fGap);
  HolderYZ->SetPoint(0,0,0);
  HolderYZ->SetPoint(1,0,550+fGap);

  TMultiGraph *TMGXZ = new TMultiGraph();
  TMGXZ->Add(All1);
  TMGXZ->Add(All3);
  TMGXZ->Add(Graph1);
  TMGXZ->Add(Graph3);
  TMGXZ->Add(HolderXZ);
  TMultiGraph *TMGYZ = new TMultiGraph();
  TMGYZ->Add(All0);
  TMGYZ->Add(All2);
  TMGYZ->Add(Graph0);
  TMGYZ->Add(Graph2);
  TMGYZ->Add(HolderYZ);
  TF1 *LineXZ = new TF1("LineXZ","pol1",0,660);
  LineXZ->SetParameters(fYintXZ,fSlopeXZ);
  LineXZ->SetLineStyle(2);
  LineXZ->SetLineWidth(1);
  TF1 *LineYZ = new TF1("LineYZ","pol1",0,660);
  LineYZ->SetParameters(fYintYZ,fSlopeYZ);
  LineYZ->SetLineStyle(2);
  LineYZ->SetLineWidth(1);

  std::string s_EventID = MakeString((double)fSelectedEventID);
  std::string s_AngleXZ = MakeString(fAngleXZ*180/3.14159);
  std::string s_AngleYZ = MakeString(fAngleYZ*180/3.14159);

  gStyle->SetFrameLineWidth(2);
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadRightMargin(0.1);

  char tEID[30];
  char tGap[30];
  char tSlopeXZ[30];
  char tSlopeYZ[30];
  char tAngleXZ[30];
  char tAngleYZ[30];
  char tPhi[30];
  char tTheta[30];
  
  sprintf(tEID,     "Event %d",                 fSelectedEventID);
  sprintf(tGap,     "Gap = %3.3f cm",                fGap);
  sprintf(tSlopeXZ, "Slope XZ = %3.3f",         fSlopeXZ);
  sprintf(tSlopeYZ, "Slope YZ = %3.3f",         fSlopeYZ);
  sprintf(tAngleXZ, "Angle XZ = %3.3f degrees", fAngleXZ*180/3.14159);
  sprintf(tAngleYZ, "Angle YZ = %3.3f degrees", fAngleYZ*180/3.14159);
  sprintf(tPhi,     "Phi = %3.3f degrees",      fPhi*180/3.14159);
  sprintf(tTheta,   "Theta = %3.3f degrees",    fTheta*180/3.14159);
  
  const char *tEIDP     = tEID;  
  const char *tGapP     = tGap;
  const char *tSlopeXZP = tSlopeXZ;
  const char *tSlopeYZP = tSlopeYZ;
  const char *tAngleXZP = tAngleXZ;
  const char *tAngleYZP = tAngleYZ;
  const char *tPhiP     = tPhi;
  const char *tThetaP   = tTheta;
  
  TPaveText *EventTitle = new TPaveText(0.0,0.2,1,0.9,"brNDC");
  EventTitle->SetTextFont(63);
  EventTitle->SetTextSize(18);
  EventTitle->SetFillColor(0);
  EventTitle->SetBorderSize(0);
  EventTitle->AddText("True Event Display");
  EventTitle->AddText(tEIDP);
  EventTitle->AddText(tGapP);
  EventTitle->AddText(tSlopeXZP);
  EventTitle->AddText(tSlopeYZP);
  EventTitle->AddText(tAngleXZP);
  EventTitle->AddText(tAngleYZP);
  EventTitle->AddText(tPhiP);
  EventTitle->AddText(tThetaP);
  
  TPaveText *XZ_title = new TPaveText(0.36,.93,.7,.95,"brNDC");
  XZ_title->SetTextSize(22);
  XZ_title->SetTextFont(63);
  XZ_title->SetBorderSize(0);
  XZ_title->SetFillColor(0);
  XZ_title->AddText("XZ plane");
  TPaveText *YZ_title = new TPaveText(0.36,.93,.7,.95,"brNDC");
  YZ_title->SetTextSize(22);
  YZ_title->SetTextFont(63);
  YZ_title->SetBorderSize(0);
  YZ_title->SetFillColor(0);
  YZ_title->AddText("YZ plane");

  fApp = new TApplication("app",&argc,argv);
  TCanvas *can = new TCanvas("evd","evd",1300,800);

  TPad *padXZ = new TPad("padXZ","padXZ",.2,0.,.6,1.);
  TPad *padYZ = new TPad("padYZ","patYZ",.6,0.,1.,1.);
  TPad *padT  = new TPad("padT", "padT",.0,.3,.20,.9);

  padXZ->cd();
  TMGXZ->Draw("AP");
  LineXZ->Draw("same");
  XZ_title->Draw("same");

  padYZ->cd();
  TMGYZ->Draw("AP");
  LineYZ->Draw("same");
  YZ_title->Draw("same");

  padT->cd();
  EventTitle->Draw();

  can->cd();
  padXZ->Draw();
  padYZ->Draw();
  padT->Draw();
  fApp->Run();


}

void evd::DrawSim(int argc, char *argv[])
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
  TGraph *Graph0 = new TGraph();
  Graph0->SetMarkerColor(kBlue);
  Graph0->SetMarkerStyle(8);
  TGraph *Graph1 = new TGraph();
  Graph1->SetMarkerStyle(8);
  Graph1->SetMarkerColor(kBlue);
  TGraph *Graph2 = new TGraph();
  Graph2->SetMarkerStyle(8);
  Graph2->SetMarkerColor(kBlue);
  TGraph *Graph3 = new TGraph();
  Graph3->SetMarkerStyle(8);
  Graph3->SetMarkerColor(kBlue);

  int counter = 0;
  for ( int i = 0; i < 256; i++ ) {
    if ( fSimMod0[i] == 1 ) {
      Graph0->SetPoint(counter,Mod0[i].first,Mod0[i].second);
      counter++;
    }
    else {
      continue;
    }
  }
  counter = 0;
  for ( int i = 0; i < 256; i++ ) {
    if ( fSimMod1[i] == 1 ) {
      Graph1->SetPoint(counter,Mod1[i].first,Mod1[i].second);
      counter++;
    }
    else {
      continue;
    }
  }
  counter = 0;
  for ( int i = 0; i < 256; i++ ) {
    if ( fSimMod2[i] == 1 ) {
      Graph2->SetPoint(counter,Mod2[i].first,Mod2[i].second);
      counter++;
    }
    else {
      continue;
    }
  }
  counter = 0;
  for ( int i = 0; i < 256; i++ ) {
    if ( fSimMod3[i] == 1 ) {
      Graph3->SetPoint(counter,Mod3[i].first,Mod3[i].second);
      counter++;
    }
    else {
      continue;
    }
  }
  
  TGraph *All0 = new TGraph(); All0->SetMarkerStyle(7);
  TGraph *All1 = new TGraph(); All1->SetMarkerStyle(7);
  TGraph *All2 = new TGraph(); All2->SetMarkerStyle(7);
  TGraph *All3 = new TGraph(); All3->SetMarkerStyle(7);
  
  counter = 0;
  for ( auto fib : Mod0 ) {
    All0->SetPoint(counter,fib.second.first,fib.second.second);
    counter++;
  }
  counter = 0;
  for ( auto fib : Mod1 ) {
    All1->SetPoint(counter,fib.second.first,fib.second.second);
    counter++;
  }
  counter = 0;
  for ( auto fib : Mod2 ) {
    All2->SetPoint(counter,fib.second.first,fib.second.second);
    counter++;
  }
  counter = 0;
  for ( auto fib : Mod3 ) {
    All3->SetPoint(counter,fib.second.first,fib.second.second);
    counter++;
  }
  
  TGraph *HolderXZ = new TGraph();
  TGraph *HolderYZ = new TGraph();
  HolderXZ->SetMarkerColor(kWhite);
  HolderYZ->SetMarkerColor(kWhite);
  HolderXZ->SetPoint(0,0,0);
  HolderXZ->SetPoint(1,0,550+fGap);
  HolderYZ->SetPoint(0,0,0);
  HolderYZ->SetPoint(1,0,550+fGap);

  TMultiGraph *TMGXZ = new TMultiGraph();
  TMGXZ->Add(All1);
  TMGXZ->Add(All3);
  TMGXZ->Add(Graph1);
  TMGXZ->Add(Graph3);
  TMGXZ->Add(HolderXZ);
  TMultiGraph *TMGYZ = new TMultiGraph();
  TMGYZ->Add(All0);
  TMGYZ->Add(All2);
  TMGYZ->Add(Graph0);
  TMGYZ->Add(Graph2);
  TMGYZ->Add(HolderYZ);
  TF1 *LineXZ = new TF1("LineXZ","pol1",0,660);
  LineXZ->SetParameters(fYintXZ,fSlopeXZ);
  LineXZ->SetLineStyle(2);
  LineXZ->SetLineWidth(1);
  TF1 *LineYZ = new TF1("LineYZ","pol1",0,660);
  LineYZ->SetParameters(fYintYZ,fSlopeYZ);
  LineYZ->SetLineStyle(2);
  LineYZ->SetLineWidth(1);

  std::string s_EventID = MakeString((double)fSelectedEventID);
  std::string s_AngleXZ = MakeString(fAngleXZ*180/3.14159);
  std::string s_AngleYZ = MakeString(fAngleYZ*180/3.14159);

  gStyle->SetFrameLineWidth(2);
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadRightMargin(0.1);

  char tEID[30];
  char tGap[30];
  char tSlopeXZ[30];
  char tSlopeYZ[30];
  char tAngleXZ[30];
  char tAngleYZ[30];
  char tPhi[30];
  char tTheta[30];
  
  sprintf(tEID,     "Event %d",                 fSelectedEventID);
  sprintf(tGap,     "Gap = %3.3f cm",                fGap);
  sprintf(tSlopeXZ, "Slope XZ = %3.3f",         fSlopeXZ);
  sprintf(tSlopeYZ, "Slope YZ = %3.3f",         fSlopeYZ);
  sprintf(tAngleXZ, "Angle XZ = %3.3f degrees", fAngleXZ*180/3.14159);
  sprintf(tAngleYZ, "Angle YZ = %3.3f degrees", fAngleYZ*180/3.14159);
  sprintf(tPhi,     "Phi = %3.3f degrees",      fPhi*180/3.14159);
  sprintf(tTheta,   "Theta = %3.3f degrees",    fTheta*180/3.14159);
  
  const char *tEIDP     = tEID;  
  const char *tGapP     = tGap;
  const char *tSlopeXZP = tSlopeXZ;
  const char *tSlopeYZP = tSlopeYZ;
  const char *tAngleXZP = tAngleXZ;
  const char *tAngleYZP = tAngleYZ;
  const char *tPhiP     = tPhi;
  const char *tThetaP   = tTheta;
  
  TPaveText *EventTitle = new TPaveText(0.0,0.2,1,0.9,"brNDC");
  EventTitle->SetTextFont(63);
  EventTitle->SetTextSize(18);
  EventTitle->SetFillColor(0);
  EventTitle->SetBorderSize(0);
  EventTitle->AddText("Sim Event Display");
  EventTitle->AddText(tEIDP);
  EventTitle->AddText(tGapP);
  EventTitle->AddText(tSlopeXZP);
  EventTitle->AddText(tSlopeYZP);
  EventTitle->AddText(tAngleXZP);
  EventTitle->AddText(tAngleYZP);
  EventTitle->AddText(tPhiP);
  EventTitle->AddText(tThetaP);
  
  TPaveText *XZ_title = new TPaveText(0.36,.93,.7,.95,"brNDC");
  XZ_title->SetTextSize(22);
  XZ_title->SetTextFont(63);
  XZ_title->SetBorderSize(0);
  XZ_title->SetFillColor(0);
  XZ_title->AddText("XZ plane");
  TPaveText *YZ_title = new TPaveText(0.36,.93,.7,.95,"brNDC");
  YZ_title->SetTextSize(22);
  YZ_title->SetTextFont(63);
  YZ_title->SetBorderSize(0);
  YZ_title->SetFillColor(0);
  YZ_title->AddText("YZ plane");

  fApp = new TApplication("app",&argc,argv);
  TCanvas *can = new TCanvas("evd","evd",1300,800);

  TPad *padXZ = new TPad("padXZ","padXZ",.2,0.,.6,1.);
  TPad *padYZ = new TPad("padYZ","patYZ",.6,0.,1.,1.);
  TPad *padT  = new TPad("padT", "padT",.0,.3,.20,.9);

  padXZ->cd();
  TMGXZ->Draw("AP");
  LineXZ->Draw("same");
  XZ_title->Draw("same");

  padYZ->cd();
  TMGYZ->Draw("AP");
  LineYZ->Draw("same");
  YZ_title->Draw("same");

  padT->cd();
  EventTitle->Draw();

  can->cd();
  padXZ->Draw();
  padYZ->Draw();
  padT->Draw();
  fApp->Run();


}


void DrawSim(int argc, char *argv[])
{
  std::cout << "Under construction" << std::endl;
}

std::string evd::MakeString(double value)
{
  std::string return_me;
  std::ostringstream s;
  s << value;
  return_me = s.str();
  return return_me;
}
