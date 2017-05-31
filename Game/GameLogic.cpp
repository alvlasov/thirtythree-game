/*!
    @file GameLogic.cpp
    @brief Класс игровой логики
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#include "Engine.h"
#include "GameLogic.h"
#include "TextureProvider.h"

namespace thirtythree {

GameLogic::GameLogic(Randomizer *rand, ObjectsFactory *factory,
                     TextureProvider *texture_provider, Engine *engine)
    : engine_ (engine),
      rand_ (rand),
      factory_ (factory),
      texture_provider_ (texture_provider),
      score_ (0) {
    clock_food_create_.restart();
    clock_enemy_create_.restart();
    texture_provider_->LoadPlayerTexturesFromDirectory("Textures/Players");
    LOG_INFO("Game logic unit initialized");
}

GameLogic::~GameLogic(){
    LOG_INFO("Game logic unit destroyed");
}

void GameLogic::StartGame() {
    if (engine_ == nullptr) throw std::runtime_error("No Engine associated with GameLogic");
    spawn_factor_ = engine_->GetMapSize() / 1000.0f;
    score_ = 0;
    int num_food = rand_->UniformInt(kFoodInitialDensityFactor * kFoodMinDensity * spawn_factor_.x,
                                     kFoodInitialDensityFactor * kFoodMaxDensity * spawn_factor_.y);
    for (int i = 0; i < num_food; i++) {
        engine_->AddObject(factory_->CreateFood());
    }
    int num_enemies = rand_->UniformInt(kEnemyInitialDensityFactor * kEnemyMinDensity * spawn_factor_.x,
                                        kEnemyInitialDensityFactor * kEnemyMaxDensity * spawn_factor_.y);
    for (int i = 0; i < num_enemies; i++) {
        GameObject *new_enemy = factory_->CreateEnemy();
        new_enemy->SetTexture(texture_provider_->GetRandomPlayerTexture());
        engine_->AddObject(new_enemy);
    }
    GameObject *new_player = factory_->CreatePlayer(kPlayerInitialRadius);
    new_player->SetTexture(texture_provider_->GetRandomPlayerTexture());
    engine_->AddObject(new_player);
}

void GameLogic::DoLogic() {
    auto map_size_ = engine_->GetMapSize();
    if (clock_food_create_.getElapsedTime().asSeconds() > kFoodCreateIntervalSeconds) {
        int num_obj = rand_->UniformInt(kFoodMinDensity * spawn_factor_.x,
                                        kFoodMaxDensity * spawn_factor_.y);
        for (int i = 0; i < num_obj; i++) {
            engine_->AddObject(factory_->CreateFood());
        }
        clock_food_create_.restart();
    }

    if (clock_enemy_create_.getElapsedTime().asSeconds() > kEnemyCreateIntervalSeconds) {
        int num_obj = rand_->UniformInt(kEnemyMinDensity * spawn_factor_.x,
                                        kEnemyMaxDensity * spawn_factor_.y);
        for (int i = 0; i < num_obj; i++) {
            GameObject *new_enemy = factory_->CreateEnemy();
            new_enemy->SetTexture(texture_provider_->GetRandomPlayerTexture());
            engine_->AddObject(new_enemy);
        }
        clock_enemy_create_.restart();
    }

}

void GameLogic::HandleEvent(Event &event) {
    switch (event.type) {
        case COLLISION: {
            if (!OnCollide(*event.obj1, *event.obj2)) {
                OnCollide(*event.obj2, *event.obj1);
            }
            break;
        }
        case INTERACTION: {
            if (!OnInteract(*event.obj1, *event.obj2)) {
                OnInteract(*event.obj2, *event.obj1);
            }
            break;
        }
    }
}

bool GameLogic::OnCollide(GameObject &obj1, GameObject &obj2) {
    auto obj1_type = obj1.GetType();
    auto obj2_type = obj2.GetType();
    auto obj1_radius = obj1.GetRadius();
    auto obj2_radius = obj2.GetRadius();
    bool obj1_is_player_or_enemy = (obj1_type == PLAYER || obj1_type == ENEMY);

    if (obj1_is_player_or_enemy && obj2_type == FOOD) {
        obj2.Kill();
        obj1.SetRadius(CalcNewRadius(obj1_radius, obj2_radius));
        if (obj1_type == PLAYER) UpdateScore(obj1_radius);
        return true;
    }

    if (obj1_is_player_or_enemy && obj2_type == ENEMY) {
        if (obj1_radius > obj2_radius) {
            obj2.Kill();
            obj1.SetRadius(CalcNewRadius(obj1_radius, obj2_radius));
            if (obj1_type == PLAYER) UpdateScore(obj1_radius);
        } else {
            obj1.Kill();
            obj2.SetRadius(CalcNewRadius(obj1_radius, obj2_radius));
        }
        return true;
    }

    return false;
}

bool GameLogic::OnInteract(GameObject &obj1, GameObject &obj2) {
    auto obj1_type = obj1.GetType();
    auto obj2_type = obj2.GetType();
    auto obj1_radius = obj1.GetRadius();
    auto obj2_radius = obj2.GetRadius();
    auto obj1_pos = obj1.GetPos();
    auto obj2_pos = obj2.GetPos();
    float obj1_speed = obj1.GetMaxSpeed();
    float obj2_speed = obj2.GetMaxSpeed();
    bool obj1_is_player_or_enemy = (obj1_type == PLAYER || obj1_type == ENEMY);

    if (obj1_is_player_or_enemy && obj2_type == ENEMY) {
        auto distance = length(obj2_pos - obj1_pos) - std::max(obj1_radius, obj2_radius);
        auto direction = normalize(obj2_pos - obj1_pos);
        if (distance <= 0) distance = 1;
        float reaction = rand_->UniformInt(1, 10);
        auto speed_factor = direction /(float)sqrt(distance) / reaction;
        if (obj1_radius > obj2_radius) {
            if (obj1_type != PLAYER) {
                obj1.AddSpeed(obj1_speed * speed_factor);
            }
            obj2.AddSpeed(obj2_speed * speed_factor);
        } else {
            if (obj1_type != PLAYER) {
                obj1.AddSpeed(- obj1_speed * speed_factor);
            }
            obj2.AddSpeed(- obj2_speed * speed_factor);
        }
        return true;
    }

    if (obj1_type == ENEMY && obj2_type == FOOD) {
        auto direction = normalize(obj2_pos - obj1_pos);
        auto speed_factor = direction / 100.0f;
        obj1.AddSpeed(- obj1_speed * speed_factor);
        return true;
    }

    return false;
}

}
