
// __________________________________________________________________
// __________________________________________________________________
// _______ crmt TestVolume class ____________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

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
    ~TestVolume();
    
    virtual void SetOrigin(double x, double y, double z);    

    double GetLength() { return fLength; }
    double GetWidth()  { return fWidth;  }
    double GetHeight() { return fHeight; }
    double GetRadius() { return fRadius; }    
    double GetXO()     { return fXO;     }
    double GetYO()     { return fYO;     }
    double GetZO()     { return fZO;     }

  };

}

#endif
