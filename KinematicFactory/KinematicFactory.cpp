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

    Arm arm({600,400}, 400);

    std::vector<sf::CircleShape> circles;

    for (int i = 0; i < 5; i++) {
        sf::CircleShape c(10);
        c.setPosition(300, 400);
        circles.push_back(c);
    }

    sf::CircleShape* grabbed = nullptr;

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
                bool found = false;
                for (auto& item : circles) {
                    if (item.getGlobalBounds().contains((sf::Vector2f)arm.limbs[arm.limbs.size() - 1].end)) {
                        grabbed = &item;
                        found = true;
                        break;
                    }
                }
                if (!found) { grabbed = nullptr; }
            }
        }

        if (grabbed != nullptr) {
            grabbed->setPosition((sf::Vector2f)arm.limbs[arm.limbs.size() - 1].end);
        }

        ImGui::SFML::Update(window, dt.restart());

        arm.follow((sf::Vector2<double>)mouse_pos);

        window.clear();

        for (auto& item : circles) {
            window.draw(item);
        }

        arm.draw(window);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}