#pragma once

#include <cstdio>
#include <vector>
#include "event.h"

class Chocolate:public EventInterface
{
    EventInterface* last;
    public:
    Chocolate():EventInterface(),last(nullptr){};
    void zoo(EventInterface* a)
    {
        increase_mood(5);
        last=a;
    }
    void shop(EventInterface* a)
    {
        increase_mood(1);
    }
    void birthday()
    {
        increase_mood(1);
        if(last!=nullptr)
        {
            increase_mood(5);
            last->increase_mood(1);
        }
    }
};

class Strawberry:public EventInterface
{
    std::vector<EventInterface*> you;
    public:
    Strawberry():EventInterface(){};
    void zoo(EventInterface* a)
    {
        increase_mood(1);
        if (dynamic_cast<Chocolate*>(a))
        {
        increase_mood(5);
        }
    }
    void shop(EventInterface* a)
    {
        increase_mood(5);
        if (dynamic_cast<Chocolate*>(a))
        {
        increase_mood(5);
        }
        int panduan=0;
        for(auto it:you)
        {
            if(it==a)panduan=1;
        }
        if(panduan==0)you.push_back(a);
    }
    void birthday()
    {
        if(you.size()>=1)
        {
            increase_mood(you.size());
            for(auto it:you)
            {
                it->increase_mood(1);
            }
        }
    }
};