#include "define.h"

int main(void){
	
	char a[12] = "Hello World";
	char b[12];
	int y[5] = {9, 11, 13, 15, 17};
	unsigned int x[2] = {4294967295,2};
	int z[2] = {2147483647,1};
	long long result; 
	
	strcpy_and_reverse(a, b, sizeof(a));
	
	result = u_sum(x, sizeof(x)/4);
	result = sum(z, sizeof(z)/4);
	printf ("%i",&result);
	while(1);
	
}