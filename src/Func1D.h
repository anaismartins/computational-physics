#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"

class Func1D {
	
public:
	//constructors
	Func1D(const TF1 *fp = NULL);
	Func1D(const TF1& fp) : Func1D(&fp) {;};
	// destructor
	~Func1D();

	//methods
	void Draw() const;
	double Eval(double) const;

protected:
	void Settings();

	TF1 *f;

};