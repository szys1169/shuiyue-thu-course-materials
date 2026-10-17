#pragma once
#include "Pair.h"
#include <vector>

class Map{
    Pair * data;
    int sz;
public:
    Map(int n);
    // TODO
    vector <Pair*> kor;
    int& operator[](string);
    int const operator[](string)const; 
    ~Map();
    int const size();
};