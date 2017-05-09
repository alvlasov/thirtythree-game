#include "Engine.h"

int main() {
    thirtythree::Engine engine(sf::VideoMode(1024, 600), "Game33", {900, 900});
    engine.StartGame();
    return 0;
}
