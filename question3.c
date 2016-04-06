#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

void *print_prime_factors(void * na)
{
	
	uint64_t n= *((uint64_t *)na);
	printf("%ju :",n);
	if(n==1) printf(" 1");
	int racine = sqrt(n);
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

return NULL;
}

int main(int nb,char * args[])
{
	FILE *file = fopen(args[1], "r");
	uint64_t n1,n2;
	pthread_t thread1, thread2;
	
	while(fscanf(file, "%ju",&n1)!=EOF){
		pthread_create(&thread1,NULL, print_prime_factors, &n1);
		if(fscanf(file, "%ju",&n2)!=EOF)
		{
			pthread_create(&thread2,NULL, print_prime_factors, &n2);
			pthread_join(thread2,NULL);
		}
		pthread_join(thread1,NULL);
	}
    return 0;
}
