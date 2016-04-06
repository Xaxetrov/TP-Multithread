#include <stdio.h>

using namespace std;

void Premier ( unsigned int max)
{
        unsigned int i, j, essai, sommet = 1, pasI = 4;
        unsigned int * m = new unsigned int [ max / 3 + 1 ];
        unsigned int * dP = new unsigned int [ max / 3 + 1 ];
        
        dP [ 0 ] = 5;
        m [ 0 ] = 25;
        
        for ( i = 7; i < max; i += pasI, pasI = 6 - pasI )
        {
                for ( essai = dP [ j = 0 ]; ( i != m [ j ] ) && ( essai * essai < i ); essai = dP [ ++j ] )
                {
                        if ( i > m [ j ] ) m [ j ] += essai << 1;
                }
                
                if ( i != m [ j ] )
                {
                        printf ( "%u\n", i );
                        m [ sommet ] = i * i;
                        dP [ sommet++ ] = i;
                }
        }
        delete [ ] dP;
        delete [ ] m;
}

int main ()
{
        Premier (100);
        return 0;
}
