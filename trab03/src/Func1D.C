#include "Func1D.h"

Func1D::Func1D(const TF1 *fp){
	
	if (fp){
		func = new TF1(*fp);		
		Settings();
	}

}

Func1D::~Func1D(){

  //	if (f)
	  //	delete f;

}

void Func1D::Draw() const{

	TApplication A("A", 0, 0);
	TCanvas c("c", "Func1D canvas", 0, 0, 1000, 800);
	func->Draw();
	c.Update();
	A.Run();

}

double Func1D::Eval(double xval) const{

	return func->Eval(xval);

}

void Func1D::Settings(){

	func->SetNpx(1000);
	func->SetLineColor(38);
	func->SetLineWidth(4);

}
