#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <cmath>

#include "GlobalOptions.h"

namespace thirtythree {
class Engine;
class GameLogic {
public:

    GameLogic(Engine *engine);
    ~GameLogic();

    void DoLogic();

private:

    Engine *associated_engine_;

    float Rand() { return rand_engine_() / (float)rand_engine_.max(); }
    std::default_random_engine rand_engine_;
    sf::Clock clock_food_create_;
    static const int min_food_create_time_ = 0.5;
};

}

#endif // GAMELOGIC_H_INCLUDED
