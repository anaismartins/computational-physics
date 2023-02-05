#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define PI 3.14159265

int main(){

	float pi_f;
	double pi_d;

	pi_f = atan(1) * 4;
	pi_d = atan(1) * 4;

	cout << "Para float, a diferença é de: " << PI - pi_f << endl;
	cout << "Para double, a diferença é de: " << PI - pi_d << endl;

	if (abs(PI - pi_f) > abs(PI - pi_d))
		cout << "O double tem maior precisão." << endl;
	else
		cout << "O float tem maior precisão." << endl;

	return 0;

}
