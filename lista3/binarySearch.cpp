#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>


int comparisions = 0;
int BS( int array[], int low, int high, int i ) {

    if ( high >= low ) {
        int mid = ( high + low ) / 2;

        if ( array[ mid ] > i ) {
            comparisions++;
            return BS( array, low, mid - 1, i );

        } else if ( array[ mid ] < i ) {
            comparisions++;
            return BS( array, mid + 1, high, i );

        } else if ( array[ mid ] == i ) {
            comparisions++;
            return 1;
            
        }
    }
    return 0;
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
    int j = atoi( argv[ 1 ] );
    int array[ argc - 2 ];
    for ( int i = 2; i < argc; i++ ) {
        array[ i - 2 ] = atoi( argv[ i ] );
    }
    int return_value;

    std::ofstream file_id;
    bool exists = exists_test1("BS_rnd.txt");//3 5 7 9
    file_id.open("BS_rnd.txt",std::ios_base::app);
    
    if(!exists){
        file_id << "\"n\",\"comparisions\",\"duration\"\n"; 
    }
    auto start = std::chrono::high_resolution_clock::now();
    return_value = BS( array, 0, argc - 3, j );
    printf( "comparisions: %d, return_value: %d\n", comparisions, return_value );
    std::cout << "szuk el: " << j << " Tablica: "<< std::endl;
       for ( int i = 2; i < argc; i++ ) {
            std::cout << array[i-2] << " " << std::endl;
       }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
    printf("duration: %d, comparisions: %d\n", duration, comparisions );
    file_id << "\"" << argc - 2 << "\",\""  << comparisions << "\",\"" << duration << "\"\n";

    file_id.close();
    return 0;
}
