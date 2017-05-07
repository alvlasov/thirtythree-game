#include "Player.h"

namespace thirtythree {

Player::~Player() {
    LOG_INFO("Object " << GetType() << " destroyed");
}

void Player::Control() {

    sf::Vector2f mouse_pos = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));
    float modulus = sqrt(pow(mouse_pos.x - pos_.x, 2) +
                      pow(mouse_pos.y - pos_.y, 2));
    if (modulus > radius_) {
        speed_ = (mouse_pos - pos_) / modulus * speed_factor_;
    }

}

void Player::Logic(const sf::Vector2u &map_size) {
    if (pos_.x < size_.x / 2) {
        speed_.x = abs(speed_.x);
    }
    if (pos_.y < size_.y / 2) {
        speed_.y = abs(speed_.y);
    }
    if (pos_.x > map_size.x - size_.x / 2) {
        speed_.x = -abs(speed_.x);
    }
    if (pos_.y > map_size.y - size_.y / 2) {
        speed_.y = -abs(speed_.y);
    }
}

}
