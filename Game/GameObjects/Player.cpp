#include "Player.h"

namespace thirtythree {

Player::Player(const sf::Vector2f &pos, float radius, float speed_factor,
               const sf::Color &color, float friction)
    : GameObject(pos, radius, color, {0, 0}, friction),
      speed_factor_ (speed_factor) {
    LOG_INFO("Object " << GetType() << " created on pos (" << pos_.x << ", " << pos_.y << ")");
}

Player::~Player() {
    LOG_INFO("Object " << GetType() << " destroyed");
}

void Player::Control() {

    sf::Vector2f mouse_pos = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));
    float len = length(mouse_pos - pos_);
    if (len > radius_) {
        speed_ = normalize(mouse_pos - pos_) * speed_factor_;
    }
}

void Player::Logic(const sf::Vector2u &map_size) {
    if (pos_.x < radius_) {
        speed_.x = abs(speed_.x);
    }
    if (pos_.y < radius_) {
        speed_.y = abs(speed_.y);
    }
    if (pos_.x > map_size.x - radius_) {
        speed_.x = -abs(speed_.x);
    }
    if (pos_.y > map_size.y - radius_) {
        speed_.y = -abs(speed_.y);
    }
}

}
