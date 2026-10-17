#include <iostream>
#include <string>
#include <vector>
#include "agent.h"
#include "coder.h"
#include "tester.h"

Agent* Agent::create_agent(int agent_type, int id, std::string& codes)
{
    if(agent_type==0)
    {
        return new Coder(id,codes);
    }
    if(agent_type==1)
    {
        int Flag;
        char Marker;
        cin>>Marker>>Flag;
        return new Tester(id,codes,Marker,Flag);
    }
}