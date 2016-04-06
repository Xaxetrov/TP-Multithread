#include <stdio.h>
#include <stdint.h>
#include <math.h>

void print_prime_factors(uint64_t n)
{
	printf("%ju :",n);
	int racine = sqrt(n);
	if(n==1) printf(" 1");
	while(n!=1)
	{
		uint64_t i=2;
		while(n%i!=0  && i<=racine)
		{
			i++;
		}
		if(i>racine)
		{
			printf(" %ju",n);
			 n=1; 
			}
		else
		{ n/=i;
		printf(" %ju",i);}
	}
	printf("\n");


}

int main(int nb,char * args[])
{
	FILE *file = fopen(args[1], "r");
	uint64_t n;
	while(fscanf(file, "%ju",&n)!=EOF){
		print_prime_factors(n);
	}

    return 0;
}
