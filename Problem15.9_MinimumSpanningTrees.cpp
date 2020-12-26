#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "adjGraph.hpp"
using namespace std;


int main(int argc, char* argv[]){
    fstream in(argv[1]);
    string s;
    int numE, numV;
    getline(in, s);
    numV = stoi(s.substr(0, s.find_first_of(' ')));
    numE = stoi(s.substr(s.find_first_of(' ')));
    graph adj = graph(numV);
    while (numE--){
        getline(in, s);
        int src = stoi(s.substr(0, s.find_first_of(' ')));
        int des = stoi(s.substr(s.find_first_of(' '), s.find_last_of(' ')));
        int cost = stoi(s.substr(s.find_last_of(' ')));
        //cout<<src<<' '<<des<<' '<<cost<<endl;
        //if (src==des) continue;
        adj.addEdge(src-1, des-1, cost);
    }
    cout<<adj.prim()<<endl;
    return 0;
}