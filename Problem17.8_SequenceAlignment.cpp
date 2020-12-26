#include <iostream>
#include <string>
using namespace std;

int MIN(int a, int b, int c){
    if (a<b){
        return a<c?a:c;
    }else{
        return b<c?b:c;
    }
}

int misMatch(char a, char b, int mismatchC){
    if (a==b) return 0;
    else return mismatchC;
}

int NW(string X, string Y, int gapC, int mismatchC){
    //sub problem solution (indexed from 0)
    int** A = new int*[X.size()+1];
    for (int i=0; i<=X.size(); i++){
        A[i] = new int[Y.size()+1];
    }
    // base case #1 (i=0)
    for (int i=0; i<=X.size(); i++){
        A[i][0] = i*gapC;
    }
    // base case #2 (j=0)
    for (int j=0; j<=Y.size(); j++){
        A[0][j] = j*gapC;
    }
    // systematically solve all subproblems
    for (int i=1; i<=X.size(); i++){
        for (int j=1; j<=Y.size(); j++){
            int case1 = A[i-1][j-1]+misMatch(X[i], Y[j], mismatchC);
            int case2 = A[i-1][j]+gapC;
            int case3 = A[i][j-1]+gapC;
            A[i][j] = MIN(case1, case2, case3);
        }
    }
    return A[X.size()][Y.size()];
}

int main(int argc, char* argv[]){
    int lenX = 148, lenY=123; // length of X, Y
    int gapC = 4, mismatchC=5; // gaps cost, mismatch cost
    string X = "ACACATGCATCATGACTATGCATGCATGACTGACTGCATGCATGCATCCATCATGCATGCATCGATGCATGCATGACCACCTGTGTGACACATGCATGCGTGTGACATGCGAGACTCACTAGCGATGCATGCATGCATGCATGCATGC";
    string Y = "ATGATCATGCATGCATGCATCACACTGTGCATCAGAGAGAGCTCTCAGCAGACCACACACACGTGTGCAGAGAGCATGCATGCATGCATGCATGCATGGTAGCTGCATGCTATGAGCATGCAG";
    cout<<NW(X, Y, gapC, mismatchC)<<endl;
    return 0;
}