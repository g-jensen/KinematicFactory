#include <SFML/Graphics.hpp>

#include <math.h>
#include <iostream>
#include <array>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Limb.h"
#include "Arm.h"
#include "Item.h"

// courtesy https://github.com/Nightfallen/EquiLand
void DarkStyle()
{
    // try : rgb(120, 119, 113) rgb(77, 79, 82) rgb(236, 236, 241) rgb(198, 125, 104) rgb(241, 241, 228)
    // rgb(77, 79, 82)
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.635, 0.678, 0.678, 1.f);//ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.30, 0.31, 0.33, 0.1);//ImVec4(0.8f, 0.10f, 0.10f, 0.80f); // red thing 
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.180, 0.190, 0.200,1.f);//ImVec4(0.470, 0.470, 0.44,1.f);//ImVec4(0.06f, 0.06f, 0.06f, 1.00f); // same
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.180, 0.190, 0.200, 1.f);//ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.180, 0.190, 0.200, 1.f);//ImVec4(0.470, 0.470, 0.44, 1.f);//ImVec4(0.06f, 0.06f, 0.06f, 1.00f); // same
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.80f);

    ImGuiStyle& style = ImGui::GetStyle();
    style.AntiAliasedLines = true;
    style.AntiAliasedFill = true;
    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(5.00f, 2.00f);
    style.CellPadding = ImVec2(6.00f, 6.00f);
    style.ItemSpacing = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 25;
    style.ScrollbarSize = 15;
    style.GrabMinSize = 10;
    style.WindowBorderSize = 5;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 1;
    style.TabBorderSize = 1;
    style.WindowRounding = 7;
    //style.ChildRounding = 4;
    //style.FrameRounding = 3;
    //style.PopupRounding = 4;
    //style.ScrollbarRounding = 9;
    style.GrabRounding = 3;
    style.LogSliderDeadzone = 4;
    //style.TabRounding = 4;
}

void SelectableColor(ImU32 color)
{
    ImVec2 p_min = ImGui::GetItemRectMin();
    ImVec2 p_max = ImGui::GetItemRectMax();
    ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, color);
}

int main(int argc, char** argv) {
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Kinematic Factory",sf::Style::Default, contextSettings);
    ImGui::SFML::Init(window);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;

    sf::Clock dt;

    Arm arm1({ 200,200 }, 100);
    Arm arm2({ 600,400 }, 200);
    Arm arm3({ 400,500 }, 200);

    std::vector<Arm*> arms;
    arms.push_back(&arm1);
    arms.push_back(&arm2);
    arms.push_back(&arm3);

    Arm* selected_arm = nullptr;

    std::array<Item,10> items;
    items[0] = Item("Arm", false);
    items[1] = Item("Cheese", false);
    items[2] = Item("jayx", false);
    items[3] = Item("fart-\nacid", false);

    bool record_mode = false;


    while (window.isOpen()) {
        window.setFramerateLimit(60);

        sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    // deal with selecting arms
                    bool has_selected = false;
                    for (const auto& a : arms) {
                        if (a == nullptr) { continue; }
                        if (!has_selected && a->hitbox.contains(mouse_pos) && selected_arm == nullptr) {
                            a->selected = true;
                            selected_arm = a;
                            has_selected = true;
                        }
                    }

                    if (selected_arm != nullptr && record_mode) {
                        selected_arm->add_recording_point(mouse_pos);
                    }

                }

            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (selected_arm == nullptr) { break; }
                    if (!selected_arm->playing_recording) {
                        selected_arm->selected = false;
                        selected_arm = nullptr;
                    }
                }
            }
        }
        ImGui::SFML::Update(window, dt.restart());

        DarkStyle();

        // manage arm select UI
        for (const auto& a : arms) {
            if (a == nullptr) { continue; }
            if (a->selected) {
                ImGui::SetNextWindowPos({ a->hitbox.left+(float)a->reach+20,a->hitbox.top });
                ImGui::SetNextWindowBgAlpha(1);
                ImGui::Begin("edit arm",NULL,window_flags);
                if (!record_mode) {
                    if (!a->playing_recording) {
                        if (ImGui::Button("start recording")) {
                            a->reset_recording();
                            record_mode = true;
                        }
                        if (ImGui::Button("test animation")) {
                            a->play_recording();
                        }
                        if (ImGui::Button("deselect arm (esc)")) {
                            a->selected = false;
                            selected_arm = nullptr;
                        }
                    }
                    else {
                        if (ImGui::Button("stop playing")) {
                            a->stop_recording();
                        }
                    }
                }
                else {
                    if (ImGui::Button("stop recording")) {
                        record_mode = false;
                        a->recording_iteration = 0;
                        a->recorded_points.erase(a->recorded_points.end() - 1);
                    }
                }
                ImGui::End();
                a->follow((sf::Vector2<double>)mouse_pos);
            }
        }

        // testing item grid
        ImGui::SetNextWindowPos({0,800-65});
        ImGui::SetNextWindowSize({1200,65});
        ImGui::SetNextWindowBgAlpha(1);

        ImGui::Begin("Items",NULL,window_flags | ImGuiWindowFlags_NoTitleBar);
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->ChannelsSplit(2);
        draw_list->ChannelsSetCurrent(1);
        for (int i = 0; i < items.size(); i++) {
            if (i != 0) {
                ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::Spacing();
                ImGui::SameLine();
                ImGui::Spacing();
                ImGui::SameLine();
            }
            draw_list->ChannelsSetCurrent(1);
            ImGui::SameLine();
            if (ImGui::Selectable(items[i].name.c_str(), items[i].selected, 0, ImVec2(50, 50)))
            {
                bool temp = items[i].selected;
                for (auto& item : items) { item.selected = false; }
                items[i].selected = temp;
                items[i].selected = !items[i].selected;
            }
            draw_list->ChannelsSetCurrent(0);
            SelectableColor(ImColor(0.1, 0.1, 0.1, 1.f));
            ImGui::PopID();
        }
        draw_list->ChannelsSetCurrent(0);
        draw_list->ChannelsMerge();
        ImGui::End();

        // update recording
        if (selected_arm != nullptr && selected_arm->playing_recording) {
            selected_arm->update_recording();
        }

        window.clear();

        for (const auto& a : arms) {
            if (a == nullptr) { continue; }
            a->draw(window);
        }


        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}