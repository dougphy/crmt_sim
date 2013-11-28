
// __________________________________________________________________
// __________________________________________________________________
// _______ crmt TestVolume methods __________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#include "TestVolume.h"

namespace geo {
  
  TestVolume::TestVolume() {}
  
  TestVolume::TestVolume(const std::string type, double radius)
  {
    if ( type != "sphere" ) {
      std::cout << "Test Volume Constructor Bad" << std::endl;
      return;
    }

    fType   = type;
    fRadius = radius;
    fLength = 0;
    fHeight = 0;
    fWidth  = 0;
  }
  
  TestVolume::TestVolume(const std::string type, double length, double width, double height)
  {
    if ( type != "box" ) {
      std::cout << "Test Volume Constructor Bad" << std::endl;
      return;
    }

    fType   = type;
    fRadius = 0;
    fLength = length;
    fHeight = height;
    fWidth  = width;
  }
  
  TestVolume::~TestVolume() {}

  void TestVolume::SetOrigin(double x, double y, double z)
  {
    fXO = x;
    fYO = y;
    fZO = z;
  }
  
}
