#include "Engine.h"

namespace thirtythree{

Engine::Engine(sf::VideoMode mode, const sf::String name, sf::Vector2i map_size)
    : logic_ (this) {
    window_.create(mode, name);
    window_.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(60);
    Window = &window_;
    map_.create(map_size.x, map_size.y);
    view_.reset(sf::FloatRect(0, 0, mode.width, mode.height));
    LOG_INFO("Engine created: Video mode = " << mode.width << "x" << mode.height <<
             ", Map size = " << map_size.x << "x" << map_size.y);
}

void Engine::AddObject(GameObject *object) {
    objects_.emplace_back(object);
}

void Engine::StartGame() {
    AddObject(new GameObject ({50, 50}, 10, sf::Color::Red, {500, 10}));
    AddObject(new GameObject ({150, 150}, 15, sf::Color::Green, {-400, 0}));
    AddObject(new Player ({400, 234}, 25, 100, sf::Color::Blue));
    AddObject(new Food ({500, 500}));
    LOG_INFO("Game initialized");
    GameLoop();
}

void Engine::GameLoop() {
    LOG_INFO("Game loop started");
    while (window_.isOpen()) {
        float time = clock_.restart().asSeconds();
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window_.close();
            if (event.type == sf::Event::Resized) {
                view_.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
            }
        }
        logic_.DoLogic();
        map_.clear(sf::Color::White);
        for (const auto& obj : objects_) {
            if (obj->GetType() == "PLAYER") {
                view_.setCenter(obj->GetPos());
                obj->Control();
            }
            if (!(obj->IsDead())) {
                obj->Logic(map_.getSize());
                obj->Move(time);
                obj->Draw(map_);
            }
        }

        auto obj = objects_.begin();
        while (obj != objects_.end()) {
            if ((*obj)->IsDead()) {
                obj = objects_.erase(obj);
            } else {
                obj++;
            }
        }

        map_.display();
        window_.clear();
        sf::Sprite sprite(map_.getTexture());

        window_.draw(sprite);
        window_.setView(view_);

        int fps = 1.f / time;
        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text text(std::to_string(fps), font);
        text.setPosition(view_.getCenter() - (sf::Vector2f)window_.getSize() / 2.0f);
        text.setColor(sf::Color::Red);
        window_.draw(text);

        window_.display();
    }
}
}
