#pragma once
#include<iostream>
#include<string>
#include"weapon.h"
#include"dragon.h"
using namespace std;

class Ninja
{
    public:
    Dragon dragon;
    Weapon weapon;
    Ninja(string dragon_name,string weapon_name):dragon(dragon_name),weapon(weapon_name)
    {}
    virtual void describe();
};