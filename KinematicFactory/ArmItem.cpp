#include "ArmItem.h"

void ArmItem::activate()
{
	// hard-code, fix later...
	// idea: make zone (sf::FloatRect) of possible points to activate
	if (Game::mouse_pos_window.y < 735 ) { // 735 is where the inventory grid is
		sf::Vector2<double> clamped = { (double)_Math::clamp((int)Game::mouse_pos_world.x,Game::tile_size),(double)_Math::clamp((int)Game::mouse_pos_world.y,Game::tile_size) };
		Arm::Arms.push_back(new Arm(clamped + sf::Vector2<double>{Game::tile_size/2.0, Game::tile_size/2.0}, 200));
	}
}
