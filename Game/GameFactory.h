#ifndef INJECTOR_H_INCLUDED
#define INJECTOR_H_INCLUDED

#include "Engine.h"
#include "Drawer.h"
#include "Logger.h"
#include "GameLogic.h"
#include "Randomizer.h"
#include "ObjectsFactory.h"
#include "TextureProvider.h"

namespace thirtythree {

class GameFactory {
public:

    GameFactory();
    ~GameFactory();
    void StartEngine();

private:

    Engine *engine_;

    Drawer *drawer_;
    TextureProvider *texture_provider_;

    Randomizer *rand_;
    GameLogic *logic_;
    ObjectsFactory *factory_;

};

}

#endif // INJECTOR_H_INCLUDED
