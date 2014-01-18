//////////////////////////////////////////////////////////////////////
/// \file Line.cxx
/// \brief Line class methods
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include "Line.h"

namespace geo {

  Line::Line() {}

  Line::~Line() {}

  void Line::SetInitialPos(double x, double y, double z)
  {
    fX0 = x;
    fY0 = y;
    fZ0 = z;
  }

  void Line::SetAngleXZ(double x)
  {
    fAngleXZ = x;
  }

  void Line::SetAngleYZ(double y)
  {
    fAngleYZ = y;
  }

  void Line::SetLinePropertiesFromPhiTheta(double phi, double theta)
  {
    fPhi = phi;
    fTheta = theta;

    double x = sin(theta)*cos(phi);
    double y = sin(theta)*sin(phi);
    double z = cos(theta);
  
    double mag = sqrt(x*x+y*y+z*z);
    fTx = x/mag; fTy = y/mag; fTz = z/mag;

    // QUAD 1 and 2 and 3 and 4 GOOD ?????????
    fAngleXZ = atan2(-1*x,z);
    fAngleYZ = atan2(-1*y,z);
		  
    fSlopeXZ = -1/tan(fAngleXZ);
    fSlopeYZ = -1/tan(fAngleYZ);

    fYintXZ = fZ0 - fSlopeXZ*fX0;
    fYintYZ = fZ0 - fSlopeYZ*fY0;
  }

  void Line::SetLinePropertiesFromAngles()
  {
    fSlopeXZ = -1/tan(fAngleXZ);
    fSlopeYZ = -1/tan(fAngleYZ);
    
    fYintXZ = fZ0 - fSlopeXZ*fX0;
    fYintYZ = fZ0 - fSlopeYZ*fY0;

    fTx = 0; // not needed
    fTy = 0; // not needed
    fTz = 0; // not needed
  }

}
