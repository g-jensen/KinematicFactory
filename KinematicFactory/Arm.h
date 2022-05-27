#pragma once

#include "Limb.h"
#include "_Math.h"

class Arm
{
public:
	Arm(sf::Vector2<double> origin, double reach);
	void draw(sf::RenderWindow& window);
	void follow(sf::Vector2<double> position);
	void rotate(size_t index, double angle_rad);
	void reset();
	sf::Vector2<double> get_end();
	std::vector<Limb> limbs;
	sf::FloatRect hitbox;
private:
	double reach;
	double per;
	size_t limb_count;
	sf::Vector2<double> origin;
};

