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
  return 0;

  std::cout << "\n\n";

  Line *l = new Line();
  l->SetInitialPos(30.0,30.0,700.0);
  l->SetLinePropertiesFromPhiTheta(PI/2.,PI/12.);

}


