#ifndef EVD_H
#define EVD_H

#include <iostream>
#include "TApplication.h"
#include "evg.h"

class evd : public evg {

private:
  TApplication *fApp;

public:
  evd();
  ~evd();
  void Draw();

};

#endif
