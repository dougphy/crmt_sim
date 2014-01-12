//////////////////////////////////////////////////////////////////////
/// \file Module.cxx
/// \brief Module class methods
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Module.h"

namespace geo {

  Module::Module() {}

  Module::Module(unsigned int module_type, double gap)
  {
    fModuleType = module_type;
    fGap        = gap;
    double y;
    double x = 0;
    double raise;
    
    switch ( fModuleType ) {
    case 0:
      raise = 3*(4*fScintHeight+3*fScintGap)+gap;
      break;
    case 1:
      raise = 2*(4*fScintHeight+3*fScintGap)+gap;
      break;
    case 2:
      raise = 1*(4*fScintHeight+3*fScintGap);
      break;
    case 3:
      raise = 0;
      break;
    default:
      std::cout << "fModuleType bad in Module::Module" << std::endl;
      break;
    }
    
    for (int i = 0; i < 256; i++) {
      if ( i < 64 ) {
	y = fScintShift+fModGap+3*fScintGap+3.5*fScintHeight+raise;
	x = (0.5+i)*fScintWidth;
	fFiberMap[i] = std::make_pair(x,y);
      }
      else if ( i > 63 && i < 128 ) {
	y = fModGap+2*fScintGap+2.5*fScintHeight+raise;
	x = 2*fScintShift+(0.5+(i-64))*fScintWidth;
	fFiberMap[i] = std::make_pair(x,y);
      }
      else if ( i > 127 && i < 192) {
	y = fModGap+1*fScintGap+1.5*fScintHeight+raise;
	x = fScintShift+(0.5+(i-128))*fScintWidth;
	fFiberMap[i] = std::make_pair(x,y);
      }
      else if ( i > 191 ) {
	y = fModGap+0.5*fScintHeight+raise;
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
