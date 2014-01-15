#include "Module.h"
#include <stdio.h>
#include <iostream>

int main()
{
  geo::Module mod0(0,200.0);
  geo::Module mod1(1,200.0);
  geo::Module mod2(2,200.0);
  geo::Module mod3(3,200.0);
  
  auto map0 = mod0.GetMap();
  auto map1 = mod1.GetMap();
  auto map2 = mod2.GetMap();
  auto map3 = mod3.GetMap();
  
  printf("MOD 0\n********\n");
  for ( auto loc : map0 ) {
    printf("%d ",loc.first);
    printf("%4.8f %4.8f \n",loc.second.first,loc.second.second);
  }
  printf("MOD 1\n\n");
  for ( auto loc : map1 ) {
    printf("%d ",loc.first);
    printf("%4.8f %4.8f \n",loc.second.first,loc.second.second);
  }
  printf("MOD 2\n\n");
  for ( auto loc : map2 ) {
    printf("%d ",loc.first);
    printf("%4.8f %4.8f \n",loc.second.first,loc.second.second);
  }
  printf("MOD 3\n\n");
  for ( auto loc : map3 ) {
    printf("%d ",loc.first);
    printf("%4.8f %4.8f \n",loc.second.first,loc.second.second);
  }
  return 0;
}
