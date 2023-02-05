#include "Gas.h"
#include "TF1.h"
#include "TH1.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"

#include "TROOT.h"

int main() {

	double e_k = 120; //kelvin
	double k = 1.380649 * pow(10, -23); //J/kelvin
	double epsilon = e_k*k; //J
	double sigma = 34 * pow(10, -9); //m
	double m = 6.69e-26; //kg
	double delta_t = 1e-3; //normalizado

	double L = 22; // 22 * sigma
	int N = 100; // partículas
	double d = 1.;

	double dt = 0.001;
	double tmax = 50;

	Gas Argon(N, d, L, e_k, sigma, m, dt);

	cout << "\n A computar......"<<endl;
	TCanvas *cc = new TCanvas("cc", "", 0,0,800,800);

	for(int i = 0; i <= tmax/dt; i++){
	  if(i != 0){
	    Argon.NextTime();
	    if (i % 20 == 0)
	    std::cout << "A computar..." << std::endl;
	}
	  if(i==tmax/dt){
	    TGraph graph = Argon.GetGraphPositions();
	    graph.SetTitle(Form("Posicoes para t = %.1f", i*dt));
	    graph.Draw("AP");
	    cc->SaveAs("trab03_2a_sistema.pdf");
	    
	  }

	}

	// Energy
	TCanvas *cET = new TCanvas("cET", "Energia Total");
	TGraph graph_E = Argon.GetGraphEnergy();
	TGraph graph_dE = Argon.GetGraphVariationEnergy();
	TMultiGraph *Mgraph_E = new TMultiGraph("Mgraph_E", "Energia Total");
	Mgraph_E->Add(&graph_E, "L");
	Mgraph_E->Add(&graph_dE, "L");
	Mgraph_E->Draw("AL");
	cET->SaveAs("trab03_2a_energiatotal.pdf");

	TCanvas *cT = new TCanvas("cT", "Temperatura");
	TGraph graph_T = Argon.GetGraphTemperature();
	graph_T.Draw("AL");
	cT->SaveAs("trab03_2a_temperatura.pdf");

	TCanvas *cdQ = new TCanvas("cdQ", "Desvio Quadratico");
	TGraph graph_dQ = Argon.GetGraphDesvioQuadratico();
	graph_dQ.Draw("AL");
	cdQ->SaveAs("trab03_2a_desvioquadratico.pdf");


	//// alinea b

	TCanvas *cEc = new TCanvas("cEc", "Energia Cinetica");
	TGraph graph_Ec = Argon.GetGraphKineticEnergy();
	graph_Ec.Draw("AL");
	cEc->SaveAs("trab03_2a_energiacinetica.pdf");

	double Ec = 0.;
	double temp;
	double t_eq = 0;
	double step = 10;

	for (int t = (tmax*1./5)/dt; t <= tmax/dt; t+=step){ // encontrar o equilíbrio
		temp = graph_Ec.Eval(t*delta_t);
		if (Ec - temp <= 0.001){
			t_eq = t;
			break;
		}
		Ec = temp;
	}

	vector<double> vec_t = Argon.GetTemperatureVector();
	double T_eq = vec_t[t_eq];
	///////////////////////////////////////////////////////////
	std::cout << "Ec = " << Ec << std::endl;
	std::cout << "t_eq = " << t_eq << std::endl;
	std::cout << "T_eq = " << T_eq << std::endl;
	//////////////////////////////////////////////////////////
	vector<vector<double>> vec_vel = Argon.GetVelocityVector();
	double vel_eq[N];

	double vel_max = 1000;
	
	double vc = sqrt(epsilon/m);
	
	for(int i = 0; i < N; i++){
	  vel_eq[i] = vec_vel[i][t_eq]*vc;//*vc
	  if(vel_eq[i] > vel_max)
	    vel_max = vel_eq[i];
	}

	TCanvas *cveq = new TCanvas("cVeq", "Distribuicao de Velocidades das Particulas em Equilibrio");
	TH1F *vel_histo = new TH1F("vel_histo", "Distribuicao de Velocidades das Particulas em Equilibrio", 100, 0, vel_max);
	for(int i = 0; i < N; i++)
	  vel_histo->Fill(vel_eq[i]);///N
	vel_histo->SetLineColor(kBlue+1);
	vel_histo->Draw("HIST");


	TF1 *max_bolt = new TF1("fmb", "4*pi * pow(([0]/(2*pi*[1]*[2])), (3./2)) * x*x * exp(-([0]*x*x)/(2*[1]*[2]))", 0, vel_max); // * [3]
	//m = (2.02/6.02214)* pow(10,-26);
	//m = 1;
	//k = 1;
	double T = T_eq;
	max_bolt->SetParameters(m,k,T);//,N
	max_bolt->SetParNames("m","k","T");//,"N"
	max_bolt->SetNpx(1000);

	int N_gerados = 2000;
	double vel_MB[N_gerados];
	for(int i = 0; i<N_gerados; i++){
	  vel_MB[i] = max_bolt->GetRandom(0,vel_max);
	}
	TH1F *velMB_histo = new TH1F("velMB_histo", "Distribuicao de Velocidades das Particulas em Equilibrio", N_gerados, 0, vel_max);
	for(int i = 0; i < N_gerados; i++)
	  velMB_histo->Fill(vel_MB[i]);
	velMB_histo->SetLineColor(kRed+1);
	velMB_histo->Draw("SAME");

	cveq->SaveAs("trab03_2b_MB.pdf");

	return 0;

}
