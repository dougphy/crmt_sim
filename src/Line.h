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
public:
  Line();
  ~Line();
  void SetInitialPos(double x, double y, double z);
  void SetInitialTraj(double tx, double ty, double tz);
  void SetTheta(double theta);
  void SetPhi(double phi);
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
