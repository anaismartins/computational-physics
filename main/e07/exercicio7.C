#include <cstdio>

int addnumbers (int a, int b) {
  int sum = 0;

  for (int i = a; i <= b; i++){
    sum += (i*i);
  }

  return sum;
}

double addnumbersD (int a, int b) {
  double sum = 0;

  for (int i = a; i <= b; i++){
    sum += (i*i);
  }

  return sum;
}

int main(){
  int a, b;
  printf("Limite 1: ");
  scanf("%d", &a);
  printf("Limite 2: ");
  scanf("%d", &b);
  printf("\nResultado int: %d\n", addnumbers(a,b));
  printf("\nResultado double: %lf\n", addnumbersD(a,b));

  return 0;
}
