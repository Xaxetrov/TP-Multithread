#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

static pthread_mutex_t muMuTeTex;
static FILE* file;
void *print_prime_factors(void)
{
	
	uint64_t n;
	pthread_mutex_lock(&muMuTeTex);
	int retourRead = fscanf(file, "%ju",&n);
	pthread_mutex_unlock(&muMuTeTex);
	
	while(retourRead!=EOF){
		
		
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
		{ 
			n/=i;
			printf(" %ju",i);}
		}
		printf("\n");
		pthread_mutex_lock(&muMuTeTex);
		retourRead = fscanf(file, "%ju",&n);
		pthread_mutex_unlock(&muMuTeTex);
	}
return NULL;
}

int main(int nb,char * args[])
{
	
	file = fopen(args[1], "r");
	pthread_t thread1, thread2;
	
	pthread_mutex_init(&muMuTeTex, NULL);
	
	
	pthread_create(&thread1,NULL, print_prime_factors, NULL);
	pthread_create(&thread2,NULL, print_prime_factors, NULL);
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
	pthread_mutex_destroy(&muMuTeTex);

    return 0;
}
