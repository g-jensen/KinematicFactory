#include "Limb.h"

Limb::Limb(sf::Vector2<double> root, double length, double rotation_rad)
{
	this->root = root;
	this->length = length;
	this->rotation = rotation_rad;

	end = sf::Vector2<double>(length * cos(rotation) + root.x, length * sin(rotation) + root.y);

}

void Limb::follow(sf::Vector2<double> position)
{
	// point towards point
	double dy = position.y - root.y;
	double dx = position.x - root.x;
	double len = sqrt((dx * dx) + (dy * dy));
	end = { 
		root.x + ( dx / len * length), 
		root.y + ( dy / len * length) 
	};
	
	// readjust
	dy = (position.y - end.y);
	dx = (position.x - end.x);
	end += {dx, dy};
	root += {dx, dy};

	dy = (end - root).y;
	dx = (end - root).x;
	rotation = atan(dy / dx);
	if (rotation < 0) { rotation += M_PI; }
	if (dy < 0) { rotation += M_PI; }

}

void Limb::draw(sf::RenderWindow& window)
{
	sf::VertexArray lines(sf::LinesStrip, 2);
	lines[0].position = (sf::Vector2f)root;
	lines[1].position = (sf::Vector2f)end;

	window.draw(lines);
}

void Limb::rotate(double angle_rad)
{
	double r = _Math::length(root, end);
	this->rotation += angle_rad;
	end = root + sf::Vector2<double>(r*cos(rotation), r*sin(rotation));
}

void Limb::setRotation(double angle_rad)
{
	rotation = angle_rad;
	end = sf::Vector2<double>(length * cos(rotation) + root.x, length * sin(rotation) + root.y);
}
