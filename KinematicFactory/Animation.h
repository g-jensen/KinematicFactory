#pragma once

#include <SFML/Graphics/Transformable.hpp>

enum class AnimationType
{
	LINEAR,
	EXPONENTIAL,
	LERP_QUADRATIC,
	LERP_QUINTIC
};

class Animation
{
public:
	/// <summary>
	/// iterates once through the animation
	/// </summary>
	/// <returns>if the animation is complete</returns>
	virtual bool iterate() = 0;
	virtual bool isFinished() = 0;
protected:
	AnimationType animationType;
	sf::Transformable* object;
	size_t iteration;
	size_t iterations;
};

