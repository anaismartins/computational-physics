#include "Vandermonde.h"

#include "TFile.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TF1.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TText.h"

#include <cmath>
#include <iostream>
using namespace std;

int main(){

  // create a ROOT object manager
  // that will allow us to keep track of object created and use it to store them into a file and delete them
  std::vector<TObject*> ROOTmanager;

  double n = 10;
  double xmin = 0;
  double xmax = 1;
  TF1 *func = new TF1("func", "sin(2*pi*x) + 0.002*cos(100*x)", xmin, xmax);
  
  // determinar a
  Vandermonde A(n, xmin, xmax, *func); // os pontos 0 e 1 devem estar incluidos
  Vec a = A.GetCoefficients(); // vetor de coeficientes
  cout << "Vetor Coefs a = "<< a << endl; // impressão do vetor

  // obter gráficos dos pontos e a curva interpolada
  auto gPoints = A.GetGraphPoints();
  auto fPoly = A.GetPolyFunc();
  gPoints.SetName("gPoints");
  fPoly.SetName("fPoly");

  ROOTmanager.emplace_back(&gPoints);
  ROOTmanager.emplace_back(&fPoly);

  /////////////// cPoly -> CANVAS
  TText *t = new TText();
  t->SetTextAlign(22);
  t->SetTextColor(kBlack);
  t->SetTextFont(43);
  t->SetTextSize(20);
  t->SetTextAngle(0);
  TCanvas *cPoly = new TCanvas("cPoly","cPoly"); // pontos + curva interpolada
  auto gPointsNT = new TGraph(gPoints);
  auto fPolyNT = new TF1(fPoly);
  gPointsNT->SetTitle("");
  fPolyNT->SetTitle("");
  gPointsNT->Draw("AP");
  fPolyNT->Draw("ALSAME");
  t->DrawTextNDC(0.5, 0.95, "gPoints + fPoly");
  cPoly->Update();
  cPoly->Modified();
  
  ROOTmanager.emplace_back(cPoly);

  
  ////////////////////////// alinea b)

  int i_n = 16;
  auto gErrors = new TGraph();
 
  for(int i = 0; i < i_n; i++) {
    n = 4*(1 + i);
    Vandermonde B(n, xmin, xmax, *func);
    double logE = log10(B.GetCoeffError());
    //double logE = B.GetCoeffError();

    gErrors->SetPoint(gErrors->GetN(), n, logE);
  }

  // Estilo dos pontos
  gErrors->SetMarkerStyle(21);
  gErrors->SetMarkerColor(39);
  gErrors->SetMarkerSize(2);
  // Estilo da linha
  gErrors->SetLineColor(kGreen+2);
  gErrors->SetLineWidth(2);

  gErrors->SetNameTitle("gErrors","gErrors");
  gErrors->GetXaxis()->SetTitle("n");
  gErrors->GetYaxis()->SetTitle("log10(E)");
  gErrors->GetXaxis()->CenterTitle();
  gErrors->GetYaxis()->CenterTitle();

  ROOTmanager.emplace_back(gErrors);

  
  ////////////////////////// alinea c)
  // matriz inversa para os pontos em a) A
  n = 10;
  FCmatrixFull I(n, n);
  A.GetInverseMatrix(I);
  cout << "\nA matriz inversa é:\n" << I << endl;
  
  ////////////////////////// file .root
  
  TFile* file = new TFile("trab02.root", "RECREATE");

  for (auto froot : ROOTmanager)
    froot->Write();

  file->Close();

  std::cout << "\nend of the program....." << std::endl;
  return 0;

}
