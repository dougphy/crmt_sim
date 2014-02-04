#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TApplication.h"
#include "TPolyLine3D.h"
#include "TPad.h"
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "Module.h"
#include "ev3d.h"
#include <vector>
#include <map>

void Draw3DGL(const std::string& file_name, const bool& true_view, const unsigned int& event_id)
{
  TFile *the_file   = new TFile(file_name.c_str());
  TTree *event_tree = (TTree*)the_file->Get("SimulationTree");
  TTree *tv_tree    = (TTree*)the_file->Get("TestVolumeTree");

  bool TrueMod0[256], SimMod0[256];
  bool TrueMod1[256], SimMod1[256];
  bool TrueMod2[256], SimMod2[256];
  bool TrueMod3[256], SimMod3[256];
  double Gap;
  double topx,topy,topz;
  double botx,boty,botz;

  event_tree->SetBranchAddress("TrueMod0",TrueMod0);
  event_tree->SetBranchAddress("TrueMod1",TrueMod1);
  event_tree->SetBranchAddress("TrueMod2",TrueMod2);
  event_tree->SetBranchAddress("TrueMod3",TrueMod3);
  event_tree->SetBranchAddress("SimMod0", SimMod0);
  event_tree->SetBranchAddress("SimMod1", SimMod1);
  event_tree->SetBranchAddress("SimMod2", SimMod2);
  event_tree->SetBranchAddress("SimMod3", SimMod3);

  event_tree->SetBranchAddress("InitialX",&topx);
  event_tree->SetBranchAddress("InitialY",&topy);
  event_tree->SetBranchAddress("InitialZ",&topz);
  event_tree->SetBranchAddress("BottomX",&botx);
  event_tree->SetBranchAddress("BottomY",&boty);
  event_tree->SetBranchAddress("BottomZ",&botz);

  tv_tree->SetBranchAddress("Gap",&Gap);
  tv_tree->GetEntry(0);

  geo::Module Mod0(0,Gap); auto Mod0Loc = Mod0.GetMap();
  geo::Module Mod1(1,Gap); auto Mod1Loc = Mod1.GetMap();
  geo::Module Mod2(2,Gap); auto Mod2Loc = Mod2.GetMap();
  geo::Module Mod3(3,Gap); auto Mod3Loc = Mod3.GetMap();
  
  TGeoVolume *extrusions0[256];
  TGeoVolume *extrusions1[256];
  TGeoVolume *extrusions2[256];
  TGeoVolume *extrusions3[256];
  
  double half_scint_length = 325.0;
  double half_scint_width  = 5.200;
  double half_scint_height = 15.40;
  
  new TGeoManager("world","the simplest geometry");  
  TGeoMaterial *mat = new TGeoMaterial("Vacuum",0,0,0);
  TGeoMedium   *med = new TGeoMedium("Vacuum",1,mat);
  TGeoVolume   *top = gGeoManager->MakeBox("Top",med,5000.,5000.,5000.);
  gGeoManager->SetTopVolume(top);

  for ( unsigned int id = 0; id < 256; id++ ) {
    extrusions0[id] = gGeoManager->MakeBox("box",med,half_scint_length,half_scint_width,half_scint_height);
    extrusions0[id]->SetLineColor(kWhite);
    top->AddNode(extrusions0[id],
		 id,
		 new TGeoTranslation(half_scint_length,Mod0Loc[id].first,Mod0Loc[id].second));
  }

  for ( unsigned int id = 0; id < 256; id++ ) {
    extrusions1[id] = gGeoManager->MakeBox("box",med,half_scint_width,half_scint_length,half_scint_height);
    extrusions1[id]->SetLineColor(kWhite);
    top->AddNode(extrusions1[id],
		 id,
		 new TGeoTranslation(Mod1Loc[id].first,half_scint_length,Mod1Loc[id].second));
  }
  for ( unsigned int id = 0; id < 256; id++ ) {
    extrusions2[id] = gGeoManager->MakeBox("box",med,half_scint_length,half_scint_width,half_scint_height);
    extrusions2[id]->SetLineColor(kWhite);
    top->AddNode(extrusions2[id],
		 id,
		 new TGeoTranslation(half_scint_length,Mod2Loc[id].first,Mod2Loc[id].second));
  }

  for ( unsigned int id = 0; id < 256; id++ ) {
    extrusions3[id] = gGeoManager->MakeBox("box",med,half_scint_width,half_scint_length,half_scint_height);
    extrusions3[id]->SetLineColor(kWhite);
    top->AddNode(extrusions3[id],
		 id,
		 new TGeoTranslation(Mod3Loc[id].first,half_scint_length,Mod3Loc[id].second));
  }
  
  event_tree->GetEntry(event_id);
  
  for ( unsigned int i = 0; i < 256; i++ ) {
    if ( true_view ) {
      if ( TrueMod0[i] )
	extrusions0[i]->SetLineColor(kGreen);
      if ( TrueMod1[i] )
	extrusions1[i]->SetLineColor(kGreen);
      if ( TrueMod2[i] )
	extrusions2[i]->SetLineColor(kGreen);
      if ( TrueMod3[i] )
	extrusions3[i]->SetLineColor(kGreen);
    }
    else {
      if ( SimMod0[i] )
	extrusions0[i]->SetLineColor(kGreen);
      if ( SimMod1[i] )
	extrusions1[i]->SetLineColor(kGreen);
      if ( SimMod2[i] )
	extrusions2[i]->SetLineColor(kGreen);
      if ( SimMod3[i] )
	extrusions3[i]->SetLineColor(kGreen);
    }
  }
  
  gGeoManager->CloseGeometry();
  top->Draw("ogl");
  TPolyLine3D *muon_line = new TPolyLine3D();
  muon_line->SetPoint(0,topx,topy,topz);
  muon_line->SetPoint(1,botx,boty,botz);
  muon_line->SetLineColor(kRed);
  muon_line->SetLineWidth(3);
  muon_line->Draw();
}
