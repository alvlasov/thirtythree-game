#include "Engine.h"
extern sf::RenderWindow* Window = nullptr;

int main() {

    thirtythree::Engine engine(sf::VideoMode(1024, 600), __FILE__, {900, 900});
    engine.StartGame();
    return 0;

}
