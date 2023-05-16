#include <random>
#include <iostream>
using namespace std;

int main( int argc, char* argv[] ) {
    int n = 0;
    int k = 0;
    int z = 0;
    if (argc > 1) {
        z = atoi( argv[1] );
        n = atoi( argv[2] );
        k = atoi( argv[3] );
    }
    random_device rd{};    
    mt19937 engine{rd()};
    uniform_int_distribution<int> dist{0, ((2*n)-1)};

    //for zad3
    cout << z << " ";


    cout << n << " ";
    cout << k << " ";

    for(int i = 0; i < n; i++){
        cout << dist(engine) << " " ;
    }
}
