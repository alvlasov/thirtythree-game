#include "Engine.h"
#include "GameLogic.h"

namespace thirtythree {

GameLogic::GameLogic(Engine *engine)
    : associated_engine_ (engine) {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    rand_engine_.seed(seed);
    clock_food_create_.restart();
    LOG_INFO("Game logic unit created.");
}

GameLogic::~GameLogic(){
    LOG_INFO("Game logic unit destroyed.");
}


void GameLogic::DoLogic() {
    sf::Vector2u map_size = associated_engine_->GetMapSize();
    if (clock_food_create_.getElapsedTime().asSeconds() > min_food_create_time_) {
        if (Rand() > 0.995) {
            associated_engine_->AddObject(new Food ({(int)(map_size.x * Rand()),
                                                     (int)(map_size.y * Rand())}));
        }
    }

}
}
