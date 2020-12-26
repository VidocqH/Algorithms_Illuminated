#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
static long long int numInv=0;

int brute_force_counting_inversions(vector<int>arr){
    int res=0;
    vector<int>::iterator i,j;
    for (i=arr.begin();i!=arr.end()-1;i++){
        for (j=i+1;j!=arr.end();j++){
            if (*i>*j) res++;
        }
    }
    return res;
}

vector<int> merge(vector<int>::iterator head,vector<int>::iterator mid, vector<int>::iterator end){
    vector<int> v;
    vector<int>::iterator l=head, r=mid, m=mid, e=end;
    while (l!=m && r!=e){
        if (*l <= *r){
            v.push_back(*l);
            l++;
        }else{
            v.push_back(*r);
            r++;
            numInv+=distance(l,m);
        }
    }
    v.insert(v.end(), l, m);
    v.insert(v.end(), r, e);
    return move(v);
}

void split_inv(vector<int>::iterator head, vector<int>::iterator end){
    int size=distance(head,end);
    if (size <= 1) return;
    else{
        vector<int>::iterator mid=next(head,size>>1);
        split_inv(head, mid);//left
        split_inv(mid, end);//right
        vector<int> &&arr=merge(head, mid, end);
        move(arr.cbegin(), arr.cend(), head);
    }
}

int main(int argc, char* argv[]){
    vector<int>arr;
    //for(int i=8;i>0;i--){
        //arr.push_back(i);       
    //}
    ifstream in(argv[1]);
    string s;
    while (!in.eof()){
        getline(in, s);
        try{
            arr.push_back(stoi(s));
        }catch(exception){}
    }
    split_inv(arr.begin(),arr.end());
    cout<<numInv<<endl;
    return 0;
}
