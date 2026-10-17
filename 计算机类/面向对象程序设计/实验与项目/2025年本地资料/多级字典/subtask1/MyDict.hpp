#ifndef __SUBTASK1__
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
    int cap=0;
    PopStrategy<Key>* popStrategy = nullptr;
public:
    MyDict():cap(0),popStrategy(nullptr){};
    MyDict(int capacity, PopStrategy<Key>* popStrategyPtr):cap(capacity),popStrategy(popStrategyPtr){};
    Value& operator[](Key key)
    {
        auto it=data.find(key);
        if(it!=data.end())
        {
            hitcount++;
            if(popStrategy)popStrategy->visit(key);
            return it->second;
        }
        else
        {
            misscount++;
            if(popStrategy)popStrategy->visit(key);
            if(cap!=0&&data.size() > cap)
            {
                Key zanshi=popStrategy->pop();
                data.erase(zanshi);
            }
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
        if(popStrategy)
        {
            cap=0;
            popStrategy = nullptr;
        }
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
