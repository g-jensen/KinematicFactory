#pragma once

#include "Game.h"

#include "Item.h"
#include "ConveyorBelt.h"

class ConveyorBeltItem : public Item
{
public:
	// inherit constructors
	using Item::Item;
	void activate();
};

