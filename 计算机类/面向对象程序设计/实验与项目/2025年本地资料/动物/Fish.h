#include<iostream>
#include"Animal.h"
using namespace std;

class Fish:public Animal
{
    public:
    Fish(int C):Animal(C){};
    void sing()
    {
        cout<<"Fish can not sing."<<endl;
    }
    void swim()
    {
        if(color==0){cout<<"Red";}
        else{cout<<"Blue";}
        cout<<" fish is swimming."<<endl;   
    }
    ~Fish() override
    {
        if(color==0){cout<<"Red";}
        else{cout<<"Blue";}
        cout<<" fish is gone."<<endl;
    }
};
