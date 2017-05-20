#include "GameFactory.h"

namespace thirtythree {

GameFactory::GameFactory() {

    drawer_             = new Drawer(sf::VideoMode(1024, 600), "Game33", {3000, 3000});
    rand_               = new Randomizer();
    factory_            = new ObjectsFactory(rand_);
    texture_provider_   = new TextureProvider(rand_);
    logic_              = new GameLogic(rand_, factory_, texture_provider_);
    engine_             = new Engine(drawer_, logic_);

    factory_->AssociateEngine(engine_);
    logic_->AssociateEngine(engine_);
    LOG_INFO("Game assembled");
}

GameFactory::~GameFactory() {
    delete drawer_;
    delete rand_;
    delete factory_;
    delete texture_provider_;
    delete logic_;
    delete engine_;
    LOG_INFO("Game destroyed");
}

void GameFactory::StartEngine() {
    engine_->StartGame();
}


}
