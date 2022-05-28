#pragma once

#include <string>

class Item
{
public:
	virtual void activate() = 0;
	Item();
	Item(std::string name, bool selected);
	std::string name;
	bool selected;
};

