#include <stdio.h>

int fact(int x){

	int f = 1;

	if (x != 0 && x != 1)
		for (int i = 2; i <= x; i++)
			f *= i;

	return f;

}

int main(){

	int x, f;
	
	scanf("%d", &x);

	f = fact(x);

	printf("\nO fatorial de %d é: %d.\n", x, f);

	return 0;

}