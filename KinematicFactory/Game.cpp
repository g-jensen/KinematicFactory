#include "Game.h"

sf::RenderWindow* Game::window;
sf::Vector2f Game::mouse_pos_window;
sf::Vector2f Game::mouse_pos_world;
size_t Game::tile_size;
//sf::Vector2f Game::mouse_pos_global;
Camera* Game::camera;

Game::Game()
{
    window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Kinematic Factory", sf::Style::Default, sf::ContextSettings(0, 0, 8));
    mouse_pos_window = (sf::Vector2f)sf::Mouse::getPosition(*window);
    camera = new Camera(*window);
    tile_size = 32;

    ConveyorBelt::Textures[0] = new sf::Texture(); ConveyorBelt::Textures[0]->loadFromFile("resources/conveyor/default/conveyor_default_1.png");
    ConveyorBelt::Textures[1] = new sf::Texture(); ConveyorBelt::Textures[1]->loadFromFile("resources/conveyor/default/conveyor_default_2.png");
    ConveyorBelt::Textures[2] = new sf::Texture(); ConveyorBelt::Textures[2]->loadFromFile("resources/conveyor/default/conveyor_default_3.png");
    ConveyorBelt::Textures[3] = new sf::Texture(); ConveyorBelt::Textures[3]->loadFromFile("resources/conveyor/default/conveyor_default_4.png");
    ConveyorBelt::Textures[4] = new sf::Texture(); ConveyorBelt::Textures[4]->loadFromFile("resources/conveyor/default/conveyor_default_5.png");
    ConveyorBelt::Textures[5] = new sf::Texture(); ConveyorBelt::Textures[5]->loadFromFile("resources/conveyor/default/conveyor_default_6.png");
    ConveyorBelt::Textures[6] = new sf::Texture(); ConveyorBelt::Textures[6]->loadFromFile("resources/conveyor/default/conveyor_default_7.png"); 
    ConveyorBelt::Textures[7] = new sf::Texture(); ConveyorBelt::Textures[7]->loadFromFile("resources/conveyor/default/conveyor_default_8.png");
    ConveyorBelt::Textures[8] = new sf::Texture(); ConveyorBelt::Textures[8]->loadFromFile("resources/conveyor/left/conveyor_left_1.png");
    ConveyorBelt::Textures[9] = new sf::Texture(); ConveyorBelt::Textures[9]->loadFromFile("resources/conveyor/left/conveyor_left_2.png");
    ConveyorBelt::Textures[10] = new sf::Texture(); ConveyorBelt::Textures[10]->loadFromFile("resources/conveyor/left/conveyor_left_3.png");
    ConveyorBelt::Textures[11] = new sf::Texture(); ConveyorBelt::Textures[11]->loadFromFile("resources/conveyor/left/conveyor_left_4.png");
    ConveyorBelt::Textures[12] = new sf::Texture(); ConveyorBelt::Textures[12]->loadFromFile("resources/conveyor/left/conveyor_left_5.png");
    ConveyorBelt::Textures[13] = new sf::Texture(); ConveyorBelt::Textures[13]->loadFromFile("resources/conveyor/left/conveyor_left_6.png");
    ConveyorBelt::Textures[14] = new sf::Texture(); ConveyorBelt::Textures[14]->loadFromFile("resources/conveyor/left/conveyor_left_7.png");
    ConveyorBelt::Textures[15] = new sf::Texture(); ConveyorBelt::Textures[15]->loadFromFile("resources/conveyor/left/conveyor_left_8.png");

}

