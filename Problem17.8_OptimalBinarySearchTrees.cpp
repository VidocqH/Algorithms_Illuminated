#include <iostream>
#include <vector>
using namespace std;

int MIN(vector<int> v){
    int res=v.front();
    vector<int>::iterator it;
    for (it=v.begin(); it!=v.end(); it++){
        res = res<(*it) ? res:(*it);
    }
    return res;
}

int optBST(vector<int> v){
    vector<int> t;
    // subproblems (i indexed from 1, j from 0)
    int** A = new int*[v.size()+1];
    for (int i=0; i<=v.size(); i++){
        A[i] = new int[v.size()+1];
    }
    // base cases i=j+1
    for (int i=1; i<=v.size(); i++){
        A[i][i-1] = 0;
    }
    // systematically sovle all subproblems (a<=j)
    for (int i=0; i<=v.size(); i++){
        for (int j=1; j<=v.size()-i; j++){
            int sumP = 0;
            for (int k=j; k<=i+j; k++){
                sumP+=v[k];
            }
            for (int r=j; r<i+j; r++) {
                v.push_back(A[j][r-1] + A[r+1][j+i]);
            }
            A[j][j+i] = sumP + MIN(t);
            t.clear();
        }
    }
    return A[1][v.size()];
}

int main(int argc, char* argv[]){
    int numN = 50;
    // frequencies
    vector<int> v = {2,8,2,5,5,2,8,3,6,1,1,6,3,2,6,7,4,63,2,9,10,1,60,5,2,7,34,11,31,76,21,6,8,1,81,37,15,6,8,24,12,18,42,8,51,21,8,6,5,7};
    cout<<optBST(v)<<endl;
    return 0;
}