#pragma once

#include "Arm.h"
#include "PositionAnimation.h"
#include "SFML/Graphics/Transformable.hpp"

class ArmRecording
{
public:
	ArmRecording(Arm* arm);
	void add_point(sf::Vector2f point);
	void set_points(std::vector<sf::Vector2f> points);
	void update();
	void play();
	void stop();
	void reset();
	bool playing_recording;
	size_t recording_iteration;
	std::vector<sf::Vector2f> recorded_points;
private:
	Arm* arm;
	sf::Transformable temp;
	PositionAnimation animation;
};