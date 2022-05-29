#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

class SpeedCalculator{
 public:
  SpeedCalculator(double x0, double y0, double v0x, double v0y, double m, double b);  //SpeedCalculator constructor
  virtual ~SpeedCalculator() = 0; //virtual SpeedCalculator destructor

  virtual void velocity(double dt, double N) const = 0; //Virtual method 

  //Setters for the initial position and  velocity
  void Set_x0(double x0); 
  void Set_y0(double y0); 

  void Set_v0x(double v0x);
  void Set_v0y(double v0y);

  //Setters for constant physical parametres
  void Set_m(double m); 
  void Set_b(double b); 

  //Getters for the initial position and  velocity
  double Get_x0() const; 
  double Get_y0() const; 
  double Get_v0x() const; 
  double Get_v0y() const;

  //Getters for constant physical parametres
  double Get_m() const; 
  double Get_b() const;
  double Get_g() const; 

  void print() const; //Print method

 private:
  //Initial position
  double x0_;  
  double y0_;

  //Initial velocity
  double v0x_;  
  double v0y_;

  //constant parametres
  double m_;  //Point material's mass
  double b_;  //Friction factor of the medium
  double g;   //Gravitational constant
};


class Analytical: public SpeedCalculator{
 public:
  Analytical(double x0, double y0, double v0x, double v0y, double m, double b);
  virtual ~Analytical();

  virtual void velocity(double dt, double N) const;
};


class RungeKutta2: public SpeedCalculator{
 public:
  RungeKutta2(double x0, double y0, double v0x, double v0y, double m, double b);
  virtual ~RungeKutta2();

  virtual void velocity(double t, double N) const;
};

