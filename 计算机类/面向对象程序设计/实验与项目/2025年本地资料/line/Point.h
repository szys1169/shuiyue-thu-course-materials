#pragma once
#include<iostream>
#include"Line.h"

template <class T>
class Point
{
    T x;
    T y;
    public:
    Point(T x1,T y1):x(x1),y(y1){};
    void move(T x1,T y1)
    {
    x=x+x1;
    y=y+y1;
    }
    void show()
    {
        std::cout<<"("<<x<<","<<y<<")"<<std::endl;
    }
    bool check(Line<T> const& line)
    {
        if(line.k*x+line.b==y)return true;
        return false;
    }
};