#include "DrawPrimitives.h"

void thirtythree::DrawCircle(sf::Vector2f pos, float radius, sf::Color fillColor, sf::Color outlineColor, sf::RenderTarget* screen)
{
    sf::CircleShape circle;

    circle.setRadius(radius);
    circle.setFillColor(fillColor);

    circle.setOutlineColor(outlineColor);
    if (outlineColor != sf::Color::Transparent)
    {
        circle.setOutlineThickness(3);
    }

    circle.setOrigin(radius, radius);
    circle.setPosition(pos.x, pos.y);

    screen -> draw(circle);
}
