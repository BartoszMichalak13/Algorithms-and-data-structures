#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;
int swaps = 0;
int comparisions = 0;

void sort( int array[], int p, int q ) {
    if( p >= q ) {
        return;
    }
    int i = p - 1;
    int j = q + 1;
    int pivot = array[ p ];

    while ( true ) {
        do {
            ++i;
        } while ( array[ i ] < pivot );

        do {
            --j;
        } while ( array[ j ] > pivot );

        if ( i < j ) {
            int tmp = array[ i ];
            *( &array[ i ] ) = *( &array[ j ] );
            *( &array[ j ] ) = tmp;
        } else 
            break;
    }
    sort( array, p, j );
    sort( array, j + 1 , q );
}

void swap( int *i, int *j ) {
    swaps++;
    int bufor = *i;
    *i = *j;
    *j = bufor;
}

int select( int *arr, int n, int k, int len_of_arr, bool print ) {

    if ( print ) {
        for ( int i = 0; i < n; i++ ) {
            printf( "%02d ", arr[ i ] );
        }
        printf( "\n" );
    }

    if ( n == 1 && k == 0 ) {
        comparisions++;
        return arr[ 0 ];
    }

    int m = ( n + len_of_arr - 1 ) / len_of_arr;
    int *medians = new int[ m ];

    for ( int i = 0; i < m; i++ ) {
        comparisions++;

        if ( len_of_arr * i + len_of_arr - 1 < n ) {
            int *w = arr + len_of_arr * i;

            for ( int j0 = 0; j0 <= len_of_arr / 2; j0++ ) {
                comparisions++;
                int jmin = j0;

                for ( int j = j0 + 1; j < len_of_arr; j++ ) {
                    comparisions++;
                    if ( w[ j ] < w[ jmin ] ) 
                        jmin = j;
                }
                swap( &w[ j0 ], &w[ jmin ] );
            }
            medians[ i ] = w[ len_of_arr / 2 ];
        } else {
            medians[ i ] = arr[ len_of_arr * i ];
        }
    }

    int pivot = select( medians, m, m / 2, len_of_arr, print );
    delete [] medians;

    for ( int i = 0; i < n; i++ ) {
        comparisions++;
        if ( arr[ i ] == pivot ) {
            swap( &arr[ i ], &arr[ n - 1 ] );
            break;
        }
    }

    int store = 0;
    for ( int i = 0; i < n - 1; i++ ) {
        comparisions++;
        if ( arr[ i ] < pivot ) {
            swap( &arr[ i ], &arr[ store++ ] );
        }
    }
    swap( &arr[ store ], &arr[ n - 1 ] );

    if ( store == k ) {
        comparisions++;
        return pivot;
    } else if ( store > k ) {
        comparisions++;
        return select( arr, store, k, len_of_arr, print );
    } else {
        comparisions++;
        return select( arr + store + 1, n - store - 1, k - store - 1, len_of_arr, print );
    }
}


inline bool exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

int main( int argc, char *argv[] ) {

    int len_of_arr = atoi( argv[ 1 ] );
    int n = atoi( argv[ 2 ] );
    int k = atoi( argv[ 3 ] );
    int array[ argc - 4 ];
    for ( int i = 4; i < argc; i++ ) {
        array[ i - 4 ] = atoi( argv[ i ] );
    }


    if ( argc - 4 < 50 ) {
        int statistic = select( array, argc - 4, k, len_of_arr, true );
        printf( "\nTable at the end: " );
        for ( int i = 0; i < argc - 4; i++ ) {
            printf( "%02d ",array[ i ] );
        }
        sort( array, 0, argc - 4 );
        printf( "\nSorted table: " );
        for ( int i = 1; i < argc - 4; i++ ) {
            printf( "%02d ",array[ i ] );
        }
        printf( "\n%d statistic: %d\n", k, statistic );
    } else {
        // select( array, argc - 4, k, len_of_arr, false );
        // printf( "comparisions: %d, swaps: %d\n", comparisions, swaps );

        //SKOMPILUJ
        ofstream file_id;
        bool exists = exists_test1("SL9.txt");//3 5 7 9
        file_id.open("SL9.txt",ios_base::app);
        
        if(!exists){
            file_id << "\"n\",\"len_of_arr\",\"k\",\"comparisions\",\"swaps\"\n"; 
        }

                //bazowo dla k = n/2
        select( array, argc - 4, k, len_of_arr, false );
        printf( "comparisions: %d, swaps: %d\n", comparisions, swaps );

        file_id << "\"" << n << "\",\"" << len_of_arr << "\",\"" << k<< "\",\"" << comparisions << "\",\"" << swaps << "\"\n";
        comparisions = 0;
        swaps = 0;
        for (int i = 4; i < argc; i++ ) {
            array[ i - 4 ] = atoi( argv[ i ] );
        }   

        //z poczatku
        k = std::floor( 0.05 * n );
        select( array, argc - 4, k, len_of_arr, false );
        printf( "Z poczatku: k %d\n", k );
        printf( "comparisions: %d, swaps: %d\n", comparisions, swaps );

        file_id << "\"" << n << "\",\"" << len_of_arr << "\",\"" << k<< "\",\"" << comparisions << "\",\"" << swaps << "\"\n";
        comparisions = 0;
        swaps = 0;
        for (int i = 4; i < argc; i++ ) {
            array[ i - 4 ] = atoi( argv[ i ] );
        }   

        //z konca
        k = std::floor( 0.95 * n );
        select( array, argc - 4, k, len_of_arr, false );
        printf( "Z konca: k %d\n", k );
        printf( "comparisions: %d, swaps: %d\n", comparisions, swaps );
        
        file_id << "\"" << n << "\",\""<< len_of_arr << "\",\"" << k<< "\",\"" << comparisions << "\",\"" << swaps << "\"\n";
        comparisions = 0;
        swaps = 0;

        file_id.close();
    }
}
