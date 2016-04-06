#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>
#define MAX_FACTORS 64
static pthread_mutex_t muMuTeTex, ecran;
static FILE* file;
void *print_prime_factors(void)
{
	uint64_t factors[MAX_FACTORS];
	int j,k;
	
	
	uint64_t n;
	pthread_mutex_lock(&muMuTeTex);
	int retourRead = fscanf(file, "%ju",&n);
	pthread_mutex_unlock(&muMuTeTex);
	
	
	while(retourRead!=EOF){
		
		k = get_prime_factors(n,factors);
		
		pthread_mutex_lock(&ecran);
		printf("%ju :",n);
		for(j=0;j<k;j++)
		{
			printf(" %ju",factors[j]);
		}
		printf("\n");
		pthread_mutex_unlock(&ecran);
		
		pthread_mutex_lock(&muMuTeTex);
		retourRead = fscanf(file, "%ju",&n);
		pthread_mutex_unlock(&muMuTeTex);
	}
return NULL;
}
int get_prime_factors(uint64_t n, uint64_t* factors){
	int k=0;
	if(n==1) factors[k++]=1; 
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
		factors[k++]=n;
		 n=1; 
		}
	else
	{ 
		n/=i;
		factors[k++]=i;}
	}
	return k;
}
int main(int nb,char * args[])
{
	
	file = fopen(args[1], "r");
	pthread_t thread1, thread2;
	
	pthread_mutex_init(&muMuTeTex, NULL);
	pthread_mutex_init(&ecran, NULL);
	
	
	pthread_create(&thread1,NULL, print_prime_factors, NULL);
	pthread_create(&thread2,NULL, print_prime_factors, NULL);
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
	pthread_mutex_destroy(&muMuTeTex);
	pthread_mutex_destroy(&ecran);

    return 0;
}
