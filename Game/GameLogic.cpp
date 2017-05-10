/*!
    @file GameLogic.cpp
    @brief Класс игровой логики
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#include "Engine.h"
#include "GameLogic.h"

namespace thirtythree {

GameLogic::GameLogic(Engine *engine, Randomizer *rand)
    : engine_ (engine),
      rand_ (rand),
      factory_ (engine, rand, this),
      score_ (0) {
    clock_food_create_.restart();
    LOG_INFO("Game logic unit initialized");
}

GameLogic::~GameLogic(){
    LOG_INFO("Game logic unit destroyed");
}

void GameLogic::StartGame() {
    int num_obj = rand_->UniformInt(0, 15);
    for (int i = 0; i < num_obj; i++) {
        engine_->AddObject(factory_.CreateObject("FOOD"));
    }
    engine_->AddObject(factory_.CreateObject("PLAYER"));
}

void GameLogic::DoLogic() {
    sf::Vector2f map_size = engine_->GetMapSize();

    if (clock_food_create_.getElapsedTime().asSeconds() > min_food_create_interval_) {
        if (rand_->Uniform() > 0.995) {
            clock_food_create_.restart();
            int num_obj = rand_->UniformInt(0, 5);
            for (int i = 0; i < num_obj; i++) {
                engine_->AddObject(factory_.CreateObject("FOOD"));
            }
        }
    }

}

void GameLogic::Collide(GameObject &obj1, GameObject &obj2) {
    auto obj1_type = obj1.GetType();
    auto obj2_type = obj2.GetType();

    if (obj1_type == "PLAYER" && obj2_type ==  "FOOD") {
        obj2.Kill();
        obj1.AddRadius(1);
        score_++;
    }
    if (obj1_type == "FOOD" && obj2_type ==  "PLAYER") {
        obj1.Kill();
        obj2.AddRadius(1);
        score_++;
    }
}


}
