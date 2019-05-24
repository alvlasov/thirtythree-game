/*!
    @file GameObjects\GameObject.cpp
    @brief Базовый класс игрового объекта
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/


#include "GameObject.h"

namespace thirtythree {

GameObject::GameObject()
    : pos_      (sf::Vector2f()),
      speed_    (sf::Vector2f()),
      friction_ (0),
      radius_   (1),
      color_    (sf::Color::White) {}

GameObject::GameObject(const sf::Vector2f& pos, float radius,
                       const sf::Color &color, const sf::Vector2f& speed,
                       float friction)
    : pos_       (pos),
      speed_     (speed),
      friction_  (friction),
      radius_    (radius),
      color_     (color) {}

GameObject::~GameObject() {}

void GameObject::SetTexture(sf::Texture *texture) {
    if (texture == nullptr) return;
    texture_ = texture;
    auto alpha = color_.a;
    color_ = sf::Color::White;
    color_.a = alpha;
    body_.setTexture(texture_);
}

float GameObject::GetMaxSpeed() {
    return 200 * sqrt(30 / radius_);
}

void GameObject::Logic() {
    speed_ = normalize(speed_) * GetMaxSpeed();
}

void GameObject::Draw(sf::RenderTarget &screen) {
    body_.setRadius(radius_);
    body_.setFillColor(color_);
//    body_.setOutlineColor(color_ - sf::Color(25, 25, 25, 0));
//    body_.setOutlineThickness(-4);
    body_.setOrigin(radius_, radius_);
    body_.setPosition(pos_.x, pos_.y);
    screen.draw(body_);
}

void GameObject::Move(float dt) {
    speed_.x *= 1 - friction_;
    speed_.y *= 1 - friction_;
    pos_.x += speed_.x * dt;
    pos_.y += speed_.y * dt;
}

void GameObject::Kill() {
    dead_ = true;
    LOG_DEBUG("Object " << GetType() << " died");
}

}
