/*!
    @file GameObjects\Player.h
    @brief Игровой объект "Player"
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GameObject.h"

namespace thirtythree {

class Player : public GameObject {
public:

    Player() : GameObject() {}
    Player(sf::RenderWindow *window,
           const sf::Vector2f &map_size,
           const sf::Vector2f &pos,
           float radius,
           const sf::Color &color = sf::Color::White,
           float friction = 0.03f);

    ~Player();

    void Logic() {};
    void Control();

    std::string GetType() { return "PLAYER"; }
private:

    sf::RenderWindow *window_;
    sf::Vector2f map_size_;
};

}

#endif // PLAYER_H_INCLUDED
