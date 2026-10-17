#include<iostream>
#include<string>
#include"weapon.h"
#include"dragon.h"
#include"ninja.h"
#include"fire_ninja.h"
using namespace std;

void FireNinja::describe()
{
    cout<<"Fire ninja is coming!"<<endl;
    cout<<"Fire ninja is with "<<dragon.get_name()<<" and "<<weapon.get_name()<<"."<<endl;
}

void FireNinja::fire_power()
{
    cout<<"I will burn the night!"<<endl;
}