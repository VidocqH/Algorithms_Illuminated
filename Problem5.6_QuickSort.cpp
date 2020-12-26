#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

static int firstElemCount=0;
static int lastElemCount=0;
static int threeMElemCount=0;

void printVector(vector<int> arr){
    vector<int>::iterator i;
    for (i=arr.begin();i!=arr.end();i++){
        cout<<*i<<endl;
    }
}
void swap(int& a,int& b){
    int tem=a;
    a=b;
    b=tem;
}

vector<int>::iterator median(vector<int>::iterator a, vector<int>::iterator b, vector<int>::iterator c){
    if (*c>*b && *c>*a){
        if (*a>*b) return a;
        else return b;
    }else if (*b>*c && *b>*a){
        if (*a>*c) return a;
        else return c;
    }else{
        if (*b>*c) return b;
        else return c;
    }
}

// return pivot's iterator
vector<int>::iterator split(vector<int>::iterator head, vector<int>::iterator end, int method){
    int pivot=*head;
    vector<int>::iterator i=head+1,j;
    for (j=i;j!=end;j++){
        if (*j < pivot){
            swap(*i, *j);
            i++;// restores invariant
        }
        if (method==2) threeMElemCount++;
        else if (method==1) lastElemCount++;
        else firstElemCount++;
    }
    i--;// go to the last elements that less than pivot
    swap(*i,*head);// place pivot correctly
    return i;
}

vector<int>::iterator choosePivot(vector<int>::iterator head, vector<int>::iterator end, int method){
    int size=distance(head, end);
    if (method==0) return head;
    if (method==1) return prev(end, 1);
    if (method==2){
        if (size%2) return median(head, prev(end, 1), next(head, size>>1));
        else return median(head, prev(end, 1), next(head, (size>>1)-1)); 
    }
    return head;// default case
}

void quicksort(vector<int>::iterator head, vector<int>::iterator end, int method){
    int size=distance(head, end);
    if (size<2) return;
    vector<int>::iterator i=choosePivot(head, end, method), j;
    swap(*head, *i);// make pivot first
    j=split(head, end, method);
    quicksort(head, j, method);
    quicksort(j+1, end, method);
}

int main(int argc, char* argv[]){
    string s;
    fstream in(argv[1]);
    vector<int> fir, sec, thd;
    while (!in.eof()){
        getline(in, s);
        try {fir.push_back(stoi(s));}
        catch(exception){}
    }
    sec.assign(fir.begin(), fir.end());//copy arr
    thd.assign(fir.begin(), fir.end());//copy arr
    quicksort(fir.begin(), fir.end(), 0);// first element as pivot
    quicksort(sec.begin(), sec.end(), 1);// last element as pivot
    quicksort(thd.begin(), thd.end(), 2);
    cout<<firstElemCount<<endl;
    cout<<lastElemCount<<endl;
    cout<<threeMElemCount<<endl;
    return 0;
}