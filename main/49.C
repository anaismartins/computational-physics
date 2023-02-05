#include "Vec.h"

int main(){

	// alinea a
	//matrix 5x5
	double cm[][5] = {{1., 7., 5., 3., -3.}, {5., 2., 8., -2., 4.}, {1., -5., -4., 6., 7.6},
	{0., -5., 3., 3.2, 3.3}, {1., 7., 2., 2.1, 1.2}};

	Vec v[5];

	for (int i = 0; i < 5; i++){
		v[i].SetEntries(5, cm[i]);
		v[i].Print();
	}

	//alinea b
	Vec v2(v[0]*2.);
	v2.Print();

	//alinea c
	Vec D[5];

	for (int i = 0; i < 5; i++)
		D[i] = v[i];

	D[1] = v[1] - v[0] * (v[1][0]/v[0][0]);

	for (int i = 0; i < 5; i++)
		D[i].Print();

	//alinea d
	Vec v3;
	v3 = v[0]*v[1];

	v3.Print();

	//alinea e
	swap(v[3], v[4]);

	for (int i = 0; i < 5; i++)
		v[i].Print();

	return 0;
}