#ifndef __DataManip__
#define __DataManip__

#include "TGraph.h"
#include "TCanvas.h"
#include "TH1.h"
#include "DataReader.h"
#include <string>
#include <vector>
using namespace std;

class DataManip : protected DataReader {
 public:
  // constructor
  DataManip(string s = "");

  //destructor
  //~DataManip();

  vector<pair<double,double>> GetDataVector();
  TGraph* GetDataGraph();

  vector<pair<double,double>> GetDataVectorSorted(int);

  vector<pair<double,double>> GetDataDerivativeVector();
  TGraph* GetDataDerivativeGraph();
  TH1* GetDataDerivativeHisto();

  vector<pair<double,double>> GetMovingAverage(int);
  TGraph* GetMovingAverageGraph(int, char*);

  TGraph* GetAutocorrelationGraph(double, double, double, char*);
  
 private:
  vector<pair<double,double>> vec;      // (time, sunspot number) destructor

  
};

#endif
