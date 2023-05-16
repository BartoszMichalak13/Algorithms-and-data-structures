#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>
using namespace std;

int comp_coutner = 0;
int swap_coutner = 0;
bool to_print; 

int partition(int* arr, int low, int high, int* lp);
 
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
void DualPivotQuickSort(int* arr, int low, int high)
{
    
    if (low < high) {
        if(to_print){
            cout << "Partition between: " << setw(2) << setfill('0') << low 
            << " & " << setw(2) << setfill('0') << high << endl;
            for(int i = 0; i < sizeof(arr); i++){
                cout << setw(2) << setfill('0') << arr[i] << " ";
            }
            cout << endl;
        }
        // lp means left pivot, and rp means right pivot.
        int lp, rp;
        rp = partition(arr, low, high, &lp);
        DualPivotQuickSort(arr, low, lp - 1);
        DualPivotQuickSort(arr, lp + 1, rp - 1);
        DualPivotQuickSort(arr, rp + 1, high);
    }
}
 
int partition(int* arr, int low, int high, int* lp)
{
    ++comp_coutner;
    if (arr[low] > arr[high]){
        swap(&arr[low], &arr[high]);
        ++swap_coutner;
    }
 
    // p is the left pivot, and q is the right pivot.
    int j = low + 1;
    int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
    //int tempP = p, tempQ = q;
    while (k <= g) {
 
        // if elements are less than the left pivot
        if((j-low)>=(abs(g-high))){
            comp_coutner = comp_coutner + 2;
            if (arr[k] < p) {
                swap(&arr[k], &arr[j]);
                ++swap_coutner;
                j++;
                comp_coutner--;
            }
    
            // if elements are greater than or equal
            // to the right pivot
            else if (arr[k] >= q) {
                ++comp_coutner;
                while (arr[g] > q && k < g){
                    g--;
                    ++comp_coutner;
                }
                swap(&arr[k], &arr[g]);
                ++swap_coutner;
                g--;
                ++comp_coutner;
                if (arr[k] < p) {
                    swap(&arr[k], &arr[j]);
                    ++swap_coutner;
                    j++;
                }
            }
        }else{
            comp_coutner = comp_coutner + 2;
            // if elements are greater than or equal
            // to the right pivot
            if (arr[k] >= q) {
                ++comp_coutner;
                while (arr[g] > q && k < g){
                    g--;
                    ++comp_coutner;
                }
                swap(&arr[k], &arr[g]);
                ++swap_coutner;
                g--;
                ++comp_coutner;
                if (arr[k] < p) {
                    swap(&arr[k], &arr[j]);
                    ++swap_coutner;
                    j++;
                }
            }
            else if (arr[k] < p) {
                swap(&arr[k], &arr[j]);
                ++swap_coutner;
                j++;
                comp_coutner--;
            }
        }
       
        k++;
    }
    j--;
    g++;
 
    // bring pivots to their appropriate positions.
    swap(&arr[low], &arr[j]);
    ++swap_coutner;
    swap(&arr[high], &arr[g]);
    ++swap_coutner;
 
    // returning the indices of the pivots.
    *lp = j; // because we cannot return two elements
    // from a function.
 
    return g;
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
    DualPivotQuickSort(array, 0, (n-1));
    //printf( "comparisions: %d, return_value: %d\n", comp_coutner, return_value );

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();

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
    bool exists = exists_test1("QSD.txt");
    file_id.open("QSD.txt",ios_base::app);
    
    if(!exists){
        file_id << "\"n\",\"comparisions\",\"swaps\",\"duration\",\n"; 
    }
    file_id << "\"" << n << "\",\"" << comp_coutner << "\",\"" << swap_coutner << "\",\"" << duration << "\"\n";
    file_id.close();

    //delete[] array;
    return 0;
}
