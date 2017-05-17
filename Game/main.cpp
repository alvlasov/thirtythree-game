#include "Engine.h"

int main() {
    thirtythree::Engine engine(sf::VideoMode(1024, 600), "Game33", {3000, 3000});
    engine.StartGame();
    return 0;
}
