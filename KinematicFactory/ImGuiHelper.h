#pragma once

#include "imgui/imgui.h"

#include "Item.h"
#include <array>

class ImGuiHelper
{
public:
	static void DarkStyle();
	static void SelectableColor(ImU32 color);
	static void DrawItemGrid(std::array<Item*, 10>& items, Item*& selected_item);
};

