#include <iostream>
#include <algorithm>
#include <cmath>


double findMedian( int a[], int n )
{
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
    int *array =  new int[ argc - 2 ];
    for ( int i = 2; i < argc; i++ ) {
        array[ i - 2 ] = atoi( argv[ i ] );
    }

    //int N = sizeof(array) / sizeof(array[0]);
    int size_of_array = argc - 2;    

    int *B = new int[ argc - 2 ];
    for ( int i = 0; i < argc - 2; i++ ) {
        B[i] = array[i];
    }
    int median = findMedian( B, size_of_array );

    //PAMIETAJ ZE TO ROZKLADASZ DLA POSORTOWANEGO ARRAYA A NORMALNIE JEST NIE POSORTOWANY
    //WIEC JAK COS ZWRACASZ TO MEDIANE Z TEJ TABLICY

    //sprawdz P i NP
    // 4 cases bo podzielne na 4

        //PARZYSTE
    if ( size_of_array % 2 == 0 ) {


    
    
    // NP
    } else {
        
        //k jest mediana
        if ( k == (size_of_array - 1) / 2 ){
            return median;

        //syt jak na wykladzie 4 case'y
        if ( ( (size_of_array - 1) / 2 ) % 2 ==0 ) {


        // lewo mid prawo MEDIANA lewo mid prawo
        } else {

            //dla 9 ==5
            int med_index = (size_of_array - 1) / 2;
            if ( k == (med_index - 1) / 2 ) {
                return array;

        }

        // lower

        

        // 2nd              //CHECK
        } else if ( k >= ( ( size_of_array - 1 ) / 4) && k < ( ( size_of_array - 1) / 2 ) ) {

        

            for ( int i = 0; i  ) {

            }
        //1st 
        } else if ( k < ( size_of_array / 4) ) {


        //upper
        //1st
        } else if ( k < ( 3 * size_of_array / 4) && k > ( size_of_array / 2 ) ) {


        //2nd
        } else  if (k > ( 3 * size_of_array / 4 ) ) {


        } else {
            std::cout << "Error? k:" << k << "size of array: " << size_of_array << std::endl;

        }
    }


    

}
