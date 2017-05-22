#ifndef DRAWER_H_INCLUDED
#define DRAWER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "GameObjects\GameObject.h"
#include "Logger.h"
#include "Engine/QuadTree.h"


namespace thirtythree {

class Drawer {
public:

    struct Text {

        Text(const std::string &ntext, int nsize, sf::Vector2f npos,
             sf::Color ncolor = sf::Color::Black, bool norigin_centering =  false,
             bool ndraw_to_map = false)
            : text (ntext),
              size (nsize),
              pos (npos),
              color(ncolor),
              origin_centering (norigin_centering),
              draw_to_map (ndraw_to_map) {}

        Text(const std::string &ntext, int nsize, sf::Vector2f npos,
             bool norigin_centering, bool ndraw_to_map = false)
            : Text(ntext, nsize, npos, sf::Color::Black, norigin_centering, ndraw_to_map) {}

        std::string text;
        int size;
        sf::Vector2f pos;
        sf::Color color;
        bool origin_centering;
        bool draw_to_map;
    };


    Drawer(sf::VideoMode mode, const sf::String name, sf::Vector2i map_size);
    ~Drawer();

    void ClearMap() { map_.clear(map_background_color_); }

    void DrawObject(GameObject &obj) { obj.Draw(map_); }

    void DisplayMap() { map_.display(); }

    void ClearWindow() { window_.clear(window_background_color_); }

    void DrawMap();

    void DisplayWindow() { window_.display(); }

    void ZoomWindow(int ticks) { view_.zoom(1 - (ticks * 0.05)); }

    void ResizeWindow(int width, int height);

    void DrawText(Text txt);

    bool WindowIsOpen() { return window_.isOpen(); }

    bool PollEvent(sf::Event &event) { return window_.pollEvent(event); }

    void CloseWindow() { window_.close(); }

    void SetViewCenter(sf::Vector2f pos) { view_.setCenter(pos); }

    void VisualizeQuadTree(QuadTree &tree, sf::Color color = sf::Color::Blue);

    //! Возвращает размер карты
    sf::Vector2f GetMapSize() { return (sf::Vector2f)map_.getSize(); }

    //! Возвращает размер окна
    sf::Vector2f GetWindowSize() { return (sf::Vector2f)window_.getSize(); }

    //! Возвращает указатель на окно
    sf::RenderWindow* GetWindow() { return &window_; }

private:

    sf::Color map_background_color_ = sf::Color::White;
    sf::Color window_background_color_ = sf::Color(222, 222, 222);

    //! Окно, в которое производится отрисовка
    sf::RenderWindow window_;

    //! Игровая карта
    sf::RenderTexture map_;

    //! Камера для перемещения по игровой карте
    sf::View view_;

    //! Камера для вывода на экран интерфейса
    sf::View default_view_;

    //! Шрифт для отрисовки надписей
    sf::Font font_;

};

}

#endif // DRAWER_H_INCLUDED
