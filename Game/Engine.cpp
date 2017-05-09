#include "Engine.h"

namespace thirtythree{

Engine::Engine(sf::VideoMode mode, const sf::String name, sf::Vector2i map_size)
    : logic_ (this, &rand_) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    window_.create(mode, name, sf::Style::Default, settings);
    window_.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(60);
    Window = &window_;
    default_view_ = window_.getDefaultView();
    map_.create(map_size.x, map_size.y);
    map_.setSmooth(true);
    view_.reset(sf::FloatRect(0, 0, mode.width, mode.height));
    if (!font_.loadFromFile("HelveticaRegular.ttf")) {
        LOG_ERROR("Failed to load font");
    }
    LOG_INFO("Engine created: Video mode = " << mode.width << "x" << mode.height <<
             ", Map size = " << map_size.x << "x" << map_size.y);
}

void Engine::AddObject(GameObject *object) {
    if (GetObjectsCount() < max_object_number_) {
        objects_.emplace_back(object);
    } else {
        LOG_INFO("Objects limit exceeded!");
    }
}

void Engine::StartGame() {
    int num_obj = rand_.UniformInt(0, 15);
    for (int i = 0; i < num_obj; i++) {
        AddObject(new Food (rand_.UniformRect(GetMapSize()), &rand_));
    }
    GameObject *player = new Player (rand_.UniformRect(GetMapSize()),
                                     25, 100, rand_.ColorOpaque());
    AddObject(player);
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
        for (const auto& obj : objects_) {
            if (obj->GetType() == "PLAYER") {
                view_.setCenter(obj->GetPos());
                obj->Control();
            }
            if (!(obj->IsDead())) {
                obj->Logic(map_.getSize());
                obj->Move(time_);
                obj->Draw(map_);
            }
        }
        map_.display();

        window_.clear(sf::Color(203, 203, 203));
        window_.setView(view_);
        window_.draw(sf::Sprite(map_.getTexture()));
        DrawUI();
        window_.display();

        DestroyDeadObjects();
    }
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
                }
                break;
            }
            case sf::Event::MouseWheelMoved: {
                view_.zoom(1 - (event.mouseWheel.delta * 0.05));
                break;
            }

        }
    }
}

void Engine::DestroyDeadObjects() {
    auto obj = objects_.begin();
    while (obj != objects_.end()) {
        if ((*obj)->IsDead()) {
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
    text.setColor(sf::Color::Black);
    window_.draw(text);
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
    text.setColor(sf::Color::Black);

    window_.draw(text);
}

}
