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
#include "boost/program_options.hpp"

int main(int argc, char *argv[])
{
  namespace po = boost::program_options;
  po::options_description desc("Options");
  desc.add_options()
    ("help,h","Print help message")
    ("generate,g",po::value<std::string>(),
     "generate events -g output file name")
    ("display,d",po::value<std::string>(),
     "run the event display -d input file name")
    ("true,t","true event display (without multiplexing)")
    ("sim,s","simulated event display (with multiplexing)")
    ("num-events,n",po::value<int>(),"set number of events")
    ("event-id,e",po::value<int>(),"event ID for display");
  
  po::variables_map vm;
  po::store(po::parse_command_line(argc,argv,desc),vm);
  po::notify(vm);
  
  if ( vm.count("help") ) {
    std::cout << desc << std::endl;
    return 0;
  }
  
  else if ( vm.count("generate") ) {
    if ( vm.count("num-events") ) {
      ev::evg event_set(vm["generate"].as<std::string>(),
			vm["num-events"].as<int>());
      event_set.ReadParameters();
      event_set.RunEvents();
      std::cout << "root file written" << std::endl;
    }
    else
      std::cout << desc << std::endl;
  }
  
  else if ( vm.count("display") ) {
    ev::evd display;
    display.InitFile(vm["display"].as<std::string>(),
		vm["event-id"].as<int>());
    if ( vm.count("true") )
      display.DrawTrue(argc,argv);
    else if ( vm.count("sim") )
      display.DrawSim(argc,argv);
    else
      std::cout << desc << std::endl;
  }

  else
    std::cout << desc << std::endl;

  return 0;
}

