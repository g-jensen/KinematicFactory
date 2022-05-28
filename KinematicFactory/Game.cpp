#include "Game.h"

sf::RenderWindow* Game::window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Kinematic Factory", sf::Style::Default, sf::ContextSettings(0, 0, 8));

sf::Vector2f Game::mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(*Game::window);