#pragma once
#include<iostream>
#include<string>
#include"weapon.h"
#include"dragon.h"
#include"ninja.h"
using namespace std;

class FireNinja:public Ninja
{
    public:
    FireNinja(string dragon_name,string weapon_name):Ninja(dragon_name,weapon_name)
    {}
    void describe();
    void fire_power();
};
