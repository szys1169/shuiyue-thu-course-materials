#pragma once
#include "Pair.h"

class Map
{
    Pair * data;
    int sz;
    int capcity=0;
public:
    Map(int n);
    int size();
    ~Map();
    int& operator[](const string& name);
    int operator[](const string& name) const;
    
    // TODO
};