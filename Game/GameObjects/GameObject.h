/*!
    @file GameObjects\GameObject.h
    @brief Базовый класс игрового объекта
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "Logger.h"
#include "Utility.h"

namespace thirtythree {

enum {
    ABSTRACT = 0,
    PLAYER,
    FOOD,
    ENEMY
};

class GameObject {
public:

    GameObject();
    GameObject(const sf::Vector2f& pos,
               float radius,
               const sf::Color &color = sf::Color::White,
               const sf::Vector2f& speed = {0, 0},
               float friction = 0);
    virtual ~GameObject();

    void SetTexture(const std::string &texturename);
    void SetTexture(sf::Texture *texture);

    virtual void Draw(sf::RenderTarget &screen);
    virtual void Control() {}
    virtual void Logic();
    virtual void Move(float dt);

    virtual int GetType() { return ABSTRACT; }

    void Kill();
    bool IsDead() { return dead_; }
    bool IsInteractable() { return interactable_; }

    sf::Vector2f GetPos() { return pos_; }
    sf::Vector2f GetSpeed() { return speed_; }
    float GetMaxSpeed();
    float GetRadius() { return radius_; }

    void SetPos(sf::Vector2f pos) { pos_ = pos; }
    void SetSpeed(sf::Vector2f speed) { speed_ = speed; }
    void SetRadius(float radius) { radius_ = radius; }
    void AddRadius(float radius) { radius_ += radius; }
    void AddSpeed(sf::Vector2f speed) { speed_ += speed; }
    int GetId() { return id_; }
    void SetId(int id) { id_ = id; }

    sf::FloatRect GetBoundary() { return body_.getGlobalBounds();}

protected:

    sf::Vector2f pos_;
    sf::Vector2f speed_;
    float friction_;

    float radius_;
    sf::Color color_;
    sf::Texture *texture_;
    sf::CircleShape body_;

    bool dead_ = false;
    bool interactable_ = true;

    int id_;
};
}

#endif // GAMEOBJECT_H_INCLUDED
