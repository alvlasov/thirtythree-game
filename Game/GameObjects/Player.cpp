/*!
    @file GameObjects\Player.cpp
    @brief Игровой объект "Player"
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#include "Player.h"

namespace thirtythree {

Player::Player(sf::RenderWindow *window, const sf::Vector2f &map_size, const sf::Vector2f &pos, float radius,
               float speed_factor, const sf::Color &color, float friction)
    : GameObject(pos, radius, color, {0, 0}, friction),
      speed_factor_ (speed_factor),
      window_ (window),
      map_size_ (map_size) {
    LOG_INFO("Object " << GetType() << " created on pos (" << pos_.x << ", " << pos_.y << ")");
}

Player::~Player() {
    LOG_INFO("Object " << GetType() << " destroyed");
}

void Player::Control() {
    sf::Vector2f mouse_pos = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
    float len = length(mouse_pos - pos_);
    if (len > radius_) {
        speed_ = normalize(mouse_pos - pos_) * speed_factor_;
    }
    if (pos_.x < radius_ && speed_.x < 0 ||
        pos_.x > map_size_.x - radius_ && speed_.x > 0) {
        speed_.x = 0;
    }
    if (pos_.y < radius_ && speed_.y < 0 ||
        pos_.y > map_size_.y - radius_ && speed_.y > 0) {
        speed_.y = 0;
    }

}

}
