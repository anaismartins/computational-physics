#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define PI 3.14159265

double f(double x){

	return (sin(x * PI/180) * sin(x * PI/180));

}

double z(double x){

	return (x + f(x));

}

int main(){


	cout << z(0.4) << endl;
	cout << z(2.1) << endl;
	cout << z(1.5) << endl;

	return 0;

}