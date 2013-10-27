
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

  // x = r*sin(theta)*cos(phi)
  // y = r*sin(theta)*sin(phi)
  // z = r*cos(theta)
  // tan(angleXZ) = x/z
  // tan(angleYZ) = y/z

  fAngleXZ = tan(fTheta)/sqrt(1+pow(tan(fPhi),2));
  fAngleYZ = tan(fTheta)*tan(fPhi)/sqrt(1+pow(tan(fPhi),2));

  fSlopeXZ = 1/tan(fAngleXZ);
  fSlopeYZ = 1/tan(fAngleYZ);
}
