#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
#define MAX(a, b) a>b?a:b



long Knapsack(vector<pair<long, long>>v, int kbSize){
    // subproblem solution
    // long A[v.size()+1][kbSize+1];
    // the array A is too large that it for stack size, declare it globally or use memory allocate
    int** A = new int*[v.size()+1];
    for (int i=0; i<=v.size(); i++){
        A[i] = new int[kbSize+1];
    }
    // base case (i=0)
    for (int i=0; i<=kbSize; i++) A[0][i]=0;
    // systematically solve all subproblems
    for (int i=1; i<=v.size(); i++){
        for (int j=0; j<=kbSize; j++){
            // use recurrence
            if (v[i-1].second > j){
                A[i][j] = A[i-1][j];
            }else{
                A[i][j] = MAX(A[i-1][j], A[i-1][j-v[i-1].second]+v[i-1].first);
            }
        }
    }
    return A[v.size()][kbSize];
}

int main(int argc, char* argv[]){
    string s;
    fstream in(argv[1]);
    getline(in, s);
    int kbSize, numItem;
    vector<pair<long, long>> v; // value weight
    kbSize = stoi(s.substr(0, s.find_first_of(' ')));
    numItem = stoi(s.substr(s.find_first_of(' ')));
    while (numItem--){
        getline(in, s);
        long value = stol(s.substr(0, s.find_first_of(' ')));
        long weight = stol(s.substr(s.find_first_of(' ')));
        v.push_back(make_pair(value, weight));
    }
    cout<<Knapsack(v, kbSize)<<endl;
    return 0;
}