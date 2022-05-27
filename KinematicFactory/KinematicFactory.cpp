#include <SFML/Graphics.hpp>

#include <math.h>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Limb.h"
#include "Arm.h"

#include "ArmRecording.h"

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Kinematic Factory");
    ImGui::SFML::Init(window);

    sf::Clock dt;

    Arm arm1({ 200,200 }, 100);
    Arm arm2({ 600,400 }, 200);
    Arm arm3({ 400,500 }, 200);

    ArmRecording recording(&arm1);

    std::vector<Arm*> arms;
    arms.push_back(&arm1);
    arms.push_back(&arm2);
    arms.push_back(&arm3);

    bool record_mode = false;

    while (window.isOpen()) {

        sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(window);

        window.setFramerateLimit(60);
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    bool hasSelected = false;
                    for (const auto& a : arms) {
                        if (a == nullptr) { continue; }
                        a->selected = false;
                        if (!hasSelected && a->hitbox.contains(mouse_pos)) {
                            a->selected = true;
                            hasSelected = true;
                        }
                    }
                }

            }
        }
        ImGui::SFML::Update(window, dt.restart());

        for (const auto& a : arms) {
            if (a == nullptr) { continue; }
            if (a->selected) {
                a->follow((sf::Vector2<double>)mouse_pos);
            }
        }

        /*if (!recording.playing_recording) {
            arm.follow((sf::Vector2<double>)mouse_pos);
        }
        else {
            recording.update();
        }

        ImGui::Begin("controls");
        if (!record_mode) {
            if (!recording.playing_recording) {
                if (ImGui::Button("start recording")) {
                    recording.reset();
                    record_mode = true;
                }
                if (ImGui::Button("play recording")) {
                    recording.play();
                }
            }
            else {
                if (ImGui::Button("stop playing")) {
                    recording.stop();
                }
            }
        }
        else {
            if (ImGui::Button("stop recording")) {
                record_mode = false;
                recording.recording_iteration = 0;
                recording.recorded_points.erase(recording.recorded_points.end() - 1);
            }
        }
        ImGui::End();*/

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