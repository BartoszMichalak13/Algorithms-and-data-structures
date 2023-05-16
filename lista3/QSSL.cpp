#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>

using namespace std;

int comp_coutner = 0;
int swap_coutner = 0;
bool to_print; 

void myswap( int *i, int *j ) {
    swap_coutner++;
    int bufor = *i;
    *i = *j;
    *j = bufor;
}

int select( int *v, int n, int k ) {
    if ( n == 1 && k == 0 ) {
        comp_coutner++;
        return v[ 0 ];
    }

    int m = ( n + 4 ) / 5;
    int *medians = new int[ m ];
    for ( int i = 0; i < m; i++ ) {
        comp_coutner++;
        if ( 5 * i + 4 < n ) {
            int *w = v + 5 * i;
            for ( int j0 = 0; j0 < 3; j0++ ) {
                int jmin = j0;
                for ( int j = j0 + 1; j < 5; j++ ) {
                    if ( w[ j ] < w[ jmin ] ) 
                        jmin = j;
                }
                myswap( &w[ j0 ], &w[ jmin ] );
            }
            medians[ i ] = w[ 2 ];
        } else {
            medians[ i ] = v[ 5 * i ];
        }
    }

    int pivot = select( medians, m, m / 2 );
    delete [] medians;

    for ( int i = 0; i < n; i++ ) {
        comp_coutner++;
        if ( v[ i ] == pivot ) {
            myswap( &v[ i ], &v[ n - 1 ] );
            break;
        }
    }

    int store = 0;
    for ( int i = 0; i < n - 1; i++ ) {
        comp_coutner++;
        if ( v[ i ] < pivot ) {
            myswap( &v[ i ], &v[ store++ ] );
        }
    }
    myswap( &v[ store ], &v[ n - 1 ] );

    if ( store == k ) {
        comp_coutner++;
        return pivot;
    } else if ( store > k ) {
        comp_coutner++;
        return select( v, store, k );
    } else {
        comp_coutner++;
        return select( v + store + 1, n - store - 1, k - store - 1 );
    }
}
void Sort( int array[], int n ) {
    if ( n > 0 ) {
        int pivot = select( array, n, n / 2 );
        if ( to_print ) {
            for ( int i = 0; i < n; i++ ) {
                printf( "%02d ", array[ i ] );
            }
            printf( "\n" );
        }
        Sort( array, n / 2 );
        Sort( array + n / 2 + 1 , n - n / 2 - 1 );
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
int main(int argc, char* argv[]){
    int n;
    //int *array; 
    //int licz = 0;
    // for (string line; getline(cin, line, ' '); licz++) {
    //     if(licz == 0){
    //         cout << "h1 " << stoi(line);
    //         n = stoi(line);
    //         array = new int[n];
    //     }
    //     else{
    //         array[licz - 1] = stoi(line);
    //         cout << "h2 "<< stoi(line);
    //     }
    // }
    int array[argc-2];
    n = atoi( argv[1] );
    for(int i=2; i<argc; i++) {
        array[i-2] = atoi(argv[i]);
    }

    if( n >= 40 ){
        to_print = false;
    }else{
        to_print = true;
    }

    if(to_print){
        cout << "Tablica wejściowa: ";
            for(int i = 2; i < n + 2; i++)
                cout << setw(2) << setfill('0') << array[i - 2] << " "; 
        cout << endl;
    }

    auto start = std::chrono::high_resolution_clock::now();
    Sort(array, n);
    //printf( "comparisions: %d, return_value: %d\n", comp_coutner, return_value );

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
    cout << "comp: " << comp_coutner << " duration: " << duration << endl;
    if(to_print){
        cout << "Tablica Posortowana: " << endl;
        for(int i = 0; i < n; i++)
            cout << setw(2) << setfill('0') << array[i] << " " ;

        cout << endl;
        cout << "Comparisions: " << comp_coutner << endl;
        cout << "Swaps: " << swap_coutner << endl;

    }
    for(int i = 0; i < n-1; i++){
        if(array[i] > array[i+1]){
            cout << "Ciąg jest źle posortowany" << endl;
        }else if(i = n-2){
            cout << "Ciąg jest dobrze posortowany" << endl;
        }
    }
    std::ofstream file_id;
    bool exists = exists_test1("QSSL.txt");
    file_id.open("QSSL.txt",ios_base::app);
    
    if(!exists){
        file_id << "\"n\",\"comparisions\",\"swaps\",\"duration\",\n"; 
    }
    file_id << "\"" << n << "\",\"" << comp_coutner << "\",\"" << swap_coutner << "\",\"" << duration << "\"\n";
    file_id.close();

    //delete[] array;
    return 0;
}
