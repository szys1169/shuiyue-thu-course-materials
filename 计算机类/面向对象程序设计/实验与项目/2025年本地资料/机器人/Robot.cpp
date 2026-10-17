#include<iostream>
#include"Part.h"
#include"Robot.h"
using namespace std;

ostream& operator<<(ostream& out,const Robot& robot)
{
    string name=robot.robottype();
    out<<"Build robot "<<name;
    return out;
}