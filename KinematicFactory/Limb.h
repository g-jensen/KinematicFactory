#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Mouse.hpp>
#include "_Math.h"

class Limb
{
public:
	sf::Vector2<double> root;
	sf::Vector2<double> end;
	double length;
	double rotation;
	Limb(sf::Vector2<double> root, double length, double rotation);
	void follow(sf::Vector2<double> position); // "point" at that position
	void draw(sf::RenderWindow& window);
	void rotate(double angle_rad);
	void setRotation(double angle_rad);
private:
};

