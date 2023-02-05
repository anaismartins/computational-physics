class ODEpoint{
	
public:
	//constructors
	ODEpoint(int fndim = 0, const double* x = nullptr);
	ODEpoint(const ODEpoint&);
	~ODEpoint();

	//methods
	int Ndim() const {return ndim;};
	double T() const {return x[0];};
	double X(int i) const {return x[i+1];};
	double* GetArray() {return x;};/*
											PARA ESCREVER
	ODEpoint operator*(double) const;
	ODEpoint operator+(const ODEpoint&) const;
	ODEpoint operator-(const ODEpoint&) const;

	void operator(const ODEpoint&);

	const double& operator[] (int) const;
	double& operator[] (int);*/

private:
	int ndim; //number of dependent variables
	double* x; // independent variable + dependent variables (ndim+1)


};