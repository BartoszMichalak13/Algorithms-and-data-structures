#include <random>
#include <iostream>
#include <string.h>

using namespace std;

void Sort( int tab[], int left, int right )
{
    int i = left;
    int j = right;
    int x = tab[( left + right ) / 2 ];
    do
    {
        while( tab[ i ] < x )
             i++;
       
        while( tab[ j ] > x )
             j--;
       
        if( i <= j )
        {
            swap( tab[ i ], tab[ j ] );
           
            i++;
            j--;
        }
    } while( i <= j );
   
    if( left < j ) Sort( tab, left, j );
   
    if( right > i ) Sort( tab, i, right );
   
}

int main( int argc, char* argv[] ) {
    int n = 0;
    char *operation;

    if (argc > 2) {
        n = atoi( argv[1] );
        operation = argv[2];
    }
    random_device rd{};    
    mt19937 engine{rd()};
    uniform_int_distribution<int> dist{0, ((2*n)-1)};

    int *x = new int[n];
    for(int i = 0; i < n; i++){
        x[i] = dist(engine);
    }
    //wstepnie
    Sort(x, 0, (n-1));
    
    if ( strcmp ( operation, "insert" ) == 0 || strcmp ( operation, "delete" ) == 0 ) {
        
            for(int i = 0; i < n; i++){
                cout << operation << " ";
                cout << x[i] << " " ;
            }
    } else {
        perror ("wrong data in gen");
        return -1;
    }
    for(int i = 0; i < n; i++){
        cout << x[i] << " " ;
    }
    delete[] x;
}
