#pragma once
#include<iostream>
#include<string>
#include"weapon.h"
#include"dragon.h"
#include"ninja.h"
using namespace std;

class IceNinja:public Ninja
{
    public:
    IceNinja(string dragon_name,string weapon_name):Ninja(dragon_name,weapon_name)
    {}
    void describe();
    void  ice_power();
};
