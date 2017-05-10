/*!
    @file GameLogic.h
    @brief Класс игровой логики
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Logger.h"
#include "Randomizer.h"
#include "ObjectsFactory.h"
#include "GameObjects\GameObject.h"

namespace thirtythree {

class Engine;
class GameLogic {
public:

    GameLogic(Engine *engine, Randomizer *rand);
    ~GameLogic();

    void StartGame();
    void DoLogic();
    void Collide(GameObject &obj1, GameObject &obj2);

    int GetScore() { return score_; }

private:

    Randomizer *rand_;
    Engine *engine_;
    ObjectsFactory factory_;

    int score_;

    sf::Clock clock_food_create_;
    static const int min_food_create_interval_ = 3;

};

}

#endif // GAMELOGIC_H_INCLUDED
