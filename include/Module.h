//////////////////////////////////////////////////////////////////////
/// \class Module
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
    unsigned int fModuleType; 
    double       fScintWidth  = 10.40;
    double       fScintHeight = 30.80;
    double       fScintGap    = 4.800;
    double       fModGap      = 6.400;
    double       fScintShift  = 3.333;
    double       fGap;        
  
    std::map<int, std::pair<double,double> > fFiberMap; ///< map of fiber locations
  
  public:

    /// Default constructor takes no arguments
    Module();

    /// Constructor used takes module type and gap arguments
    Module(const unsigned int& module_type, const double& gap);

    /// Virtual destructor
    virtual ~Module();
    
    const std::map<int, std::pair<double,double> > GetMap()        const;
    const unsigned int                             GetModuleType() const;
  };
}

inline const std::map<int, std::pair<double,double> > geo::Module::GetMap()        const { return fFiberMap;   }
inline const unsigned int                             geo::Module::GetModuleType() const { return fModuleType; } 

#endif
