#ifndef MODULE_H
#define MODULE_H

#include <map>
#include <vector>

class Module {
  
private:
  int          fModuleType;
  const double fScintWidth  = 10.4;
  const double fScintHeight = 30.8;
  const double fStripShift  = 0.33;
  const double fScintGap    = 4.80;
  const double fModGap      = 6.40;
  const double fScintShift  = 0.33;
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
