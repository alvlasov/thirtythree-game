/*!
    @file GameObjects\Food.h
    @brief Игровой объект "Food"
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "GameObject.h"
#include "../Randomizer.h"

namespace thirtythree {

class Food : public GameObject {
public:

    Food() : GameObject() {}
    Food(const sf::Vector2f &pos, Randomizer *rand, float friction = 0.01f);

    ~Food();
    void Logic();

    int GetType() { return FOOD; }

private:

    static const int min_radius_ = 10;
    static const int max_radius_ = 15;
    static const int max_pinch_speed_ = 100;
    static const int min_seconds_alive_ = 240;
    int min_seconds_idle_;
    sf::Clock clock_pinch_;
    sf::Clock clock_life_;

    Randomizer *rand_;
};

}



#endif // FOOD_H_INCLUDED
