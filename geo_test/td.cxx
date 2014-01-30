#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TApplication.h"
#include "TPad.h"
#include "TROOT.h"
#include "Module.h"
#include <vector>
#include <map>

void DrawGL();

int main(int argc, char *argv[])
{
  TApplication *tapp = new TApplication("tapp",&argc,argv);
  DrawGL();
  tapp->Run();
  return 0;
}

void DrawGL()
{
  geo::Module Mod0(0,200);
  geo::Module Mod1(1,200);
  geo::Module Mod2(2,200);
  geo::Module Mod3(3,200);

  auto Mod0Loc = Mod0.GetMap();
  auto Mod1Loc = Mod1.GetMap();
  auto Mod2Loc = Mod2.GetMap();
  auto Mod3Loc = Mod3.GetMap();

  TGeoVolume *extrusions0[256];
  TGeoVolume *extrusions1[256];
  TGeoVolume *extrusions2[256];
  TGeoVolume *extrusions3[256];
  
  double scint_length = 325.0;
  double scint_width  = 5.200;
  double scint_height = 15.40;
  
  new TGeoManager("world","the simplest geometry");  
  TGeoMaterial *mat = new TGeoMaterial("Vacuum",0,0,0);
  TGeoMedium   *med = new TGeoMedium("Vacuum",1,mat);
  TGeoVolume   *top = gGeoManager->MakeBox("Top",med,5000.,5000.,5000.);
  gGeoManager->SetTopVolume(top);

  for ( unsigned int id = 0; id < 256; id++ ) {
    extrusions0[id] = gGeoManager->MakeBox("box",med,scint_length,scint_width,scint_height);
    extrusions0[id]->SetLineColor(kWhite);
    top->AddNode(extrusions0[id],
		 id,
		 new TGeoTranslation(scint_length,Mod0Loc[id].first,Mod0Loc[id].second));
  }

  for ( unsigned int id = 0; id < 256; id++ ) {
    extrusions1[id] = gGeoManager->MakeBox("box",med,scint_width,scint_length,scint_height);
    extrusions1[id]->SetLineColor(kWhite);
    top->AddNode(extrusions1[id],
		 id,
		 new TGeoTranslation(Mod1Loc[id].first,scint_length,Mod1Loc[id].second));
  }
  for ( unsigned int id = 0; id < 256; id++ ) {
    extrusions2[id] = gGeoManager->MakeBox("box",med,scint_length,scint_width,scint_height);
    extrusions2[id]->SetLineColor(kWhite);
    top->AddNode(extrusions2[id],
		 id,
		 new TGeoTranslation(scint_length,Mod2Loc[id].first,Mod2Loc[id].second));
  }

  for ( unsigned int id = 0; id < 256; id++ ) {
    extrusions3[id] = gGeoManager->MakeBox("box",med,scint_width,scint_length,scint_height);
    extrusions3[id]->SetLineColor(kWhite);
    top->AddNode(extrusions3[id],
		 id,
		 new TGeoTranslation(Mod3Loc[id].first,scint_length,Mod3Loc[id].second));
  }
  
  
  /*
  double scint_height  =  1.04;
  double scint_width   =  3.08;
  double scint_length  =  25.;
  double up_z_high     =  0.55*scint_height + 5.0;
  double down_z_high   = -0.55*scint_height + 5.0;
  double up_z_low      =  0.55*scint_height - 5.0;
  double down_z_low    = -0.55*scint_height - 5.0;
  */
  /*
  unsigned int n_boxes = 32;
  TGeoVolume *boxes[32];
  
  for ( unsigned int boxid = 0; boxid < n_boxes; boxid++ ) {
    if ( boxid < 8 ) {
      boxes[boxid] = gGeoManager->MakeBox("box",med,scint_length,scint_height,scint_width);
      boxes[boxid]->SetLineColor(kWhite);
      top->AddNode(boxes[boxid],
		   boxid,
		   new TGeoTranslation(0,
				       (up_z_high*2),
				       -3.5*(scint_width*2)+(scint_width*2)*boxid));
    }
    else if ( boxid > 7 && boxid < 16 ) {
      boxes[boxid] = gGeoManager->MakeBox("box",med,scint_width,scint_height,scint_length);
      boxes[boxid]->SetLineColor(kWhite);
      top->AddNode(boxes[boxid],
     		   boxid,
		   new TGeoTranslation(-3.5*(scint_width*2)+(scint_width*2)*(boxid-8),
				       (down_z_high*2),
				       0));
    }
    else if ( boxid > 15 && boxid < 24 ) {
      boxes[boxid] = gGeoManager->MakeBox("box",med,scint_length,scint_height,scint_width);
      boxes[boxid]->SetLineColor(kWhite);    
      top->AddNode(boxes[boxid],
		   boxid,
		   new TGeoTranslation(0,
				       (2*up_z_low),
				       -3.5*(scint_width*2)+(scint_width*2)*(boxid-16)));
    }
    else if ( boxid > 23 && boxid < 32 ) {
      boxes[boxid] = gGeoManager->MakeBox("box",med,scint_width,scint_height,scint_length);
      boxes[boxid]->SetLineColor(kWhite);
      top->AddNode(boxes[boxid],
     		   boxid,
		   new TGeoTranslation(-3.5*(scint_width*2)+(scint_width*2)*(boxid-24),
				       (down_z_low*2),
				       0));
    }
  }
  */
  gGeoManager->CloseGeometry();
  top->Draw("ogl");
}
