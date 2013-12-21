//////////////////////////////////////////////////////////////////////
/// \file crmt.cxx
/// \brief Main file calls classes based on user arguments
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include "evd.h"
#include "evg.h"
#include "Line.h"
#include "Module.h"
#include "TestVolume.h"

void usage()
{
  std::cout << "crmt usage:" << std::endl;
  std::cout << "./crmt -g,--generate [file name] [# events] " << std::endl;
  std::cout << "./crmt -d,--display -t,--true [file name] [event #] " << std::endl;
  std::cout << "./crmt -d,--display -s,--sim [file name] [event #] " << std::endl;
  std::cout << "./crmt -p,--parameters " << std::endl;
}

int main(int argc, char *argv[])
{
  if(argc < 2 )
    usage();
  else {
    std::string first_arg = argv[1];
    
    if ( first_arg == "-g" || first_arg == "--generate" ) {
      if ( argc < 4 )
	usage();
      else {
	std::string n_holder  = argv[3];
	std::string fname     = argv[2];
	int events = atoi(n_holder.c_str());
	gen::evg *event_set = new gen::evg(fname.c_str(),events);
	event_set->ReadParameters();
	// event_set->CheckParameters();
	event_set->RunEvents();
      }
    }
    
    else if ( first_arg == "-d" || first_arg == "--display") {
      if ( argc < 5 ) 
	usage();
      else {
	std::string n_holder  = argv[4];
	std::string fname = argv[3];
	int event = atoi(n_holder.c_str());
	disp::evd *display = new disp::evd();
	display->InitFile(fname.c_str(),event);
	std::string doption = argv[2];
	if ( doption == "-s" || doption == "--sim" ) {
	  display->DrawSim(argc,argv);
	}
	else if ( doption == "-t" || doption == "--true" ) {
	  display->DrawTrue(argc,argv);
	}
	else {
	  usage();
	}
      }  
    }
    
    else if ( first_arg == "-p" || first_arg == "--parameters" ) {
      gen::evg *event_set = new gen::evg("temp.root",1);
      event_set->ReadParameters();
      event_set->CheckParameters();
      event_set->RunEvents();
      remove("output/temp.root");
    }
    
    else {
      usage();
    }
  }
  return 0;
}

