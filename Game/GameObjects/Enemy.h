/*!
    @file GameObjects\Enemy.h
    @brief Игровой объект "Enemy"
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/
#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "GameObjects/GameObject.h"
#include "Randomizer.h"

namespace thirtythree {

class Enemy : public GameObject {
public:
    Enemy() : GameObject() {}
    Enemy(const sf::Vector2f &pos, Randomizer *rand, float radius = 0, float friction = 0);

    ~Enemy();

    int GetType() { return ENEMY; }

private:

    static const int min_radius_ = 20;
    static const int max_radius_ = 50;

    Randomizer *rand_;
};

}

#endif // ENEMY_H_INCLUDED
