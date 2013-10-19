#include <iostream>
#include "Module.h"

Module::Module() {}

Module::Module(int type)
{
  double y;
  double x;
  fModuleType = type;
  for (int i = 0; i < 256; i++) {
    if ( i < 64 ) {
      y = fModGap+fScintGap+0.5*fScintHeight;
      x = (0.5+i)*fScintWidth;
      fFiberMap[i] = std::make_pair(x,y);
    }
    
    else {
      std::cout << "Mad fFiberMap key" << std::endl;
      continue;
    }
  }
}  

Module::~Module() {}

