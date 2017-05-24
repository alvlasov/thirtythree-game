/*!
    @file ObjectsFactory.h
    @brief Класс "фабрика объектов"
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef OBJECTSFACTORY_H_INCLUDED
#define OBJECTSFACTORY_H_INCLUDED

#include <string>
#include "GameObjects\GameObject.h"
#include "GameObjects\Player.h"
#include "GameObjects\Food.h"
#include "GameObjects\Enemy.h"
#include "Randomizer.h"
#include "Logger.h"

namespace thirtythree {

class Engine;
class GameLogic;
class ObjectsFactory {
public:

    ObjectsFactory(Randomizer *rand, Engine *engine = nullptr);
    ~ObjectsFactory();

    GameObject* CreatePlayer(float radius);
    GameObject* CreateFood();
    GameObject* CreateEnemy();
    GameObject* CreateEnemy(float radius);

    void AssociateEngine(Engine *engine) { engine_ = engine; }

private:

    Engine *engine_;
    Randomizer *rand_;
    GameLogic *logic_;

};

}


#endif // OBJECTSFACTORY_H_INCLUDED
