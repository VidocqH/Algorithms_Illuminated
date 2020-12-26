#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
using namespace std;

void printVector(vector<int>::iterator head, vector<int>::iterator end){
    for (vector<int>::iterator i=head;i!=end;i++){
        cout<<*i<<' ';
    }
    cout<<endl;
}

// Return pivot's iterator
vector<int>::iterator split(vector<int>::iterator head, vector<int>::iterator end){
    vector<int>::iterator i=head+1,j;
   for (j=i;j!=end;j++){
        if (*j < *head){
            swap(*i, *j);
            i++;// restores invariant
        }
    }
    i--;// go to the last elements that less than pivot
    swap(*i,*head);// place pivot correctly
    return i; 
    }

// Return ith smallest elements's iterator
vector<int>::iterator rselect(vector<int>::iterator head, vector<int>::iterator end, int i){
    int size=distance(head,end);
    if (size<2) return head;
    vector<int>::iterator j;
    int pivotIndex=rand()%(size);
    swap(*head,*next(head, pivotIndex)); // let pivot to head
    j=split(head, end); // pivot iterator
    int jIndex=distance(head,j)+1; // j's index
    if (jIndex==i) return j;
    else if(jIndex>i){
        return rselect(head, j, i);
    }else{
        return rselect(j+1, end, i-jIndex);
    }
}

int main(int argc, char* argv[]){
    //vector<int>arr = {1,2,3,4,2,1,5,6,4,3,1,5,4,2,1,5,5,2,3,4,6,6,2,5};
    //vector<int>arr = {1,2,3,4,2,1,5};
    //vector<int>arr = {1,3,4,2,9,7,6,5,8};
    vector<int>arr = {2148,9058,7742,3153,6324,609,7628,5469,7017,504,4092,1582,9572,1542,5697,2081,4218,3130,7923,9595,6558,3859,9832,3062,6788,7578,7432,479,8439,9079,7173,2667,2770,2655,972,4264,2014,3171,4715,345,4388,3816,8887,3915,3490,2327,123,4596,4307,8737,4007,6798,6551,1627,1190,4984,2480,3404,2027,4778,2951,2795,5002,8121,8910,9593,5254,448,6237,5565,1816,392,8143,9310,9293,3138,4869,6756,872,6183,3517,3513,1676,5498,9172,5739,6108,7538,7671,5780,8666,540,9771,6837,9341,1590,5689,1605,1103,5859
    };
    int i, size=arr.size();
    if (size%2) i=(size>>1)+1;
    else i=size>>1;
    vector<int>::iterator j;
    j=rselect(arr.begin(), arr.end(), i); // i stands for order statistic that looking for
    cout<<*j<<endl;
    return 0;
}