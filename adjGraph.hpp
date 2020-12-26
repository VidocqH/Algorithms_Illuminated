#include <vector>
#include <unordered_map>
#include <algorithm>
#include <list>
using namespace std;

class graph{
    private:
        int V;
        list<pair<int, int>>* adj;
    public:
        graph(int V);
        void addEdge(int src, int des, int cost);
        int prim();
        int Floyd_Warshall();
};

graph::graph(int V){
    this->V=V;
    adj = new list<pair<int, int>>[V];
}

// non-directed graph
void graph::addEdge(int src, int des, int cost){
    adj[src].push_back(make_pair(des, cost));
    adj[des].push_back(make_pair(src, cost));
}

int graph::prim(){
    int numV = this->V;
    vector<int> dis(numV), explored(numV);
    fill(dis.begin(), dis.end(), 10000000); // distance
    fill(explored.begin(), explored.end(), 0); // explored or not
    list<pair<int, int>>::iterator it;
    int sum = 0;
    dis[0]=0;
    for (int i=0;i<numV;i++){
        int u= -1, min = 10000000;
        for (int j=0;j<numV;j++){
            if (explored[j]==false && dis[j]<min){
                min = dis[j];
                u = j;
            }
        }
        if (u==-1) return -1; // can't find any edge weight that smaller than 10000000
        explored[u] = true;
        sum += dis[u];
        for (it=adj[u].begin();it!=adj[u].end();it++){
            int des = (*it).first;
            if (explored[des]==false && (*it).second<dis[des]){
                dis[des] = (*it).second;
            }
        }
    }
    sum=0;
    for (int i=0;i<numV;i++){
        sum+=dis[i];
    }
    return sum;
}

int graph::Floyd_Warshall(){
    
    
    return 0;
}
