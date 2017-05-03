#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <stdexcept>
#include "DrawPrimitives.h"
#include "GlobalOptions.h"
#include <SFML/Graphics.hpp>

extern sf::RenderWindow* Window;

namespace thirtythree
{
    enum ObjectType {ABSTRACT};

    class GameObject
    {
    public:

        GameObject();

        GameObject(const sf::Vector2f& pos,
                   const sf::Vector2f& speed = {0, 0},
                   const sf::Vector2f& scale = {1, 1},
                   std::string texturename = "",
                   float mass = 0,
                   float friction = 0,
                   float rotation = 0);

        virtual void Draw(sf::RenderTarget* screen = Window);

        virtual void Control() { }
        virtual void Logic();
        virtual void Move(float dt);

        virtual ~GameObject();

        virtual void Intersect(ObjectType type) { }

        virtual ObjectType GetType() { return ABSTRACT; }

        void Kill();
        bool isDead() { return dead_; }

    private:

        sf::Vector2f pos_;
        sf::Vector2f speed_;
        sf::Vector2f size_;
        sf::Vector2f scale_;

        float mass_;
        float friction_;
        float rotation_;

        sf::Sprite sprite_;
        sf::Texture texture_;

        bool dead_ = false;

    };

}

#endif // GAMEOBJECT_H_INCLUDED
