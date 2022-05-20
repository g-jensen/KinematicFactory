#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Mouse.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

class Limb
{
public:
	sf::Vector2f root;
	sf::Vector2f end;
	float length;
	float rotation;
	Limb(sf::Vector2f root, float length, float rotation);
	void follow(sf::Vector2f position); // "point" at that position
	void draw(sf::RenderWindow& window);
private:
};

