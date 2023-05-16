#include <iostream>
#include <string>

using namespace std;
int main(int argc, char* argv[]){//PODAJEMY K, GENERATOR I RODZAJ SORTOWANIA
    int n;
    int m = 100;
    char* v;//RNG
    char* s;//NG                 //s = IS; MS; QS
    char* extra;
    if(argc > 1){
        //m = atoi(argv[1]);
        v = argv[1];// RANDOM RND
        s = argv[2];// NG NGI NGD
        //n = atoi(argv[3]);
        //extra = argv[3];
    }
    string s2 = s;
    string v2 = v;
    //string extra2 = extra;


    // /.RND $(./NG 100 50)
    for(int n = 100; n <= 10000; n=n+100){
    //for(int n = 10; n <= 200; n=n+10){
        string cmd ="./";
        cmd = cmd + v2 + " $(./" + s2;
        cmd = cmd + " " + to_string(n) + " ";
        cmd = cmd + to_string(n/2) + " " +  ")";//"./%s %d | ./%s",v, n, s
        
        for(int i = 0; i < m; i++)
            system(cmd.c_str());
                
    }
}
