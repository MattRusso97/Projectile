#include <iostream>
#include <cmath>
#include <fstream>
#include "Proj.h"
using namespace std;

//----SpeedCalculator class's implementation----//

SpeedCalculator::SpeedCalculator(double x0, double y0, double v0x, double v0y, double m, double b){
  x0_ = x0;
  y0_ = y0;
  v0x_ = v0x;
  v0y_ = v0y;
  m_ = m;
  b_ = b;
  g = 9.81;
}

SpeedCalculator::~SpeedCalculator(){
  cout << "SpeedCalculator is destroyed!" << endl;
}

void SpeedCalculator::Set_x0(double x0){
  x0_ = x0;
}

void SpeedCalculator::Set_y0(double y0){
  y0_ = y0;
}

void SpeedCalculator::Set_v0x(double v0x){
  v0x_ = v0x;
}

void SpeedCalculator::Set_v0y(double v0y){
  v0y_ = v0y;
}

void SpeedCalculator::Set_m(double m){
  m_ = m;
}

void SpeedCalculator::Set_b(double b){
  b_ = b;
}

double SpeedCalculator::Get_x0() const {
  return x0_;
}

double SpeedCalculator::Get_y0() const {
  return y0_;
}

double SpeedCalculator::Get_v0x() const {
  return v0x_;
}

double SpeedCalculator::Get_v0y() const {
  return v0y_;
}

double SpeedCalculator::Get_m() const {
  return m_;
}

double SpeedCalculator::Get_b() const {
  return b_;
}

double SpeedCalculator::Get_g() const {
  return g;
}

void SpeedCalculator::print() const {
  cout << "x0 = " << x0_ << endl
       << "y0 = " << y0_ << endl
       << "vx0 = " << v0x_ << endl
       << "vy0 = " << v0y_ << endl
       << "m = " << m_ << endl
       << "b = " << b_ << endl;
}

//----Analytical class implementation----//

Analytical::Analytical(double x0, double y0, double v0x, double v0y, double m, double b): SpeedCalculator(x0, y0, v0x, v0y, m, b) {};

Analytical::~Analytical(){
  cout << "Analytical is destroyed!" << endl;
}

void Analytical::velocity(double dt, double N) const{

  double t = 0, Vx = 0, Vy = 0;

  ofstream myfile("analitical.txt");

  for(int j = 0; j < N; j++){
  
  Vx = Get_v0x()*exp(- Get_b()*t/Get_m());
  Vy = Get_v0y()*exp(- Get_b()*t/Get_m()) - Get_m()*Get_g()*(1 - exp(- Get_b()*t/Get_m()))/Get_b();

  myfile << Vx << "\t" << Vy << "\t" << t << endl;
  
  t += dt;
  }
  myfile.close();
}


//----RungeKutta2 class implementation----//

RungeKutta2::RungeKutta2(double x0, double y0, double v0x, double v0y, double m, double b): SpeedCalculator(x0, y0, v0x, v0y, m, b) {};

RungeKutta2::~RungeKutta2(){
  cout << "Analytical is destroyed!" << endl;
}

void RungeKutta2::velocity(double dt, double N) const{

  ofstream myfile("runge.txt");
  double t = 0;
  double V0x = Get_v0x();
  double V0y = Get_v0y();

  for(int i = 0; i < N; i++){

     myfile << V0x << "\t" << V0y << "\t" << t << endl;

     double K1x = dt*(- Get_b()*V0x*exp(- Get_b()*t/Get_m())/Get_m());
     double K1y = dt*(- Get_b()*V0y*exp(- Get_b()*t/Get_m())/Get_m() - Get_g()*exp(- Get_b()*t/Get_m()));
    
     double K2x = dt*(- Get_b()*(V0x + K1x*dt/2.)*exp(- Get_b()*(t + dt/2.)/Get_m())/Get_m());
     double K2y = dt*(- Get_b()*(V0y + K1y*dt/2.)*exp(- Get_b()*(t + dt/2.)/Get_m())/Get_m() - Get_g()*exp(- Get_b()*(t + dt/2.)/Get_m()));
    
     double Vx = V0x + K2x;
     double Vy = V0y + K2y;
    
     t += dt;
     V0x = Vx;
     V0y = Vy;
  }
  myfile.close();
}
