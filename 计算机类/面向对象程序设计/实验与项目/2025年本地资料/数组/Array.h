#pragma once
#include"Node.h"
#include<iostream>
using namespace std;

class Array
{
    Node* shuju;
    int lengh;
    public:
    Array(int len):lengh(len)
    {
        shuju=new Node[len];
    }
    Array(const Array& a):lengh(a.lengh)
    {
        shuju=new Node[a.lengh];
        for(int i=0;i<a.lengh;i++)
        {
            shuju[i]=a.shuju[i];
        }
    }
    Array(Array&& a):shuju(a.shuju),lengh(a.lengh)
    {
        a.lengh=0;
        a.shuju=nullptr;
    }
    Array& operator=(const Array& a)
    {
        if(this!=&a)
        {
            delete[] shuju;
            lengh=a.lengh;
            shuju=new Node[a.lengh];
            for(int i=0;i<a.lengh;i++)
            {
                shuju[i]=a.shuju[i];
            }
        }
        return *this;
    }
    Array& operator=(Array&& a)
    {
        {
            if(this!=&a)
            {
                delete[] shuju;
                lengh=a.lengh;
                shuju=a.shuju;
                a.lengh=0;
                a.shuju=nullptr;
            }
            return *this;
        }
    }
    Node& operator[](int b);
    const Node& operator[](int b) const;
    ~Array();
};