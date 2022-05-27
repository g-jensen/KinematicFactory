#include <SFML/Graphics.hpp>

#include <math.h>
#include <iostream>
#include <array>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Limb.h"
#include "Arm.h"

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Kinematic Factory");
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

    Arm* selectedArm = nullptr;

    bool record_mode = false;

    //char itemSlots[4] = { 0,0,0,0 };
    std::array<char,10> itemSlots;
    memset(&itemSlots[0], 0, sizeof(char) * itemSlots.size());

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
                    bool hasSelected = false;
                    for (const auto& a : arms) {
                        if (a == nullptr) { continue; }
                        //a->selected = false;
                        if (!hasSelected && a->hitbox.contains(mouse_pos) && selectedArm == nullptr) {
                            a->selected = true;
                            selectedArm = a;
                            hasSelected = true;
                        }
                    }

                    if (selectedArm != nullptr && record_mode) {
                        selectedArm->add_recording_point(mouse_pos);
                    }

                }

            }
        }
        ImGui::SFML::Update(window, dt.restart());

        // manage arm select UI
        for (const auto& a : arms) {
            if (a == nullptr) { continue; }
            if (a->selected) {
                ImGui::SetNextWindowPos({ a->hitbox.left+(float)a->reach+20,a->hitbox.top });
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
                        if (ImGui::Button("deselect arm")) {
                            a->selected = false;
                            selectedArm = nullptr;
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

        // testing grid
        ImGui::SetNextWindowPos({0,800-100});
        ImGui::SetNextWindowSize({1200,100});
        ImGui::SetNextWindowBgAlpha(1);
        ImGui::Begin("Items",NULL,window_flags);
        for (int i = 0; i < itemSlots.size(); i++) {
            ImGui::SameLine();
            ImGui::PushID(i * itemSlots.size());
            if (ImGui::Selectable("Item", itemSlots[i] != 0, 0, ImVec2(50, 50)))
            {
                memset(&itemSlots[0], 0, sizeof(char) * itemSlots.size());
                itemSlots[i] = 1;
            }
            ImGui::PopID();
        }
        ImGui::End();

        // update recording
        if (selectedArm != nullptr && selectedArm->playing_recording) {
            selectedArm->update_recording();
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