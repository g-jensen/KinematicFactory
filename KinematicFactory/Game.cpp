#include "Game.h"

sf::RenderWindow* Game::window;
sf::Vector2f Game::mouse_pos;

Game::Game()
{
    Game::window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Kinematic Factory", sf::Style::Default, sf::ContextSettings(0, 0, 8));
    Game::mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(*Game::window);
}

void Game::run()
{
    ImGui::SFML::Init(*Game::window);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;

    sf::Clock dt;

    Arm* selected_arm = nullptr;

    Item* selected_item = nullptr;

    std::array<Item*, 10> items;
    for (auto& i : items) {
        i = nullptr;
    }
    items[0] = new ArmItem("Arm", false);
    items[1] = new ArmItem("other\nitem", false);
    items[2] = new ArmItem("other\nitem", false);
    items[3] = new ArmItem("other\nitem", false);
    items[4] = new ArmItem("other\nitem", false);
    items[5] = new ArmItem("other\nitem", false);


    bool record_mode = false;


    while (Game::window->isOpen()) {
        Game::window->setFramerateLimit(60);

        Game::mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(*Game::window);

        sf::Event event;
        while (Game::window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                Game::window->close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    // deal with selecting arms
                    bool has_selected = false;
                    for (const auto& a : Arm::Arms) {
                        if (a == nullptr) { continue; }
                        if (!has_selected && a->hitbox.contains(Game::mouse_pos) && selected_arm == nullptr) {
                            a->selected = true;
                            selected_arm = a;
                            has_selected = true;
                        }
                    }

                    if (selected_arm != nullptr && record_mode) {
                        selected_arm->add_recording_point(Game::mouse_pos);
                    }

                    if (selected_item != nullptr && !has_selected && selected_arm == nullptr) {
                        selected_item->activate();
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
        ImGui::SFML::Update(*Game::window, dt.restart());

        // UI
        {
            ImGuiHelper::DarkStyle();

            // manage arm select UI
            for (size_t i = 0; i < Arm::Arms.size(); i++) {
                Arm* a = Arm::Arms[i];
                if (a == nullptr) { continue; }
                if (a->selected) {
                    ImGui::SetNextWindowPos({ a->hitbox.left + (float)a->reach + 20,a->hitbox.top });
                    ImGui::SetNextWindowSize({ 155,120 });
                    ImGui::SetNextWindowBgAlpha(1);
                    ImGui::Begin("edit arm", NULL, window_flags);
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
                            if (ImGui::Button("delete arm")) {
                                Arm* pointer = Arm::Arms[i];
                                Arm::Arms.erase(Arm::Arms.begin() + i);
                                delete pointer;
                                selected_arm = nullptr;
                                // NOTE: this is technically fine beccause "i" is not used after this but its not a good idea
                                i--;

                                break;
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
                    a->follow((sf::Vector2<double>)Game::mouse_pos);
                }
            }

            // item grid
            ImGui::SetNextWindowPos({ 0,800 - 65 });
            ImGui::SetNextWindowSize({ 1200,65 });
            ImGui::SetNextWindowBgAlpha(1);
            ImGui::Begin("Items", NULL, window_flags | ImGuiWindowFlags_NoTitleBar);
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            draw_list->ChannelsSplit(2);
            draw_list->ChannelsSetCurrent(1);
            for (size_t i = 0; i < items.size(); i++) {
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
                if (items[i] != nullptr) {
                    if (ImGui::Selectable(items[i]->name.c_str(), items[i]->selected, 0, ImVec2(50, 50)))
                    {
                        bool temp = items[i]->selected;
                        for (auto& item : items) { if (item != nullptr) { item->selected = false; } }
                        items[i]->selected = temp;
                        items[i]->selected = !items[i]->selected;
                        if (items[i]->selected) {
                            selected_item = items[i];
                        }
                        else {
                            selected_item = nullptr;
                        }
                    }
                    draw_list->ChannelsSetCurrent(0);
                    ImGuiHelper::SelectableColor(ImColor(0.1f, 0.1f, 0.1f, 1.f));
                }
                draw_list->ChannelsSetCurrent(0);
                ImGui::PopID();
            }
            draw_list->ChannelsSetCurrent(0);
            draw_list->ChannelsMerge();
            ImGui::End();
        }

        // update recording
        if (selected_arm != nullptr && selected_arm->playing_recording) {
            selected_arm->update_recording();
        }

        Game::window->clear();

        for (const auto& a : Arm::Arms) {
            if (a == nullptr) { continue; }
            a->draw(*Game::window);
        }


        ImGui::SFML::Render(*Game::window);
        Game::window->display();
    }

    for (auto& item : items) {
        delete item;
    }
    
    for (auto& arm : Arm::Arms) {
        delete arm;
    }
    delete Game::window;

    ImGui::SFML::Shutdown();
}
