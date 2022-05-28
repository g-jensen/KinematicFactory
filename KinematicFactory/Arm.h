#pragma once

#include "Limb.h"
#include "_Math.h"
#include "PositionAnimation.h"
#include "SFML/Graphics/RectangleShape.hpp"

class Arm
{
public:
	static std::vector<Arm*> Arms;
	Arm(sf::Vector2<double> origin, double reach);
	void draw(sf::RenderWindow& window);
	void follow(sf::Vector2<double> position);
	void rotate(size_t index, double angle_rad);
	void reset();

	void add_recording_point(sf::Vector2f point);
	void set_recording_points(std::vector<sf::Vector2f> points);
	void update_recording();
	void play_recording();
	void stop_recording();
	void reset_recording();

	bool playing_recording;
	size_t recording_iteration;
	std::vector<sf::Vector2f> recorded_points;

	sf::Vector2<double> get_end();
	std::vector<Limb> limbs;
	sf::FloatRect hitbox;
	bool selected;
	double reach;
private:
	double per;
	size_t limb_count;
	sf::Vector2<double> origin;

	sf::Transformable temp;
	PositionAnimation animation;
};

