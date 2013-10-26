#include <iostream>
#include "evd.h"
#include "evg.h"
#include "Module.h"
#include "Line.h"

#define PI 3.1415926

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


  std::cout << "XZ to the RIGHT\n"
	    << "YZ to the RIGHT\n";
  Line *l = new Line();
  l->SetInitialPos(30.0,30.0,700.0);
  l->SetLinePropertiesFromPhiTheta(PI/4.,PI/12.);
  double xz = l->AngleXZ();
  double yz = l->AngleYZ();
  std::cout << "xz: " << xz << std::endl;
  std::cout << "yz: " << yz << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "XZ to the LEFT\n"
	    << "YZ to the RIGHT\n";
  Line *ll = new Line();
  ll->SetInitialPos(1,1,1);
  ll->SetLinePropertiesFromPhiTheta(3*PI/4.,PI/12);
  yz = ll->AngleYZ();
  xz = ll->AngleXZ();
  std::cout << "xz: " << xz << std::endl;
  std::cout << "yz: " << yz << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  

  return 0;


}


