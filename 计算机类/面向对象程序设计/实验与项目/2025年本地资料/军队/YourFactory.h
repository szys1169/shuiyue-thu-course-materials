#pragma once

#include "AbstractFactory.h"

class HumanFactory: public AbstractFactory
{
public:
    Casern* createCasern()
    {
        return new HumanCasern;
    }
    Footman* createFootman(std::string _footmanId)
    {
        return new HumanFootman(_footmanId);
    }
    Commander* createCommander(std::string _commanderId)
    {
        return new HumanCommander(_commanderId);
    }
    Belong* createBelong(Footman* _footman, Commander* _commander)
    {
        return new HumanBelong(_footman,_commander);
    }
};

class OrcFactory : public AbstractFactory {
public: 
    Casern* createCasern()
    {
        return new OrcCasern;
    }
    Footman* createFootman(std::string _footmanId)
    {
        return new OrcFootman(_footmanId);
    }
    Commander* createCommander(std::string _commanderId)
    {
        return new OrcCommander(_commanderId);
    }
    Belong* createBelong(Footman* _footman, Commander* _commander)
    {
        return new OrcBelong(_footman,_commander);
    }
    //TODO
};
