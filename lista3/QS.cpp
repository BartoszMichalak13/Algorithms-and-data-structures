#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>
using namespace std;

int comp_coutner = 0;
int swap_coutner = 0;
bool to_print; 

void Sort( int tab[], int left, int right )
{
    if(to_print){
        cout << "Sorting between: " << setw(2) << setfill('0') << left << " & " << setw(2) << setfill('0') << right << endl;
        cout << "Array under sorting : " << endl;
        for(int i = left; i <= right; i++)
            cout << setw(2) << setfill('0') << tab[i] << " " << endl;
    }   
    int i = left;
    int j = right;
    int x = tab[( left + right ) / 2 ];
    do
    {
        ++comp_coutner;
        while( tab[ i ] < x ){
            i++;
            ++comp_coutner;
        }
        ++comp_coutner;
        while( tab[ j ] > x ){
            j--;
            ++comp_coutner;

        }

        if( i <= j )
        {
            swap( tab[ i ], tab[ j ] );   
            i++;
            j--;
            ++swap_coutner;
        }
    } while( i <= j );

    if( left < j ){
        Sort( tab, left, j );
    }
    if( right > i ){
        Sort( tab, i, right );
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
    // int *array; 
    // int licz = 0;
    // for (string line; getline(cin, line, ' '); licz++) {
    //     if(licz == 0){
    //         n = stoi(line);
    //         array = new int[n];
    //     }
    //     else{
    //         array[licz - 1] = stoi(line);
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
    //printf( "comparisions: %d, return_value: %d\n", comp_coutner, return_value );

    Sort(array, 0, (n-1));

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
    bool exists = exists_test1("QS.txt");
    file_id.open("QS.txt",ios_base::app);
    
    if(!exists){
        file_id << "\"n\",\"comparisions\",\"swaps\",\"duration\",\n"; 
    }
    file_id << "\"" << n << "\",\"" << comp_coutner << "\",\"" << swap_coutner << "\",\"" << duration << "\"\n";
    file_id.close();

    //delete[] array;
    return 0;
}
