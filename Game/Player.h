#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GameObject.h"
#include <cmath>


namespace thirtythree {

class Player : public GameObject {
public:

    Player() : GameObject() {}
    Player(const sf::Vector2f &pos,
           float radius,
           float speed_factor = 100,
           const sf::Color &color = sf::Color::White,
           float friction = 0.03f)
        : GameObject(pos, radius, color, {0, 0}, friction),
          speed_factor_ (speed_factor) {}

    ~Player();

    void Control();
    void Logic(const sf::Vector2u &map_size);

    ObjectType GetType() { return PLAYER; }
private:
    float speed_factor_;
};

}

#endif // PLAYER_H_INCLUDED
