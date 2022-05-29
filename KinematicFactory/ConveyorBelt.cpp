#include "ConveyorBelt.h"

std::vector<ConveyorBelt*> ConveyorBelt::Belts;
std::array<sf::Texture*, 16> ConveyorBelt::Textures;

ConveyorBelt::ConveyorBelt(sf::Vector2f position)
{
	this->position = position;
	this->sprite.setPosition(position);
	this->sprite.setTexture(*ConveyorBelt::Textures[0]);
	selected = false;
	hitbox.left = position.x;
	hitbox.top = position.y;
	hitbox.width = Game::tile_size;
	hitbox.height = Game::tile_size;
}

void ConveyorBelt::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void ConveyorBelt::rotate90()
{
	sprite.rotate(90);
	if (sprite.getRotation() == 90) {
		position.x += Game::tile_size;
		sprite.setPosition(position);
	}
	else if (sprite.getRotation() == 180) {
		position.y += Game::tile_size;
		sprite.setPosition(position);
	}
	else if (sprite.getRotation() == 270) {
		position.x -= Game::tile_size;
		sprite.setPosition(position);
	}
	else {
		position.y -= Game::tile_size;
		sprite.setPosition(position);
	}
}
