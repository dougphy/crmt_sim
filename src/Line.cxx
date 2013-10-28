
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy Line methods _______________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#include <iostream>
#include <cmath>
#include "Line.h"

Line::Line() {}

Line::~Line() {}

void Line::SetInitialPos(double x, double y, double z)
{
  fX0 = x;
  fY0 = y;
  fZ0 = z;
}

void Line::SetLinePropertiesFromPhiTheta(double phi, double theta)
{
  fPhi = phi;
  fTheta = theta;

  double x = sin(theta)*cos(phi);
  double y = sin(theta)*sin(phi);
  double z = cos(theta);
  
  fAngleXZ = atan2(x,z);
  fAngleYZ = atan2(y,z);
		  
  fSlopeXZ = -1/tan(fAngleXZ);
  fSlopeYZ = -1/tan(fAngleYZ);

  fYintXZ = fZ0 - fSlopeXZ*fX0;
  fYintYZ = fZ0 - fSlopeYZ*fY0;
}
