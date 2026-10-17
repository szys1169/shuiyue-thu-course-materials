#include<iostream>
#include"Robot.h"
#include"Part.h"
#include"Alice.h"
using namespace std;

Alice::Alice(int partnum):Robot(partnum){};

bool Alice::is_full()
{
    if(count==number)return true;
    return false;
}

void Alice::add_part(Part part)
{
    count++;
    value+=part.getnum();
}

int Alice::run()
{
    return value;
}

string Alice::robottype()const
{
    return "Alice";
}

