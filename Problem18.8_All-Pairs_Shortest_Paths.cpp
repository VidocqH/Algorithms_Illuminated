#include <iostream>
#include <string>
#include <fstream>
#include "adjGraph.hpp"
using namespace std;

int main(int argc, char* argv[]){
    fstream in(argv[1]);
    int numV, numE;
    string s;
    getline(in, s);
    numV = stoi(s.substr(0, s.find_first_of(' ')));
    numE = stoi(s.substr(s.find_first_of(' ')));
    graph G = graph(numE);
    while (numE--){
        getline(in, s);
        int tail = stoi(s.substr(0, s.find_first_of(' ')));
        int head = stoi(s.substr(s.find_first_of(' '), s.find_last_of(' ')));
        int weight = stoi(s.substr(s.find_last_of(' ')));
        G.addEdge(tail, head, weight);
    }
    return 0;
}