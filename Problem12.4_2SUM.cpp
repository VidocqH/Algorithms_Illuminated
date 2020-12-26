#include <map>
#include <unordered_map>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "hashtable.h"
using namespace std;
#define TABLE_SIZE 640000

struct mod10KeyFunc{
    unsigned long operator()(const int& k) const{
        return k%10;
    }
};

int whe_hash(vector<long long> v, HashMap<long long, int, struct mod> H){
    vector<long long>::iterator it;
    int res=0, count, value;
    for (int j=-10000;j<=10000;j++){
        count = 0;
        for (it=v.begin();it!=v.end();it++){
            long long y = j-*it;
            if (H.get(y, value)) {
                res++;
                break;
            }
            H.put(*it, count);
            count++;
        }
    }
    return res;
}

int stl_hash(vector<long long> v, unordered_map<long long, int> H){
    vector<long long>::iterator it;
    int res=0, count;
    for (int j=-10000;j<=10000;j++){
        count = 0;
        for (it=v.begin();it!=v.end();it++){
            H.insert_or_assign(*it, count++);
        }
        count = 0;
        for (it=v.begin();it!=v.end();it++){
            long long y = j-*it;
            if (H.find(y)!=H.end() && H[y]!=count++){
                res++;
                break;
            }
        }
    }
    return res;
}

int main(int argc, char* argv[]){
    fstream in(argv[1]);
    string s;
    vector<long long> v;
    unordered_map<long long, int> H;
    while (!in.eof()){
        getline(in, s);
        try{
            v.push_back(stoull(s));
        }catch(exception){}
    }
    //cout<<stl_hash(v, H)<<endl;
    return 0;
}