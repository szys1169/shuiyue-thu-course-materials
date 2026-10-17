#pragma once
#include<iostream>
using namespace std;

class Animal
{
    public:
    int color;
    Animal():color(){}
    Animal(int C):color(C){}
    virtual void sing()=0;
    virtual void swim()=0;
    virtual ~Animal()=default;
};