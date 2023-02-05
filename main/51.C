#include "Vec.h"
#include "FCmatrixT.h"
#include "FCmatrixFull.h"

int main (){

	double a[][3] = {{4., -2., 1.}, {3., 3., -1.5}, {1., 0., 3.}};
	Vec v1(3, a[0]);
	Vec v2(3, a[1]);
	Vec v3(3, a[2]);
	vector<Vec> v;
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);

	FCmatrixFull Mf(v);
	Mf.Print();
	double det = Mf.Determinant();

	std::cout << det << std::endl;

	int rmax = Mf.GetRowMax(2);

	std::cout << rmax << std::endl;

	return 0;
}