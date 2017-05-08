#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "GameObject.h"
#include <random>
#include <chrono>
#include <cmath>

namespace thirtythree {

class Food : public GameObject {
public:

    Food() : GameObject() {}
    Food(const sf::Vector2f &pos,
         float friction = 0.01f);

    ~Food();
    void Logic(const sf::Vector2u &map_size);

    std::string GetType() { return "FOOD"; }

private:

    float Rand() { return rand_engine_() / (float)rand_engine_.max(); }

    std::default_random_engine rand_engine_;
    static const int min_radius_ = 5;
    static const int max_radius_ = 25;
    static const int max_pinch_speed_ = 100;
    static const int min_seconds_idle_ = 3;
    static const int min_seconds_alive_ = 60;
    sf::Clock clock_pinch_;
    sf::Clock clock_life_;
};

}



#endif // FOOD_H_INCLUDED
