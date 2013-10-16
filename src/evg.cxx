#include <map>
#include <vector>
#include "evg.h"

evg::evg() {}

evg::evg(std::string file_name, int n_events)
{
  fFile    = new TFile(file_name.c_str(),"RECREATE");
  fNEvents = n_events;
}

evg::~evg() {}
