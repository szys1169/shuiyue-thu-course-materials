#pragma once
#include "card.h"
#include <vector>

class Cards {
	// ...
public:
	Cards();
	Cards(std::string, std::vector<int>);
	void put(Card);
	void print();
	int count();
	void merge(Cards &);
};