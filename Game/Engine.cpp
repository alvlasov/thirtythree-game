#include <Engine.h>

namespace thirtythree{

Engine::Engine(){

    sf::RenderWindow window (sf::VideoMode (1100, 650), __FILE__, sf::Style::Default & ~sf::Style::Resize);

    window.setVerticalSyncEnabled (true);
    window.setFramerateLimit (25);

    Window = &window;

    sf::Clock clock;

    objects_.emplace_back(new thirtythree::GameObject ({50, 50}, {250, 10}, {0.2, 0.2}, "example.png", 0, 0, 0.1));
    objects_.emplace_back(new thirtythree::GameObject ({150, 150}, {-50, 0}, {1, 1}, "error.png"));
    objects_.emplace_back(new thirtythree::GameObject ({400, 234}, {100, -100}, {0.3, 0.3}, "example.png", 0, 0, 5));

    while (window.isOpen()) {
        float time = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        for (const auto& obj : objects) {
            if (!(obj -> isDead())) {
                obj -> Logic();
                obj -> Move(time);
                obj -> Draw();
            }
        }

        auto obj = objects.begin();
        while (obj != objects.end()) {
            if ((*obj) -> isDead()) {
                obj = objects.erase(obj);
            } else {
                obj++;
            }

        }
        window.display();
    }


}
}
