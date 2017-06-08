#include "EngineAssembler.h"

namespace thirtythree {

EngineAssembler::~EngineAssembler() {
    delete drawer_;
    delete rand_;
    delete factory_;
    delete texture_provider_;
    delete logic_;
    delete engine_;
    LOG_INFO("Game destroyed");
}

Engine* EngineAssembler::AssemblyEngine() {
    int map_size_x = 4000;
    int map_size_y = 4000;
    drawer_             = new Drawer(sf::VideoMode(1024, 600), "Game33", {map_size_x, map_size_y});
    tree_               = new QuadTree(Box({0, 0}, {map_size_x, map_size_y}), drawer_);
    rand_               = new Randomizer();
    factory_            = new ObjectsFactory(rand_);
    texture_provider_   = new TextureProvider(rand_);
    logic_              = new GameLogic(rand_, factory_, texture_provider_);
    engine_             = new Engine(drawer_, logic_, tree_);
    // объекты создаем много раз, unique_ptr
    factory_->AssociateEngine(engine_);
    logic_->AssociateEngine(engine_);
    LOG_INFO("Engine assembled");
    return engine_;
}


}
