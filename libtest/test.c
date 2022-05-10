#include<stdio.h>
#include"debil/debil.h"

int main()
{
	int a = add(2,3);
	int b = mult(2,3);
	printf("add(2,3) -> %d\n", a);
	printf("mult(2,3) -> %d\n", b);
	printf("debil() -> %s\n", debil());
	return 0;
}
