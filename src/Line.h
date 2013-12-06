
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
    ~Line();

    void SetInitialPos(double x, double y, double z);
    void SetLinePropertiesFromPhiTheta(double phi, double theta);
    void SetLinePropertiesFromAngles();

    void SetAngleXZ(double x);
    void SetAngleYZ(double y);

    double Tx()      const { return fTx;      }
    double Ty()      const { return fTy;      }
    double Tz()      const { return fTz;      }
    double X0()      const { return fX0;      }
    double Y0()      const { return fY0;      }
    double Z0()      const { return fZ0;      }
    double Theta()   const { return fTheta;   }
    double Phi()     const { return fPhi;     }
    double AngleYZ() const { return fAngleYZ; }
    double AngleXZ() const { return fAngleXZ; }
    double SlopeXZ() const { return fSlopeXZ; }
    double SlopeYZ() const { return fSlopeYZ; }
    double YintXZ()  const { return fYintXZ;  }
    double YintYZ()  const { return fYintYZ;  }

  };

}
#endif
