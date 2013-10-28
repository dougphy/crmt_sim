#include <iostream>
#include "evd.h"
#include "evg.h"
#include "Module.h"
#include "Line.h"
#include "TApplication.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TMultiGraph.h"

#define Pi 3.1415926

void usage()
{
  std::cout << "mutoy usage" << std::endl;
}

int main(int argc, char *argv[])
{
  std::cout << "Based God Simulation Under Construction" << std::endl;
  //  evg *event_set = new evg("file.root",100);
  //  event_set->ReadParameters();
  //  event_set->CheckParameters();
  //  event_set->RunEvents();

  std::cout << "\n\n";

  double slopeXZ;
  double slopeYZ;
  double yintXZ;
  double yintYZ;

  std::cout << "XZ to the RIGHT (+)\n"
	    << "YZ to the RIGHT (+)\n";
  Line *l = new Line();
  l->SetInitialPos(330.0,330.0,900.0);
  l->SetLinePropertiesFromPhiTheta(Pi/4.,Pi/12.);
  double xz = l->AngleXZ();
  double yz = l->AngleYZ();
  slopeXZ   = l->SlopeXZ();
  slopeYZ   = l->SlopeYZ();
  yintXZ    = l->YintXZ();
  yintYZ    = l->YintYZ();
  std::cout << "xz: " << xz << std::endl;
  std::cout << "yz: " << yz << std::endl;
  std::cout << "sxz:" << slopeXZ << std::endl;
  std::cout << "syz:" << slopeYZ << std::endl;
  std::cout << "yxz:" << yintXZ << std::endl;
  std::cout << "yyz:" << yintYZ << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "XZ to the LEFT (-)\n"
	    << "YZ to the RIGHT (+)\n";
  Line *ll = new Line();
  ll->SetInitialPos(330,330,900);
  ll->SetLinePropertiesFromPhiTheta(3*Pi/4.,Pi/12.);
  yz = ll->AngleYZ();
  xz = ll->AngleXZ();
  slopeXZ = ll->SlopeXZ();
  slopeYZ = ll->SlopeYZ();
  yintXZ    = ll->YintXZ();
  yintYZ    = ll->YintYZ();
  std::cout << "xz: " << xz << std::endl;
  std::cout << "yz: " << yz << std::endl;
  std::cout << "sxz:" << slopeXZ << std::endl;
  std::cout << "syz:" << slopeYZ << std::endl;
  std::cout << "yxz:" << yintXZ << std::endl;
  std::cout << "yyz:" << yintYZ << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

 
  std::cout << "XZ to the LEFT (-)\n"
	    << "YZ to the LEFT (-)\n";
  Line *lll = new Line();
  lll->SetInitialPos(330,330,900);
  lll->SetLinePropertiesFromPhiTheta(5*Pi/4.,Pi/12.);
  yz = lll->AngleYZ();
  xz = lll->AngleXZ();
  slopeXZ = lll->SlopeXZ();
  slopeYZ = lll->SlopeYZ();
  yintXZ    = lll->YintXZ();
  yintYZ    = lll->YintYZ();
  std::cout << "xz: " << xz << std::endl;
  std::cout << "yz: " << yz << std::endl;
  std::cout << "sxz:" << slopeXZ << std::endl;
  std::cout << "syz:" << slopeYZ << std::endl;
  std::cout << "yxz:" << yintXZ << std::endl;
  std::cout << "yyz:" << yintYZ << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "XZ to the RIGHT (+)\n"
	    << "YZ to the LEFT (-)\n";
  Line *llll = new Line();
  llll->SetInitialPos(330,330,900);
  llll->SetLinePropertiesFromPhiTheta(7*Pi/4.,Pi/12.);
  yz = llll->AngleYZ();
  xz = llll->AngleXZ();
  slopeXZ = llll->SlopeXZ();
  slopeYZ = llll->SlopeYZ();
  yintXZ    = llll->YintXZ();
  yintYZ    = llll->YintYZ();
  std::cout << "xz: " << xz << std::endl;
  std::cout << "yz: " << yz << std::endl;
  std::cout << "sxz:" << slopeXZ << std::endl;
  std::cout << "syz:" << slopeYZ << std::endl;
  std::cout << "yxz:" << yintXZ << std::endl;
  std::cout << "yyz:" << yintYZ << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  

  double gap   = 300;
  Module *mod0 = new Module(0,gap);
  Module *mod1 = new Module(1,gap);
  Module *mod2 = new Module(2,gap);
  Module *mod3 = new Module(3,gap);
  std::map<int, std::pair<double,double> > mod0fibs = mod0->GetMap();
  std::map<int, std::pair<double,double> > mod1fibs = mod1->GetMap();
  std::map<int, std::pair<double,double> > mod2fibs = mod2->GetMap();
  std::map<int, std::pair<double,double> > mod3fibs = mod3->GetMap();

  TGraphErrors *mod0graph = new TGraphErrors();
  mod0graph->SetMarkerStyle(7);
  mod0graph->SetMarkerColor(1);
  TGraphErrors *mod1graph = new TGraphErrors();
  mod1graph->SetMarkerStyle(7);
  mod1graph->SetMarkerColor(2);
  TGraphErrors *mod2graph = new TGraphErrors();
  mod2graph->SetMarkerStyle(7);
  mod2graph->SetMarkerColor(3);
  TGraphErrors *mod3graph = new TGraphErrors();
  mod3graph->SetMarkerStyle(7);
  mod3graph->SetMarkerColor(4);

  int counter = 0;
  for ( auto j : mod0fibs ) {
    mod0graph->SetPoint(counter,j.second.first,j.second.second);
    counter++;
  }
  counter = 0;
  for ( auto j : mod1fibs ) {
    mod1graph->SetPoint(counter,j.second.first,j.second.second);
    counter++;
  }
  counter = 0;
  for ( auto j : mod2fibs ) {
    mod2graph->SetPoint(counter,j.second.first,j.second.second);
    counter++;
  }
  counter = 0;
  for ( auto j : mod3fibs ) {
    mod3graph->SetPoint(counter,j.second.first,j.second.second);
    counter++;
  }
  
  TF1 *fxpyp = new TF1("fxpyp","pol1",0,900);
  fxpyp->SetParameters(l->YintXZ(),l->SlopeXZ());
  fxpyp->SetLineColor(kCyan);
  TF1 *fxnyp = new TF1("fxnyp","pol1",0,900);
  fxnyp->SetParameters(ll->YintXZ(),ll->SlopeXZ());
  fxnyp->SetLineColor(kOrange);
  TF1 *fxnyn = new TF1("fxnyn","pol1",0,900);
  fxnyn->SetParameters(lll->YintXZ(),lll->SlopeXZ());
  fxnyn->SetLineColor(kBlack);
  TF1 *fxpyn = new TF1("fxpyn","pol1",0,900);
  fxpyn->SetParameters(llll->YintXZ(),llll->SlopeXZ());
  fxpyn->SetLineColor(kRed);


  TMultiGraph *mg = new TMultiGraph();
  mg->Add(mod0graph);
  mg->Add(mod1graph);
  mg->Add(mod2graph);
  mg->Add(mod3graph);

  TApplication *tapp = new TApplication("tapp",&argc,argv);
  TCanvas *can = new TCanvas();
  mg->Draw("AP");
  fxpyp->Draw("sames");  // TF1
  fxpyn->Draw("sames");  // TF1
  tapp->Run();
  return 0;


}


