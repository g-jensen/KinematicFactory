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

    Arm arm({600,400}, 400);

    ArmRecording recording(&arm);

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
                    if (record_mode) {
                        recording.add_point((sf::Vector2f)arm.get_end());
                    }
                }

            }
        }
        ImGui::SFML::Update(window, dt.restart());

        if (!recording.playing_recording) {
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
        ImGui::End();

        window.clear();

        arm.draw(window);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}