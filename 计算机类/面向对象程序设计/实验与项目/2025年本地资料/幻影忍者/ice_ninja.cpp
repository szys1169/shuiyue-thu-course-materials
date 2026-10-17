#include<iostream>
#include<string>
#include"weapon.h"
#include"dragon.h"
#include"ninja.h"
#include"ice_ninja.h"
using namespace std;

void IceNinja::describe()
{
    cout<<"Ice ninja is coming!"<<endl;
    cout<<"Ice ninja is with "<<dragon.get_name()<<" and "<<weapon.get_name()<<"."<<endl;
}

void IceNinja::ice_power()
{
    cout<<"You will be the dust of frozen bones!"<<endl;
}