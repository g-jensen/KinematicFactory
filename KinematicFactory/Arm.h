#pragma once

#include "Limb.h"

class Arm
{
public:
	Arm(sf::Vector2f origin, size_t n, float reach);
	void draw(sf::RenderWindow& window);
	void follow(sf::Vector2f position);
	sf::Vector2f origin;
	size_t limb_count;
	float reach;
private:
	std::vector<Limb> limbs;
};

