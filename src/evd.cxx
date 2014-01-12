//////////////////////////////////////////////////////////////////////
/// \file evd.cxx
/// \brief evd class methods
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

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
#include "TEllipse.h"

namespace ev {

  evd::evd() {}

  evd::~evd()
  {
    delete fApp;
    delete fTree;
    delete fFile;
    delete fAll0;
    delete fAll1;
    delete fAll2;
    delete fAll3;
    delete fTMGXZ;
    delete fTMGYZ;
    delete fEllipseXZ;
    delete fEllipseYZ;
    delete fBoxXZ;
    delete fBoxYZ;
  }

  void evd::InitFile(const std::string& file_name, unsigned int event_number)
  {
    fFile = new TFile(file_name.c_str());
    fTree = (TTree*)fFile->Get("SimulationTree");
    fTree->SetBranchAddress("InitialX",   &fInitialX);
    fTree->SetBranchAddress("InitialY",   &fInitialY);
    fTree->SetBranchAddress("InitialZ",   &fInitialZ);
    fTree->SetBranchAddress("AngleXZ",    &fAngleXZ);
    fTree->SetBranchAddress("AngleYZ",    &fAngleYZ);
    fTree->SetBranchAddress("Phi",        &fPhi);
    fTree->SetBranchAddress("Theta",      &fTheta);
    fTree->SetBranchAddress("SlopeXZ",    &fSlopeXZ);
    fTree->SetBranchAddress("SlopeYZ",    &fSlopeYZ);
    fTree->SetBranchAddress("YintXZ",     &fYintXZ);
    fTree->SetBranchAddress("YintYZ",     &fYintYZ);
    fTree->SetBranchAddress("Gap",        &fGap);
    fTree->SetBranchAddress("Coincidence",&fCoincidence);
    fTree->SetBranchAddress("TrueMod0",    fTrueMod0);
    fTree->SetBranchAddress("TrueMod1",    fTrueMod1);
    fTree->SetBranchAddress("TrueMod2",    fTrueMod2);
    fTree->SetBranchAddress("TrueMod3",    fTrueMod3);
    fTree->SetBranchAddress("SimMod0",     fSimMod0);
    fTree->SetBranchAddress("SimMod1",     fSimMod1);
    fTree->SetBranchAddress("SimMod2",     fSimMod2);
    fTree->SetBranchAddress("SimMod3",     fSimMod3);
    fSelectedEventID = event_number;

    fVolTree = (TTree*)fFile->Get("TestVolumeTree");
    fVolTree->SetBranchAddress("TVOn",    &fTVOn);
    fVolTree->SetBranchAddress("TVCenter", fTVCenter);
    fVolTree->SetBranchAddress("TVRadius",&fTVRadius);
    fVolTree->SetBranchAddress("TVLength",&fTVLength);
    fVolTree->SetBranchAddress("TVWidth", &fTVWidth);
    fVolTree->SetBranchAddress("TVHeight",&fTVHeight);
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

  void evd::SetupTVs()
  {
    fVolTree->GetEntry(0);
    fTVChecker = false;
    if ( fTVOn ) {
      fTVChecker = true;  
      if ( fTVRadius != 0 ) {
	fEllipseXZ = new TEllipse(fTVCenter[0],fTVCenter[2],fTVRadius,fTVRadius);
	fEllipseYZ = new TEllipse(fTVCenter[1],fTVCenter[2],fTVRadius,fTVRadius);
	fEllipseXZ->SetFillColor(kBlack);
	fEllipseYZ->SetFillColor(kBlack);
      }
      else if ( fTVLength != 0 ) {
	fBoxXZ = new TBox(fTVCenter[0]-fTVLength/2.,fTVCenter[2]-fTVHeight/2.,
			  fTVCenter[0]+fTVLength/2.,fTVCenter[2]+fTVHeight/2.);
	fBoxYZ = new TBox(fTVCenter[1]-fTVWidth/2.,fTVCenter[2]-fTVHeight/2.,
			  fTVCenter[1]+fTVWidth/2.,fTVCenter[2]+fTVHeight/2.);
	fBoxXZ->SetFillColor(kBlack);
	fBoxYZ->SetFillColor(kBlack);
      }
      else {
	std::cout << "Bad Test Volume Setup" << std::endl;
      }
    }
  }

  void evd::InitAllGraphs()
  {
    fTree->GetEntry(fSelectedEventID);
    double gap = fGap;
    geo::Module *mod0 = new geo::Module(0,gap);
    geo::Module *mod1 = new geo::Module(1,gap);
    geo::Module *mod2 = new geo::Module(2,gap);
    geo::Module *mod3 = new geo::Module(3,gap);
    std::map<int, std::pair<double,double> > Mod0 = mod0->GetMap();
    std::map<int, std::pair<double,double> > Mod1 = mod1->GetMap();
    std::map<int, std::pair<double,double> > Mod2 = mod2->GetMap();
    std::map<int, std::pair<double,double> > Mod3 = mod3->GetMap();

    fAll0 = new TGraph(); fAll0->SetMarkerStyle(7);
    fAll1 = new TGraph(); fAll1->SetMarkerStyle(7);
    fAll2 = new TGraph(); fAll2->SetMarkerStyle(7);
    fAll3 = new TGraph(); fAll3->SetMarkerStyle(7);
  
    int counter = 0;
    for ( auto fib : Mod0 ) {
      fAll0->SetPoint(counter,fib.second.first,fib.second.second);
      counter++;
    }
    counter = 0;
    for ( auto fib : Mod1 ) {
      fAll1->SetPoint(counter,fib.second.first,fib.second.second);
      counter++;
    }
    counter = 0;
    for ( auto fib : Mod2 ) {
      fAll2->SetPoint(counter,fib.second.first,fib.second.second);
      counter++;
    }
    counter = 0;
    for ( auto fib : Mod3 ) {
      fAll3->SetPoint(counter,fib.second.first,fib.second.second);
      counter++;
    }
  }


  void evd::DrawTrue(int argc, char *argv[])
  {
    SetupTVs();
    fTree->GetEntry(fSelectedEventID);
    double gap = fGap;
    geo::Module *mod0 = new geo::Module(0,gap);
    geo::Module *mod1 = new geo::Module(1,gap);
    geo::Module *mod2 = new geo::Module(2,gap);
    geo::Module *mod3 = new geo::Module(3,gap);
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
      if ( fTrueMod0[i] ) {
	Graph0->SetPoint(counter,Mod0[i].first,Mod0[i].second);
	counter++;
      }
      else {
	continue;
      }
    }
    counter = 0;
    for ( int i = 0; i < 256; i++ ) {
      if ( fTrueMod1[i] ) {
	Graph1->SetPoint(counter,Mod1[i].first,Mod1[i].second);
	counter++;
      }
      else {
	continue;
      }
    }
    counter = 0;
    for ( int i = 0; i < 256; i++ ) {
      if ( fTrueMod2[i] ) {
	Graph2->SetPoint(counter,Mod2[i].first,Mod2[i].second);
	counter++;
      }
      else {
	continue;
      }
    }
    counter = 0;
    for ( int i = 0; i < 256; i++ ) {
      if ( fTrueMod3[i] ) {
	Graph3->SetPoint(counter,Mod3[i].first,Mod3[i].second);
	counter++;
      }
      else {
	continue;
      }
    }
  
    InitAllGraphs();

    TGraph *HolderXZ = new TGraph();
    TGraph *HolderYZ = new TGraph();
    HolderXZ->SetMarkerColor(kWhite);
    HolderYZ->SetMarkerColor(kWhite);
    HolderXZ->SetPoint(0,0,0);
    HolderXZ->SetPoint(1,0,550+fGap);
    HolderYZ->SetPoint(0,0,0);
    HolderYZ->SetPoint(1,0,550+fGap);

    fTMGXZ = new TMultiGraph();
    fTMGXZ->Add(fAll1);
    fTMGXZ->Add(fAll3);
    if ( fCoincidence ) {
      fTMGXZ->Add(Graph1);
      fTMGXZ->Add(Graph3);
    }
    fTMGXZ->Add(HolderXZ);
    fTMGYZ = new TMultiGraph();
    fTMGYZ->Add(fAll0);
    fTMGYZ->Add(fAll2);
    if ( fCoincidence ) {
      fTMGYZ->Add(Graph0);
      fTMGYZ->Add(Graph2);
    }
    fTMGYZ->Add(HolderYZ);
    TF1 *LineXZ = new TF1("LineXZ","pol1",0,660);
    LineXZ->SetParameters(fYintXZ,fSlopeXZ);
    LineXZ->SetLineStyle(2);
    LineXZ->SetLineWidth(1);
    TF1 *LineYZ = new TF1("LineYZ","pol1",0,660);
    LineYZ->SetParameters(fYintYZ,fSlopeYZ);
    LineYZ->SetLineStyle(2);
    LineYZ->SetLineWidth(1);

    gStyle->SetFrameLineWidth(2);
    gStyle->SetPadTopMargin(0.08);
    gStyle->SetPadBottomMargin(0.12);
    gStyle->SetPadLeftMargin(0.14);
    gStyle->SetPadRightMargin(0.1);

    char tEID[30];
    char tIX[30];
    char tIY[30];
    char tIZ[30];
    char tGap[30];
    char tSlopeXZ[30];
    char tSlopeYZ[30];
    char tAngleXZ[30];
    char tAngleYZ[30];
    char tPhi[30];
    char tTheta[30];
  
    sprintf(tEID,     "Event %d",                 fSelectedEventID);
    sprintf(tIX,      "x_{0} = %3.3f",      fInitialX);
    sprintf(tIY,      "y_{0} = %3.3f",      fInitialY);
    sprintf(tIZ,      "z_{0} = %3.3f",      fInitialZ);
    sprintf(tGap,     "Gap = %3.3f mm",           fGap);
    sprintf(tSlopeXZ, "Slope XZ = %3.3f",         fSlopeXZ);
    sprintf(tSlopeYZ, "Slope YZ = %3.3f",         fSlopeYZ);
    if ( fAngleXZ > 0 ) {
      sprintf(tAngleXZ, "Angle XZ = %3.3f degrees", fAngleXZ*180/3.14159 - 180.);
      sprintf(tAngleYZ, "Angle YZ = %3.3f degrees", fAngleYZ*180/3.14159 - 180.);
    }
    else {
      sprintf(tAngleXZ, "Angle XZ = %3.3f degrees", fAngleXZ*180/3.14159 + 180.);
      sprintf(tAngleYZ, "Angle YZ = %3.3f degrees", fAngleYZ*180/3.14159 + 180.);
    }
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
    const char *tIXP      = tIX;
    const char *tIYP      = tIY;
    const char *tIZP      = tIZ;
  
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
    EventTitle->AddText(tIXP);
    EventTitle->AddText(tIYP);
    EventTitle->AddText(tIZP);
  
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
    TCanvas *can = new TCanvas("evd","evd",1300,570);

    TPad *padXZ = new TPad("padXZ","padXZ",.2,0.,.6,1.);
    TPad *padYZ = new TPad("padYZ","patYZ",.6,0.,1.,1.);
    TPad *padT  = new TPad("padT", "padT",.0,.3,.20,.9);

    padXZ->cd();
    fTMGXZ->Draw("AP");
    LineXZ->Draw("same");
    XZ_title->Draw("same");
    if ( fTVChecker )
      if ( fTVRadius != 0 )
	fEllipseXZ->Draw("same");
    if ( fTVChecker )
      if ( fTVLength != 0 )
	fBoxXZ->Draw("same");

    padYZ->cd();
    fTMGYZ->Draw("AP");
    LineYZ->Draw("same");
    YZ_title->Draw("same");
    if ( fTVChecker )
      if ( fTVRadius != 0 )
	fEllipseYZ->Draw("same");
    if ( fTVChecker )
      if ( fTVLength != 0 )
	fBoxYZ->Draw("same");

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
    SetupTVs();
    fTree->GetEntry(fSelectedEventID);
    double gap = fGap;
    geo::Module *mod0 = new geo::Module(0,gap);
    geo::Module *mod1 = new geo::Module(1,gap);
    geo::Module *mod2 = new geo::Module(2,gap);
    geo::Module *mod3 = new geo::Module(3,gap);
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
      if ( fSimMod0[i] ) {
	Graph0->SetPoint(counter,Mod0[i].first,Mod0[i].second);
	counter++;
      }
      else {
	continue;
      }
    }
    counter = 0;
    for ( int i = 0; i < 256; i++ ) {
      if ( fSimMod1[i] ) {
	Graph1->SetPoint(counter,Mod1[i].first,Mod1[i].second);
	counter++;
      }
      else {
	continue;
      }
    }
    counter = 0;
    for ( int i = 0; i < 256; i++ ) {
      if ( fSimMod2[i] ) {
	Graph2->SetPoint(counter,Mod2[i].first,Mod2[i].second);
	counter++;
      }
      else {
	continue;
      }
    }
    counter = 0;
    for ( int i = 0; i < 256; i++ ) {
      if ( fSimMod3[i] ) {
	Graph3->SetPoint(counter,Mod3[i].first,Mod3[i].second);
	counter++;
      }
      else {
	continue;
      }
    }
  
