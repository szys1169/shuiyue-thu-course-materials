#pragma once

#include "Footman.h"
#include "Commander.h"
#include "Belong.h"
#include "Casern.h"

class HumanFootman :  public Footman 
{
public:
    HumanFootman(std::string _footmanId):Footman(_footmanId){};
    //TODO
};

class OrcFootman :  public Footman 
{
public:
    OrcFootman(std::string _footmanId):Footman(_footmanId){};
    //TODO
};

class HumanCommander :  public Commander 
{
public:
    HumanCommander(std::string _commanderId):Commander(_commanderId){};
    //TODO
};

class OrcCommander :  public Commander 
{
public:
    OrcCommander(std::string _commanderId):Commander(_commanderId){};
    //TODO
};

class HumanBelong :  public Belong
{
public:
    HumanBelong(Footman* _footman, Commander* _commander):Belong(_footman,_commander){};
    //TODO
};

class OrcBelong :  public Belong
{
public:
    OrcBelong(Footman* _footman, Commander* _commander):Belong(_footman,_commander){};
    //TODO
};

class HumanCasern : public Casern
{
public:
    std::string getKind()
    {
        return "HumanCasern";
    }
    //TODO
};

class OrcCasern : public Casern
{
public:
    std::string getKind()
    {
        return "OrcCasern";
    }
	//TODO
};
