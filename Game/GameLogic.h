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
class TextureProvider;
class GameLogic {
public:

    enum EventType {COLLISION, INTERACTION};

    struct Event {
        Event (EventType ntype, GameObject &nobj1, GameObject &nobj2)
            : type (ntype), obj1 (&nobj1), obj2 (&nobj2) {}
        EventType type;
        GameObject *obj1;
        GameObject *obj2;
    };

    GameLogic(Engine *engine, Randomizer *rand);
    ~GameLogic();

    void StartGame();
    void DoLogic();
    void HandleEvent(Event &event);

    int GetScore() { return score_; }

private:

    static const int player_initial_radius_ = 30;

    bool OnInteract(GameObject &obj1, GameObject &obj2);
    bool OnCollide(GameObject &obj1, GameObject &obj2);

    inline float CalcNewRadius(float radius1, float radius2) {
        return cbrt(pow(radius1, 3) + pow(radius2, 3));
    }
    inline void UpdateScore(float player_radius) {
        score_ = pow(player_radius - player_initial_radius_, 3);
    }

    Randomizer *rand_;
    Engine *engine_;
    ObjectsFactory factory_;
    TextureProvider *texture_provider_;

    int score_;

    sf::Clock clock_food_create_;
    sf::Clock clock_enemy_create_;
    static const int min_food_create_interval_ = 1;
    static const int min_enemy_create_interval_ = 3;

};

}

#endif // GAMELOGIC_H_INCLUDED
