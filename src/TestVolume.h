//////////////////////////////////////////////////////////////////////
/// \file TestVolume.h
/// \brief A class which describes a test volume
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#ifndef TESTVOLUME_H
#define TESTVOLUME_H

#include <iostream>

namespace geo {

  class TestVolume {
    
  private:
    
    std::string fType;
    double      fRadius;
    double      fLength;
    double      fHeight;
    double      fWidth;
    double      fXO;
    double      fYO;
    double      fZO;
    
  public:
    
    TestVolume();
    TestVolume(const std::string type, double radius);
    TestVolume(const std::string type, double length, double width, double height);
    virtual ~TestVolume();
    
    void SetOrigin(double x, double y, double z);

    inline double GetLength() const { return fLength; }
    inline double GetWidth()  const { return fWidth;  }
    inline double GetHeight() const { return fHeight; }
    inline double GetRadius() const { return fRadius; }    
    inline double GetXO()     const { return fXO;     }
    inline double GetYO()     const { return fYO;     }
    inline double GetZO()     const { return fZO;     }

  };

}

#endif
