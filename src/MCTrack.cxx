//////////////////////////////////////////////////////////////////////
/// \file MCTrack.cxx
/// \brief MCTrack class methods
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include "MCTrack.h"

namespace geo {

  MCTrack::MCTrack() {}

  MCTrack::~MCTrack() {}

  void MCTrack::SetInitialPos(const double& x, const double& y, const double& z)
  {
    fX0 = x;
    fY0 = y;
    fZ0 = z;
  }

  void MCTrack::SetAngleXZ(const double& x)
  {
    fAngleXZ = x;
  }

  void MCTrack::SetAngleYZ(const double& y)
  {
    fAngleYZ = y;
  }

  void MCTrack::SetMCTrackPropertiesFromPhiTheta(const double& phi, const double& theta)
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

    fBottomX = -fYintXZ/fSlopeXZ;
    fBottomY = -fYintYZ/fSlopeYZ;
    fBottomZ = 0.0;
  }

  void MCTrack::SetMCTrackPropertiesFromAngles()
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
