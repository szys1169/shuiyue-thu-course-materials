#pragma once
#include<iostream>

template <class T>
class Line
{
    public:
    T k;
    T b;
    Line(T k1,T b1):k(k1),b(b1){};
    Line(T k1):k(k1),b(0){};
    T get_k(){return k;}
    T get_b(){return b;}
    void show()
    {
        std::cout<<k<<","<<b<<std::endl;
    }
    bool operator <(const Line<T>& line)
    {
        if(k<line.k)return true;
        return false;
    }
    bool intersect(const Line<T>& line)
    {
        if(k==line.k&&b!=line.b)return false;
        return true;
    }
};