#include "Item.h"

Item::Item()
{
	this->name = std::string();
	this->selected = false;
}

Item::Item(std::string name, bool selected)
{
	this->name = name;
	this->selected = selected;
}
