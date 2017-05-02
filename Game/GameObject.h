#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

namespace thirtythree
{
    enum ObjectType {ABSTRACT};

    class GameObject
    {
    public:

        GameObject():
            pos_      (sf::Vector2f()),
            speed_    (sf::Vector2f()),
            size_     (sf::Vector2f()),
            mass_     (0),
            friction_ (0),
            rotation_ (0),
            sprite_   (sf::Sprite())
            {
                auto bounds = sprite_.getLocalBounds();
                size_.x = bounds.width;
                size_.y = bounds.height;
            }

        GameObject(const sf::Vector2f& pos,
                   const sf::Vector2f& speed,
                   float mass = 0,
                   float friction = 0,
                   float rotation = 0,
                   sf::Sprite sprite = sf::Sprite()) :
            pos_      (pos),
            speed_    (speed),
            size_     (sf::Vector2f()),
            mass_     (mass),
            friction_ (friction),
            rotation_ (rotation),
            sprite_   (sprite)

        {
            auto bounds = sprite_.getLocalBounds();
            size_.x = bounds.width;
            size_.y = bounds.height;
        }

        virtual void Draw();
        virtual void Move() = 0;
        virtual void ~GameObject() = 0;

        virtual ObjectType GetType() { return ABSTRACT; }

    private:

        sf::Vector2f pos_;
        sf::Vector2f speed_;
        sf::Vector2f size_;

        float mass_;
        float friction_;
        float rotation_;

        sf::Sprite sprite_;

    }
}

#endif // GAMEOBJECT_H_INCLUDED
