#include "Player.h"

namespace thirtythree {

Player::~Player() {
    LOG_INFO("Object " << GetType() << " destroyed");
}

void Player::Control() {

    auto mouse = sf::Mouse::getPosition(*Window);
    float abs = sqrt(pow(mouse.x - pos_.x, 2) + pow(mouse.y - pos_.y, 2));
    if (abs > 2.0f) {
        speed_.x = speed_factor_ * (mouse.x - pos_.x) / abs;
        speed_.y = speed_factor_ * (mouse.y - pos_.y) / abs;
    } else {
        speed_ = {0, 0};
    }

}

void Player::Logic(sf::Vector2u map_size) {
    if (pos_.x <= size_.x / 2 || pos_.x >= map_size.x - size_.x / 2) {
        speed_.x *= -1;
    }
    if (pos_.y <= size_.y / 2 || pos_.y >= map_size.y - size_.y / 2) {
        speed_.y *= -1;
    }
}

}
