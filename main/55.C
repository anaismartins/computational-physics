#include "DataPoints.h"
#include "TF1.h"
#include "TFile.h"
#include "NevilleInterpolator.h"
#include "TCanvas.h"

int main(){

	std::vector<TObject*> ROOTmanager;

	TFile* file = new TFile("55.root", "RECREATE");

	double x[3] = {-1.2, 0.3, 1.1};
	double y[3] = {-5.76, -5.61, -3.69};

	TF1* f0 = new TF1();

	DataPoints d(3, x, y);
	NevilleInterpolator ni(3, x, y, f0);
	ni.Interpolate(0);
	ni.Draw();
	ni.SetResolution();
	const TCanvas &cv = ni.GetCanvas();

	//ROOTmanager.emplace_back(cv);

	//get graph

 	for (auto x : ROOTmanager)
		x->Write();

 	file->Close();

 }