    InitAllGraphs();
  
    TGraph *HolderXZ = new TGraph();
    TGraph *HolderYZ = new TGraph();
    HolderXZ->SetMarkerColor(kWhite);
    HolderYZ->SetMarkerColor(kWhite);
    HolderXZ->SetPoint(0,0,0);
    HolderXZ->SetPoint(1,0,550+fGap);
    HolderYZ->SetPoint(0,0,0);
    HolderYZ->SetPoint(1,0,550+fGap);
    
    fTMGXZ = new TMultiGraph();
    fTMGXZ->Add(fAll1);
    fTMGXZ->Add(fAll3);
    if ( fCoincidence ) {
      fTMGXZ->Add(Graph1);
      fTMGXZ->Add(Graph3);
    }
    fTMGXZ->Add(HolderXZ);
    fTMGYZ = new TMultiGraph();
    fTMGYZ->Add(fAll0);
    fTMGYZ->Add(fAll2);
    if ( fCoincidence ) {
      fTMGYZ->Add(Graph0);
      fTMGYZ->Add(Graph2);
    }
    fTMGYZ->Add(HolderYZ);
    TF1 *LineXZ = new TF1("LineXZ","pol1",0,660);
    LineXZ->SetParameters(fYintXZ,fSlopeXZ);
    LineXZ->SetLineStyle(2);
    LineXZ->SetLineWidth(1);
    TF1 *LineYZ = new TF1("LineYZ","pol1",0,660);
    LineYZ->SetParameters(fYintYZ,fSlopeYZ);
    LineYZ->SetLineStyle(2);
    LineYZ->SetLineWidth(1);

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
    char tIX[30];
    char tIY[30];
    char tIZ[30];

