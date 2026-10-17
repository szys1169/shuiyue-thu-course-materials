#include <iostream>
#include <string>
#include <vector>
#include "agent.h"

class Tester:public Agent
{
    char marker;
    int flag;
    int counnt;
public:
    Tester(int id, std::string& codes,char Marker,int Flag):Agent(id,codes),counnt(0),flag(Flag),marker(Marker){}
    void action()
    {
        int sum=0;
        for(auto it:Agent::codes)
        {
            if(it==marker)
            {
                sum++;
            }
        }
        if(sum%2==flag)counnt++;
    }
    void report()
    {
        cout<<"Tester "<<get_agent_id()<<": "<<counnt<<" tests passed"<<endl;
    }
};