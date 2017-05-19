/*!
    @file ObjectsFactory.cpp
    @brief Класс "фабрика объектов"
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#include "Engine.h"
#include "GameLogic.h"
#include "ObjectsFactory.h"

namespace thirtythree {

ObjectsFactory::ObjectsFactory(Engine *engine, Randomizer *rand, GameLogic *logic)
    : engine_ (engine), rand_ (rand), logic_ (logic) {
     LOG_INFO("Objects factory initialized");
}

ObjectsFactory::~ObjectsFactory() {
     LOG_INFO("Objects factory destroyed");
}

GameObject* ObjectsFactory::CreatePlayer(float radius) {
    return new Player (engine_->GetWindow(),
                       rand_->UniformRect(engine_->GetMapSize()),
                       radius, rand_->ColorOpaque());
}

GameObject* ObjectsFactory::CreateFood() {
    return new Food (rand_->UniformRect(engine_->GetMapSize()), rand_);
}

GameObject* ObjectsFactory::CreateEnemy() {
    return new Enemy (rand_->UniformRect(engine_->GetMapSize()), rand_);
}

GameObject* ObjectsFactory::CreateEnemy(float radius) {
    return new Enemy (rand_->UniformRect(engine_->GetMapSize()), rand_, radius);
}


}
