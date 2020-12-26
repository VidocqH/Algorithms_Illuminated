#include <cmath>
#include <algorithm>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

bool sortIntWithGreater(pair<int, pair<int, int>>a, pair<int, pair<int, int>>b){
    return a.first>b.first;
}
bool sortDoubleWithGreater(pair<double, pair<int, int>>a, pair<double, pair<int, int>>b){
    return a.first>b.first;
}
bool sortEqualDiff(pair<int, pair<int, int>>a, pair<int, pair<int, int>>b){
    return a.second.first>b.second.first;
}
void printVector(vector<pair<int, pair<int, int>>>v){
    vector<pair<int, pair<int, int>>>::iterator it;
    for (it=v.begin();it!=v.end();it++){
        cout<<(*it).first<<' '<<(*it).second.first<<' '<<(*it).second.second<<endl;
    }
}
vector<pair<int, pair<int, int>>> handleSameDiff(vector<pair<int, pair<int, int>>> diff){
    vector<pair<int, pair<int, int>>>::iterator it, lef=diff.begin(), rig=diff.begin();
    for (it=diff.begin();it!=diff.end();it++){
        if ((*it).first != (*lef).first){
            //cout<<(*it).second.first<<' '<<(*it).second.second<<endl;
            sort(lef, rig, sortEqualDiff);
            lef = it;
        }
        rig =next(it, 1);
    }
    sort(lef, diff.end(), sortEqualDiff);
    //printVector(diff);
    return diff;
}

long greedyDiff(vector<pair<int, int>> v){
    long res = 0, count=0;
    vector<pair<int, pair<int, int>>> diff; // list<diff, pair<weight, length>>
    //vector<pair<int, pair<int, int>>>::iterator it;
    vector<pair<int, int>>::iterator it;
    for (it=v.begin();it!=v.end();it++){
        diff.push_back(make_pair(((*it).first - (*it).second), *it));
        //cout<<((*it).first - (*it).second)<<' '<<(*it).first<<' '<<(*it).second<<endl;
    }
    sort(diff.begin(), diff.end(), sortIntWithGreater);
    diff = handleSameDiff(diff);
    vector<pair<int, pair<int, int>>>::iterator itp;
    for (itp=diff.begin();itp!=diff.end();itp++){
        count += (*itp).second.second;
        res += count * (*itp).second.first;
        //cout<<res<<endl;
        //cout<<(*itp).first<<' '<<(*itp).second.first<<' '<<(*itp).second.second<<endl;
    }
    return res;
}

long greedyRatio(vector<pair<int, int>> v){
    long res = 0, count=0;
    double ratio=1;
    vector<pair<double, pair<int, int>>> diff; // list<diff, pair<weight, length>>
    //vector<pair<int, pair<int, int>>>::iterator it;
    vector<pair<int, int>>::iterator it;
    for (it=v.begin();it!=v.end();it++){
        diff.push_back(make_pair(double((*it).first) / double((*it).second), *it));
        //cout<<((*it).first - (*it).second)<<' '<<(*it).first<<' '<<(*it).second<<endl;
    }
    sort(diff.begin(), diff.end(), sortDoubleWithGreater);
    vector<pair<double, pair<int, int>>>::iterator itp;
    for (itp=diff.begin();itp!=diff.end();itp++){
        count += (*itp).second.second;
        res += count * (*itp).second.first;
        //cout<<res<<endl;
        //cout<<(*itp).first<<' '<<(*itp).second.first<<' '<<(*itp).second.second<<endl;
    }
    return res;
 }

int main(int argc, char* argv[]){
    string s;
    vector<pair<int, int>> v; // weight, length
    ifstream in(argv[1]);
    getline(in ,s);
    int dataNum = stoi(s);
    int i = dataNum;
    while (i--){
        getline(in, s);
        int a = stoi(s.substr(0, s.find_first_of(' ')));
        int b = stoi(s.substr(s.find_first_of(' ')));
        v.push_back(make_pair(a, b));
    }
    cout<<greedyDiff(v)<<endl;
    cout<<greedyRatio(v)<<endl;
    return 0;
}