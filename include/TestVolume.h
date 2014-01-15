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
    
    std::string fType;    ///< test volume type (box or sphere currently suppored)
    double      fRadius;  ///< sphere test volume radius
    double      fLength;  ///< box test volume length (x)
    double      fHeight;  ///< box test volume height (z)
    double      fWidth;   ///< box test volume width (y)
    double      fXO;      ///< test volume x center
    double      fYO;      ///< test volume y center
    double      fZO;      ///< test volume z center
    
  public:
    
    /// Default constructor
    TestVolume();
 
    /// Constructor for a sphere (type, radius)
    TestVolume(const std::string& type, double radius);

    /// Constructor for a box (type, length, width, height)
    TestVolume(const std::string& type, double length,
	       double width, double height);

    /// virtual destructor
    virtual ~TestVolume();
    
    /// Set the origin of the test volume
    void SetOrigin(double x, double y, double z);

    const double GetLength() const;
    const double GetWidth()  const;
    const double GetHeight() const;
    const double GetRadius() const;
    const double GetXO()     const;
    const double GetYO()     const;
    const double GetZO()     const;

  };

}

inline const double geo::TestVolume::GetLength() const { return fLength; }
inline const double geo::TestVolume::GetWidth()  const { return fWidth;  }
inline const double geo::TestVolume::GetHeight() const { return fHeight; }
inline const double geo::TestVolume::GetRadius() const { return fRadius; }
inline const double geo::TestVolume::GetXO()     const { return fXO;     }
inline const double geo::TestVolume::GetYO()     const { return fYO;     }
inline const double geo::TestVolume::GetZO()     const { return fZO;     }

#endif
