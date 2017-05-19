/*!
    @file Engine.cpp
    @brief Класс игрового движка
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#include "Engine.h"

namespace thirtythree{

Engine::Engine(sf::VideoMode mode, const sf::String name, sf::Vector2i map_size)
    : logic_ (this, &rand_),
      drawer_ (mode, name, map_size) {
    LOG_INFO("Engine created");
}

void Engine::AddObject(GameObject *object) {
    if (GetObjectsCount() < max_object_number_) {
        objects_.emplace_back(object);
    } else {
        if (object != nullptr) delete object;
        LOG_INFO("Objects limit exceeded!");
    }
}

void Engine::StartGame() {
    logic_.StartGame();
    LOG_INFO("Game initialized");
    GameLoop();
}

void Engine::GameLoop() {
    LOG_INFO("Game loop started");
    while (drawer_.WindowIsOpen()) {
        time_ = clock_.restart().asSeconds();

        HandleEvents();
        logic_.DoLogic();

        for (auto obj1 = std::begin(objects_); obj1 != std::end(objects_); obj1++) {
            auto nearest_to_obj1 = obj1;
            float nearest_distance = std::numeric_limits<float>::max();
            for (auto obj2 = obj1 + 1; obj2 != std::end(objects_); obj2++) {
                if (ObjectsAreAlive(obj1, obj2)) {
                    float distance = CalculateDistance(obj1, obj2);
                    if (Collision(obj1, obj2, distance)) {
                        GameLogic::Event event(GameLogic::EventType::COLLISION, **obj1, **obj2);
                        logic_.HandleEvent(event);

                    } else if (ObjectsAreInteractable(obj1, obj2)) {
                        if (distance < nearest_distance) {
                            nearest_distance = distance;
                            nearest_to_obj1 = obj2;
                        }
                    }

                }
            }
            if (ObjectIsInteractable(obj1)) {
                GameLogic::Event event(GameLogic::EventType::INTERACTION, **obj1, **nearest_to_obj1);
                logic_.HandleEvent(event);
            }
        }

        drawer_.ClearMap();
        for (auto& obj : objects_) {
            if (!(obj->IsDead())) {
                HandleObject(*obj);
                HandleBorderCollisions(*obj);
            }
        }

        HandleDeadObjects();
        drawer_.DisplayMap();

        drawer_.ClearWindow();
        drawer_.DrawMap();
        DrawUI();
        drawer_.DisplayWindow();

    }
}

void Engine::RestartGame() {
    game_over_ = false;
    //objects_.clear();
    StartGame();
}

void Engine::HandleEvents() {
    sf::Event event;
    while (drawer_.PollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                drawer_.CloseWindow();
                break;
            }
            case sf::Event::Resized: {
                drawer_.ResizeWindow(event.size.width, event.size.height);
                break;
            }
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Tab) {
                    draw_debug_info_ = !draw_debug_info_;
                } else if (event.key.code == sf::Keyboard::R && game_over_) {
                    RestartGame();
                }
                break;
            }
            case sf::Event::MouseWheelMoved: {
                drawer_.ZoomWindow(event.mouseWheel.delta);
                break;
            }
            default: {}
        }
    }
}

void Engine::HandleObject(GameObject &obj) {
    if (obj.GetType() == PLAYER) {
        drawer_.SetViewCenter(obj.GetPos());
        obj.Control();
    }
    obj.Logic();
    obj.Move(time_);
    drawer_.DrawObject(obj);
}

void Engine::HandleBorderCollisions(GameObject &obj) {

    auto pos = obj.GetPos();
    auto radius = obj.GetRadius();
    auto speed = obj.GetSpeed();
    auto map_size = GetMapSize();

    if (pos.x < radius) {
        speed.x = abs(speed.x);
        pos.x = radius;
    } else if (pos.x > map_size.x - radius) {
        speed.x = -abs(speed.x);
        pos.x = map_size.x - radius;
    }
    if (pos.y < radius) {
        speed.y = abs(speed.y);
        pos.y = radius;
    } else if (pos.y > map_size.y - radius) {
        speed.y = -abs(speed.y);
        pos.y = map_size.y - radius;
    }
    obj.SetPos(pos);
    obj.SetSpeed(speed);

//    if (pos.x < 0) {
//        pos.x += map_size.x;
//    } else if (pos.x > map_size.x) {
//        pos.x -= map_size.x;
//    }
//    if (pos.y < 0) {
//        pos.y += map_size.y;
//    } else if (pos.y > map_size.y) {
//        pos.y -= map_size.y;
//    }
//    obj.SetPos(pos);
}

void Engine::HandleDeadObjects() {

    auto obj = std::begin(objects_);
    while (obj != std::end(objects_)) {
        if ((*obj)->IsDead()) {
            if ((*obj)->GetType() == PLAYER) game_over_ = true;
            obj = objects_.erase(obj);
        } else {
            obj++;
        }
    }

}

void Engine::DrawUI() {
    drawer_.DrawText(Drawer::Text("Score: " + std::to_string(logic_.GetScore()), 25, {5, 0}));
    if (game_over_) {
        sf::Vector2i pos1 = (sf::Vector2i)GetWindowSize() / 2;
        sf::Vector2i pos2 = (sf::Vector2i)GetWindowSize() / 2 + sf::Vector2i(0, 50);
        drawer_.DrawText(Drawer::Text("Game over!", 45, pos1, true));
        drawer_.DrawText(Drawer::Text("Press R to restart", 30, pos2, true));
    }
    if (draw_debug_info_) {
        DrawDebugInfo();
    }

}

void Engine::DrawDebugInfo() {
    int fps = 1.f / time_;
    std::string debug_text = "FPS: " + std::to_string(fps) + "\nObj. count: " +
                             std::to_string(GetObjectsCount());
    sf::Vector2i pos = {0, GetWindowSize().y - 45};
    drawer_.DrawText(Drawer::Text(debug_text, 20, pos));
}

}
