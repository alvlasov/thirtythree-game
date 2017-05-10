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

GameObject* ObjectsFactory::CreateObject(std::string object_type) {
    if (object_type == "PLAYER") {
        return new Player (engine_->GetWindow(), engine_->GetMapSize(),
                           rand_->UniformRect(engine_->GetMapSize()),
                           30, 200, rand_->ColorOpaque());
    } else if (object_type == "FOOD") {
        return new Food (rand_->UniformRect(engine_->GetMapSize()), rand_);
    }
}


}
