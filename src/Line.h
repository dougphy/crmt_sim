
// __________________________________________________________________
// __________________________________________________________________
// _______ crmt Line class __________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#ifndef LINE_H
#define LINE_H

#include <cmath>
#include <iostream>

namespace geo {

  class Line {
  
  protected:

    double fTx;
    double fTy;
    double fTz;
    double fX0;
    double fY0;
    double fZ0;
    double fTheta;
    double fPhi;
    double fAngleXZ;
    double fAngleYZ;
    double fSlopeXZ;
    double fSlopeYZ;
    double fYintXZ;
    double fYintYZ;

  public:

    Line();
    virtual ~Line();

    void SetInitialPos(double x, double y, double z);
    void SetLinePropertiesFromPhiTheta(double phi, double theta);
    void SetLinePropertiesFromAngles();

    inline void SetAngleXZ(double x);
    inline void SetAngleYZ(double y);

    inline double Tx()      const { return fTx;      }
    inline double Ty()      const { return fTy;      }
    inline double Tz()      const { return fTz;      }
    inline double X0()      const { return fX0;      }
    inline double Y0()      const { return fY0;      }
    inline double Z0()      const { return fZ0;      }
    inline double Theta()   const { return fTheta;   }
    inline double Phi()     const { return fPhi;     }
    inline double AngleYZ() const { return fAngleYZ; }
    inline double AngleXZ() const { return fAngleXZ; }
    inline double SlopeXZ() const { return fSlopeXZ; }
    inline double SlopeYZ() const { return fSlopeYZ; }
    inline double YintXZ()  const { return fYintXZ;  }
    inline double YintYZ()  const { return fYintYZ;  }

  };

}
#endif
