//////////////////////////////////////////////////////////////////////
/// \file Module.cxx
/// \brief Module class methods
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Module.h"

namespace geo {

  Module::Module() {}

  Module::Module(const unsigned int& module_type, const double& gap)
  {
    fModuleType = module_type;
    fGap        = gap;

    double y;
    double x = 0;
    double raise;
    
    switch ( fModuleType ) {
    case 0:
      raise = 3*(4*fScintHeight+3*fScintGap)+gap+7*fModGap;
      break;
    case 1:
      raise = 2*(4*fScintHeight+3*fScintGap)+gap+5*fModGap;
      break;
    case 2:
      raise = 1*(4*fScintHeight+3*fScintGap)+3*fModGap;
      break;
    case 3:
      raise = fModGap;
      break;
    default:
      raise = 0;
      std::cout << "fModuleType bad in Module::Module, raise set to 0." << std::endl;
      break;
    }
    
    for (int i = 0; i < 256; i++) {
      if ( i < 64 ) {
	y = 3*fScintGap+3.5*fScintHeight+raise;
	x = fScintShift+(0.5+i)*fScintWidth;
	fFiberMap[i] = std::make_pair(x,y);
      }
      else if ( i > 63 && i < 128 ) {
	y = 2*fScintGap+2.5*fScintHeight+raise;
	x = 2*fScintShift+(0.5+(i-64))*fScintWidth;
	fFiberMap[i] = std::make_pair(x,y);
      }
      else if ( i > 127 && i < 192) {
	y = 1*fScintGap+1.5*fScintHeight+raise;
	x = fScintShift+(0.5+(i-128))*fScintWidth;
	fFiberMap[i] = std::make_pair(x,y);
      }
      else if ( i > 191 ) {
	y = .5*fScintHeight+raise;
	x = (0.5+(i-192))*fScintWidth;
	fFiberMap[i] = std::make_pair(x,y);
      }	     
      else {
	std::cout << "Mad fFiberMap key" << std::endl;
	continue;
      }
    }
  }  
  
  Module::~Module() {}
 
}
