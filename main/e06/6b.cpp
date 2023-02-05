#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
using namespace std;

#define PI 3.14159265

int square(int x, int n){

	if (n > 1)
		return x + square(x, n-1);
	else
		return x;

}

int main(){

	int n = square(3, 3);

	cout << n << endl;

	return 0;

}
