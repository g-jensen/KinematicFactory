//#pragma once
//
//#include "Arm.h"
//#include "PositionAnimation.h"
//#include "SFML/Graphics/Transformable.hpp"
//
//class ArmRecording
//{
//public:
//	ArmRecording(Arm* arm);
//	void add_recording_point(sf::Vector2f point);
//	void set_recording_points(std::vector<sf::Vector2f> points);
//	void update_recording();
//	void play_recording();
//	void stop_recording();
//	void reset_recording();
//	bool playing_recording;
//	size_t recording_iteration;
//	std::vector<sf::Vector2f> recorded_points;
//private:
//	Arm* arm;
//	sf::Transformable temp;
//	PositionAnimation animation;
//};