#include <iostream>
#include <cmath>
#include "Proj.h"
using namespace std;

//Let's show how SpeedCalculator and RungeKutta classes work:

int main(){
  Analytical a(10., 10., 15., 15., 25., 0.15);
  a.velocity(0.01, 1000);
  a.print();

  RungeKutta2 b(10., 10., 15., 15., 25., 0.15);
  b.velocity(0.01, 1000);
  b.print();
  
  return 0;
}