void Game::run()
{
    ImGui::SFML::Init(*window);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;

    sf::Clock dt;

    Arm* selected_arm = nullptr;

    Item* selected_item = nullptr;

    ConveyorBelt* selected_belt = nullptr;

    std::array<Item*, 10> items;
    for (auto& i : items) {
        i = nullptr;
    }
    items[0] = new ArmItem("Arm", false);
    items[1] = new ConveyorBeltItem("Conveyor", false);
    items[2] = new ArmItem("other\nitem", false);
    items[3] = new ArmItem("other\nitem", false);
    items[4] = new ArmItem("other\nitem", false);
    items[5] = new ArmItem("other\nitem", false);


    bool record_mode = false;

    bool moving = false;

    sf::Vector2f original_pos = {0,0};

    size_t tick = 0;
    size_t animation_tick = 0;

    sf::RectangleShape selected_tile({ (float)tile_size,(float)tile_size });
    selected_tile.setFillColor({100,255,100,255});

    while (window->isOpen()) {
        //if (!window->hasFocus()) { continue; }
        window->setFramerateLimit(60);
        window->setView(camera->view);
        tick++;

        if (tick % 8 == 0) {
            animation_tick++;
            for (auto& a : ConveyorBelt::Belts) {
                a->sprite.setTexture(*ConveyorBelt::Textures[animation_tick % 8]);
            }
        }
        

        //mouse_pos_global = (sf::Vector2f)sf::Mouse::getPosition();
        mouse_pos_window = (sf::Vector2f)sf::Mouse::getPosition(*window);
        mouse_pos_world = (sf::Vector2f)window->mapPixelToCoords((sf::Vector2i)mouse_pos_window);

        selected_tile.setPosition(_Math::clamp(mouse_pos_world.x, tile_size), _Math::clamp(mouse_pos_world.y, tile_size));

        sf::Event event;
        while (window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta >= 1) {
                    camera->zoom(0.8);
                }
                else if (event.mouseWheel.delta <= -1) {
                    camera->zoom(1.25);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    moving = true;
                    original_pos = mouse_pos_window;

                    // deal with selecting arms
                    bool has_selected = false;
                    for (const auto& a : Arm::Arms) {
                        if (a == nullptr) { continue; }
                        if (!has_selected && a->hitbox.contains(mouse_pos_world) && selected_arm == nullptr) {
                            a->selected = true;
                            selected_arm = a;
                            has_selected = true;
                        }
                    }

                    // deal with selecting belts
                    for (const auto& a : ConveyorBelt::Belts) {
                        if (a == nullptr) { continue; }
                        if (!has_selected && a->hitbox.contains(mouse_pos_world) && selected_belt == nullptr) {
                            a->selected = true;
                            selected_belt = a;
                            has_selected = true;
                        }
                    }

                    if (selected_arm != nullptr && record_mode) {
                        selected_arm->add_recording_point(mouse_pos_world);
                    }

                                                                     /*           fix/generalize this part             */
                    if (selected_item != nullptr && !has_selected && selected_arm == nullptr && selected_belt == nullptr) {
                        selected_item->activate();
                    }

                }

            }
            if (event.type == sf::Event::MouseButtonReleased) {
                moving = false;
            }
            if (event.type == sf::Event::MouseMoved) {
                                /*           fix/generalize this part             */
                if (moving && selected_arm == nullptr && selected_belt == nullptr) {
                    camera->move(original_pos - mouse_pos_window);
                    original_pos = mouse_pos_window;
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
        ImGui::SFML::Update(*window, dt.restart());

        // UI
        {
            ImGuiHelper::DarkStyle();

            // manage arm select UI
            for (size_t i = 0; i < Arm::Arms.size(); i++) {
                Arm* a = Arm::Arms[i];
                if (a == nullptr) { continue; }
                if (a->selected) {
                    sf::Vector2f pos = {a->hitbox.left + (float)a->reach + 20,a->hitbox.top };
                    ImGui::SetNextWindowPos(window->mapCoordsToPixel(pos));
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
                    a->follow((sf::Vector2<double>)mouse_pos_world);
                }
            }

            // manage belt select UI
            for (size_t i = 0; i < ConveyorBelt::Belts.size(); i++) {
                ConveyorBelt* b = ConveyorBelt::Belts[i];
                if (b == nullptr) { continue; }
                if (b->selected) {
                    sf::Vector2f pos = { b->hitbox.left + Game::tile_size,b->hitbox.top };
                    ImGui::SetNextWindowPos(window->mapCoordsToPixel(pos));
                    ImGui::SetNextWindowSize({ 155,120 });
                    ImGui::SetNextWindowBgAlpha(1);
                    ImGui::Begin("edit arm", NULL, window_flags);
                    if (ImGui::Button("rotate conveyor")) {
                        b->rotate90();
                    }
                    if (ImGui::Button("delete conveyor")) {}
                    if (ImGui::Button("deselect arm (esc)")) {
                        b->selected = false;
                        selected_belt = nullptr;
                    }
                    ImGui::End();
                }
            }

            // item grid
            ImGuiHelper::DrawItemGrid(items, selected_item);
            
        }

        // update recording
        if (selected_arm != nullptr && selected_arm->playing_recording) {
            selected_arm->update_recording();
        }

        window->clear(sf::Color(170, 170, 170,255));
        
        /*           fix/generalize this part                 */
        if (selected_arm == nullptr && selected_belt == nullptr) {
            window->draw(selected_tile);
        }

        for (const auto& a : Arm::Arms) {
            if (a == nullptr) { continue; }
            a->draw(*window);
        }

        for (auto& a : ConveyorBelt::Belts) {
            a->draw(*window);
        }

        ImGui::SFML::Render(*window);
        window->display();
    }

    for (auto& item : items) {
        delete item;
    }

    for (auto& arm : Arm::Arms) {
        delete arm;
    }

    delete window;
    delete camera;
   
    ImGui::SFML::Shutdown();
}
