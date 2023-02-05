#include "IntegratorMC.h"

#include "TRandom.h"
#include "TF1.h"
#include "TH1.h"
#include "TApplication.h"
#include "TCanvas.h"

#include <cmath>
#include <cstdio>

void IntegratorMC::ImportanceSampling(int& N, double& value, double& error, 
	const TF1& px, const TF1& xy){

//check if N is valid or error
	bool bN = true;
	if (error > 0.){

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