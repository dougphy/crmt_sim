//////////////////////////////////////////////////////////////////////
/// \file Module.h
/// \brief A class which describes a single module
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#ifndef MODULE_H
#define MODULE_H

#include <map>
#include <vector>

namespace geo {

  class Module {
  
  private:
    int          fModuleType;           ///< Module type (1, 2, 3, or 4)
    double       fScintWidth  = 10.40;  ///< scintillator width
    double       fScintHeight = 30.80;  ///< scintillator height
    double       fStripShift  = 3.333;  ///< 1/3 cm shift for rows
    double       fScintGap    = 4.800;  ///< gap between rows
    double       fModGap      = 6.400;  ///< gap between modules
    double       fScintShift  = 3.333;  ///< 1/3 cm shift for rows (needed repeat)
    double       fGap;                  ///< gap between 2 halves
  
    std::map<int, std::pair<double,double> > fFiberMap; ///< map of fiber locations
  
  public:

    /// Default constructor takes no arguments
    Module();

    /// Constructor used takes module type and gap arguments
    Module(int module_type, double gap);

    /// Virtual destructor
    virtual ~Module();

    inline std::map<int, std::pair<double,double> > GetMap()        const { return fFiberMap;   }
    inline int                                      GetModuleType() const { return fModuleType; }
  };
}

#endif
