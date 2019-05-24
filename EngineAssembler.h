#ifndef ENGINEASSEMBLER_H_INCLUDED
#define ENGINEASSEMBLER_H_INCLUDED

#include "Utility.h"
#include "Engine.h"
#include "Drawer.h"
#include "Logger.h"
#include "GameLogic.h"
#include "Randomizer.h"
#include "ObjectsFactory.h"
#include "TextureProvider.h"
#include "Engine/QuadTree.h"

namespace thirtythree {

class EngineAssembler {
public:

    ~EngineAssembler();
    Engine* AssemblyEngine();

private:

    Engine *engine_;

    Drawer *drawer_;
    TextureProvider *texture_provider_;
    Randomizer *rand_;
    GameLogic *logic_;
    ObjectsFactory *factory_;
    QuadTree *tree_;

};

}

#endif // ENGINEASSEMBLER_H_INCLUDED
