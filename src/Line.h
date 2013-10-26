
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy Line class _________________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#ifndef LINE_H
#define LINE_H

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

public:

  Line();
  ~Line();

  void SetInitialPos(double x, double y, double z);
  void SetLinePropertiesFromPhiTheta(double phi, double theta);

  double Tx()      { return fTx;      }
  double Ty()      { return fTy;      }
  double Tz()      { return fTz;      }
  double X0()      { return fX0;      }
  double Y0()      { return fY0;      }
  double Z0()      { return fZ0;      }
  double Theta()   { return fTheta;   }
  double Phi()     { return fPhi;     }
  double AngleYZ() { return fAngleYZ; }
  double AngleXZ() { return fAngleXZ; }
  double SlopeXZ() { return fSlopeXZ; }
  double SlopeYZ() { return fSlopeYZ; }

};

#endif
