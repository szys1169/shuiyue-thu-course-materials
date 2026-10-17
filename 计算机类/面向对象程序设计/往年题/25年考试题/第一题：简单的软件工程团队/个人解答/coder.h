#include <iostream>
#include <string>
#include <vector>
#include "agent.h"
using namespace std;

class Coder:public Agent
{
    int counnt=0;
public:
    Coder(int id, std::string& codes):Agent(id,codes),counnt(0){}
    void action()
    {
        string code;
        cin>>code;
        Agent::codes+=code;
        counnt+=code.size();
    }
    void report()
    {
        cout<<"Coder "<<get_agent_id()<<": "<<counnt<<" characters coded"<<endl;
    }
};