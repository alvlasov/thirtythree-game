#ifndef rand_H_INCLUDED
#define rand_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include "GlobalOptions.h"
#include <random>
#include <chrono>
#include <cmath>

namespace thirtythree {

class Randomizer {
public:

    Randomizer();
    ~Randomizer();


    float Uniform(float b = 1, float a = 0);

    int UniformInt(int b = 1, int a = 0);

    sf::Vector2f Direction();

    template <typename T>
    sf::Vector2<T> UniformRect(sf::Vector2<T> b, sf::Vector2<T> a = {0, 0}) {
        return {Uniform(a.x, b.x), Uniform(a.y, b.y)};
    }

    sf::Color Color();

    sf::Color ColorOpaque();

private:

    std::default_random_engine rand_engine_;
    int max_random_number_;
};

}
#endif // rand_H_INCLUDED
