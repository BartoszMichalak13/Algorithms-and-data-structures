#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int comparisions = 0;
int swaps = 0;

void sort( int array[], int p, int q ) {

    if ( p >= q ) {
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
    sort (array, j + 1 , q );
}

void swap( int &a, int &b ) {

    int temp = a;
    a = b;
    b = temp;
    swaps++;
}



int partition( int arr[], int left, int right, int pivot ) {

    int pivot_val = arr[ pivot ];
    swap( arr[ pivot ], arr[ right ] );
    int tmp_left = left;

    for ( int i = left; i < right; i++ ) {

        comparisions++;
        if ( arr[ i ] < pivot_val ) {

            swap( arr[ i ], arr[ tmp_left ] );
            tmp_left++;
        }
    }
    //we did swap( arr[ pivot ], arr[ right ] ); so now arr[ right ] is really arr[ pivot ] before
    swap( arr[ tmp_left ], arr[ right ] );
    return tmp_left; 
}

// kth statistic in arr[]
int randomSelect( int arr[], int left, int right, int k, bool print ) {

    if ( print ) {

        for ( int i = left; i <= right; i++ ) {
            printf( "%02d ", arr[ i ] );
        }
        printf( "\n" );
    }

    if ( left == right ) {

        comparisions++;
        return arr[ left ];
    }
    
    int pivot = rand() % ( right - left + 1 ) + left;
    pivot = partition( arr, left, right, pivot );
    if ( k == pivot ) {
        comparisions++;
        return arr[ k ];
    } else if ( k < pivot ) {
        comparisions++;
        return randomSelect( arr, left, pivot - 1, k, print );
    } else {
        comparisions++;
        return randomSelect( arr, pivot + 1, right, k, print );

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
    //printf( "\ninput: " );

    int n = atoi( argv[ 1 ] );
    int k = atoi( argv[ 2 ] );
    // for ( int i = 1; i < argc; i++ ) {
    //    printf( "%02d ", atoi( argv[ i ] ) );
    // }
    // printf( "\n") ;

    int array[ argc - 3 ];
    for (int i = 3; i < argc; i++ ) {
        array[ i - 3 ] = atoi( argv[ i ] );
    }
    if ( argc - 3 < 50 ) {
        int statistic = randomSelect( array, 0, argc - 4, k, true );
        printf( "\nTable at the end: " );
        for ( int i = 0; i < argc - 3; i++ ) {
            printf( "%02d ",array[ i ] );
        }
        sort( array, 0, argc - 4 );

        printf( "\nSorted table: " );
        for ( int i = 0; i < argc - 3; i++ ) {
            printf( "%02d ", array[ i ] );
        }
        printf( "\n%d statistic: %d\n", k, statistic );
    } else {

        ofstream file_id;
        bool exists = exists_test1("RND.txt");
        file_id.open("RND.txt",ios_base::app);
        
        if(!exists){
            file_id << "\"n\",\"k\",\"comparisions\",\"swaps\"\n"; 
        }
        
        //bazowo dla k = n/2
        randomSelect( array, 0, argc - 4, k, false );
        printf( "comparisions: %d, swaps: %d\n", comparisions, swaps );

        file_id << "\"" << n << "\",\"" << k<< "\",\"" << comparisions << "\",\"" << swaps << "\"\n";
        comparisions = 0;
        swaps = 0;
        for (int i = 3; i < argc; i++ ) {
            array[ i - 3 ] = atoi( argv[ i ] );
        }   

        //z poczatku
        k = std::floor( 0.05 * n );
        randomSelect( array, 0, argc - 4, k, false );
        printf( "Z poczatku: k %d\n", k );
        printf( "comparisions: %d, swaps: %d\n", comparisions, swaps );

        file_id << "\"" << n << "\",\"" << k<< "\",\"" << comparisions << "\",\"" << swaps << "\"\n";
        comparisions = 0;
        swaps = 0;
        for (int i = 3; i < argc; i++ ) {
            array[ i - 3 ] = atoi( argv[ i ] );
        }   

        //z konca
        k = std::floor( 0.95 * n );
        randomSelect( array, 0, argc - 4, k, false );
        printf( "Z konca: k %d\n", k );
        printf( "comparisions: %d, swaps: %d\n", comparisions, swaps );

        file_id << "\"" << n << "\",\"" << k<< "\",\"" << comparisions << "\",\"" << swaps << "\"\n";
        comparisions = 0;
        swaps = 0;

        file_id.close();
    }
}
