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

void Line::SetTraj()
{
  // Do some stuff with angles

}

void Line::SetPlaneAngles()
{
  // Do some stuff with angles
}
