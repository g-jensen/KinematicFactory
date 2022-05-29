#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "_Math.h"
#include <vector>
#include <array>

#include "Game.h"

class ConveyorBelt
{
public:
	static std::vector<ConveyorBelt*> Belts;
	static std::array<sf::Texture*,16> Textures;
	ConveyorBelt(sf::Vector2f position);
	void draw(sf::RenderWindow& window);
	void rotate90();
	sf::Sprite sprite;
	bool selected;
	sf::FloatRect hitbox;
private:
	sf::Vector2f position;
};

