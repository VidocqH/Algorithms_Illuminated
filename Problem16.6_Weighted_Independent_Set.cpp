#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#define MAX(a, b) a>b?a:b
using namespace std;

void printWIS(vector<long> v, vector<long> S){
    int arr[8] = {1,2,3,4,17,117,517,997};
    string res;
    bool t = false;
    vector<long>::reverse_iterator it;
    for (int i=0; i<8; i++){
        if (arr[i]-1 >= v.size()) break; // out of range
        for (it=S.rbegin();it!=S.rend();it++){
            if (v[arr[i]-1] == *it){
                res.push_back('1');
                t = true;
                break;
            }
        }
        if (!t) res.push_back('0');
        t = false;
    }
    while (res.size()<8) res.push_back('0');
    cout<<res<<endl;
}

void WIS_Reconstruction(vector<long> v, vector<long> A){
    vector<long> S; // vertices that in MWIS
    int i = v.size();
    while (i>=2){
        if (A[i-1] >= A[i-2]+v[i-1]){
            i--;
        }else{
            S.push_back(v[i-1]);
            i-=2;
        }
    }
    if (i==1){
        S.push_back(v[i-1]);
    }
    printWIS(v, S);
}

vector<long> WIS(vector<long> v){
    vector<long> A(v.size()+1); // subproblem solutions
    A[0] = 0; // base case #1
    A[1] = v[0]; // base case #2
    for (int i=2; i<v.size()+1; i++){
        // use recurrence
        A[i] = MAX(A[i-1], A[i-2]+v[i-1]);
    }
    return A;
}

int main(int argc, char* argv[]){
    vector<long> v;
    fstream in(argv[1]);
    string s;
    getline(in, s);
    int numV = stoi(s);
    while (numV--){
        getline(in, s);
        v.push_back(stol(s));
    }
    //v = {280, 618, 762, 908, 409, 34, 312, 277, 246, 779};
    WIS_Reconstruction(v, WIS(v));
    return 0;
}