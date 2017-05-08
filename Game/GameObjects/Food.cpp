#include "Food.h"

namespace thirtythree {

Food::Food(const sf::Vector2f &pos, float friction)
    : GameObject(pos, 1, sf::Color::White, {0, 0}, friction) {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    rand_engine_.seed(seed);
    clock_pinch_.restart();
    clock_life_.restart();
    radius_ = round(min_radius_ + (max_radius_ - min_radius_) * Rand());
    color_ = sf::Color((int)(255 * Rand()), (int)(255 * Rand()),
                       (int)(255 * Rand()), (int)(255 * Rand()));
    LOG_INFO("Object " << GetType() << " created on pos (" << pos_.x << ", " << pos_.y << ")");
}

void Food::Logic(const sf::Vector2u &map_size) {
    GameObject::Logic(map_size);
    if (clock_pinch_.getElapsedTime().asSeconds() > min_seconds_idle_) {
        if (Rand() > 0.99) {
            speed_.x = pow(-1, rand_engine_()) * Rand() * max_pinch_speed_;
            speed_.y = pow(-1, rand_engine_()) * Rand() * max_pinch_speed_;
            clock_pinch_.restart();
        }
    }
    if (clock_life_.getElapsedTime().asSeconds() > min_seconds_alive_) {
        if (Rand() > 0.997) {
            Kill();
        }
    }
}

Food::~Food() {
    LOG_INFO("Object " << GetType() << " destroyed");
}

}
