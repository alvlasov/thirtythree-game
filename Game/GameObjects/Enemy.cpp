/*!
    @file GameObjects\Enemy.cpp
    @brief Игровой объект "Enemy"
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/
#include "Enemy.h"

namespace thirtythree {

Enemy::Enemy(const sf::Vector2f &pos, Randomizer *rand, float radius, float friction)
    : GameObject(pos, radius, sf::Color::White, {0, 0}, friction),
      rand_ (rand) {
    if (radius <= 0) radius_ = rand_->UniformInt(min_radius_, max_radius_);
    color_ = rand_->ColorOpaque();

    LOG_INFO("Object " << GetType() << " created on pos (" << pos_.x << ", " << pos_.y << ")");
}

Enemy::~Enemy() {
    LOG_INFO("Object " << GetType() << " destroyed");
}

}
