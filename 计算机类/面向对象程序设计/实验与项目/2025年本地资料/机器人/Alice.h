#pragma once
#include<iostream>
#include"Robot.h"
#include"Part.h"
using namespace std;

class Alice:public Robot
{
    public:
    Alice(int Partnum);
    bool is_full();
    void add_part(Part part);
    int run(); 
    string robottype() const;
    ~Alice(){};
};