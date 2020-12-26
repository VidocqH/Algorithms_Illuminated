#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;
/*
Input: two n-digit positive integers x and y.
Output: the product x · y.
Assumption: n is a power of 2.
*/

string splitString(string s, int pos){
    
}

unsigned long long karatsuba(unsigned long long x,unsigned long long y){
    if (x<10 || y<10){
        return x*y;
    }
    else{
        string sx = to_string(x);
        string sy = to_string(y);
        //string a,b,c,d,p,q,ac,bd,pq;
        unsigned long long an,bn,cn,dn,pn,qn,acn,bdn,pqn,acbd;
        if (sx.length() != sy.length()){
            if (sx.length() < sy.length()){
                sx.insert(0,1,'0');
            }else{
                sy.insert(0,1,'0');
            }
        }
        size_t len = sx.length(), halfLen=len>>1;
        if (len%2){
            an=stoull(sx.substr(0, halfLen+1));
            bn=stoull(sx.substr(halfLen+1));
            cn=stoull(sy.substr(0,halfLen+1));
            dn=stoull(sy.substr(halfLen+1));
        }else{
            an=stoull(sx.substr(0, halfLen));
            bn=stoull(sx.substr(halfLen));
            cn=stoull(sy.substr(0,halfLen));
            dn=stoull(sy.substr(halfLen));
        }
        pn=an+bn;
        qn=cn+dn;
        acn=karatsuba(an,cn);
        bdn=karatsuba(bn,dn);
        pqn=karatsuba(pn,qn);
        acbd=pqn-acn-bdn;
        return (pow(10,halfLen<<1)*acn+pow(10,halfLen)*acbd+bdn);
    }
}

int main(int argc, char* argv[]){
    string x,y,file;
    ifstream in(argv[1]);
    getline(in, x);
    getline(in, y);
    unsigned long long xn=stoull(x,NULL,10), yn=stoull(y,NULL,10);
    cout<<karatsuba(xn,yn)<<endl;
    return 0;
}
