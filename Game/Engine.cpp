/*!
    @file Engine.cpp
    @brief Класс игрового движка
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#include "Engine.h"

namespace thirtythree{

Engine::Engine(sf::VideoMode mode, const sf::String name, sf::Vector2i map_size)
    : logic_ (this, &rand_) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 2;
    window_.create(mode, name, sf::Style::Default, settings);
    window_.setVerticalSyncEnabled(true);
    default_view_ = window_.getDefaultView();
    map_.create(map_size.x, map_size.y);
    map_.setSmooth(true);
    view_.reset(sf::FloatRect(0, 0, mode.width, mode.height));
    if (!font_.loadFromFile("Fonts/default.ttf")) {
        LOG_ERROR("Failed to load font");
        throw std::runtime_error("Failed to load font");
    }
    LOG_INFO("Engine created: Video mode = " << mode.width << "x" << mode.height <<
             ", Map size = " << map_size.x << "x" << map_size.y);
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
    while (window_.isOpen()) {
        time_ = clock_.restart().asSeconds();

        HandleEvents();
        logic_.DoLogic();
        map_.clear(sf::Color::White);

        for (auto obj1 = std::begin(objects_); obj1 != std::end(objects_); obj1++) {
            auto nearest_obj = obj1 + 1;
            float distance;
            if ((*obj1)->IsInteractable() && nearest_obj != std::end(objects_)) {
                distance = length((*obj1)->GetPos() - (*nearest_obj)->GetPos());
            }
            for (auto obj2 = obj1 + 1; obj2 != std::end(objects_); obj2++) {
                if (!(*obj1)->IsDead() && !(*obj2)->IsDead()) {
                    if (Collision(**obj1, **obj2)) {
                        logic_.CollideBoth(**obj1, **obj2);
                    }
                    if ((*obj1)->IsInteractable() && (*obj2)->IsInteractable()) {
                        float new_distance = length((*obj1)->GetPos() - (*obj2)->GetPos());
                        if (new_distance < distance) {
                            distance = new_distance;
                            nearest_obj = obj2;
                        }
                    }
                }
            }
            if ((*obj1)->IsInteractable() && nearest_obj != std::end(objects_)) {
                logic_.InteractBoth(**obj1, **nearest_obj);
            }
        }

        for (auto& obj : objects_) {
            if (!(obj->IsDead())) {
                HandleObject(*obj);
                HandleBorderCollisions(*obj);
            }
        }

        HandleDeadObjects();
        map_.display();

        window_.clear(sf::Color(222, 222, 222));
        window_.setView(view_);
        window_.draw(sf::Sprite(map_.getTexture()));
        DrawUI();
        window_.display();

    }
}

void Engine::RestartGame() {
    game_over_ = false;
    //objects_.clear();
    StartGame();
}

void Engine::HandleEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                window_.close();
                break;
            }
            case sf::Event::Resized: {
                view_.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
                default_view_.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
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
                view_.zoom(1 - (event.mouseWheel.delta * 0.05));
                break;
            }
            default: {}
        }
    }
}

void Engine::HandleObject(GameObject &obj) {
    if (obj.GetType() == "PLAYER") {
        view_.setCenter(obj.GetPos());
        obj.Control();
    }
    obj.Logic();
    obj.Move(time_);
    obj.Draw(map_);
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

bool Engine::Collision(GameObject &obj1, GameObject &obj2) {
    auto pos1 = obj1.GetPos();
    auto pos2 = obj2.GetPos();
    auto radius1 = obj1.GetRadius();
    auto radius2 = obj2.GetRadius();
    if (length(pos2 - pos1) <= std::max(radius1, radius2)) {
        return true;
    }
    return false;
}

void Engine::HandleDeadObjects() {

    auto obj = std::begin(objects_);
    while (obj != std::end(objects_)) {
        if ((*obj)->IsDead()) {
            if ((*obj)->GetType() == "PLAYER") game_over_ = true;
            obj = objects_.erase(obj);
        } else {
            obj++;
        }
    }

}

void Engine::DrawUI() {
    sf::View prev_view = window_.getView();
    window_.setView(default_view_);
    std::string score = "Score: " + std::to_string(logic_.GetScore());
    sf::Text text(score, font_, 25);
    text.setPosition(5, 0);
    text.setFillColor(sf::Color::Black);
    window_.draw(text);
    if (game_over_) {
        sf::Text text("Game over!", font_, 45);
        text.setPosition(GetWindowSize() / 2.0f);
        auto bounds = text.getGlobalBounds();
        text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        text.setFillColor(sf::Color::Black);

        sf::Text hint("Press R to restart", font_, 30);
        auto hint_pos = GetWindowSize() / 2.0f;
        hint_pos.y += 50;
        hint.setPosition(hint_pos);
        auto hint_bounds = hint.getGlobalBounds();
        hint.setOrigin(hint_bounds.width / 2.0f, hint_bounds.height / 2.0f);
        hint.setFillColor(sf::Color::Black);

        window_.draw(text);
        window_.draw(hint);
    }
    if (draw_debug_info_) {
        DrawDebugInfo();
    }
    window_.setView(prev_view);
}

void Engine::DrawDebugInfo() {
    int fps = 1.f / time_;

    std::string debug_text = "FPS: " + std::to_string(fps) +
                             "\nObj. count: " + std::to_string(GetObjectsCount());
    sf::Text text(debug_text, font_, 20);
    text.setOrigin(0, 45);
    text.setPosition(0, GetWindowSize().y);
    text.setFillColor(sf::Color::Black);

    window_.draw(text);
}

}
