#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include"ChatUser.h"
using namespace std;
void ChatUser::addFriend(ChatUser* user)
{
    auto it=find(friends.begin(),friends.end(),user);
    if(it==friends.end())
    {
        friends.push_back(user);
        cout<<name<<" -> add friend -> "<<user->getName()<<endl;
    }
    else
    {
        cout<<name<<" and "<<user->getName()<<" are already friends"<<endl;
    }
}
void ChatUser::removeFriend(ChatUser* user)
{
    auto it=find(friends.begin(),friends.end(),user);
    if(it==friends.end())
    {
        cout<<name<<" and "<<user->getName()<<" are not yet friends"<<endl;
    }
    else
    {
        friends.erase(it);
        cout<<name<<" -> remove friend -> "<<user->getName()<<endl;
    }
}
void ChatUser::sendMessage(ChatUser* user, std::string message)
{
    if (user == nullptr)return;
	std::cout << name << " -> send message -> " << user->getName() << " : " << message << std::endl;
    user->receiveMessage(this,message);
}
void ChatUser::receiveMessage(ChatUser* user, std::string message)
{
  /*  if (user == nullptr)return;
    auto it=find(messageQueue.begin(),messageQueue.end(),user);
    if(it==messageQueue.end())
    {
        messageQueue.emplace_back(user,message);
    }
    else 
    {
        for (auto& pair : messageQueue) 
        {
            if (pair.first == user) {
                pair.second.push_back(message);
                return;
            }
        }
    }
    cout<<name<<" -> send message -> "<<user->getName()<<" : "<<message<<endl;
    cout<<name<<" -> receive message -> "<<user->getName()<<" : "<<message<<endl;*/
    if (user == nullptr)return;
	for (int i = 0; i < messageQueue.size(); i++) {
		if (messageQueue[i].first == user) {
			messageQueue[i].second.push_back(message);
			std::cout << name << " -> receive message -> " << user->getName() << " : " << message << std::endl;
			return;
		}
	}
	std::vector<std::string>m;
	m.push_back(message);
	messageQueue.push_back(make_pair(user, m));
    std::cout << name << " -> receive message -> " << user->getName() << " : " << message << std::endl;
}
void ChatUser::showMessage()
{
    cout<<"Chat "<<name<<endl;
    for(auto names:messageQueue)
    {
        cout<<">>From "<<names.first->getName()<<":"<<endl;
        for(auto messages:names.second)
        {
            cout<< ">> " << messages << endl;
        }
    }
}   
void ChatUser::showFriends()
{
    cout<<name<<"'s friend:";
    for(auto fre:friends)
    {
        cout<<" "<<fre->getName();
    }
    cout<<endl;
}
    