    sprintf(tIX,      "x_{0} = %3.3f",      fInitialX);
    sprintf(tIY,      "y_{0} = %3.3f",      fInitialY);
    sprintf(tIZ,      "z_{0} = %3.3f",      fInitialZ);
    sprintf(tEID,     "Event %d",                 fSelectedEventID);
    sprintf(tGap,     "Gap = %3.3f mm",           fGap);
    sprintf(tSlopeXZ, "Slope XZ = %3.3f",         fSlopeXZ);
    sprintf(tSlopeYZ, "Slope YZ = %3.3f",         fSlopeYZ);
    sprintf(tPhi,     "Phi = %3.3f degrees",      fPhi*180/3.14159);
    sprintf(tTheta,   "Theta = %3.3f degrees",    fTheta*180/3.14159);
    if ( fAngleXZ > 0 ) {
      sprintf(tAngleXZ, "Angle XZ = %3.3f degrees", fAngleXZ*180/3.14159 - 180.);
      sprintf(tAngleYZ, "Angle YZ = %3.3f degrees", fAngleYZ*180/3.14159 - 180.);
    }
    else {
      sprintf(tAngleXZ, "Angle XZ = %3.3f degrees", fAngleXZ*180/3.14159 + 180.);
      sprintf(tAngleYZ, "Angle YZ = %3.3f degrees", fAngleYZ*180/3.14159 + 180.);
    }

