#include "TGraph.h"
#include "TCanvas.h"
#include "DataManip.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


#define DEBUG

// Driver function to sort the vector elements 
// by second element of pairs 
bool sortbysec(const pair<int,int> &a, 
	       const pair<int,int> &b) 
{ 
  return (a.second < b.second); 
}



DataManip::DataManip(string s) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  vec = ReadFile(s);
}

//DataManip::~DataManip() : default;
/*DataManip::~DataManip(){
  delete this->vec;
  delete this->Vderiv;
}*/

vector<pair<double,double>> DataManip::GetDataVector() {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  return this->vec;
}

TGraph* DataManip::GetDataGraph(){
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  int size = (this->vec).size();
  double date[size];
  double sun[size];
  for (int i = 0; i < size; i++){

    date[i] = (this->vec)[i].first;
    sun[i] = (this->vec)[i].second;

  }

  TCanvas *c1 = new TCanvas();

  TGraph *GData = new TGraph(size, date, sun);
  GData->SetMarkerStyle(20);
  GData->SetMarkerSize(0.4);
  GData->SetMarkerColor(kBlue+1);
  GData->SetNameTitle("Gdata","Gdata");

  return GData;
}

vector<pair<double,double>> DataManip::GetDataVectorSorted(int n) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  vector<pair<double,double>> vecs = vec;
  
  sort(vecs.begin(), vecs.end(), sortbysec);
 
  if(n == 0){
    reverse(vecs.begin(), vecs.end());
  }

  return vecs;
}

vector<pair<double,double>> DataManip::GetDataDerivativeVector(){

#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  pair<double,double> deriv;
  vector<pair<double,double>> Vderiv;
 
  for (int i = 0; i < (this->vec).size(); i++){

    deriv.second = ((this->vec)[i+1].second - (this->vec)[i].second) / ((this->vec)[i+1].first - (this->vec)[i].first);
    deriv.first = (this->vec)[i].first;
    Vderiv.push_back(deriv);

  }

  return Vderiv;
}


TGraph* DataManip::GetDataDerivativeGraph(){
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  vector <pair<double,double>> Vderiv = this->GetDataDerivativeVector();

  int size = (this->vec).size();
  double derivative[size];
  double time[size];
  
  for (int i = 0; i < size; i++){

    time[i] = (Vderiv)[i].first;
    derivative[i] = (Vderiv)[i].second;

  }

  TCanvas *c2 = new TCanvas();

  TGraph *GdataDeriv = new TGraph(size, time, derivative);
  GdataDeriv->SetMarkerStyle(20);
  GdataDeriv->SetMarkerSize(0.4);
  GdataDeriv->SetMarkerColor(kGreen+2);
  GdataDeriv->SetNameTitle("GdataDeriv","GdataDeriv");
  GdataDeriv->Draw();

  return GdataDeriv;
}

TH1* DataManip::GetDataDerivativeHisto(){

#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  vector <pair<double,double>> Vderiv = this->GetDataDerivativeVector();

  int size = (this->vec).size();
  double derivative[size];
  for (int i = 1; i < size; i++){

    derivative[i] = (Vderiv)[i].second;

  }

  TCanvas *c3 = new TCanvas();
  TH1* HdataDeriv = new TH1F("HdataDeriv", "HDataDeriv", 10, -1000, 1000);
  
  for (int i = 1; i < size; i++)
    HdataDeriv->Fill(derivative[i]);
  HdataDeriv->Draw();

  return HdataDeriv;

}



vector<pair<double,double>> DataManip::GetMovingAverage(int M) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  vector<pair<double,double>> sO = this->vec;
  vector<pair<double,double>> sM;

  int N = sO.size();
  int k = 0; // para a média
  double sum, avg;

#ifdef DEBUG
  std::cout << M/2 << endl;
#endif
 
  for(int n = 0; n < M/2; n++) {
    sM.push_back(sO[n]);
  }
  
  for(int n = M/2; n < N-M/2; n++) {
    sum = 0;
    
    for(int i = k; i < M+k; i++) {
      sum += sO[i].second;
    }
    avg = sum / (double)M;

    sM.push_back(make_pair(sO[n].first, avg));

    k++;
  }

  for(int n = N-M/2; n < N; n++) {
    sM.push_back(sO[n]);
  }

  return sM;
}

TGraph* DataManip::GetMovingAverageGraph(int M, char* name) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  vector<pair<double,double>> sM = this->GetMovingAverage(M);
  
  int size = sM.size();
  double signal[size];
  double time[size];
  for (int i = 0; i < size; i++){

    time[i] = sM[i].first;
    signal[i] = sM[i].second;

  }

  //TCanvas *c2 = new TCanvas();
  TCanvas *c4 = new TCanvas();
  TGraph *GdataDeriv = new TGraph(size, time, signal);
  GdataDeriv->SetMarkerStyle(20);
  GdataDeriv->SetMarkerSize(0.4);

  if(M == 11) {GdataDeriv->SetMarkerColor(kYellow);}
  else if(M == 181) {GdataDeriv->SetMarkerColor(kMagenta);}

  GdataDeriv->SetNameTitle(name,name);
  //  GdataDeriv->SetNameTitle("","");
  GdataDeriv->Draw();

  return GdataDeriv;
}


TGraph* DataManip::GetAutocorrelationGraph(double k_min, double k_max, double delta_t, char* name) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  /*vector<double> X;
  vector<double> Xlinha;
  int k = k_min;
  
  int i = 0;
  while(vec[i].first <= 2020-k) {
    X.push_back(vec[i].second);
    i++;
  }

  for(int j = 0; j < vec.size(); j++) {
    if(vec[j].first >= 1849+k) {
      Xlinha.push_back(vec[j].second);}
  }

*/
  //int size = X.size();

  //TCanvas *c2 = new TCanvas();

  int sizev = vec.size();
  double X[sizev];
  double Xlinha[sizev];
  int k = k_min;
  
  int i = 0;
  while(vec[i].first <= 2020-k) {
    X[i] = vec[i].second;
    i++;
  }

  for(int j = 0; j < vec.size(); j++) {
    if(vec[j].first >= 1849+k) {
      Xlinha[i]  = (vec[j].second);}
  }

  TCanvas *c5 = new TCanvas();
  TGraph *GdataDeriv = new TGraph(sizeof(X)/sizeof(X[0]), X, Xlinha);
  GdataDeriv->SetMarkerStyle(22);
  GdataDeriv->SetMarkerSize(0.4);
  GdataDeriv->SetMarkerColor(kGreen+2);
  GdataDeriv->SetNameTitle(name,name);
  //GdataDeriv->SetNameTitle("","");
  GdataDeriv->Draw();

  return GdataDeriv;
}
