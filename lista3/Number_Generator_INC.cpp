#include <random>
#include <iostream>
#include <algorithm>
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
    int k = 0;
    if (argc > 2) {
        n = atoi( argv[1] );
        k = atoi( argv[2] );
    }
    random_device rd{};    
    mt19937 engine{rd()};
    uniform_int_distribution<int> dist{0, ((2*n)-1)};
    uniform_int_distribution<int> dist2{0, n};

    int *x = new int[n];
    for(int i = 0; i < n; i++){
        x[i] = dist(engine);
    }
    //wstepnie
    Sort(x, 0, (n-1));


    // ((int)floor( 0.05 *  n ))
    // ((int)floor( n/2 ))
    // ((int)floor( 0.95 *  n ))
    //+ losowy
    //spoza
    cout << x[dist2(engine)] << " ";
    //cout << k << " ";
    for(int i = 0; i < n; i++){
        cout << x[i] << " " ;
    }
    delete[] x;
}
