#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "GlobalOptions.h"
#include "Randomizer.h"

namespace thirtythree {
class Engine;
class GameLogic {
public:

    GameLogic(Engine *engine, Randomizer *rand);
    ~GameLogic();

    void DoLogic();
    int GetScore() { return score_; }

private:

    Randomizer *rand_;
    Engine *engine_;

    int score_;

    sf::Clock clock_food_create_;
    static const int min_food_create_interval_ = 3;
};

}

#endif // GAMELOGIC_H_INCLUDED
