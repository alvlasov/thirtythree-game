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

extern sf::RenderWindow* Window;

namespace thirtythree {

class Engine {
public:
    Engine(sf::VideoMode mode, const sf::String name, sf::Vector2i map_size);

    void AddObject(GameObject *object);
    void StartGame();
    sf::Vector2u GetMapSize() { return map_.getSize(); }
private:

    void GameLoop();

    std::vector<std::unique_ptr<GameObject>> objects_;
    sf::RenderWindow window_;
    sf::RenderTexture map_;
    sf::Clock clock_;
    sf::View view_;
    GameLogic logic_;

};

}

#endif // ENGINE_H_INCLUDED
