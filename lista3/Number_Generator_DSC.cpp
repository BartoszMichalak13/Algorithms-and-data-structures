#include <random>
#include <iostream>
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

    int *x = new int[n];
    for(int i = 0; i < n; i++){
        x[i] = dist(engine);
    }
    //wstepnie
    Sort(x, 0, (n-1));
    
    for (int i = 0, j = n-1; i < floor(n/2); i++, j--) {     
        int temp = x[i];  
        x[i] = x[j];  
        x[j] = temp;  
    }  

    cout << n << " ";
    cout << k << " ";
    for(int i = 0; i < n; i++){
        cout << x[i] << " " ;
    }
    delete[] x;
}
