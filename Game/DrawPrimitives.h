#ifndef DRAWPRIMITIVES_H_INCLUDED
#define DRAWPRIMITIVES_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace thirtythree {

void DrawCircle(sf::Vector2f pos, float radius, sf::Color fillColor, sf::Color outlineColor, sf::RenderTarget* screen);

}
#endif // DRAWPRIMITIVES_H_INCLUDED
