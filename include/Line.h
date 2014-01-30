//////////////////////////////////////////////////////////////////////
/// \class Line
/// \file Line.h
/// \brief A class which describes the geometric muon line in 3D
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#ifndef LINE_H
#define LINE_H

#include <cmath>
#include <iostream>

namespace geo {

  class Line {
    
  private:
    
    double fTx;        ///< x trajectory unit vector
    double fTy;        ///< y trajectory unit vector
    double fTz;        ///< z trajectory unit vector
    double fX0;        ///< x initial position
    double fY0;        ///< y initial position
    double fZ0;        ///< z initial position
    double fBottomX;  ///< bottom x point for drawing ev3d
    double fBottomY;  ///< bottom y point for drawing ev3d
    double fBottomZ;  ///< bottom z point for drawing ev3d
    double fTheta;     ///< theta, spherical zenith)
    double fPhi;       ///< phi, spherical polar)
    double fAngleXZ;   ///< xz projection zenith angle
    double fAngleYZ;   ///< yz projection zenith angle
    double fSlopeXZ;   ///< xz projection line slope
    double fSlopeYZ;   ///< yz projection line slope
    double fYintXZ;    ///< xz projection line y-int
    double fYintYZ;    ///< yz projection line y-int

  public:

    /// Default constructor
    Line();

    /// Virtual destructor
    virtual ~Line();

    /// Set's the initial position of the muon (x,y,z)
    void SetInitialPos(const double& x, const double& y, const double& z);

    /// Set's the angles in spherical 3D space (phi,theta)
    void SetLinePropertiesFromPhiTheta(const double& phi, const double& theta);

    /// Set's the remaining attributes of the line from Phi and Theta
    void SetLinePropertiesFromAngles();

    /// Manually sets the xz projection angle
    inline void SetAngleXZ(const double& x);

    /// Manually sets the yz projection angle
    inline void SetAngleYZ(const double& y);

    const double Tx()      const;
    const double Ty()      const;
    const double Tz()      const;
    const double X0()      const;
    const double Y0()      const;
    const double Z0()      const;
    const double BottomX() const;
    const double BottomY() const;
    const double BottomZ() const;
    const double Theta()   const;
    const double Phi()     const;
    const double AngleYZ() const;
    const double AngleXZ() const;
    const double SlopeXZ() const;
    const double SlopeYZ() const;
    const double YintXZ()  const;
    const double YintYZ()  const;

  };

}

inline const double geo::Line::Tx()      const { return fTx;      }
inline const double geo::Line::Ty()      const { return fTy;      }
inline const double geo::Line::Tz()      const { return fTz;      }
inline const double geo::Line::X0()      const { return fX0;      }
inline const double geo::Line::Y0()      const { return fY0;      }
inline const double geo::Line::Z0()      const { return fZ0;      }
inline const double geo::Line::BottomX() const { return fBottomX; }
inline const double geo::Line::BottomY() const { return fBottomY; }
inline const double geo::Line::BottomZ() const { return fBottomZ; }
inline const double geo::Line::Theta()   const { return fTheta;   }
inline const double geo::Line::Phi()     const { return fPhi;     }
inline const double geo::Line::AngleXZ() const { return fAngleXZ; }
inline const double geo::Line::AngleYZ() const { return fAngleYZ; }
inline const double geo::Line::SlopeXZ() const { return fSlopeXZ; }
inline const double geo::Line::SlopeYZ() const { return fSlopeYZ; }
inline const double geo::Line::YintXZ()  const { return fYintXZ;  }
inline const double geo::Line::YintYZ()  const { return fYintYZ;  }

#endif
