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
  evg *event_set = new evg("file.root",100);
  event_set->ReadParameters();
  event_set->CheckParameters();
  event_set->RunEvents();

  return 0;


}


