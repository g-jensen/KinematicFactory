#include "Limb.h"

Limb::Limb(sf::Vector2f root, float length, float rotation_rad)
{
	this->root = root;
	this->length = length;
	this->rotation = rotation_rad;
	this->base = false;

	end = sf::Vector2f(length * cosf(-rotation) + root.x, length * sinf(-rotation) + root.y);

}

void Limb::follow(sf::Vector2f position)
{
	float dy = position.y - root.y;
	float dx = position.x - root.x;
	float len = sqrt((dx * dx) + (dy * dy));
	end = { 
		root.x + ( dx / len * length), 
		root.y + ( dy / len * length) 
	};
	
	//if (!base) {
		dy = (position.y - end.y);
		dx = (position.x - end.x);
		end += {dx, dy};
		root += {dx, dy};

		// readjust to stay connected

	//}

	dy = (end - root).y;
	dx = (end - root).x;
	rotation = atanf(dy / dx);
	if (rotation < 0) { rotation += M_PI; }
	if (dy < 0) { rotation += M_PI; }

}

void Limb::draw(sf::RenderWindow& window)
{
	sf::VertexArray lines(sf::LinesStrip, 2);
	lines[0].position = root;
	lines[1].position = end;

	window.draw(lines);
}
