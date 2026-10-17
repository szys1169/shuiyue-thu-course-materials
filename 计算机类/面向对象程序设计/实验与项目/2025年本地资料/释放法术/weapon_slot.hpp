#pragma once
#include "weapon.hpp"
#include<iostream>
using namespace std;

class WeaponSlot
{
    Weapon* weapon;
    public:
    ~WeaponSlot()
    {
        delete weapon;
    }
    void create_weapon(int p)
    {
        delete weapon;
        weapon=new Weapon(p);
    };
    void add_spell(int p)
    {
        weapon->spells.push_back(p);
    };
    WeaponSlot& operator=(const WeaponSlot& w)
    {
        if (this != &w){
			delete weapon;
            vector<int> newspells;
            for(int spell : w.weapon->spells)
            {
                if(spell%2==0)
                {
                    newspells.push_back(spell);
                }
            }
            weapon=new Weapon(w.weapon->penetration);
			weapon->spells=newspells;
		}
		return *this;
    };
    WeaponSlot& operator=(WeaponSlot&& w)
    {
        if (this != &w){
			delete weapon;
			weapon =w.weapon;
            w.weapon=nullptr;
		}
		return *this;
    };
    int calc_damage_typeA(int d)
    {
        int h=d-weapon->penetration;
        if(h<=0)h=0;
        int sum=0;
        for(int spell : weapon->spells)
        {
            if(spell>h)
            {
                sum+=spell-h;
            }
        }
        return sum;
    }
    int calc_damage_typeB()
    {
        int d=0;
        int h=0;
        int sum=0;
        for(int spell : weapon->spells)
        {
            h=d-weapon->penetration;
            if(h<=0)h=0;
            if(spell>h)
            {
                sum+=spell-h;
            }
            d++;
        }
        return sum;
    }
    int calc_damage_typeC()
    {
        int d=0;
        int h=0;
        int sum=0;
        for(int spell : weapon->spells)
        {
            h=d-weapon->penetration;
            if(h<=0)h=0;
            int p=spell-h;
            if(p<=0)p=0;
            if(p%2==1)
            {
                sum+=p;
                d++;
            }
            else
            {
                sum+=p/2;
            }
        }
        return sum;
    }
};