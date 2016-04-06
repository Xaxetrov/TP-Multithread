#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>
#define MAX_FACTORS 64
#define TAILLE 1000
#define GROSNOMBREPREMIER 120823
#define TAILLEDELATABLE 100000


typedef struct decomp{
	int n;
	int size;
	int *factors;
}decomp;
static decomp  tabl[ TAILLEDELATABLE ];
int hash(uint64_t n)
{
	return n % GROSNOMBREPREMIER % TAILLEDELATABLE;
}
int returnCase(uint64_t n)
{
	int a=hash(n);
	if(tabl[a].n!=n)
	return -1;
	else 
	return a;
}
decomp find_factor(uint64_t n)
{
	int a=returnCase(n);
	if(a!=-1)
	{
		return tabl[a];
	}
	else
	{
		decomp fakeDecomp;
		fakeDecomp.n=0;
		fakeDecomp.size=0;
		fakeDecomp.factors=NULL;
		return fakeDecomp;
	}
}
void enregistrer(decomp d)
{
	int a=hash(d.n);
	if(tabl[a].n==0)
	{
		tabl[a]=d;
	}
}
static pthread_mutex_t muMuTeTex, ecran;
static FILE* file;
static decomp dec;
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
		decomp a;
		a.size=k;
		a.n=n;
		a.factors=factors;
		enregistrer(a);
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
		decomp dec = find_factor(n);
		if(dec.size!=0)
		{
			int i;
			for(i=0;i<dec.size;i++)
			{
				factors[k++]=dec.factors[i];
			}
		}else{
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
				factors[k++]=i;
			}
		}
	}
	return k;
}
int main(int nb,char * args[])
{
	
	file = fopen(args[1], "r");
	dec.size=0;
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
