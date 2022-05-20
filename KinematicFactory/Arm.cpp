#include "Arm.h"

Arm::Arm(sf::Vector2f origin, size_t n, float reach)
{
	this->origin = origin;
	this->limb_count = n;
	this->reach = reach;
	limbs.push_back(Limb(origin,reach/n,3*M_PI/4));
	limbs[0].base = true;
	for (int i = 1; i < n; i++) {
		limbs.push_back(Limb(limbs[i-1].root,reach/n,3*M_PI/4));
	}
}

void Arm::draw(sf::RenderWindow& window)
{
	for (auto item : limbs) {
		item.draw(window);
	}
}

void Arm::follow(sf::Vector2f position)
{
	sf::Vector2f delta = position - limbs[0].root;
	//if (sqrt((delta.x * delta.x) + (delta.y * delta.y)) <= reach) {
		limbs[limbs.size() - 1].follow(position);
		for (int i = limbs.size() - 2; i >= 0; i--) {
			limbs[i].follow(limbs[i + 1].root);
		}
	//}
}
