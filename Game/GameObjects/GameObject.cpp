#include "GameObject.h"

namespace thirtythree {

GameObject::GameObject()
    : pos_      (sf::Vector2f()),
      speed_    (sf::Vector2f()),
      size_     (sf::Vector2f()),
      scale_    (sf::Vector2f()),
      friction_ (0),
      radius_   (1),
      color_    (sf::Color::White),
      sprite_   (sf::Sprite()) {}

GameObject::GameObject(const sf::Vector2f& pos, float radius,
                       const sf::Color &color, const sf::Vector2f& speed,
                       float friction)
    : pos_       (pos),
      speed_     (speed),
      size_      ({radius, radius}),
      friction_  (friction),
      radius_    (radius),
      color_     (color) {
    LOG_INFO("Object " << GetType() << " created on pos (" << pos_.x << ", " << pos_.y << ")");
}

GameObject::~GameObject() {
    LOG_INFO("Object " << GetType() << " destroyed");
}

void GameObject::SetTexture(const std::string &texturename, const sf::Vector2f& scale) {
    scale_ = scale;
    if (!texture_.loadFromFile(texturename)) {
        LOG_ERROR("Failed to load texture: " << texturename);
        sprite_ = sf::Sprite();
    } else {
        texture_.setSmooth(true);
        sprite_ = sf::Sprite(texture_);
        sprite_.setScale(scale_);
        auto bounds = sprite_.getGlobalBounds();
        size_ = {bounds.width, bounds.height};
    }
}

void GameObject::Draw(sf::RenderTarget &screen) {
    if (sprite_.getTexture()) {
        sprite_.setPosition(pos_);
        screen.draw(sprite_);
    } else {
        DrawCircle(pos_, radius_, color_, sf::Color::Transparent, screen);
    }
}

void GameObject::Move(float dt) {
    speed_.x *= 1 - friction_;
    speed_.y *= 1 - friction_;
    pos_.x += speed_.x * dt;
    pos_.y += speed_.y * dt;
}

void GameObject::Logic(const sf::Vector2u &map_size) {
    if (pos_.x <= size_.x / 2 || pos_.x >= map_size.x - size_.x / 2) {
        speed_.x *= -1;
    }
    if (pos_.y <= size_.y / 2 || pos_.y >= map_size.y - size_.y / 2) {
        speed_.y *= -1;
    }
}

void GameObject::Kill() {
    dead_ = true;
    LOG_INFO("Object " << GetType() << " died");
}

}
