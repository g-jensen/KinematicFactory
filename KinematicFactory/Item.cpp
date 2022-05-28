#include "Item.h"

Item::Item()
{
	this->name = "Empty";
	this->selected = false;
}

Item::Item(std::string name, bool selected)
{
	this->name = name;
	this->selected = selected;
}
