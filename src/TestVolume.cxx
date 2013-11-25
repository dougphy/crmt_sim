#include "TestVolume.h"

namespace geo {
  
  TestVolume::TestVolume() {}
  
  TestVolume::TestVolume(const std::string type, double radius)
  {
    fType   = type;
    fRadius = radius;
    fLength = 0;
    fHeight = 0;
    fWidth  = 0;
  }
  
  TestVolume::TestVolume(const std::string type, double length, double width, double height)
  {
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
