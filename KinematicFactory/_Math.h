#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <SFML/System/Vector2.hpp>

class _Math
{
public:

	static int clamp(int value, size_t gap);

	// uses law of cosines to find theta given sides of a triangle
	static double loc_theta(double a, double b, double c);

	// return angle [0,2PI] between v1 and v2 relative to the x axis
	static double angle(sf::Vector2<double> v1, sf::Vector2<double> v2);

	// pythagorean theorem
	static double length(sf::Vector2<double> v1, sf::Vector2<double> v2);

	// quadratic solver
	static std::pair<double, double> quadratic_solver(double a, double b, double c);

	static bool approximately_equal(double value1, double value2, double err);

	// finds the x and y positions of the intersections between
	// x^2 + y^2 = r^2
	// and
	// (x-z)^2 + (y-w)^2 = r^2
	static std::pair<sf::Vector2<double>, sf::Vector2<double>> circle_intersection(double z, double w, double r);
};

