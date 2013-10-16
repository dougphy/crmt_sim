#include <iostream>
#include "evd.h"
#include "evg.h"

void usage()
{
  std::cout << "mutoy usage" << std::endl;
}

int main(int argc, const char *argv[])
{
  std::cout << "Based God Simulation" << std::endl;
  evg *event_set = new evg("file1.root",55);
  event_set->SaveFile();
}

