#pragma once
#include<iostream>
#include"Fraction.h"
using namespace std;

template<class T>
class calculate
{
    char expressionType;
    T x;
    T y;
    T z;
    T jieguo;
    public:
    calculate(char e,int xx,int yy,int zz):expressionType(e)
    {
        x=xx;y=yy;z=zz;
        yunsuan();
    };
    void yunsuan()
    {
        if(expressionType=='A')jieguo=x*x+y*y+z*z;
        if(expressionType=='B')jieguo=x*y+y/z-x*z;
        if(expressionType=='C')jieguo=y*3*z-x*z/(y-2)-x*y/(z+1);
    }
    friend std::ostream& operator<<(std::ostream& out,const calculate& obj)
    {
        out<<obj.jieguo;
        return out;
    }
};