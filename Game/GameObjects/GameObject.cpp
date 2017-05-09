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

void GameObject::SetTexture(const std::string &texturename) {
    if (!texture_.loadFromFile(texturename)) {
        LOG_ERROR("Failed to load texture: " << texturename);
    } else {
        texture_.setSmooth(true);
        auto alpha = color_.a;
        color_ = sf::Color::White;
        color_.a = alpha;
        body_.setTexture(&texture_);
    }
}

void GameObject::Draw(sf::RenderTarget &screen) {
    body_.setRadius(radius_);
    body_.setFillColor(color_);
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

void GameObject::Logic(const sf::Vector2u &map_size) {
    if (pos_.x <= radius_ || pos_.x >= map_size.x - radius_) {
        speed_.x *= -1;
    }
    if (pos_.y <= radius_ || pos_.y >= map_size.y - radius_) {
        speed_.y *= -1;
    }
}

void GameObject::Kill() {
    dead_ = true;
    LOG_INFO("Object " << GetType() << " died");
}

}
