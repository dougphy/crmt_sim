#include <iostream>
#include "evd.h"
#include "evg.h"
#include "Module.h"
#include "Line.h"

#define Pi 3.1415926

void usage()
{
  std::cout << "mutoy usage" << std::endl;
}

int main(int argc, char *argv[])
{
  std::cout << "Based God Simulation Under Construction" << std::endl;
  evg *event_set = new evg("file.root",100);
  event_set->ReadParameters();
  event_set->CheckParameters();
  event_set->RunEvents();

  std::cout << "\n\n";

  double slopeXZ;
  double slopeYZ;

  std::cout << "XZ to the RIGHT (+)\n"
	    << "YZ to the RIGHT (+)\n";
  Line *l = new Line();
  l->SetInitialPos(30.0,30.0,700.0);
  l->SetLinePropertiesFromPhiTheta(Pi/4.,Pi/12.);
  double xz = l->AngleXZ();
  double yz = l->AngleYZ();
  slopeXZ   = l->SlopeXZ();
  slopeYZ   = l->SlopeYZ();
  std::cout << "xz: " << xz << std::endl;
  std::cout << "yz: " << yz << std::endl;
  std::cout << "sxz:" << slopeXZ << std::endl;
  std::cout << "syz:" << slopeYZ << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "XZ to the LEFT (-)\n"
	    << "YZ to the RIGHT (+)\n";
  Line *ll = new Line();
  ll->SetInitialPos(1,1,1);
  ll->SetLinePropertiesFromPhiTheta(3*Pi/4.,Pi/12.);
  yz = ll->AngleYZ();
  xz = ll->AngleXZ();
  slopeXZ = ll->SlopeXZ();
  slopeYZ = ll->SlopeYZ();
  std::cout << "xz: " << xz << std::endl;
  std::cout << "yz: " << yz << std::endl;
  std::cout << "sxz:" << slopeXZ << std::endl;
  std::cout << "syz:" << slopeYZ << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

 
  std::cout << "XZ to the LEFT (-)\n"
	    << "YZ to the LEFT (-)\n";
  Line *lll = new Line();
  lll->SetInitialPos(0,0,0);
  lll->SetLinePropertiesFromPhiTheta(5*Pi/4.,Pi/12.);
  yz = lll->AngleYZ();
  xz = lll->AngleXZ();
  slopeXZ = lll->SlopeXZ();
  slopeYZ = lll->SlopeYZ();
  std::cout << "xz: " << xz << std::endl;
  std::cout << "yz: " << yz << std::endl;
  std::cout << "sxz:" << slopeXZ << std::endl;
  std::cout << "syz:" << slopeYZ << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "XZ to the RIGHT (+)\n"
	    << "YZ to the LEFT (-)\n";
  Line *llll = new Line();
  llll->SetInitialPos(0,0,0);
  llll->SetLinePropertiesFromPhiTheta(7*Pi/4.,Pi/12.);
  yz = llll->AngleYZ();
  xz = llll->AngleXZ();
  slopeXZ = llll->SlopeXZ();
  slopeYZ = llll->SlopeYZ();
  std::cout << "xz: " << xz << std::endl;
  std::cout << "yz: " << yz << std::endl;
  std::cout << "sxz:" << slopeXZ << std::endl;
  std::cout << "syz:" << slopeYZ << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
 

  return 0;


}


