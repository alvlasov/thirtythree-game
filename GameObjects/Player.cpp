/*!
    @file GameObjects\Player.cpp
    @brief Игровой объект "Player"
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#include "Player.h"

namespace thirtythree {

Player::Player(sf::RenderWindow *window, const sf::Vector2f &pos,
               float radius, const sf::Color &color, float friction)
    : GameObject(pos, radius, color, {0, 0}, friction),
      window_ (window) {
    LOG_DEBUG("Object " << GetType() << " created on pos (" << pos_.x << ", " << pos_.y << ")");
}

Player::~Player() {
    LOG_DEBUG("Object " << GetType() << " destroyed");
}

void Player::Control() {
    sf::Vector2f mouse_pos = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
    float len = length(mouse_pos - pos_);
    if (len > radius_) {
        speed_ = normalize(mouse_pos - pos_) * GetMaxSpeed();
    }
}

}
