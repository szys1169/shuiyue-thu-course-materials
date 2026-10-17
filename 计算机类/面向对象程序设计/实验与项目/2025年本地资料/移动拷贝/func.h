#pragma once
#include<iostream>
#include"Test.h"
using namespace std;

Test f1(Test a)
{
    a.print("a");
    return a;
};

Test& f2(Test& a)
{
    a.print("b");
    return a;
};

void f3(Test& a,Test& b)
{
    Test p=move(a);
    a=move(b);
    b=move(p);
};