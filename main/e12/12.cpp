#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include <cstdlib>
using namespace std;

#define PI 3.14159265
#define g 9.80665

int main(){

	double h, t;

	cin >> h;

	t = pow(2*h/g, .5);

	cout << "O tempo que a massa demora a chegar ao solo é " << t << " segundos.\n";

	return 0;

}
