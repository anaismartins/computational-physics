#include "Vec.h"
#include "FCmatrix.h"
#include "FCmatrixAlgorithm.h"

#ifndef __FC_MATRIX_FULL__
#define __FC_MATRIX_FULL__

class FCmatrixFull : public FCmatrix{

public:
	//constructors
	FCmatrixFull(); // flag=0
	FCmatrixFull(int m2, int n2);
	FCmatrixFull(const vector<Vec>&); // flag=3
	FCmatrixFull(const FCmatrixFull&);

	// operators
	virtual Vec& operator[] (int);
	void operator= (const FCmatrixFull&);
	Vec operator*(const Vec&);
	Vec operator-(const Vec&);

	//methods
	virtual Vec GetRow(int i); // retrieve row i
	virtual Vec GetCol(int i); // retrieve column i
	virtual double Determinant();

	//row max element index
  	virtual int GetRowMax(int i = 0); // ERRADO
  	//row max element index (scaled by s, from j on)
  	//virtual int GetColMax(int j = 0);



};

#endif
