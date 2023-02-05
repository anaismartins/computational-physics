#ifndef __Integrator__
#define __Integrator__

#include "TF1.h"
#include "Func1D.h"

class Integrator : public Func1D {

public:
	//constructors
	Integrator(double fx0 = 0., double fx1 = 1., const TF1 *fp = nullptr) : x0 (fx0), x1 (fx1), Func1D(fp) {;}
	Integrator(const TF1* f);
	Integrator(double fx0, double fx1, const TF1& fp) : Integrator(fx0, fx1, &fp) {;};
	//destructor
	~Integrator() = default;

	//methods
	void TrapezoidalRule(double, double, double&); //feito pelos exercícios

	void Trapezoidal(int n, double& Integral, double& Error);// header feito pelo prof - FALTA O ERRO
	void TrapezoidalAdaptive(double&, double&);
	//void Simpson(int n, double& Integral, double& Error);
	void Romberg(double&);

protected:
	const TF1* func;
	double x0;
	double x1;

};

#endif
