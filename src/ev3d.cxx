#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TApplication.h"
#include "TPad.h"
#include "TROOT.h"
#include "Module.h"
#include "ev3d.h"
#include <vector>
#include <map>

void Draw3DGL(const bool& true_view, const unsigned int& event_id)
{
  geo::Module Mod0(0,200); auto Mod0Loc = Mod0.GetMap();
  geo::Module Mod1(1,200); auto Mod1Loc = Mod1.GetMap();
  geo::Module Mod2(2,200); auto Mod2Loc = Mod2.GetMap();
  geo::Module Mod3(3,200); auto Mod3Loc = Mod3.GetMap();
  
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
    
  gGeoManager->CloseGeometry();
  top->Draw("ogl");
}
