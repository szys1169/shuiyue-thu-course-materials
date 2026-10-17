#include<iostream>
#include"Robot.h"
#include"Part.h"
#include"Bob.h"
using namespace std;

Bob::Bob(int partnum):Robot(partnum){};

bool Bob::is_full()
{
    if(count==number)return true;
    return false;
}

void Bob::add_part(Part part)
{
    count++;
    value+=part.getnum()*part.getnum();
}

string Bob::robottype()const
{
    return "Bob";
}

int Bob::run()
{
    return value;
}