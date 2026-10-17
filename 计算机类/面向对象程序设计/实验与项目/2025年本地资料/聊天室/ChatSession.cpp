#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "ChatUser.h"
#include"ChatSession.h"
using namespace std;
void ChatSession::addUser(ChatUser *user)
{
    string addname=user->getName();
    users.push_back(user);
    cout<<"Add user:"<<addname<<endl;
}void ChatSession::removeUser(ChatUser *user)
{
    auto it=find(users.begin(),users.end(),user);
    if(it==users.end())
    {
        cout<<user->getName()<<" not in chat"<<endl;
    }
    else
    {
        users.erase(it);
        cout<<"Remove user:"<<user->getName()<<endl;
    }
}
ChatUser* ChatSession::getUserByName(std::string name)
{
    for(auto user:users)
    {
        if(user->getName()==name)
        {
            return user;
        }
    }
    cout<<name<<" not in chat "<<endl;
    return nullptr;
}