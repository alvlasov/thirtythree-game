#include "Randomizer.h"

namespace thirtythree {

Randomizer::Randomizer() {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    rand_engine_.seed(seed);
    max_random_number_ = rand_engine_.max();
    LOG_INFO("Randomizer initialized");
}

Randomizer::~Randomizer() {
    LOG_INFO("Randomizer destroyed");
}

float Randomizer::Uniform(float b, float a) {
    if (b < a) {
        float t = a;
        a = b;
        b = t;
    }
    return a + (b - a) * rand_engine_() / (float)max_random_number_;
}

int Randomizer::UniformInt(int b, int a) {
    if (b < a) {
        int t = a;
        a = b;
        b = t;
    }
    return a +  rand_engine_() % ((b - a + 1));
}

sf::Vector2f Randomizer::Direction() {
    sf::Vector2f vect = {pow(-1, UniformInt()) * Uniform(),
                         pow(-1, UniformInt()) * Uniform()};
    return normalize(vect);
}

sf::Color Randomizer::Color() {
    return sf::Color(UniformInt(255), UniformInt(255),
                     UniformInt(255), UniformInt(255));
}

sf::Color Randomizer::ColorOpaque() {
    return sf::Color(UniformInt(255), UniformInt(255),
                     UniformInt(255), 255);
}


}
