
// __________________________________________________________________
// __________________________________________________________________
// _______ mutoy Module class _______________________________________
// _______ Douglas Davis ____________________________________________
// _______ Fall 2013 ________________________________________________
// __________________________________________________________________

#ifndef MODULE_H
#define MODULE_H

#include <map>
#include <vector>

class Module {
  
private:
  int          fModuleType;
  double       fScintWidth  = 10.40;
  double       fScintHeight = 30.80;
  double       fStripShift  = 0.333;
  double       fScintGap    = 4.800;
  double       fModGap      = 6.400;
  double       fScintShift  = 0.333;
  double       fGap;
  
  std::map<int, std::pair<double,double> > fFiberMap;
  
public:
  Module();
  Module(int module_type, double gap);
  ~Module();
  std::map<int, std::pair<double,double> > GetMap() { return fFiberMap; }
  int GetModuleType() { return fModuleType; }
};

#endif
