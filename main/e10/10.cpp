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

int main(){

	int x[1000];
	double y[1000];
	int sum;
	double average, sum2, dp;

	sum = 0;
	sum2 = 0;

	for (int i = 0; i < 1000; i++){

		x[i] = (rand() % 50) + 5;
		cout << x[i] << endl;
		if (x[i] != 10)
			y[i] = (double)((double)x[i] / (double)(x[i] - 10));
		else
			y[i] = -1;
		cout << y[i] << endl;

		sum += x[i];

	}

	average = ((double)sum / 1000.);

	for (int j = 0; j < 1000; j++)
		sum2 += (x[j] - average)*(x[j] - average);

	dp = (double)pow(((double)(sum2 / 1000.)), .5);

	cout << "A média é: " << average << "\nE o desvio padrão é: " << dp << endl;

	return 0;

}