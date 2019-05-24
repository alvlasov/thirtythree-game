/*!
    @file GameObjects\Food.cpp
    @brief Игровой объект "Food"
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#include "Food.h"

namespace thirtythree {

Food::Food(const sf::Vector2f &pos, Randomizer *rand, float friction)
    : GameObject(pos, 1, sf::Color::White, {0, 0}, friction),
      rand_ (rand) {
    interactable_ = false;
    clock_pinch_.restart();
    clock_life_.restart();
    radius_ = rand_->UniformInt(min_radius_, max_radius_);
    color_ = rand_->Color();
    min_seconds_idle_ = rand->Uniform(1, 3);
    body_.setPointCount(10);
    LOG_DEBUG("Object " << GetType() << " created on pos (" << pos_.x << ", " << pos_.y << ")");
}

void Food::Logic() {
    if (clock_pinch_.getElapsedTime().asSeconds() > min_seconds_idle_) {
        if (rand_->Uniform() > 0.5) {
            speed_ = rand_->Direction() * (float)max_pinch_speed_;
        }
        clock_pinch_.restart();
    }
    if (clock_life_.getElapsedTime().asSeconds() > min_seconds_alive_) {
        if (rand_->Uniform() > 0.997) {
            Kill();
        }
    }

}

Food::~Food() {
    LOG_DEBUG("Object " << GetType() << " destroyed");
}

}
