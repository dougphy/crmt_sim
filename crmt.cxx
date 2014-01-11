//////////////////////////////////////////////////////////////////////
/// \file crmt.cxx
/// \brief Main file calls classes based on user arguments
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

/*! \mainpage The crmt_sim software package (v1.0)
 *
 * \section intro_sec Introduction
 *
 * crmt_sim is a simulation of the UTuT detector at UT Austin. <BR>
 * The package is dependent on ROOT (http://root.cern.ch/)
 * Tested versions of ROOT, v5-34-10 and later (as of 01/2014)
 *
 * \section install_sec Installation and running
 *
 * See UTKLDocDB-doc-780 for a description of this software <BR>
 * <BR>
 * === To compile with CMake === <BR>
 * $ mkdir build <BR>
 * $ cd build <BR>
 * $ cmake -DROOT_HOME=$ROOTSYS .. <BR>
 * $ make <BR>
 * <BR>
 * === Running === <BR>
 * (* return back to main directory (cd .. from previous step) *) <BR>
 * execute with: <BR>
 * $ bin/crmt <BR>
 * usage will be displayed <BR>
 * <BR>
 * === Configuration file setting === <BR>
 * See above DocDB entry for description <BR>
 * <BR>
 * === Tested Compilers === <BR>
 * * LLVM/Clang 3.3 on OS X <BR>
 * * LLVM/Clang 3.2 on Ubuntu <BR>
 * * LLVM/Clang 3.0 on FreeBSD <BR>
 * * GCC g++ 4.8.1 on Ubuntu <BR>
 * * GCC g++ 4.8.2 on FreeBSD <BR>
 *
 */

#include <iostream>
// Check to see if GNU C++ compiler
// (Needed for g++48 w/ FreeBSD)
#if __GNUG__
#include <cstdlib>
#endif
// crmt library includes
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
	ev::evg *event_set = new ev::evg(fname.c_str(),events);
	event_set->ReadParameters();
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
	ev::evd *display = new ev::evd();
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
      ev::evg *event_set = new ev::evg("temp.root",1);
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

