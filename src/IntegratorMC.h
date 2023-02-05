#ifndef __IntegratorMC__
#define __IntegratorMC__

#include "Integrator.h"
#include "TF1.h"

class IntegratorMC : public Integrator{

public:

	//function to be integrated: f
	//constructors
	IntegratorMC() = default;
	IntegratorMC(TF1& f) : Integrator(f.GetXmin(), f.GetXmax(), &f) {;};
	//destructor
	~IntegratorMC() = default;

	//integration methods
	void ImportanceSampling(int& N, double& value, double& error, const TF1& px, const TF1& xy);

	static void RandomGen(TF1& px, TF1& xy);

};

#endif