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
  double       fGap;
  
  std::map<int[256], std::vector<double> > fFibMap;
  
public:
  Module();
  Module(int type);
  ~Module();
};

#endif
