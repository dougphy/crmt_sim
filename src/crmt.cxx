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
/*
int main()
{
  geo::TestVolume *tSphere = new geo::TestVolume("sphere",6.5);
  geo::TestVolume *tBox    = new geo::TestVolume("box",1.2,3.4,5.2);

  double tS_rad = tSphere->GetRadius();
  double tS_wid = tSphere->GetWidth();
  double tS_hei = tSphere->GetHeight();
  double tS_len = tSphere->GetLength();
  
  double tB_rad = tBox->GetRadius();
  double tB_wid = tBox->GetWidth();
  double tB_hei = tBox->GetHeight();
  double tB_len = tBox->GetLength();

  std::cout << "s_rad = " << tS_rad << std::endl;
  std::cout << "s_wid = " << tS_wid << std::endl;
  std::cout << "s_hei = " << tS_hei << std::endl;
  std::cout << "s_len = " << tS_len << std::endl;

  std::cout << "b_rad = " << tB_rad << std::endl;
  std::cout << "b_wid = " << tB_wid << std::endl;
  std::cout << "b_hei = " << tB_hei << std::endl;
  std::cout << "b_len = " << tB_len << std::endl;
  
  return 0;
}
*/

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
	evg *event_set = new evg(fname.c_str(),events);
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
	evd *display = new evd();
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
      evg *event_set = new evg("temp.root",1);
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

