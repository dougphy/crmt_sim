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

void Line::SetPhiTheta(double phi, double theta)
{
  fPhi = phi;
  fTheta = theta;
}

void Line::SetPlanarAngles()
{
  fAngleXZ = tan(fTheta)/sqrt(1+pow(tan(fPhi),2));
  fAngleYZ = tan(fTheta)*tan(fPhi)/sqrt(1+pow(tan(fPhi),2));
}

void Line::SetSlopes()
{
  fSlopeXZ = 1/tan(fAngleXZ);
  fSlopeYZ = 1/tan(fAngleYZ);
}

void Line::SetTraj()
{
  //
}
