#include <iostream>
#include "evd.h"
#include "evg.h"
#include "Module.h"

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
  event_set->MakeLine();
  /*
  event_set->RunEvents();
  */
  event_set->SaveFile();

  /*
  double gap   = 100;
  Module *mod0 = new Module(0,gap);
  Module *mod1 = new Module(1,gap);
  Module *mod2 = new Module(2,gap);
  Module *mod3 = new Module(3,gap);

  std::map<int, std::pair<double,double> > mod0fibs = mod0->GetMap();
  std::map<int, std::pair<double,double> > mod1fibs = mod1->GetMap();
  std::map<int, std::pair<double,double> > mod2fibs = mod2->GetMap();
  std::map<int, std::pair<double,double> > mod3fibs = mod3->GetMap();

  std::cout << "***** MOD 0" << std::endl;
  for ( auto moditr : mod0fibs ) {
    std::cout << moditr.first << " " 
	      << moditr.second.first << " " 
	      << moditr.second.second << std::endl; }
  std::cout << "***** MOD 1" << std::endl;
  for ( auto moditr : mod1fibs) {
    std::cout << moditr.first << " " 
	      << moditr.second.first << " " 
	      << moditr.second.second << std::endl; }
  std::cout << "***** MOD 2" << std::endl;
  for ( auto moditr : mod2fibs) {
    std::cout << moditr.first << " " 
	      << moditr.second.first << " " 
	      << moditr.second.second << std::endl; }
  std::cout << "***** MOD 3" << std::endl;
  for ( auto moditr : mod3fibs) {
    std::cout << moditr.first << " " 
	      << moditr.second.first << " " 
	      << moditr.second.second << std::endl; }
  */
  return 0;
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


