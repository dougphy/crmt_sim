#include <iostream>
#include "evd.h"
#include "evg.h"

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
  event_set->SaveFile();
  
  
  /*
  evd *disp = new evd();
  disp->InitData("file.root",55);
  disp->RawDumpTrue();
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  disp->RawDumpSim();
  disp->DrawTrue(argc,argv);
  */
}


