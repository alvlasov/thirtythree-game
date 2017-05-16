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
    clock_enemy_create_.restart();
    LOG_INFO("Game logic unit initialized");
}

GameLogic::~GameLogic(){
    LOG_INFO("Game logic unit destroyed");
}

void GameLogic::StartGame() {
    score_ = 0;
    int num_obj = rand_->UniformInt(0, 15);
    for (int i = 0; i < num_obj; i++) {
        engine_->AddObject(factory_.CreateObject("FOOD"));
    }
    engine_->AddObject(factory_.CreateObject("PLAYER"));
}

void GameLogic::DoLogic() {
    sf::Vector2f map_size = engine_->GetMapSize();

    if (clock_food_create_.getElapsedTime().asSeconds() > min_food_create_interval_) {
        if (rand_->Uniform() > 0.7) {
            clock_food_create_.restart();
            int num_obj = rand_->UniformInt(1, 5);
            for (int i = 0; i < num_obj; i++) {
                engine_->AddObject(factory_.CreateObject("FOOD"));
            }
        }
    }

    if (clock_enemy_create_.getElapsedTime().asSeconds() > min_enemy_create_interval_) {
        if (rand_->Uniform() > 0.7) {
            clock_enemy_create_.restart();
            int num_obj = rand_->UniformInt(1, 3);
            for (int i = 0; i < num_obj; i++) {
                engine_->AddObject(factory_.CreateObject("ENEMY"));
            }
        }
    }
}

void GameLogic::Collide(GameObject &obj1, GameObject &obj2) {
    auto obj1_type = obj1.GetType();
    auto obj2_type = obj2.GetType();
    auto obj1_radius = obj1.GetRadius();
    auto obj2_radius = obj2.GetRadius();

    if (obj1_type == "PLAYER" && obj2_type == "FOOD") {
        obj2.Kill();
        obj1.SetRadius(cbrt(pow(obj1_radius, 3) + pow(obj2_radius, 3)));
        score_++;
    }
    if (obj1_type == "FOOD" && obj2_type == "PLAYER") {
        obj1.Kill();
        obj2.SetRadius(cbrt(pow(obj1_radius, 3) + pow(obj2_radius, 3)));
        score_++;
    }

    if (obj1_type == "ENEMY" && obj2_type == "FOOD") {
        obj2.Kill();
        obj1.SetRadius(cbrt(pow(obj1_radius, 3) + pow(obj2_radius, 3)));
    }

    if (obj1_type == "FOOD" && obj2_type == "ENEMY") {
        obj1.Kill();
        obj2.SetRadius(cbrt(pow(obj1_radius, 3) + pow(obj2_radius, 3)));
    }

    if (obj1_type == "PLAYER" && obj2_type == "ENEMY") {
        if (obj1_radius > obj2_radius) {
            obj2.Kill();
            obj1.SetRadius(cbrt(pow(obj1_radius, 3) + pow(obj2_radius, 3)));
            score_++;
        } else {
            obj1.Kill();
            obj2.SetRadius(cbrt(pow(obj1_radius, 3) + pow(obj2_radius, 3)));
        }
    }

    if (obj1_type == "ENEMY" && obj2_type == "ENEMY") {
        if (obj1_radius > obj2_radius) {
            obj2.Kill();
            obj1.SetRadius(cbrt(pow(obj1_radius, 3) + pow(obj2_radius, 3)));
        } else {
            obj1.Kill();
            obj2.SetRadius(cbrt(pow(obj1_radius, 3) + pow(obj2_radius, 3)));
        }
    }

}

void GameLogic::Interact(GameObject &obj1, GameObject &obj2) {
    auto obj1_type = obj1.GetType();
    auto obj2_type = obj2.GetType();
    auto obj1_radius = obj1.GetRadius();
    auto obj2_radius = obj2.GetRadius();
    auto obj1_pos = obj1.GetPos();
    auto obj2_pos = obj2.GetPos();

    if ((obj1_type == "PLAYER" || obj1_type == "ENEMY") && obj2_type == "ENEMY") {
        if (obj1_radius > obj2_radius) {
            auto direction = normalize(obj2_pos - obj1_pos);
            obj2.AddSpeed(direction);
        } else {
            auto direction = normalize(obj1_pos - obj2_pos);
            obj2.AddSpeed(direction);
        }
    }

    if (obj1_type == "ENEMY" && (obj2_type == "PLAYER" || obj2_type == "ENEMY")) {
        if (obj2_radius > obj1_radius) {
            auto direction = normalize(obj1_pos - obj2_pos);
            obj1.AddSpeed(direction);
        } else {
            auto direction = normalize(obj2_pos - obj1_pos);
            obj1.AddSpeed(direction);
        }
    }


}


}
