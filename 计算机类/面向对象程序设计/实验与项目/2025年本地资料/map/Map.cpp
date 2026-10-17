#include "Map.h"
#include<iostream>
using namespace std;
Map::Map(int t):sz(t){};
int& Map::operator[](string index){
    bool found=false;
    for(int i=1;i<=Pair::n_create;i++){
        if(kor[i-1]->hasKey(index)){
            return kor[i-1]->getVal();
        }
    }
    if(!found){
        Pair* n=new Pair;
        n->reset(index,0);
        kor.push_back(n);
        return n->getVal();
    }
};
int const Map::operator[](string index) const{
        bool found=false;
        for(int i=1;i<=Pair::n_create;i++){
            if(kor[i-1]->hasKey(index)){
                found=true;
                int a=kor[i-1]->getVal();
                return a;
            }
        }
        if(!found){
            return 0;
        }
};
int const Map::size(){
    return Pair::n_create;
}
Map::~Map(){
    for(int i=1;i<=Pair::n_create;i++){delete kor[i];}
}