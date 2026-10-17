#pragma once
#include "card.h"
#include <vector>
#include<list>
#include<iostream>
#include<string>
using namespace std;

class Cards
{
	std::list<Card> cards; 
public:
	Cards()=default;
	Cards(std::string name, std::vector<int> vec)
	{
		for(auto num:vec)
		{
			cards.push_back(Card(name,num));
		}
	}
	void put(Card card)
	{
		cards.push_front(card);
	}
	void print()
	{
		if(cards.empty())
		{
			std::cout<<"empty"<<std::endl;
			return;
		}
		for(auto it:cards)
		{
			std::cout<<it<<" ";
		}
		std::cout<<std::endl;
	}
	int count()
	{
		return cards.size();
	}
	void merge(Cards &other)
	{
		if(other.cards.empty()){return;}
		if(!cards.empty())
		{
			auto last=prev(cards.end());
			last->number^=other.cards.front().number;
		}
		cards.splice(cards.end(),other.cards);
	}
};