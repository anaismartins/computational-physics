#include "DataReader.h"
#include "DataManip.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <complex>
#include <vector>
#include "TObject.h"
#include "TFile.h"
#include "TGraph.h"
#include "TMultiGraph.h"

int main() {
  
  // create a ROOT object manager
  // that will allow us to keep track of object created and use it to store them into a file and delete them
  std::vector<TObject*> ROOTmanager;

  // check if data file exists otherwise quit
  if (!DataReader::FileExists("SunspotNumberDATA2020.txt")) exit(1);
  
  // create DataManip object
  DataManip D("SunspotNumberDATA2020.txt");
  
  // get vector with all data read (time, value)
  auto V = D.GetDataVector();
  std::cout << "number of data points read: " << V.size() << std::endl;
  
  // get a graph (ROOT TGraph) with all data
  auto Gdata = D.GetDataGraph(); // use marker style 20, marker size 0.4 and color kBlue+1. the TGraph should be named 'Gdata'
  ROOTmanager.emplace_back(Gdata);
  
  // make a new vector (value, time) sorted by sunspot number (from higher to lower values)
  // vector name: Vsort
  auto Vsort = D.GetDataVectorSorted(0); // 0= descending order, 1=ascending order

  // print 10 highest values
  int c = 0;
  for (auto const& x: Vsort ) {
      std::cout << c << " | " << "(" << std::setprecision(7) << x.first << ", " << x.second << ")" << std::endl;
      c++;
      if (c == 10)break;
  }
  
  // get and plot the data time derivatives: df/dx(xi) = [s(i+1) - s(i)] / Delta t_i
  // use STL to make differences
  // use again TGraph
  auto Vderiv = D.GetDataDerivativeVector(); // (time, derivative) 
  auto GdataDeriv = D.GetDataDerivativeGraph(); // use marker style 20, marker size 0.4 and color kGreen+2. the TGraph should be named 'GdataDeriv'
  auto HdataDeriv = D.GetDataDerivativeHisto(); // the Histogram should be named 'HdataDeriv'
  ROOTmanager.emplace_back(GdataDeriv);
  ROOTmanager.emplace_back(HdataDeriv);

  
  // A way of smoothing a signal (get rid of very high frequencies) is making a moving average
  // Get a vector with the moving average time array (time, moving average signals)
  auto Vsmooth181 = D.GetMovingAverage(181);
  auto Gsmooth11 = D.GetMovingAverageGraph(11, "g11"); // args: números de dias, nome do objecto. LineColor=kYellow
  auto Gsmooth181 = D.GetMovingAverageGraph(181, "g181"); // args: números de dias, nome do objecto. LineColor=kMagenta

  // make a new graph superimposing the two graphs: Gdata and Gsmooth
  TMultiGraph *G1 = new TMultiGraph("Gmult1", "Gmult1");
  G1->Add(Gdata, "P"); //only points
  G1->Add(Gsmooth11, "L"); // lines
  G1->Add(Gsmooth181, "L"); // lines

  // make a new graph superimposing the two graphs: Gdata and Gsmooth
  TMultiGraph *G2 = new TMultiGraph("Gmult2", "Gmult2");
  G2->Add(Gsmooth11, "L"); // lines
  G2->Add(Gsmooth181, "L"); // lines

  ROOTmanager.emplace_back(G1);
  ROOTmanager.emplace_back(G2);
  ROOTmanager.emplace_back(Gsmooth11);
  ROOTmanager.emplace_back(Gsmooth181);

  auto Gcorr = D.GetAutocorrelationGraph(1.,25.,1./4, "Gcorr"); // use marker style 22, marker size 0.4 and color kGreen+2. the TGraph should be named 'Gcorr'
  auto Gcorr_detailed = D.GetAutocorrelationGraph(0.,1.,1./365, "Gcorr_detailed"); // use marker style 22, marker size 0.4 and color kGreen+4. the TGraph should be named 'Gcorr_detailed'
  ROOTmanager.emplace_back(Gcorr);
  ROOTmanager.emplace_back(Gcorr_detailed);

  TFile* file = new TFile("ftrab01.root", "RECREATE");

  for (auto x : ROOTmanager)
    x->Write();

  file->Close();
  

  std::cout << "\nend of the program....." << std::endl;
}
