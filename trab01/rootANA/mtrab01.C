#include "DataReader.h"
#include "DataManip.h"
#include <TGraph.h>
#include <TCanvas.h>

void mtrab01(){

	DataManip D("../SunspotNumberDATA2020.txt");
	TGraph *GData = D.GetDataGraph();
	GData->Draw();

	TGraph *GdataDeriv = D.GetDataDerivativeGraph();
	GdataDeriv->Draw();

	TH1 *HdataDeriv = D.GetDataDerivativeHisto();
	HdataDeriv->Draw("HdataDeriv");

	TGraph *GmovingAv = D.GetMovingAverageGraph(11, "g11");
	GmovingAv->Draw();

	TGraph *Gauto = D.GetAutocorrelationGraph(1.,25.,1./4, "Gcorr");
	Gauto->Draw();

}