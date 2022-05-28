#include "ArmItem.h"

void ArmItem::activate()
{
	// hard-code, fix later...
	// idea: make zone (sf::FloatRect) of possible points to activate
	if (Game::mouse_pos_window.y < 735 ) { // 735 is where the inventory grid is
		Arm::Arms.push_back(new Arm((sf::Vector2<double>)Game::mouse_pos_world, 200));
	}
}
