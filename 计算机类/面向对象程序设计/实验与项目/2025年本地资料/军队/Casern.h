#pragma once
#include "Footman.h"
#include "Commander.h"
#include "Belong.h"
#include <vector>


class Casern 
{
    std::vector<Footman*> ff;
    std::vector<Commander*> cc;
    std::vector<Belong*> bb;
    //TODO
public:
    virtual std::string getKind() = 0;
    Footman* getFootmanbyIndex(int k)
    {
        return ff[k];
    }
    Commander* getCommanderbyIndex(int k)
    {
        return cc[k];
    }
    Belong* getBelongbyIndex(int k)
    {
        return bb[k];
    }
    void addFootman(Footman* f)
    {
        ff.push_back(f);
    }
    void addCommander(Commander* c)
    {
        cc.push_back(c);
    }
    void addBelong(Belong* b)
    {
        bb.push_back(b);
    }
	//TODO
};