//////////////////////////////////////////////////////////////////////
/// \file TestVolume.cxx
/// \brief TestVolume class methods
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#include "TestVolume.h"

namespace geo {
  
  TestVolume::TestVolume() {}
  
  TestVolume::TestVolume(const std::string& type, const double& radius)
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
  
  TestVolume::TestVolume(const std::string& type, const double& length, 
			 const double& width, const double& height)
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

  void TestVolume::SetOrigin(const double& x, const double& y, const double& z)
  {
    fXO = x;
    fYO = y;
    fZO = z;
  }
  
}
