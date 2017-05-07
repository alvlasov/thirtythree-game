#include "GameObject.h"

namespace thirtythree {

GameObject::GameObject()
    : pos_      (sf::Vector2f()),
      speed_    (sf::Vector2f()),
      size_     (sf::Vector2f()),
      scale_    (sf::Vector2f()),
      mass_     (0),
      friction_ (0),
      rotation_ (0),
      sprite_   (sf::Sprite()) {}

GameObject::GameObject(const sf::Vector2f& pos, const sf::Vector2f& speed,
                       const sf::Vector2f& scale, std::string texturename,
                       float mass, float friction, float rotation)
    : pos_       (pos),
      speed_     (speed),
      scale_     (scale),
      mass_      (mass),
      friction_  (friction),
      rotation_  (rotation) {
    if (texturename != "") {
        if (!texture_.loadFromFile(texturename)) {
            LOG_ERROR("Failed to load texture: " << texturename);
            sprite_ = sf::Sprite();
        } else {
            texture_.setSmooth(true);
            sprite_ = sf::Sprite(texture_);
            sprite_.setScale(scale_);
        }
    }
    auto bounds = sprite_.getGlobalBounds();
    size_ = {bounds.width, bounds.height};
    LOG_INFO("Object " << GetType() << " created on pos (" << pos_.x << ", " << pos_.y << ")");
}

GameObject::~GameObject() {
    LOG_INFO("Object " << GetType() << " destroyed");
}

void GameObject::Draw(sf::RenderTarget* screen) {
    if (sprite_.getTexture()) {
        sprite_.setOrigin(size_.x / 2, size_.y / 2);
        sprite_.setPosition(pos_);
        sprite_.rotate(rotation_);
        screen -> draw(sprite_);
    } else {
        DrawCircle(pos_, 15, sf::Color::White, sf::Color::Transparent, screen);
    }
}

void GameObject::Move(float dt) {
    speed_.x *= 1 - friction_;
    speed_.y *= 1 - friction_;
    pos_.x += speed_.x * dt;
    pos_.y += speed_.y * dt;
}

void GameObject::Logic() {
    auto screen_size = Window -> getSize();

    if (pos_.x < -size_.x || pos_.y < -size_.y || pos_.x > screen_size.x + size_.x ||
        pos_.y > screen_size.y + size_.y) {
        Kill();
    }
}

void GameObject::Kill() {
    dead_ = true;
    LOG_INFO("Object " << GetType() << " died");
}

}
