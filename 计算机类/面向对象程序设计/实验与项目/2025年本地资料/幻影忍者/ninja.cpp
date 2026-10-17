#include<iostream>
#include<string>
#include"weapon.h"
#include"dragon.h"
#include"ninja.h"
using namespace std;

void Ninja::describe()
{
    cout<<"Ninja is coming!"<<endl;
    cout<<"Ninja is with "<<dragon.get_name()<<" and "<<weapon.get_name()<<"."<<endl;
}