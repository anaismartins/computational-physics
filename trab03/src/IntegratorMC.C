#include "IntegratorMC.h"

#include "TRandom.h"
#include "TF1.h"
#include "TH1.h"
#include "TApplication.h"
#include "TCanvas.h"

#include <cmath>
#include <cstdio>
#include <vector>

void IntegratorMC::Integrate(double& Integral, double& ErrorRel, int& n){

  if(n<2)
    throw std::invalid_argument(Form("[%s] number of random numbers is too small...!\n", __PRETTY_FUNCTION__));
  
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

	gRandom->SetSeed(0);

	double random;
	double f;
	double sum1 = 0, sum2 = 0;
	int Nmax = 2000000;
	double temp_errorR = 0;
	int i = 0;

	for (i = 1; i <= n; i++){
		random = gRandom->Uniform(x0, x1);
		f = func->Eval(random);
		sum1 += f*f;
		sum2 += f;
	}
	for (i = n; i <= Nmax && bError; i++){
		random = gRandom->Uniform(x0, x1);
		f = func->Eval(random);
		sum1 += f*f;
		sum2 += f;
		temp_errorR = ((x1 - x0)/sqrt(i)) * sqrt(sum1/i - (sum2/i)*(sum2/i)) / (sum2 * (x1 - x0) / i);
		if (temp_errorR <= 0.001){
			break;
		} else if(i==Nmax){
		  std::cout << "Número máximo de números gerados: N =" << Nmax << std::endl;
		}

	}

	n = i;
	ErrorRel = temp_errorR;
	Integral = sum2 * (x1 - x0) / n;

}

void IntegratorMC::ImportanceSampling(int& N, double& value, double& error, 
	const TF1& px, const TF1& xy){

//check if N is valid or error
	bool bN = true;
	if (error <= 0.){

		N = 0;
		bN = false;

	}

	//integral
	double Fsum = 0.;
	double Fsum2 = 0.;

	int count = 0;
	double error_t = 1.;
	gRandom->SetSeed(0);
	while ((bN && count < N) || (!bN && error_t < error)){

		//check pdf normalization
		if (count == 0){
			TF1 ftmp(px);
			printf("integral pdf [%f, %f] = %f \n", x0, x1, ftmp.Integral(x0, x1));
		}

		//generate uniform random y
		double y = gRandom->Uniform(); // [0,1]
		double x = xy.Eval(y);

		//compute function ratio
		double ratiof = Eval(x)/px.Eval(x);

		//integral
		Fsum += ratiof;
		Fsum2 += ratiof*ratiof;

		//count
		count++;

		//error variance: variance = <f²> - <f>²
		double Fmean = Fsum/count;
		double Fmean2 = Fsum2/count;
		double variance = Fmean2 - Fmean*Fmean;
		error_t = sqrt(variance/count);

	}

	N = count;
	error = error_t;
	value = Fsum/N;

	printf("N = %d value = %f error = %f \n", N, value, error);

}

void IntegratorMC::ImportanceSampling2(int& N, double& value, double& error, 
	const TF1& px, const TF1& xy){

	error = 1.;
	double sum = 0.;
	double sum1 = 0.;
	double sum2 = 0.;
	double ratio;

	x1 = xy.GetXmax();
	x0 = xy.GetXmin();

	N = 200000000;

	while (error >= 0.001){

		double y = gRandom->Uniform();
		//double x = xy.Eval(y);

		ratio = xy.Eval(y) / (px.Eval(y));
		sum += ratio;
		value = sum / N;

		sum1 += ratio*ratio;
		sum2 += ratio;
		double mean = sum1/N;
		double mean2 = sum2/N;
		double variance = mean2 - mean*mean;
		error = sqrt(variance/N) / value;
		//error = ((x1 - x0)/sqrt(N)) * sqrt(sum1/N - (sum2/N)*(sum2/N)) / (value);
		//std::cout << error << std::endl;

		if (error <= 0.5){
			break;
		} else N++;


	}

}

void IntegratorMC::RandomGen(TF1& px, TF1& xy){

	//draw x random
	TH1F H("H", "random generated from xy", 120, -60, 60);
	TApplication A("A", 0, 0);
	gRandom->SetSeed(0);
	for (int i = 0; i < 1000; i++){
		double r = gRandom->Uniform(); //[0,1]
		H.Fill(xy.Eval(r));
	}

	//scale histogram to integral = 1
	H.Scale(1./H.Integral("width"));

	//display histogram and pdf
	TCanvas c("c", "", 0, 0, 600, 600);
	H.SetLineColor(38);
	H.SetLineWidth(4);
	H.Draw("HISTO");
	px.SetLineColor(20);
	px.SetLineWidth(4);
	px.Draw("same");
	c.Update();
	A.Run();

}
