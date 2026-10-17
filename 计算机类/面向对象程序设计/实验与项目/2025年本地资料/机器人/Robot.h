#pragma once
#include<iostream>
#include"Part.h"
using namespace std;

class Robot
{
    public:
    int number{};
    int count=0;
    int value{};
    Robot(int num):number(num){};
    virtual bool is_full()=0;
    virtual void add_part(Part part)=0;
    virtual int run()=0;
    virtual string robottype() const=0;
    friend ostream& operator<<(ostream& out,const Robot& robot);
    virtual ~Robot(){};
};
