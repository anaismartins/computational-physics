#include "Integrator.h"

Integrator::Integrator(const TF1* f){

	func = f;

}

void Integrator::TrapezoidalRule(double x1, double x2, double &F){

	if (x1 > x2){
		double temp = x2;
		x2 = x1;
		x1 = temp;
	}

	double h = x2 - x1;

	F = h * (func->Eval(x2) + func->Eval(x1)) / 2;

}

void Integrator::Trapezoidal(int n, double& Integral, double& Error){

  if(n<1)
    throw std::invalid_argument(Form("[%s] invalid number of intervals...!\n", __PRETTY_FUNCTION__));
  
	x1 = func->GetXmax();
	x0 = func->GetXmin();

	double h = (x1 - x0) / n;

	Integral = h * func->Eval(x0) / 2;

	for (int i = 1; i < n - 1; i++)
		Integral += h * func->Eval(x0 + h*i);

	Integral += h * func->Eval(x1) / 2;


	double derivada2 = (func->Derivative(x1) - func->Derivative(x0))/h;
	double avg2D = derivada2/n;
	Error = - h*h * (x1-x0) * avg2D /12;

}

void Integrator::TrapezoidalAdaptive(double& Integral, double& Error){

	x1 = func->GetXmax();
	x0 = func->GetXmin();

	double errorMin;
	if(Error!=0)
	  errorMin = Error;
	else
	  errorMin = 1e-3;

	/*int n = 4;
	double F[n];
	F[0] = (x1 - x0) * (func->Eval(x0) + func->Eval(x1)) / 2;
	for (int k = 2; k < n+2; k++){
	  std::cout << std::endl << F[k-2];

	  double sum = 0.;

	  for (int i = 1; i <= pow(2, k-2); i++){

	    sum += func->Eval(x0 + (2*i - 1)*(x1 - x0)/(pow(2, k-1)));

	  }

	  F[k-1] = (1/2) * F[k-1] + ((x1 - x0) / (pow(2, k-1))) * sum;

	}

	Integral = F[n];*/

	double F = (x1 - x0) * (func->Eval(x0) + func->Eval(x1)) / 2;
	double temp_error;
	double FA, FP;
	for (int k = 2; 1; k++){
	  std::cout << std::endl << F;
		double sum = 0.;
		int n = pow(2,k-1);
		double h = (x1-x0)/n;

		for (int i = 1; i <= pow(2, k-2); i++)
			sum += func->Eval(x0 + (2*i - 1)*h);

		
		FP = (1./2) * F + h*sum;

		if(k==2)
		  temp_error = fabs(FP-F);
		else
		  temp_error = fabs(FP-FA);

		if(temp_error <= errorMin){
		  std::cout << std::endl << FP;
		  std::cout << "\nk=" << k-1 << " n=" << n/2;
		  break;
		}

		FA = F;
		F = FP;
	}

	Integral = F;
	Error = temp_error;

}

void Integrator::Romberg(double& Integral){

	/*
	k = 1 trapezoidalrule - regra simples do trapézio 
	k = 2 
	k = 3 

	*/

	int n = 3;

	double I[n][n];
	double error;

	TrapezoidalRule(1, I[0][0], error);
	TrapezoidalRule(2, I[1][0], error);


	for (int j = 0; j < n; j++){

		for (int k = 0; k < n; k++)

			I[j+1][k+1] = I[j+1][k] + (1/(pow(4, k) - 1)) * (I[j+1][k] - I[j][k]);

	}

	Integral = I[n - 1][n - 1];

}
