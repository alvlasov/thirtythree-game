#ifndef TEXTUREPROVIDER_H_INCLUDED
#define TEXTUREPROVIDER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <Windows.h>
#include "Logger.h"
#include "Randomizer.h"

namespace thirtythree {

class TextureProvider {
public:

    TextureProvider(Randomizer *rand)
        : rand_ (rand) {}
    ~TextureProvider() {}

    void LoadPlayerTexturesFromDirectory(std::string directory);
    sf::Texture* GetRandomPlayerTexture();

private:

    std::vector<std::string> GetFileNamesInDirectory(std::string directory);
    std::vector<sf::Texture> player_textures_;
    Randomizer *rand_;

};


}

#endif // TEXTUREPROVIDER_H_INCLUDED
