#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GameObject.h"

namespace thirtythree {

class Player : public GameObject {
public:

    Player() : GameObject() {}
    Player(const sf::Vector2f &pos,
           float radius,
           float speed_factor = 100,
           const sf::Color &color = sf::Color::White,
           float friction = 0.03f);

    ~Player();

    void Control();
    void Logic(const sf::Vector2u &map_size);

    std::string GetType() { return "PLAYER"; }
private:
    float speed_factor_;
};

}

#endif // PLAYER_H_INCLUDED
