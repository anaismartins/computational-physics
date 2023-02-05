#include "FCtools.h"
#include "Vec.h"

#include <cstdio>
#include <fstream>
#include <sstream>      // std::istringstream
using namespace std;

#define DEBUG
//file name, returns lines
vector<string> FCtools::ReadFile2String(string file_name) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__ );
#endif

  ifstream file;
  file.open(file_name, ifstream::in);

  string line;
  vector<string> vecs;

  if (file.is_open()){
#ifdef DEBUG
    cout << "file is open....." << endl;
#endif
    
    while(getline(file, line)){
      vecs.push_back(line);
    }

    file.close();
  }
  else
    cout << "Não foi possível abrir o ficheiro...." << endl;

  return vecs;
}

//file name, returns vectors of Vec’s
vector<Vec> FCtools::ReadFile2Vec(string file_name) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__ );
#endif

  string line;
  vector<string> vecs = ReadFile2String(file_name);
  vector<Vec> vecvec;

  for(int i = 1; i<vecs.size(); i++) {
    istringstream iss(vecs[i]);
    vector<double> vecd;
    std::string token;
    while( std::getline( iss, token, ' ' ) )
      {
	double b;
	int test = sscanf(token.data(), "%lf", &b);
	if(test == 1) 
	  vecd.push_back(b);
      }
    int vecd_size = vecd.size();
    double arr[vecd_size];
    for(int j = 0; j<vecd_size; j++) {
      arr[j] = vecd[j];
    }
    
    vecvec.push_back(Vec(vecd_size, arr));
  }

  return vecvec;
}

//file name, returns pointer to array of Vec’s, int provides number of lines
Vec* FCtools::ReadFile2Vecp(string file_name, int& n) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__ );
#endif

  vector<Vec> vecvec = ReadFile2Vec(file_name);
  n = vecvec.size();

  Vec *vecp = new Vec [n];
  for(int i = 0; i<n; i++)
    vecp[i] = vecvec[i];

  return vecp;
}
