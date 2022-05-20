#include <SFML/Graphics.hpp>

#include <math.h>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Limb.h"
#include "Arm.h"

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Kinematic Factory");
    ImGui::SFML::Init(window);

    sf::Clock dt;

    Arm arm({600,400}, 2,200);
    Limb limb({600,400},100,270);

    while (window.isOpen()) {

        sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(window);

        window.setFramerateLimit(60);
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ImGui::SFML::Update(window, dt.restart());

        //arm.follow(mouse_pos);
        limb.follow(mouse_pos);

        window.clear();

        //arm.draw(window);
        limb.draw(window);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}