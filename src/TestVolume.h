
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
    
    void SetOrigin(double x, double y, double z);

    double GetLength() const {return fLength; }
    double GetWidth()  const {return fWidth;  }
    double GetHeight() const {return fHeight; }
    double GetRadius() const {return fRadius; }    
    double GetXO()     const {return fXO;     }
    double GetYO()     const {return fYO;     }
    double GetZO()     const {return fZO;     }

  };

}

#endif
