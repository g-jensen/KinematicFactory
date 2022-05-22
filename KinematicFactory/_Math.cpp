#include "_Math.h"

double _Math::loc_theta(double a, double b, double c)
{
	// acosf range only from 0-pi
	return acos(((a * a) + (b * b) - (c * c)) / (2 * a * b));
}

double _Math::angle(sf::Vector2<double> v1, sf::Vector2<double> v2)
{
	double dy = v2.y - v1.y;
	double dx = v2.x - v1.x;

	if (dy == 0 && dx > 0) { return 0; }
	if (dy == 0 && dx < 0) { return M_PI; }

	double theta = atan(dy / dx);

	if (theta < 0) { theta += M_PI; }
	if (dy < 0) { theta += M_PI; }

	return theta;
}

double _Math::length(sf::Vector2<double> v1, sf::Vector2<double> v2)
{
	double dy = (double)v1.y - v2.y;
	double dx = (double)v1.x - v2.x;
	double t = (dy * dy) + (dx * dx);
	return sqrt(t);
}

std::pair<double,double> _Math::quadratic_solver(double a, double b, double c)
{
	std::pair<double, double> output;
	double discriminant = (b * b) - (4 * a * c);
	if (discriminant >= 0) {
		output.first = (-b + sqrt(discriminant)) / (2 * a);
		output.second = (-b - sqrt(discriminant)) / (2 * a);
	}
	else {
		std::cout << "ERROR: negative discriminant in quadratic" << std::endl;
	}
	return output;
}

bool _Math::approximately_equal(double value1, double value2, double err)
{
	double diff = value1 - value2;
	return (diff >= -err && diff <= err);
}

std::pair<sf::Vector2<double>,sf::Vector2<double>> _Math::circle_intersection(double z, double w, double r)
{
	// https://www.desmos.com/calculator/z9meab7p9t

	if (w == 0) {
		std::pair<sf::Vector2<double>, sf::Vector2<double>> solution;

		solution.first.x = z / 2.0;
		solution.second.x = z / 2.0;

		solution.first.y = sqrt((r * r) - (solution.first.x * solution.first.x));
		solution.second.y = -solution.first.y;

		return solution;
	}

	std::pair<sf::Vector2<double>, sf::Vector2<double>> solution;
	double a = ((w * w) + (z * z)) / (w*w);
	double b = (-(z * z * z) - (z * w * w)) / (w * w);
	double c = ((z*z*z*z) / (4*w*w)) + ((z*z)/2) + ((w*w)/4) - (r*r);
	
	std::pair<double, double> sols = quadratic_solver(a, b, c);

	solution.first.x = sols.first;
	solution.second.x = sols.second;

	// the rest of this is plugging in the solutions and seeing which of the 4 y values are correct

	// y^2 + x^2 = r^2 -> y = +-sqrt( r^2 - x^2 )
	// (x-z)^2 + (y-w)^2 = r^2 -> y = +-sqrt( r^2 - (x-z)^2 ) + w
	double positive_default_sol = sqrt( (r*r) - (sols.first*sols.first) );
	double negative_default_sol = -positive_default_sol;
	double positive_offset_sol = sqrt((r * r) - ((sols.first - z) * (sols.first - z))) + w;
	double negative_offset_sol = -sqrt((r * r) - ((sols.first - z) * (sols.first - z))) + w;

	if (approximately_equal(positive_default_sol,positive_offset_sol,0.2) || approximately_equal(positive_default_sol, negative_offset_sol, 0.2)) {
		solution.first.y = positive_default_sol;
	}
	else {
		solution.first.y = negative_default_sol;
	}

	positive_default_sol = sqrt((r * r) - (sols.second * sols.second));
	negative_default_sol = -positive_default_sol;
	positive_offset_sol = sqrt((r * r) - ((sols.second - z) * (sols.second - z))) + w;
	negative_offset_sol = -sqrt((r * r) - ((sols.second - z) * (sols.second - z))) + w;

	if (approximately_equal(positive_default_sol, positive_offset_sol, 0.2) || approximately_equal(positive_default_sol, negative_offset_sol, 0.2)) {
		solution.second.y = positive_default_sol;
	}
	else {
		solution.second.y = negative_default_sol;
	}

	return solution;
}
