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
  std::string file_name = argv[1];
  evg *event_set = new evg(file_name.c_str(),55);
  event_set->SaveFile();
}

