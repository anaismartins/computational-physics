#include "IntegratorMC.h"

#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TMultiGraph.h"

#include <cmath>

int main(){

	double v1 = 0., v2 = 6000.;
	double m = 2.02/6.02214 * pow(10, -26), k = 1.380649 * pow(10, -23), T = 300;
	//////////// m = m(H + H)
	std::vector<TObject*> ROOTmanager;

	std::cout << "m = massa de H2" << std::endl;

	//FUNÇÃO DE MAXWELL-BOLTZMANN

	TF1 *max_bolt = new TF1("fmb", "4*pi * pow(([0]/(2*pi*[1]*[2])), (3./2)) * x*x * exp(-([0]*x*x)/(2*[1]*[2]))", v1, v2);
	// 0 - m
	// 1 - k
	// 2 - T
	max_bolt->SetParameters(m,k,T);
	max_bolt->SetParNames("m","k","T");
	max_bolt->SetNpx(1000);
	
	TCanvas *cpdf = new TCanvas("c1","c1");
	TGraph *max_bolt_g = new TGraph(max_bolt);
	max_bolt_g->SetTitle("Maxwell-Boltzmann");
	max_bolt_g->GetXaxis()->SetTitle("velocidade");
	max_bolt_g->GetXaxis()->CenterTitle();
	max_bolt_g->Draw("AL");
	
	cpdf->SaveAs("trab03_1a.pdf");
	
	

	//////////////////////ALINEA A
	std::cout << "Alínea a)" << std::endl << std::endl;
	////////////romberg integrator
	double romberg_integral, romberg_errorR = 0.001;
	int romberg_n = 1000;
	Integrator i(max_bolt);
	i.Romberg(romberg_integral, romberg_errorR, romberg_n); // ERRO AQUI
	std::cout << "Método de Romberg" << std::endl;
	std::cout << "N = " << romberg_n << "; Valor do Integral = " << romberg_integral << "; Valor do Erro Relativo = " << romberg_errorR << std::endl;
	
	////////////mc integrator
	double mc_integral, mc_error = 0.001;
	int mc_n = 1000;
	IntegratorMC mc_a(*max_bolt);

	mc_a.Integrate(mc_integral, mc_error, mc_n);
	std::cout << "Método Monte-Carlo" << std::endl;
	std::cout << "N = " << mc_n << "; Valor do Integral = " << mc_integral << "; Valor do Erro Relativo = " << mc_error << std::endl;


	

	//////////////////////ALINEA B
	std::cout << "\nAlínea b)" << std::endl << std::endl;
	double mv_integral, mv_error = 0.001;
	int mv_n = 1000;

	// FUNÇÃO PARA A MÉDIA DAS VELOCIDADES
	TF1 *m_v = new TF1("fmb", "x *4*pi * pow(([0]/(2*pi*[1]*[2])), (3./2)) * x*x * exp(-([0]*x*x)/(2*[1]*[2]))", v1, v2);
	m_v->SetParameters(m,k,T);
	m_v->SetParNames("m","k","T");
	m_v->SetNpx(1000);

	//TESTE OUTRA FUNÇÃO PARA A MÉDIA DAS VELOCIDADES
	auto mv_t = [v1, v2](double* x, double* par){
		return x[0] *4*3.14 * pow(((2.02/6.02214 * pow(10, -26))/(2*3.14*(1.380649 * pow(10, -23))*300)), (3./2)) * x[0]*x[0] * exp(-((2.02/6.02214 * pow(10, -26))*x[0]*x[0])/(2*(1.380649 * pow(10, -23))*300));
	};
	TF1 mvt("mv", mv_t, v1, v2, 0);

	//cauchy function

	auto cauchyt = [v1, v2](double* x, double* par){
		return (1/((1 + (x[0]-2000)*(x[0]-2000))))/(atan(v2) - atan(v1));
	};
	TF1 cauchy("cauchy", cauchyt, v1, v2, 0);

	//GRÁFICOS E CANVAS PARA CAUCHY E MÉDIA DAS VELOCIDADES
	TCanvas *cvm = new TCanvas("c2","c2");
	TGraph *gvm = new TGraph(m_v);
	//TGraph *guni = new TGraph(Uniform);
	TGraph *gcauchy = new TGraph(&cauchy);

	//JUNTAR OS GRÁFICOS NUM SÓ
	TMultiGraph *Mgraph_mv = new TMultiGraph("Mgraph_E", "Media das Velocidades");
	Mgraph_mv->Add(gvm, "L");
	Mgraph_mv->Add(gcauchy, "L");
	Mgraph_mv->Draw("AL");
	cvm->Modified();
	cvm->Update();
	cvm->WaitPrimitive();	
	cvm->SaveAs("trab03_1b.pdf");

	// VARIÁVEIS NECESSÁRIAS AO CÁLCULO
	IntegratorMC mc_b(*m_v);
	IntegratorMC mc_bt(mvt);
	mv_error = 0.001;
	mv_n = 100;

	std::cout << "Valor para o método de Monte-Carlo com importance sampling: " << std::endl;
	mc_bt.ImportanceSampling(mv_n, mv_integral, mv_error, cauchy, mvt);

	std::cout << "Valor para o método de Monte-Carlo sem importance sampling: " << std::endl;
	mc_b.Integrate(mv_integral, mv_error, mv_n);

	double vm = mv_integral;
	std::cout << "N = " << mv_n << "; Valor Médio das Velocidades = " << vm << "; Valor do Erro Relativo = " << mv_error << std::endl;



	
	//////////////////////ALINEA C
	std::cout << "\nAlínea c)" << std::endl << std::endl;
	mv_error = 0.001;
	mv_n = 1000;
	Integrator v(max_bolt);
	double erro_v0;
	double v0 = v.IntegralPercentageOf(0.05, 1, erro_v0, 0.5, mv_integral);

	std::cout << "O valor do integral usado para calcular v0 foi calculado através do nosso método de Monte-Carlo sem importance sampling, já que o valor calculado através do nosso método de Monte Carlo com importance sampling não nos dá um valor fiável." << std::endl;

	std::cout << "Para p(v > v0), v0 = " << v0 << "; Erro Relativo = " << erro_v0 << std::endl;
	//////////// v0 = 3109
	return 0;

}
