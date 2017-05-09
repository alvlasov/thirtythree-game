#include "Engine.h"
#include "GameLogic.h"

namespace thirtythree {

GameLogic::GameLogic(Engine *engine, Randomizer *rand)
    : engine_ (engine),
      rand_ (rand),
      score_ (0) {
    clock_food_create_.restart();
    LOG_INFO("Game logic unit initialized");
}

GameLogic::~GameLogic(){
    LOG_INFO("Game logic unit destroyed");
}


void GameLogic::DoLogic() {
    sf::Vector2f map_size = engine_->GetMapSize();

    if (clock_food_create_.getElapsedTime().asSeconds() > min_food_create_interval_) {
        if (rand_->Uniform() > 0.995) {
            clock_food_create_.restart();
            int num_obj = rand_->UniformInt(0, 5);
            for (int i = 0; i < num_obj; i++) {
                engine_->AddObject(new Food (rand_->UniformRect(map_size), rand_));
            }
        }
    }

}

}
