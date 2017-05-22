#include "GameFactory.h"

namespace thirtythree {

GameFactory::GameFactory() {
    int map_size_x = 5000;
    int map_size_y = 4000;
    drawer_             = new Drawer(sf::VideoMode(1024, 600), "Game33", {map_size_x, map_size_y});
    tree_               = new QuadTree(sf::FloatRect({0, 0}, {map_size_x, map_size_y}), drawer_);
    rand_               = new Randomizer();
    factory_            = new ObjectsFactory(rand_);
    texture_provider_   = new TextureProvider(rand_);
    logic_              = new GameLogic(rand_, factory_, texture_provider_);
    engine_             = new Engine(drawer_, logic_, tree_);

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
