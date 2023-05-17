#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

double findMedian( int a[], int n ) {

    // First we sort the array
    std::sort( a, a + n );
    // check for even case
    if ( n % 2 != 0 )
        return a[ ( n - 1 ) / 2 ];//bylo po prostu n
    // zwracamy mniejszy element z 2
    return (double) a[ ( n / 2 ) - 1 ];
}
int main( int argc, char *argv[] ) {
    
    // stat pozycyjna = k
    int k = atoi( argv[1] );

    //szukamy 4 czyli ind 3 w tablicy
    k = k - 1;  //BO NIE MA 0 STATYSTYKI , dodaj na koncu przy printf
    int *array =  new int[ argc - 2 ];
    std::cout << "dlugosc tablicy: " << argc - 2 << std::endl;
    //std::vector<int> array;
    for ( int i = 2; i < argc; i++ ) {
        array[ i - 2 ] = atoi( argv[ i ] );
    }

    //int N = sizeof(array) / sizeof(array[0]);
    int size_of_array = argc - 2;    
    if ( k < 0 || k > size_of_array - 1 )//hopefully good
    {
        std::cout << "Statystyka pozycyjna musi byc z przedzialu [1,rozmiar_tablicy]" << std::endl;
        return 1;
    }
    int *B = new int[ argc - 2 ];
    for ( int i = 0; i < argc - 2; i++ ) {
        B[i] = array[i];
    }
    int median = findMedian( B, size_of_array );

    //POSZERZENIE TABLICY ZAWSZE JEST OK, SKRACANIE TYLKO BLISKO SRODKA
    int *C;
    int *index_to_remove;
    //int to_cut = 0;
    double tmp = ( (size_of_array - 1) / 4 );

    //PARZYSTE // PARZYSTE // PARZYSTE // PARZYSTE // PARZYSTE // PARZYSTE // PARZYSTE // PARZYSTE // PARZYSTE // PARZYSTE // PARZYSTE // PARZYSTE // PARZYSTE
    if ( size_of_array % 2 == 0 ) {
        //EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN
        if ( k == (size_of_array / 2 ) - 1 ) {   

            std::cout << ( k + 1 ) <<" statistic is 1st median: " << median << std::endl;
            std::cout << "Sorted array: ";
            for ( int i = 0; i < size_of_array; i++ ) {
                std::cout << B[i] << " ";
            }
            std::cout << std::endl;
            delete[] array;
            delete[] B;
            return 0;
        }
    // NIEPARZYSTY // NIEPARZYSTY // NIEPARZYSTY // NIEPARZYSTY // NIEPARZYSTY // NIEPARZYSTY // NIEPARZYSTY // NIEPARZYSTY // NIEPARZYSTY // NIEPARZYSTY
    } else {
        
        //EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN//EQUAL 1ST MEDIAN
        if ( k == (size_of_array - 1) / 2 ) {   

            std::cout << ( k + 1 ) <<" statistic is 1st median: " << median << std::endl;
            std::cout << "Sorted array: ";
            for ( int i = 0; i < size_of_array; i++ ) {
                std::cout << B[i] << " ";
            }
            std::cout << std::endl;
            delete[] array;
            delete[] B;
            return 0;
        }
    }
    // 2ND CASE// 2ND CASE// 2ND CASE// 2ND CASE// 2ND CASE// 2ND CASE// 2ND CASE// 2ND CASE// 2ND CASE// 2ND CASE// 2ND CASE// 2ND CASE
    // if ( k >= floor( tmp ) &&  k < (size_of_array - 1) / 2 ) {

    //     to_cut = size_of_array - 1 - ( 2 * k ); //k = 3 (4 stat poz) -> 3 z lewej i 3 sprawej + 1 (k) zostaje. Dla tab[0,...,8] usuwamy 2 elementy wieksze od med
    //     C = new int[ size_of_array - to_cut ];
    //     index_to_remove = new int[ to_cut ];
    //     int j = 0;
    //     for ( int i = 0; i < size_of_array; i++ ) {
    //         if ( array[i] > median ) {
    //             index_to_remove[j] == i;
    //             j++;
    //             to_cut--;
    //             if ( to_cut == 0) {
    //                 break;
    //             }
    //         }
    //     }
    //     if (to_cut > 0 ) {

    //         for ( int i = 0; i < size_of_array; i++ ) {
    //             if ( array[i] == median ) {
    //                 index_to_remove[j] == i;
    //                 j++;
    //                 to_cut--;
    //                 if ( to_cut == 0) {
    //                     break;
    //                 }
    //             }
    //         }
    //     }

    //     std::sort(index_to_remove, index_to_remove + to_cut);
    //     j = 0;
    //     for ( int i = 0; i < size_of_array; i++ ) {
    //         if( i != index_to_remove[ j ] ) {
    //             C[ i - j ] = array[ i ];
    //         } else {
    //             j++;
    //         }
    //     }
    //     median = findMedian( C, ( size_of_array - to_cut ) );
    //     std::cout << "Resized array: ";
    //     for ( int i = 0; i < size_of_array - to_cut; i++ ) {
    //         std::cout << C[i] << " ";
    //     }
    //     std::cout << std::endl;
    // 1ST CASE // 1ST CASE // 1ST CASE // 1ST CASE // 1ST CASE // 1ST CASE // 1ST CASE // 1ST CASE // 1ST CASE // 1ST CASE // 1ST CASE  
    //} else if ( k < floor( tmp ) ) {
    if (k < (size_of_array - 1) / 2){
        int minimum = array[0];
        for ( int i = 1; i < size_of_array; i++ ) {
            if ( array[i] < minimum ) {
                minimum = array[i];
            }
        }

        int to_add = size_of_array - 1 - ( 2 * k );
        C = new int[ size_of_array + to_add ];
        for ( int i = 0; i < to_add; i++ ) {
            C[i] = minimum;
        }
        for ( int i = 0; i < size_of_array; i++ ) {
            C[ i + to_add ] = array[i];
        }
        median = findMedian( C, ( size_of_array + to_add ) );
        std::cout << "Resized array: ";
        for ( int i = 0; i < size_of_array + to_add; i++ ) {
            std::cout << C[i] << " ";
        }
        std::cout << std::endl;
    // 3RD CASE// 3RD CASE// 3RD CASE// 3RD CASE// 3RD CASE// 3RD CASE// 3RD CASE// 3RD CASE// 3RD CASE// 3RD CASE// 3RD CASE// 3RD CASE
    // } else if ( k <= floor( tmp * 3 ) &&  k > (size_of_array - 1) / 2 ) {
    //     to_cut = size_of_array - 1 - ( 2 * ( ( size_of_array - 1 ) - k) ); //k = 3 (4 stat poz) -> 3 z lewej i 3 sprawej + 1 (k) zostaje. Dla tab[0,...,8] usuwamy 2 elementy wieksze od med
    //     C = new int[ size_of_array - to_cut ];
    //     index_to_remove = new int[ to_cut ];
    //     int j = 0;
    //     for ( int i = 0; i < size_of_array; i++ ) {
    //         if ( array[i] < median ) {
    //             index_to_remove[j] == i;
    //             j++;
    //             to_cut--;
    //             if ( to_cut == 0) {
    //                 break;
    //             }
    //         }
    //     }
    //     if (to_cut > 0 ) {

    //         for ( int i = 0; i < size_of_array; i++ ) {
    //             if ( array[i] == median ) {
    //                 index_to_remove[j] == i;
    //                 j++;
    //                 to_cut--;
    //                 if ( to_cut == 0) {
    //                     break;
    //                 }
    //             }
    //         }
    //     }

    //     std::sort(index_to_remove, index_to_remove + to_cut);
    //     j = 0;
    //     for ( int i = 0; i < size_of_array; i++ ) {
    //         if( i != index_to_remove[ j ] ) {
    //             C[ i - j ] = array[ i ];
    //         } else {
    //             j++;
    //         }
    //     }
    //     median = findMedian( C, ( size_of_array - to_cut ) );
    //     std::cout << "Resized array: ";
    //     for ( int i = 0; i < size_of_array - to_cut; i++ ) {
    //         std::cout << C[i] << " ";
    //     }
    //     std::cout << std::endl;
    // // 4TH CASE// 4TH CASE// 4TH CASE// 4TH CASE// 4TH CASE// 4TH CASE// 4TH CASE// 4TH CASE// 4TH CASE// 4TH CASE// 4TH CASE// 4TH CASE
    // } else if ( k > floor( tmp * 3 ) ) {
    } else {
        int maximum = array[0];
        for ( int i = 1; i < size_of_array; i++ ) {
            if ( array[i] > maximum ) {
                maximum = array[i];
            }
        }
        
        int to_add = size_of_array - 1 - ( 2 * ( ( size_of_array - 1 ) - k) );
        C = new int[ size_of_array + to_add ];
        for ( int i = 0; i < to_add; i++ ) {
            C[i] = maximum;
        }
        for ( int i = 0; i < size_of_array; i++ ) {
            C[ i + to_add ] = array[i];
        }             
        median = findMedian( C, ( size_of_array + to_add ) );
        std::cout << "Resized array: ";
        for ( int i = 0; i < size_of_array + to_add; i++ ) {
            std::cout << C[i] << " ";
        }
        std::cout << std::endl;
    
    }

    std::cout << ( k + 1 ) <<" statistic: " << median << std::endl;
    std::cout << "Sorted array: ";
    for ( int i = 0; i < size_of_array; i++ ) {
        std::cout << B[i] << " ";
    }
    std::cout << std::endl;
    delete[] array;
    delete[] B;
    delete[] C;
    delete[] index_to_remove;
    //delete[] array;
    
    return 0;
}
