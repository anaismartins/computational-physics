#ifndef __Integrator__
#define __Integrator__

#include "TF1.h"
#include "Func1D.h"

class Integrator : public Func1D {

public:
	//constructors
	Integrator(double fx0 = 0., double fx1 = 1., const TF1 *fp = nullptr) : x0 (fx0), x1 (fx1), Func1D(fp) {;}
    Integrator(const TF1* f) : Func1D(f), x0(func->GetXmin()), x1(func->GetXmax()) {;}
	Integrator(double fx0, double fx1, const TF1& fp) : Integrator(fx0, fx1, &fp) {;};
	//destructor
	~Integrator() = default;

	//methods
	void TrapezoidalRule(double, double, double&); //feito pelos exercícios

	void Trapezoidal(int n, double& Integral, double& Error);// header feito pelo prof
  void TrapezoidalAdaptive(int n, double&, double&); //n, Integral, error
	//void Simpson(int n, double& Integral, double& Error);
	void Romberg(double&, double&, int& n);//Integral, error, n
  double IntegralPercentageOf(double, double, double&, double percentage0 = -1, double fx = 0); //percentage, 1 = '>' | -1 = '<', error

protected:
	double x0;
	double x1;

};

#endif
