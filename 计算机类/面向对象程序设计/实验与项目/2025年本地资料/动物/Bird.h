#include<iostream>
#include"Animal.h"
using namespace std;

class Bird:public Animal
{
    public:
    Bird(int C):Animal(C){};
    void sing()
    {
        if(color==0){cout<<"Red";}
        else{cout<<"Blue";}
        cout<<" bird is singing."<<endl;
    }
    void swim()
    {
        cout<<"Bird can not swim."<<endl;
    }
    ~Bird() override
    {
        if(color==0){cout<<"Red";}
        else{cout<<"Blue";}
        cout<<" bird is gone."<<endl;
    }
};
