#pragma once

#include "Game.h"

#include "Item.h"
#include "Arm.h"

class ArmItem : public Item
{
public:
	// inherit constructors
	using Item::Item;
	void activate();
};

