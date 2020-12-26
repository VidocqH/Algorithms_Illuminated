//https://www.geeksforgeeks.org/strongly-connected-components/

#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stack>
using namespace std;

static int sscNum=0;
static list<int> res;

class graph{
    private:
        int V; // number of vertices
        list<int>* adj; // array of adjcenycy lists
    public:
        graph(int v);
        void addEdge(int v, int w);
        graph reverse();
        void dfs_topo(int v, bool explored[], stack<int> &Stack);
        void topoSort(int v, bool explored[]);
        void dfsIterative(int v);
        void DFSUtil(int v, bool explored[]);
        void fillOrder(int v, bool explored[], stack<int> &Stack);
        void printSCC(int ver);
        graph getTranspose();
};

graph::graph(int v){
    this->V=v;
    adj=new list<int>[v];
}

void graph::addEdge(int v, int w){
    adj[v].push_back(w);
    }

graph graph::reverse(){
    list<int>::iterator j;
    graph res(this->V);
    for (int i=0; i<this->V; i++){
        for (j=adj[i].begin(); j!=adj[i].end();j++){
            res.adj[*j].push_back(i);
        }
    }
    return res;
}

void graph::topoSort(int v, bool explored[]){
    explored[v]=0;
    list<int>::iterator i;
    for (i=adj[v].begin(); i!=adj[v].end(); i++){
        //if (explored[*i]) dfs_topo(*i, explored);
    }
}

void graph::dfs_topo(int v, bool explored[], stack<int> &Stack){
    explored[v]=1;
    list<int>::iterator i;
    for (i=adj[v].begin(); i!=adj[v].end(); i++){
        if (!explored[v]) dfs_topo(*i, explored, Stack);
    }
    Stack.push(v);
}

void graph::DFSUtil(int v, bool explored[]) 
{ 
    // Mark the current node as visited and print it 
    explored[v] = true; 
    // Recur for all the vertices adjacent to this vertex 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!explored[*i])
            DFSUtil(*i, explored); 
            sscNum++;
} 

void graph::fillOrder(int v, bool explored[], stack<int> &Stack) 
{ 
    // Mark the current node as explored and print it 
    explored[v] = true; 
    // Recur for all the vertices adjacent to this vertex 
    list<int>::iterator i; 
    for(i = adj[v].begin(); i != adj[v].end(); ++i) 
        if(!explored[*i]) 
            fillOrder(*i, explored, Stack); 
    // All vertices reachable from v are processed by now, push v  
    Stack.push(v); 
} 

void graph::dfsIterative(int v){
    bool* explored=new bool[this->V]{0};
    stack<int> S;
    list<int>::iterator i;
    S.push(v);
    while (S.size()){
        int popV = S.top();
        S.pop();
        if (!explored[popV]){
            explored[popV]=1;
            for (i=adj[v].begin(); i!=adj[v].end(); i++)
                S.push(*i);
        }
    }
}

graph graph::getTranspose(){
    graph g(V);
    for (int v=0;v<V;v++){
        list<int>::iterator i;
        for(i=adj[v].begin();i!=adj[v].end();i++){
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void graph::printSCC(int ver){
    stack<int> Stack;
    bool* explored=new bool[V];
    for (int i=0;i<V;i++) explored[i]=false;
    for (int i=0;i<V;i++){
        if (!explored[i]) fillOrder(i, explored, Stack);
    }
    graph gv=getTranspose();
    for (int i=0;i<V;i++) explored[i]=false;
    while (!Stack.empty()){
        int v=Stack.top();
        Stack.pop();
        if (!explored[v]){
            gv.DFSUtil(v, explored);
            if (sscNum==1) res.push_back(0);
            else res.push_back(sscNum);
            sscNum=0;
        }
    }
    res.sort(greater<int>());
    res.resize(5);
    list<int>::iterator i;
    int j=0;
    for (i=res.begin();i!=prev(res.end() ,1);i++){
        if (j<ver && *i==0) *i=1;
        j+=*i;
        cout<<*i<<',';
    }
    int a=*prev(res.end(), 1);
    if (j<ver && a==0) a=1;
    cout<<a<<endl;
}

int getNumOfVertices(string s){
    s=s.substr(s.find_last_of('_')+1);
    s.erase(s.find('.'));
    return stoi(s);
}

int getNumOfEdges(string s){
    fstream in(s);
    char c;
    int res=0;
    while(in.get(c)){
        if(c=='\n') res++;
    }
    in.close();
    return res+20;
}

int main(int argc, char* argv[]){
    stack<int> S;
    //string s="input_mostlyCycles_14_64.txt";
    string s=argv[1];
    int i = getNumOfEdges(s);
    int ver = getNumOfVertices(s);
    graph x(i);
    fstream in(s);
    //regex ws_re("\\s+");
    while (!in.eof()){
        getline(in ,s);
        try{
            string a=s.substr(0, s.find(' '));
            string b=s.substr(s.find(' '));
            x.addEdge(stoi(a), stoi(b));
            //cout<<a<<b<<endl;
        }catch(exception){}
    }
    // x.addEdge(1,4);
    // x.addEdge(2,8);
    // x.addEdge(3,6);
    // x.addEdge(4,7);
    // x.addEdge(5,2);
    // x.addEdge(6,9);
    // x.addEdge(7,1);
    // x.addEdge(8,5);
    // x.addEdge(8,6);
    // x.addEdge(9,7);
    // x.addEdge(9,3);

//    graph revX(i);
//    revX = x.reverse();
//    bool* revXexplored=new bool[i];
//    for (int j=0;j<i;j++) revXexplored[j]=0;
//    while (!S.empty()){
//        int popV=S.top();
//        S.pop();
//        if (!revXexplored[i]){
//            revX.DFSUtil(i, revXexplored);
//        }
//    }
    x.printSCC(ver);
    return 0;
}