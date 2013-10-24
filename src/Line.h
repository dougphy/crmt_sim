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

public:
  Line();
  ~Line();
  void SetInitialPos(double x, double y, double z);
  void SetPhiTheta(double phi, double theta);
  void SetTraj();
  void SetPlanarAngles();
  double Tx()     { return fTx;    }
  double Ty()     { return fTy;    }
  double Tz()     { return fTz;    }
  double X0()     { return fX0;    }
  double Y0()     { return fY0;    }
  double Z0()     { return fZ0;    }
  double Theta()  { return fTheta; }
  double Phi()    { return fPhi;   }

};

#endif
