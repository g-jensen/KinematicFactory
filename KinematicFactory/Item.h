#pragma once

#include <string>

class Item
{
public:
	Item();
	Item(std::string name, bool selected);
	std::string name;
	bool selected;
};

