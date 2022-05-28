#include "Arm.h"

std::vector<Arm*> Arm::Arms;

// Arm::Arm(sf::Vector2<double> origin, size_t n, double reach)
Arm::Arm(sf::Vector2<double> origin, double reach)
{
	this->origin = origin;
	// this->limb_count = n;
	this->limb_count = 2;
	this->reach = reach;
	this->per = reach / limb_count;
	this->hitbox.left = origin.x - reach/2;
	this->hitbox.top = origin.y - reach/2;
	this->hitbox.height = reach;
	this->hitbox.width = reach;
	this->selected = false;

	this->animation = PositionAnimation(&temp, AnimationType::LINEAR, { 0,0 }, 100);
	this->recorded_points = std::vector<sf::Vector2f>();
	this->playing_recording = false;
	this->recording_iteration = 0;
	this->temp = sf::Transformable();

	limbs.push_back(Limb(origin, per,M_PI/2));
	// for (size_t i = 1; i < n; i++) {
	for (size_t i = 1; i < 2; i++) {
		limbs.push_back(Limb(limbs[i-1].end, per,M_PI/2));
	}
}

void Arm::draw(sf::RenderWindow& window)
{
	if (selected) {
		// draw overlay
		sf::Vector2f size = sf::Vector2f((float)reach/25,(float)reach/25);
		sf::RectangleShape r1(size);
		r1.setFillColor(sf::Color(255, 50, 50));
		r1.setPosition({ hitbox.left,hitbox.top });
		window.draw(r1);
		r1.setPosition({ hitbox.left+hitbox.width,hitbox.top });
		window.draw(r1);
		r1.setPosition({ hitbox.left,hitbox.top+hitbox.height });
		window.draw(r1);
		r1.setPosition({ hitbox.left+hitbox.width,hitbox.top+hitbox.height });
		window.draw(r1);
	}
	for (auto item : limbs) {
		item.draw(window);
	}
}

void Arm::follow(sf::Vector2<double> position)
{
	double len = _Math::length(limbs[0].root, position);
	if (len >= reach) {
		reset();
		rotate(0, _Math::angle(limbs[0].root, position) - (M_PI/2));
		return;
	}

	sf::Vector2<double> delta = position - limbs[0].root;
	std::pair<sf::Vector2<double>, sf::Vector2<double>> solutions = _Math::circle_intersection(delta.x, delta.y, per);

	// niche cases
	if (delta.y == 0 && delta.x > 0) {
		limbs[0].end = limbs[0].root + solutions.first;
		limbs[1].root = limbs[0].root + solutions.first;
		limbs[1].end = position;
		return;
	}
	if (delta.y == 0 && delta.x < 0) {
		limbs[0].end = limbs[0].root + solutions.second;
		limbs[1].root = limbs[0].root + solutions.second;
		limbs[1].end = position;
		return;
	}

	// normal cases
	if (delta.y > 0) {
		limbs[0].end = limbs[0].root + solutions.second;
		limbs[1].root = limbs[0].root + solutions.second;
	}
	else {
		limbs[0].end = limbs[0].root + solutions.first;
		limbs[1].root = limbs[0].root + solutions.first;
	}
	
	limbs[1].end = position;
}

void Arm::rotate(size_t index, double angle_rad)
{
	if (index >= limbs.size()) { return; }
	limbs[index].rotate(angle_rad);
	for (size_t i = index+1; i < limbs.size(); i++) {
		limbs[i].rotate(angle_rad);
		sf::Vector2<double> delta = limbs[i - 1].end - limbs[i].root;
		limbs[i].end += delta;
		limbs[i].root += delta;
	}
}

void Arm::reset()
{
	limbs.clear();
	double per = reach / limb_count;
	limbs.push_back(Limb(origin, per, M_PI / 2));
	for (size_t i = 1; i < limb_count; i++) {
		limbs.push_back(Limb(limbs[i - 1].end, per, M_PI / 2));
	}
}

sf::Vector2<double> Arm::get_end()
{
	return limbs[limbs.size() - 1].end;
}

void Arm::add_recording_point(sf::Vector2f point)
{
	recorded_points.push_back(point);
}

void Arm::set_recording_points(std::vector<sf::Vector2f> points)
{
	this->recorded_points = points;
}

void Arm::update_recording()
{
	if (playing_recording) {
		animation.iterate();
		this->follow((sf::Vector2<double>)temp.getPosition());
		if (animation.isFinished()) {
			if (recording_iteration + 1 < recorded_points.size()) {
				recording_iteration++;
				double len = _Math::length((sf::Vector2<double>)recorded_points[recording_iteration - 1], (sf::Vector2<double>)recorded_points[recording_iteration]);
				animation = PositionAnimation(&temp, AnimationType::LINEAR, { recorded_points[recording_iteration] }, (int)(len / 4));
			}
			else {
				playing_recording = false;
				recording_iteration = 0;
			}
		}
	}
}

void Arm::stop_recording()
{
	playing_recording = false;
	recording_iteration = 0;
}

void Arm::reset_recording()
{
	recorded_points.clear();
	recording_iteration = 0;
}

void Arm::play_recording()
{
	if (recorded_points.size() > 0) {
		playing_recording = true;
		temp.setPosition((sf::Vector2f)this->get_end());
		double len = _Math::length(this->get_end(), (sf::Vector2<double>)recorded_points[recording_iteration]);
		animation = PositionAnimation(&temp, AnimationType::LINEAR, { recorded_points[recording_iteration] }, (int)(len / 4));
	}
}