#include "ODEpoint.h"
#include <vector>
#include <cstdlib>
#include "TF1.h"

class ODEsolver {
	
public:
	//constructor
	ODEsolver(const std::vector<TF1>&);
	//destructor
	~ODEsolver();

	//methods PARA ESCREVER
	/*void SetODEfunctions(const std::vector <TF1>&);

	std::vector<ODEpoint> Euler(ODEpoint i, double step, double T);
	std::vector<ODEpoint> PredictorCorrector(ODEpoint i, double step, doble T);
	std::vector<ODEpoint> LeapFrop(ODEpoint i, double step, double T);

	std::vector<ODEpoint> RK2(ODEpoint i, double step, double T);
	std::vector<ODEpoint> RK4(ODEpoint i, double step, double T);*/

private:
	std::vector<TF1> F;

};