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
    
    double GetLength() { return fLength; }
    double GetWidth()  { return fWidth;  }
    double GetHeight() { return fHeight; }
    double GetRadius() { return fRadius; }
    
    void SetOrigin(double x, double y, double z);

  };

}

#endif
