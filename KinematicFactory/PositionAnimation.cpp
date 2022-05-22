#include "PositionAnimation.h"

PositionAnimation::PositionAnimation(sf::Transformable* object, AnimationType at, sf::Vector2f end_pos, size_t iterations)
{
	animationType = at;
	this->object = object;
	iteration = 0;
	this->iterations = iterations;
	this->end_pos = end_pos;

	// linear
	ratio = {
		(end_pos.x - object->getPosition().x) / iterations,
		(end_pos.y - object->getPosition().y) / iterations
	};

	// exponential
	if (animationType == AnimationType::EXPONENTIAL) {
		ratio = {
			(float)pow(end_pos.x,1.0f / iterations),
			(float)pow(end_pos.y,1.0f / iterations)
		};
	}
}

PositionAnimation::PositionAnimation()
{
}

bool PositionAnimation::iterate()
{
	if (!isFinished()) {
		if (animationType == AnimationType::LINEAR) {
			object->setPosition(object->getPosition().x + ratio.x, object->getPosition().y + ratio.y);
			iteration++;
			return false;
		}
		if (animationType == AnimationType::EXPONENTIAL) {
			object->setPosition(object->getPosition().x * ratio.x, object->getPosition().y * ratio.y);
			iteration++;
			return false;
		}
	}
	//object->setPosition(end_pos);
	return true;
}

bool PositionAnimation::isFinished()
{
	return !(iteration < iterations);
}
