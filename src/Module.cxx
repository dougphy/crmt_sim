#include <iostream>
#include "Module.h"

Module::Module() {}

Module::Module(int type)
{
  fModuleType = type;
  double y;
  double x = 0;
  double raise;
  if ( fModuleType == 0 )
    raise = 3*(fScintHeight+fScintGap);
  else if ( fModuleType == 1 )
    raise = 2*(fScintHeight+fScintGap);
  else if ( fModuleType == 2 )
    raise = 1*(fScintHeight+fScintGap);
  else if ( fModuleType == 3 )
    raise = 0;
  else
    std::cout << "fModuleType bad in Module::Module" << std::endl;

  for (int i = 0; i < 256; i++) {
    if ( i < 64 ) {
      y = fModGap+0.5*fScintHeight+raise;
      x = (0.5+i)*fScintWidth;
      fFiberMap[i] = std::make_pair(x,y);
    }
    else if ( i > 63 && i < 128 ) {
      y = fModGap+fScintGap+1.5*fScintHeight+raise;
      x = (0.5+(i-64))*fScintWidth;
      fFiberMap[i] = std::make_pair(x,y);
    }
    else if ( i > 127 && i < 192) {
      y = fModGap+2*fScintGap+2.5*fScintHeight+raise;
      x = (0.5+(i-128))*fScintWidth;
      fFiberMap[i] = std::make_pair(x,y);
    }
    else if ( i > 191 ) {
      y = fModGap+3*fScintGap+3.5*fScintHeight+raise;
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

