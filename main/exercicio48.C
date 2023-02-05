#include "Vec.h"
#include "FCtools.h"
#include "TObject.h"
#include "TFile.h"
#include "TH2.h"
#include "TCanvas.h"

#include <iostream>
using namespace std;

#define FILE_NAME ../main/exercicio48_matrix.txt 

int main() {

  Vec v1(10); //array with 10 values set to zero
  Vec v2(10,5.); //array with 10 values set to 5.
  
  double a[]={1.2, 3.0, 5.4, 5.2, 1.0};
  Vec v3(5,a); //array with 5 values given by "a" pointer
  
  Vec v4(v3); //define a vector by using another one

  cout << v1 << endl;
  cout << v2 << endl;
  cout << v3 << endl;
  cout << v4 << endl;

  
  // matrix 5x5
  double cm[][5] = { {1., 7., 5., 3., -3.}, {5., 2., 8., -2., 4.}, {1., -5., -4., 6., 7.6}, {0., -5., 3., 3.2, 3.3}, {1., 7., 2., 2.1, 1.2} };
  //array of Vec’s for storing matrix rows
  Vec cv[5];
  //copy rows as arrays into Vecs
  for (int i=0; i<5; i++) {
    cv[i].SetEntries(5, cm[i]);
  }

  int n=0;
  Vec* cvp = FCtools::ReadFile2Vecp("main/exercicio48_matrix.txt", n);
  for(int i = 0; i<n; i++) {
    cout << "Row " << i << " -> " << cvp[i] << endl;
  }

  auto c2 = new TCanvas();
  // instantiate 2-dim histogram
  TH2F *h2 = new TH2F("h2", "Matriz 5x5",5,0,5,5,0,5);
  // fill histogram with matrix values
  for (int i=0; i<5; i++) { //loop on rows
    for (int j=0; j<cv[i].size(); j++) { //loop on columns
	h2->Fill(i,j,cv[i].At(j));
    }
  }
  h2->SetOption("LEGO2");
  
  // make plot
  std::vector<TObject*> ROOTmanager;

  ROOTmanager.emplace_back(h2);

  TFile* file = new TFile("bin/exercicio48.root", "RECREATE");

  for (auto x : ROOTmanager)
    x->Write();

    file->Close();
}
