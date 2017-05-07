#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Player.h"

#include <vector>
#include <memory>

extern sf::RenderWindow* Window = nullptr;

using obj_uptr = std::unique_ptr<thirtythree::GameObject>;

int main() {
    sf::RenderWindow window(sf::VideoMode(1024, 600), __FILE__, sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(120);
    Window = &window;

    sf::RenderTexture map;
    if (!map.create(900, 900))
    {
        return -1;
    }

    sf::Clock clock;
    sf::View view;
    view.reset(sf::FloatRect(0, 0, 1024, 600));

    std::vector <obj_uptr> objects;
    objects.emplace_back(new thirtythree::GameObject ({50, 50}, 10, sf::Color::Red, {500, 10}));
    objects.emplace_back(new thirtythree::GameObject ({150, 150}, 15, sf::Color::Green, {-400, 0}));
    objects.emplace_back(new thirtythree::Player ({400, 234}, 25, 100, sf::Color::Blue));
    objects.emplace_back(new thirtythree::GameObject ({500, 500}, 35, sf::Color::Red, {-100, -100}));

    while (window.isOpen()) {
        float time = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized) {
                view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
            }
        }

        map.clear(sf::Color::White);
        for (const auto& obj : objects) {
            if (obj->GetType() == thirtythree::PLAYER) {
                view.setCenter(obj->GetPos());
                obj->Control();
            }
            if (!(obj->IsDead())) {
                obj->Logic(map.getSize());
                obj->Move(time);
                obj->Draw(map);
            }
        }

        auto obj = objects.begin();
        while (obj != objects.end()) {
            if ((*obj)->IsDead()) {
                obj = objects.erase(obj);
            } else {
                obj++;
            }
        }

        map.display();
        window.clear();
        sf::Sprite sprite(map.getTexture());

        window.draw(sprite);
        window.setView(view);
        window.display();
    }

    return 0;
}
