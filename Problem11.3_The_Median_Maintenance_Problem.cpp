// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define MAX(a,b) a>b?a:b
using namespace std;

struct node{
    int n; //value
    node* lef=NULL;
    node* rig=NULL;
    int h=1; //height
};

class avlTree{
    private:
        node* root;
    public:
        avlTree(int n);
        node* search(int n);
        void insert(int n);
        int max();
        int min();
        node* rightRotate(node* y);
        node* leftRotate(node* x);
        int getBalance(node* n);
        int getHeight(node* n);
        void preOrder(node* root) ;
        node* getRoot();
};
avlTree::avlTree(int n){
    root = new node;
    root->n=n;
    root->lef=NULL;
    root->rig=NULL;
    root->h=1;
}
node* avlTree::search(int n){
    node* i = root;
    while(i!=NULL){
        if (i->n==n) return i;
        if (i->n>n) i=i->lef;
        else i=i->rig;
    }
    return NULL;
}
// can't deal with repeated values
void avlTree::insert(int n){
    // normal BST insertion
    node* i = root;
    node * j;
    while(i!=NULL){
        j = i;
        if (i->n>n) i=i->lef;
        else i=i->rig;
    }
    i = new node;
    i->n = n;
    if (j->n>n) j->lef = i;
    else j->rig = i;
    j->h = 1 + MAX(getHeight(j->lef), getHeight(j->rig));
    int balance = getBalance(j);
    // If this node becomes unbalanced, then  
    // there are 4 cases  
    // Left Left Case  
    if (balance > 1 && n < (j->lef->n))  {
        root = rightRotate(j);
        return;
    }
    // Right Right Case  
    if (balance < -1 && n > (j->rig->n))  {
        root = leftRotate(j);  
        return;
    }
    // Left Right Case  
    if (balance > 1 && n > (j->lef->n))  
    {  
        j->lef = leftRotate(j->lef);  
        root = rightRotate(j);  
        return;
    }  
    // Right Left Case  
    if (balance < -1 && n < (j->rig->n))  
    {  
        j->rig = rightRotate(j->rig);  
        root = leftRotate(j);  
        return;
    }  
}
int avlTree::min(){
    node* i = root;
    int min = i->n;
    while (i!=NULL){
        min = i->n;
        i = i->lef;
    }
    return min;
}
int avlTree::max(){
    node* i = root;
    int max = i->n;
    while (i!=NULL){
        max = i->n;
        i = i->rig;
    }
    return max;
}
// rotate subtree rooted with y
node* avlTree::rightRotate(node* y){
    node* x = y->lef;
    node* t2 = x->rig;
    x->rig = y;
    y->lef = t2;
    y->h = MAX(getHeight(y->lef), getHeight(y->rig)+1);
    x->h = MAX(getHeight(x->lef), getHeight(x->rig)+1);
    return x;
}
// rotate subtree rooted with x
node* avlTree::leftRotate(node* x){
    node* y = x->lef;
    node* t2 = y->rig;
    y->lef = x;
    x->rig = t2;
    x->h = MAX(getHeight(x->lef), getHeight(x->rig)+1);
    y->h = MAX(getHeight(y->lef), getHeight(y->rig)+1);
    return y;
}
int avlTree::getBalance(node* n){
    if (n == NULL) return 0;
    return getHeight(n->lef) - getHeight(n->rig);
}
int avlTree::getHeight(node* n){
    if (n == NULL) return 0;
    return n->h;
}
void avlTree::preOrder(node* root)  {  
    if(root != NULL)  
    {  
        cout << root->n << " ";  
        preOrder(root->lef);  
        preOrder(root->rig);  
    }  
}  
node* avlTree::getRoot(){
    return root;
}
void middle_order(node* Node, vector<int>* v) {
    if(Node != NULL) {
        middle_order(Node->lef, v);
        //cout<<Node->n;
        v->push_back(Node->n);
        middle_order(Node->rig, v);
    }
}
int main(int argc, char* argv[]){
    fstream in(argv[1]);
    string s;
    vector<int> v;
    while (!in.eof()){
        getline(in, s);
        if (!s.size()) continue;
        try{v.push_back(stoi(s));}
        catch(exception){};
    }
    avlTree bt = avlTree(v.front());
    vector<int>::iterator it;
    int res = 0;
    for (it=v.begin()+1;it!=v.end();it++){
        //bt.preOrder(bt.getRoot());
        vector<int> vv;
        middle_order(bt.getRoot(), &vv);
        if (vv.size()%2) res+=vv[vv.size()/2];
        else res+=vv[vv.size()/2-1];
        bt.insert(*it);    
    }
    vector<int> vv;
    middle_order(bt.getRoot(), &vv);
    if (vv.size()%2) res+=vv[vv.size()/2];
    else res+=vv[vv.size()/2-1];
    cout<<res%10000<<endl;
    return 0;
}