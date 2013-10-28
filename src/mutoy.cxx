#include <iostream>
#include "evd.h"
#include "evg.h"

#define Pi 3.1415926

void usage()
{
  std::cout << "mutoy usage" << std::endl;
}

int main(int argc, char *argv[])
{
  std::cout << "Based God Simulation Under Construction" << std::endl;
  evg *event_set = new evg("file.root",10000);
  event_set->ReadParameters();
  event_set->CheckParameters();
  event_set->RunEvents();

  return 0;


}


