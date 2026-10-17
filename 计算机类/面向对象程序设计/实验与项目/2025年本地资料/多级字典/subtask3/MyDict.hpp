#ifndef __SUBTASK1__
#pragma once
#include<iostream>
#include<map>
#include"HitStatsResult.hpp"
#include"PopStrategy.hpp"
using namespace std;
template<class Key, class Value>
class MyDict
{
    map<Key,Value> data;
    int hitcount=0;
    int misscount=0;
    int cap=0;
    PopStrategy<Key>* popStrategy = nullptr;
public:
    MyDict():cap(0),popStrategy(nullptr){};
    MyDict(int capacity, PopStrategy<Key>* popStrategyPtr):cap(capacity),popStrategy(popStrategyPtr){};
    Value& operator[](const Key &key)
    {
        int j=0;
       for (auto it = data.begin(); it != data.end(); ++it) 
       {
        j++;
        if (it->first == key) 
        { 
            cout<<j<<endl;
            hitcount++;
            if (popStrategy) popStrategy->visit(key);
            cout<<"hit"<<endl;
            cout<<"size is "<<data.size()<<endl;
            return it->second;
        }
    }
     cout<<"miss"<<endl;
            misscount++;
            if(cap!=0&&data.size() >= cap)
            {
                Key zanshi=popStrategy->pop();
                data.erase(zanshi);
                cout<<"paichu"<<zanshi<<endl;
            }
            data[key] = Value();
            if(popStrategy)popStrategy->visit(key);
            cout<<"size is "<<data.size()<<endl;
            return data[key];
    }
    HitStatsResult hitStats() const
    {
        return HitStatsResult(hitcount,misscount);
    }
    int size() const
    {
        return data.size();
    }
    void clear()
    {
        data.clear();
        hitcount=0;
        misscount=0;
    }
};
#endif

#ifdef __SUBTASK1__

#pragma once
#include<iostream>
#include<map>
#include"HitStatsResult.hpp"
using namespace std;

template<class Key, class Value>
class MyDict
{
    map<Key,Value> data;
    int hitcount=0;
    int misscount=0;
public:
    Value& operator[](Key key)
    {
        auto it=data.find(key);
        if(it!=data.end())
        {
            hitcount++;
            return it->second;
        }
        else
        {
            misscount++;
            return data[key]=Value();
        }
    }
    HitStatsResult hitStats() const
    {
        return HitStatsResult(hitcount,misscount);
    }
    int size() const
    {
        return data.size();
    }
    void clear()
    {
        data.clear();
        hitcount=0;
        misscount=0;
    }
};

# endif
