//////////////////////////////////////////////////////////////////////
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
    void SetInitialPos(double x, double y, double z);

    /// Set's the angles in spherical 3D space (phi,theta)
    void SetLinePropertiesFromPhiTheta(double phi, double theta);

    /// Set's the remaining attributes of the line from Phi and Theta
    void SetLinePropertiesFromAngles();

    /// Manually sets the xz projection angle
    inline void SetAngleXZ(double x);

    /// Manually sets the yz projection angle
    inline void SetAngleYZ(double y);

    const double& Tx()      const { return fTx;      }
    const double& Ty()      const { return fTy;      }
    const double& Tz()      const { return fTz;      }
    const double& X0()      const { return fX0;      }
    const double& Y0()      const { return fY0;      }
    const double& Z0()      const { return fZ0;      }
    const double& Theta()   const { return fTheta;   }
    const double& Phi()     const { return fPhi;     }
    const double& AngleYZ() const { return fAngleYZ; }
    const double& AngleXZ() const { return fAngleXZ; }
    const double& SlopeXZ() const { return fSlopeXZ; }
    const double& SlopeYZ() const { return fSlopeYZ; }
    const double& YintXZ()  const { return fYintXZ;  }
    const double& YintYZ()  const { return fYintYZ;  }

  };

}
#endif
