#include <cstdio>

int addnumbers (int a, int b) {
  int sum = 0;
  int x;

  if(a > b){
    x=b;
    b=a;
    a=x;
  }
  
  for (int i = a; i <= b; i++){
    sum += i;
  }

  return sum;
}

int main(){
  int a, b;
  printf("Limite 1: ");
  scanf("%d", &a);
  printf("Limite 2: ");
  scanf("%d", &b);
  printf("\nResultado: %d\n", addnumbers(a,b));

  return 0;
}
