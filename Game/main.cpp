#include "Engine.h"

int main() {
    thirtythree::Engine engine(sf::VideoMode(1024, 600), "Game33", {2500, 2500});
    engine.StartGame();
    return 0;
}
