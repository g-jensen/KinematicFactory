#include "Arm.h"

// Arm::Arm(sf::Vector2<double> origin, size_t n, double reach)
Arm::Arm(sf::Vector2<double> origin, double reach)
{
	this->origin = origin;
	// this->limb_count = n;
	this->limb_count = 2;
	this->reach = reach;
	this->per = reach / limb_count;
	limbs.push_back(Limb(origin, per,M_PI/2));
	// for (size_t i = 1; i < n; i++) {
	for (size_t i = 1; i < 2; i++) {
		limbs.push_back(Limb(limbs[i-1].end, per,M_PI/2));
	}
}

void Arm::draw(sf::RenderWindow& window)
{
	for (auto item : limbs) {
		item.draw(window);
	}
}

void Arm::follow(sf::Vector2<double> position)
{
	double len = _Math::length(limbs[0].root, position);
	if (len >= reach) {
		reset();
		rotate(0, _Math::angle(limbs[0].root, position) - (M_PI/2));
		return;
	}

	sf::Vector2<double> delta = position - limbs[0].root;
	std::pair<sf::Vector2<double>, sf::Vector2<double>> solutions = _Math::circle_intersection(delta.x, delta.y, per);

	// niche cases
	if (delta.y == 0 && delta.x > 0) {
		limbs[0].end = limbs[0].root + solutions.first;
		limbs[1].root = limbs[0].root + solutions.first;
		limbs[1].end = position;
		return;
	}
	if (delta.y == 0 && delta.x < 0) {
		limbs[0].end = limbs[0].root + solutions.second;
		limbs[1].root = limbs[0].root + solutions.second;
		limbs[1].end = position;
		return;
	}

	// normal cases
	if (delta.y > 0) {
		limbs[0].end = limbs[0].root + solutions.second;
		limbs[1].root = limbs[0].root + solutions.second;
	}
	else {
		limbs[0].end = limbs[0].root + solutions.first;
		limbs[1].root = limbs[0].root + solutions.first;
	}
	
	limbs[1].end = position;
}

void Arm::rotate(size_t index, double angle_rad)
{
	if (index >= limbs.size()) { return; }
	limbs[index].rotate(angle_rad);
	for (size_t i = index+1; i < limbs.size(); i++) {
		limbs[i].rotate(angle_rad);
		sf::Vector2<double> delta = limbs[i - 1].end - limbs[i].root;
		limbs[i].end += delta;
		limbs[i].root += delta;
	}
}

void Arm::reset()
{
	limbs.clear();
	double per = reach / limb_count;
	limbs.push_back(Limb(origin, per, M_PI / 2));
	for (size_t i = 1; i < limb_count; i++) {
		limbs.push_back(Limb(limbs[i - 1].end, per, M_PI / 2));
	}
}

sf::Vector2<double> Arm::get_end()
{
	return limbs[limbs.size() - 1].end;
}
