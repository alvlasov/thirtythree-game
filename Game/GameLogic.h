/*!
    @file GameLogic.h
    @brief Класс игровой логики
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

#include <stdexcept>

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

    GameLogic(Randomizer *rand, ObjectsFactory *factory,
              TextureProvider *texture_provider, Engine *engine = nullptr);
    ~GameLogic();

    void StartGame();
    void DoLogic();
    void HandleEvent(Event &event);

    int GetScore() { return score_; }

    void AssociateEngine(Engine *engine) { engine_ = engine; }

private:

    static const int kPlayerInitialRadius = 30;

    bool OnInteract(GameObject &obj1, GameObject &obj2);
    bool OnCollide(GameObject &obj1, GameObject &obj2);

    inline float CalcNewRadius(float radius1, float radius2) {
        return cbrt(pow(radius1, 3) + pow(radius2, 3));
    }
    inline void UpdateScore(float player_radius) {
        score_ = pow(player_radius - kPlayerInitialRadius, 3);
    }

    Randomizer *rand_;
    Engine *engine_;
    ObjectsFactory *factory_;
    TextureProvider *texture_provider_;

    sf::Vector2f spawn_factor_;
    int score_;

    sf::Clock clock_food_create_;
    sf::Clock clock_enemy_create_;
    static constexpr int kFoodCreateIntervalSeconds = 1;
    static constexpr float kFoodInitialDensityFactor = 3.0f;
    static constexpr float kFoodMinDensity = 0.4f;
    static constexpr float kFoodMaxDensity = 2.0f;
    static constexpr int kEnemyCreateIntervalSeconds = 10;
    static constexpr float kEnemyInitialDensityFactor = 3.0f;
    static constexpr float kEnemyMinDensity = 1.5f;
    static constexpr float kEnemyMaxDensity = 4.0f;


};

}

#endif // GAMELOGIC_H_INCLUDED
