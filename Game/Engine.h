#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

#include "GameObjects\GameObject.h"
#include "GameObjects\Player.h"
#include "GameObjects\Food.h"
#include "GlobalOptions.h"
#include "GameLogic.h"
#include "Randomizer.h"

extern sf::RenderWindow* Window;

namespace thirtythree {

class Engine {
public:
    Engine(sf::VideoMode mode, const sf::String name, sf::Vector2i map_size);

    void AddObject(GameObject *object);
    void StartGame();
    int GetObjectsCount() { return objects_.size(); }
    sf::Vector2f GetMapSize() { return (sf::Vector2f)map_.getSize(); }
    sf::Vector2f GetWindowSize() { return (sf::Vector2f)window_.getSize(); }

private:
    static const size_t max_object_number_ = 1000;

    void GameLoop();
    void HandleEvents();
    void DrawUI();
    void DrawDebugInfo();

    std::vector<std::unique_ptr<GameObject>> objects_;

    sf::RenderWindow window_;
    sf::RenderTexture map_;
    sf::View view_;
    sf::View default_view_;


    float time_;
    sf::Font font_;

    Randomizer rand_;
    GameLogic logic_;
    sf::Clock clock_;

    bool draw_debug_info_ = true;

};

}

#endif // ENGINE_H_INCLUDED
