#include"Node.h"
#include<iostream>
#include"Array.h"
using namespace std;

Node& Array::operator[](int b)
{
    return shuju[b];
}

const Node& Array::operator[](int b) const
{
    return shuju[b];
}

Array::~Array()
{
    delete[] shuju;
}