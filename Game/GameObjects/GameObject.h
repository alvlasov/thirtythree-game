#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "../GlobalOptions.h"
#include "../Utility.h"

extern sf::RenderWindow* Window;

namespace thirtythree {

class GameObject {
public:
    GameObject();

    GameObject(const sf::Vector2f& pos,
               float radius,
               const sf::Color &color = sf::Color::White,
               const sf::Vector2f& speed = {0, 0},
               float friction = 0);

    void SetTexture(const std::string &texturename, const sf::Vector2f& scale = {1, 1});
    virtual void Draw(sf::RenderTarget &screen);
    virtual void Control() {}
    virtual void Logic(const sf::Vector2u &map_size);
    virtual void Move(float dt);

    virtual ~GameObject();

    virtual std::string GetType() { return "ABSTRACT"; }

    void Kill();
    bool IsDead() { return dead_; }
    sf::Vector2f GetPos() { return pos_; }
    sf::Vector2f GetSpeed() { return speed_; }
    float GetRadius() { return radius_; }

protected:

    sf::Vector2f pos_;
    sf::Vector2f speed_;
    sf::Vector2f scale_;

    float friction_;

    float radius_;
    sf::Color color_;

    sf::Texture texture_;
    sf::CircleShape body_;

    bool dead_ = false;
};
}

#endif // GAMEOBJECT_H_INCLUDED