    const char *tIXP      = tIX;
    const char *tIYP      = tIY;
    const char *tIZP      = tIZ;  
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
    EventTitle->AddText(tIXP);
    EventTitle->AddText(tIYP);
    EventTitle->AddText(tIZP);
  
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
    TCanvas *can = new TCanvas("evd","evd",1300,570);

    TPad *padXZ = new TPad("padXZ","padXZ",.2,0.,.6,1.);
    TPad *padYZ = new TPad("padYZ","patYZ",.6,0.,1.,1.);
    TPad *padT  = new TPad("padT", "padT",.0,.3,.20,.9);

    padXZ->cd();
    fTMGXZ->Draw("AP");
    LineXZ->Draw("same");
    XZ_title->Draw("same");
    if ( fTVChecker )
      if ( fTVRadius != 0 )
	fEllipseXZ->Draw("same");
    if ( fTVChecker )
      if ( fTVLength != 0 )
	fBoxXZ->Draw("same");

    padYZ->cd();
    fTMGYZ->Draw("AP");
    LineYZ->Draw("same");
    YZ_title->Draw("same");
    if ( fTVChecker )
      if ( fTVRadius != 0 )
	fEllipseYZ->Draw("same");
    if ( fTVChecker )
      if ( fTVLength != 0 )
	fBoxYZ->Draw("same");

    padT->cd();
    EventTitle->Draw();

    can->cd();
    padXZ->Draw();
    padYZ->Draw();
    padT->Draw();
    fApp->Run();
  }

}
