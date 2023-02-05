#ifndef __DataReader__
#define __DataReader__

#include <vector>
#include <string>
using namespace std;

class DataReader{

public:
  vector<pair<double,double>> ReadFile(string);
  static bool FileExists(string);

protected:
  string file;

};

#endif
