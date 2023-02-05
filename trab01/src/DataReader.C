#include "DataReader.h"

#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#define DEBUG

vector<pair<double,double>> DataReader::ReadFile(string t){
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  
  ifstream file;
  file.open(t, ifstream::in);

  vector<pair<double, double>> vec;
  string line;
  //  char line[40];

  int year, month, date, num_obs;
  float date_in_fraction_of_year, sunspot_number, deviation;
  char prov;

  if (file.is_open()){
#ifdef DEBUG
    cout << "file is open....." << endl;
#endif
    
    while(getline(file, line)){
      sscanf(line.data(), "%d %d %d %f %f %f %d %c", &year, &month, &date, &date_in_fraction_of_year, &sunspot_number, &deviation, &num_obs, &prov);

      if(year >= 1849){

	pair<double, double> p;
	
	p.first = date_in_fraction_of_year;
	p.second = sunspot_number;	
	
	vec.push_back(p);

      }

    }	

    file.close();

  }
  else
    cout << "Não foi possível abrir o ficheiro...." << endl;

  return vec;
}

bool DataReader::FileExists(string t){
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  
  ifstream file;
  file.open(t);
  if(file.is_open()){
#ifdef DEBUG
    printf("file %s exists.....\n", t.data());
#endif
      
      file.close();
      return true;
    }
  else
#ifdef DEBUG
    printf("file %s does not exist.....\n", t.data());
#endif
    return false;
	
}
