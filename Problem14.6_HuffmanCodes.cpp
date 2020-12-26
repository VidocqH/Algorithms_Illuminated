#include <stack>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::pair;

int min=10000000, max=0;

struct node{
    long weight;
    bool isMergeNode;
    node* lef=NULL;
    node* rig=NULL;
};

void printForest(vector<node> forest){
    vector<node>::iterator it;
    for (it=forest.begin();it!=forest.end();it++){
        cout<<it->weight<<endl;
    }
}

void printTree(node* n, int count){
    if (n==NULL) return;
    node* i = n;
    cout<<n->weight<<' '<<count<<endl;
    printTree(i->lef, count++);
    printTree(i->rig, count++);
}

node* setNodeValue(node n){
   node* t = new node;
   t->isMergeNode = n.isMergeNode;
   t->weight = n.weight;
   t->lef = n.lef;
   t->rig = n.rig; 
   return t;
}

node huffmanCodes(vector<int> v){
    int tem=0;
    sort(v.begin(), v.end());
    vector<int>::iterator vit;
    vector<node> forest;
    for (vit=v.begin();vit!=v.end();vit++){
        node n = {*vit, 0, NULL, NULL};
        forest.push_back(n);
    }
    vector<node>::iterator it;
    while (forest.size()!=1){
        node* subRoot = new node;
        subRoot->lef = setNodeValue(forest[0]);
        subRoot->rig = setNodeValue(forest[1]);
        subRoot->isMergeNode = 1;
        subRoot->weight = subRoot->lef->weight + subRoot->rig->weight;
        forest.erase(forest.begin(), next(forest.begin(), 2));
        for (it=forest.begin();it!=forest.end();it++){
            if (it->weight>=subRoot->weight){
                forest.emplace(it, *subRoot);
                tem = 1;
                break;
            }
        }
        if (tem == 0) forest.emplace(forest.end(), *subRoot);
        tem = 0;
        // printForest(forest);
        // cout<<"-----------"<<endl;
    }
    // cout<<"----xxxxx------"<<endl;
    // cout<<forest[0].lef->lef->weight<<endl;
    // cout<<forest[0].lef->lef->lef->weight<<endl;
    // cout<<forest[0].lef->rig->weight<<endl;
    // cout<<"-----------"<<endl;
    return forest[0];
}

void recurTree(node* n, int count){
    if (n==NULL){
        return;
    }
    recurTree(n->lef, ++count);
    //cout<<n->weight<<' '<<count<<endl;
    if (n->isMergeNode == false){
        min = min>count ? count:min;
        max = max>count ? max:count;
    }
    count--;
    recurTree(n->rig, ++count);
    count--;
}

// return pair<min, max>
pair<int ,int> findMaxMinLength(node* root){
    int count=0, t=0;
    node* i = root;
    recurTree(i, count);
    return std::make_pair(min-1, max-1); // minus 1 because the root doesn't count as a layer
}

int main(int argc, char* argv[]){
    int numOfSymbols;
    string s;
    std::fstream in(argv[1]);
    std::getline(in, s);
    numOfSymbols = stoi(s);
    vector<int> albet;
    vector<node> forest;
    while (numOfSymbols--){
        getline(in ,s);
        albet.push_back(stol(s));
    }
    node root = huffmanCodes(albet);
    pair<int, int> res = findMaxMinLength(&root);
    cout<<res.second<<endl<<res.first<<endl;
    return 0;
}