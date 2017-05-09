#ifndef OBJECTSFACTORY_H_INCLUDED
#define OBJECTSFACTORY_H_INCLUDED

#include <string>
#include "GameObjects\GameObject.h"
#include "GameObjects\Player.h"
#include "GameObjects\Food.h"
#include "Randomizer.h"
#include "Logger.h"

namespace thirtythree {

class Engine;
class GameLogic;
class ObjectsFactory {
public:

    ObjectsFactory(Engine *engine, Randomizer *rand, GameLogic *logic);
    ~ObjectsFactory();

    GameObject* CreateObject(std::string object_type);

private:

    Engine *engine_;
    Randomizer *rand_;
    GameLogic *logic_;

};

}


#endif // OBJECTSFACTORY_H_INCLUDED
