#include "Integrator.h"
#include "TFormula.h"
#include <vector>
using namespace std;

void Integrator::TrapezoidalRule(double x1, double x2, double &F){

	if (x1 > x2){
		double temp = x2;
		x2 = x1;
		x1 = temp;
	}

	double h = x2 - x1;

	F = h * (func->Eval(x2) + func->Eval(x1)) / 2.;

}

void Integrator::Trapezoidal(int n, double& Integral, double& Error){

  if(n<1)
    throw std::invalid_argument(Form("[%s] invalid number of intervals...!\n", __PRETTY_FUNCTION__));
  
	double h = (x1 - x0) / n;

	Integral = h * func->Eval(x0) / 2;

	for (int i = 1; i < n - 1; i++)
		Integral += h * func->Eval(x0 + h*i);

	Integral += h * func->Eval(x1) / 2;


	double derivada2 = (func->Derivative(x1) - func->Derivative(x0))/h;
	double avg2D = derivada2/n;
	Error = - h*h * (x1-x0) * avg2D /12;

}

void Integrator::TrapezoidalAdaptive(int m, double& Integral, double& Error){

  if(m<1)
    throw std::invalid_argument(Form("[%s] invalid number of intervals...!\n", __PRETTY_FUNCTION__));

	double errorMin;
	bool bError;
	if(Error!=0){
	  bError = true;
	  errorMin = Error;
	}
	else{
	  bError = false;
	  errorMin = 0;
	}

	double F = (x1 - x0) * (func->Eval(x0) + func->Eval(x1)) / 2.;
	double temp_error;
	double FA, FP;
	
	for (int k = 2; k <= m || bError; k++){
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

		if(temp_error <= errorMin && bError)
		  break;
		

		FA = F;
		F = FP;
	}

	Integral = F;
	Error = temp_error;

}

void Integrator::Romberg(double& Integral, double& ErrorRel, int& n){

  if(n<1)
    throw std::invalid_argument(Form("[%s] invalid number of interactions...!\n", __PRETTY_FUNCTION__));
  
	/*
	k = 1 trapezoidalrule - regra simples do trapézio 
	k = 2 
	k = 3 

	*/

	double errorRMin;
	bool bError;
	if(ErrorRel!=0){
	  bError = true;
	  errorRMin = ErrorRel;
	}
	else{
	  bError = false;
	  errorRMin = 0;
	}

	int N = 1;

	vector<vector<double>> vI;

	while(1){
		
	  double temp_I = 0;
	  vector<double> temp_vI;
	  double temp_errorR = 0;
	  double error = 0;
	  

	  if(N==1){
	    TrapezoidalRule(x0, x1, temp_I);
	    temp_vI.push_back(temp_I);
	    vI.push_back(temp_vI);
	    temp_vI.clear();
	  }
	  else {
	    TrapezoidalAdaptive(N, temp_I, error);
	    temp_vI.push_back(temp_I);
	    error = 0;
	
	    int j = N-2;
	    int k = 0;
		
	    for (k = 0; k <= j; k++){
	
	      temp_I = temp_vI[k] + (1/(pow(4, k+1) - 1)) * (temp_vI[k] - vI[j][k]);
	      temp_vI.push_back(temp_I);
	      
	    }

	    vI.push_back(temp_vI);     
	    temp_vI.clear();

	    temp_errorR = fabs( (vI[N-1][N - 1] - vI[N-1][N - 2]) / vI[N-1][N - 1]);
	  }


	  if ((temp_errorR <= errorRMin && bError && N>1) || (N==n && !bError)){
	    /*for(int i = 0; i<vI.size(); i++){
	      for(int j = 0; j<vI[i].size(); j++)
		std::cout << vI[i][j] << " ";
	      std::cout <<"\n";
	    }
	    std::cout << temp_errorR << "\n";*/
	    
	    Integral = vI[N - 1][N - 1];
	    ErrorRel = temp_errorR;
	    n = N;
	    break;
	  }
	  else
	    N++;

	}	

}

double Integrator::IntegralPercentageOf(double percentage, double back_forward, double& erro, double percentage0, double fx){ 
// back_forward = -1 usado para quando queremos valores inferiores à percentagem pedida
// back_forward = 1 usado para quando queremos valores superiores à percentagem pedida

  if(percentage>=1 || percentage<=0)
        throw std::invalid_argument(Form("[%s] percentage number is not valid...!\n", __PRETTY_FUNCTION__));
  if(back_forward!=1 && back_forward!=-1)
        throw std::invalid_argument(Form("[%s] Invalid Number for back_forward...!\n", __PRETTY_FUNCTION__));

        double temp_x0 = x0;
	double temp_x1 = x1;
	double temp_percentage = 1;
	if(percentage != -1){
	  if(back_forward == 1)
	    temp_x0 = fx;
	  if(back_forward == -1)
	    temp_x1 = fx;
    
	  temp_percentage = percentage;
	}

        double step = .05;
	double error;
	//TFormula *formula = func->GetFormula();
	//double m = 2.02/6.02214 * pow(10, -26), k = 1.380649 * pow(10, -23), T = 300;

	while (temp_percentage >= percentage){
	  error = 0.001;
	  
	  if(back_forward == 1)
	    temp_x0 += step;	
	  else
	    temp_x1 -= step;

	  /*TF1 temp_f("temp_f", "4*pi * pow(([0]/(2*pi*[1]*[2])), (3./2)) * x*x * exp(-([0]*x*x)/(2*[1]*[2]))", temp_x0, x1);
	    temp_f.SetParameters(m,k,T);
	    temp_f.SetParNames("m","k","T");*/
	  Integrator temp_I(temp_x0, temp_x1, func);
		
	  temp_I.TrapezoidalAdaptive(6, temp_percentage, error);

	}

	erro = error/percentage;
	if(back_forward == 1)
	  return temp_x0;	
	else
	  return temp_x1;

}
