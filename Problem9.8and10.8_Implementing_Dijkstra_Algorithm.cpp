// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <climits>
#include <vector>
#define INF 10000000
#define Min(a,b) a<b ? a:b
using namespace std;

class graph{
    private:
        int V;
        list<pair< int, int >>* adj;
    public:
        graph(int V);
        void addEdge2Adj(int v, int e, int w);
        void dijkstra(int v);
        void shortestPath(int s);
};
graph::graph(int V){
    this->V=V;
    adj = new list<pair<int, int>>[V];
}
// Edge from v to e, the weight is w
void graph::addEdge2Adj(int v, int e, int w){
    adj[v].push_back(make_pair(e, w));
    //adj[e].push_back(make_pair(v, w));
}
void graph::dijkstra(int s){
    // list<vector<int>>* X = new list<vector<int>>[this->V];
    // int numV=this->V;
    // X[s] = adj[s];
    // while (adj[s].size())
    //     adj[s].pop_back();
    // numV--;
    // vector<int> prev;
    // list<int> dis[this->V];
    // list<vector<int>>::iterator it;
    // dis[s].push_back(0);
    // for (it=X[s].begin();it!=X[s].end();it++)
    //     prev.push_back(it->front());
    //     dis[it->front()].push_back(it->back());
    // for (int i=0;i<this->V;i++){
    //     if (i==s) continue;
    //     for (it=adj[i].begin();it!=adj[i].end();it++)
    //         if (!dis[it->front()].size())
    //             dis[it->front()].push_back(INF);
    // }
    // while (numV){
    //     for (it=adj[prev.front()].begin();it!=adj[prev.front()].end();it++){
    //     }
    // }

}

// src: the start vertice
void graph::shortestPath(int src){
    // STL queue which uses heap to maintain priority
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>> >pq;
    // vector<type> name(size, initial value)
    vector<int> dist(V, INF);
    // Initialization
    pq.push(make_pair(0, src));
    // Distance to itself is 0
    dist[src]=0;
    while (!pq.empty()){
        // u = current vertice
        int u = pq.top().second;
        // pop means to mark it as explored
        pq.pop();
        // Iteratate all the vertices links from the current vertice
        list<pair<int, int>>::iterator i;
        for (i=adj[u].begin();i!=adj[u].end();i++){
            int v=(*i).first; // v = vertice
            int weight=(*i).second;
            if (dist[v]>dist[u]+weight){
                dist[v]=dist[u]+weight;
                pq.push(make_pair(dist[v], v)); // choose that way
            }
        }
    }
    // for (vector<int>::iterator i=dist.begin()+1;i!=prev(dist.end(), 1);i++)
    //     cout<<*i<<',';
    // cout<<*prev(dist.end(), 1)<<endl;
    vector<int> outOrder={7,37,59,82,99,115,133,165,188,197};
    vector<int>::iterator i;
    for(i=outOrder.begin();i!=prev(outOrder.end(), 1);i++){
        cout<<dist[*i]<<',';
    }
    cout<<dist[outOrder.back()]<<endl;
}

int main(int argc, char* argv[]){
    fstream in(argv[1]);
    int V=2000;
    graph g(V);string s;
    while (!in.eof()){
        getline(in ,s);
        if (!s.size()) continue;
        int v=stoi(s.substr(0, s.find_first_of('\t')));
        do
        {
            s=s.substr(s.find_first_of('\t')+1);
            g.addEdge2Adj(v, stoi(s.substr(0, s.find_first_of(','))), stoi(s.substr(s.find_first_of(',')+1)));
        } while (s.find('\t')!=string::npos);
        
    }
    // g.addEdge2Adj(1,2,1);
    // g.addEdge2Adj(1,8,2);
    // g.addEdge2Adj(2,1,1);
    // g.addEdge2Adj(2,3,1);
    // g.addEdge2Adj(3,2,1);
    // g.addEdge2Adj(3,4,1);
    // g.addEdge2Adj(4,3,1);
    // g.addEdge2Adj(4,5,1);
    // g.addEdge2Adj(5,4,1);
    // g.addEdge2Adj(5,6,1);
    // g.addEdge2Adj(6,5,1);
    // g.addEdge2Adj(6,7,1);
    // g.addEdge2Adj(7,6,1);
    // g.addEdge2Adj(7,8,1);
    // g.addEdge2Adj(8,7,1);
    // g.addEdge2Adj(8,1,2);
    g.shortestPath(1);
/* 
1	2,1	8,2
2	1,1	3,1
3	2,1	4,1
4	3,1	5,1
5	4,1	6,1
6	5,1	7,1
7	6,1	8,1
8	7,1	1,2 */
    return 0;
}