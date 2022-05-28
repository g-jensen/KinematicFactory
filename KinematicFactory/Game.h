#pragma once

#include <SFML/Graphics.hpp>

#include <math.h>
#include <iostream>
#include <array>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Limb.h"
#include "Arm.h"
#include "ArmItem.h"
#include "ImGuiHelper.h"

class Game
{
public:
	Game();
	void run();
	static sf::RenderWindow* window;
	static sf::Vector2f mouse_pos;
};

