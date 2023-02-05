#include <cmath>
#include <cstdio>

double altura(double t);

int main(){
  double h;
  double T;

  printf("O período do satélite é T (em s) = ");
  scanf("%lf", &T);
  
  h = altura(T);

  printf("Está a uma altitude de %.4lg metros.\n", h);

  return 0;
}

double altura(double t){
  const double G = 6.67e-11;
  const double M = 5.97e24;
  const double R = 6371.e3;

  return pow( (G*M*t*t) / (4*M_PI*M_PI), 1./3.) - R;
}
