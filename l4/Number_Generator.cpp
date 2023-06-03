#include <random>
#include <iostream>
#include <string.h>

using namespace std;

int main( int argc, char* argv[] ) {
    int n = 0;
    char *operation;
    if (argc > 2) {
        n = atoi( argv[1] );
        operation = argv[2];
    }
    printf ("operation %s\n",operation);
    random_device rd{};    
    mt19937 engine{rd()};
    uniform_int_distribution<int> dist{0, ((2*n)-1)};
    //cout << n << " ";
    if ( strcmp ( operation, "insert" ) == 0 || strcmp ( operation, "delete" ) == 0 ) {
        
        for(int i = 0; i < n; i++){
            cout << operation << " ";
            cout << dist(engine) << " " ;
        }
    } else {
        perror ("wrong data in gen");
        return -1;
    }

    return 0;
}
