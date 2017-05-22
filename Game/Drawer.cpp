#include "Drawer.h"

namespace thirtythree {


Drawer::Drawer(sf::VideoMode mode, const sf::String name, sf::Vector2i map_size) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window_.create(mode, name, sf::Style::Default, settings);
    window_.setVerticalSyncEnabled(true);
    default_view_ = window_.getDefaultView();
    map_.create(map_size.x, map_size.y);
    map_.setSmooth(true);
    view_.reset(sf::FloatRect(0, 0, mode.width, mode.height));
    if (!font_.loadFromFile("Fonts/default.ttf")) {
        LOG_ERROR("Failed to load font");
        throw std::runtime_error("Failed to load font");
    }

    LOG_INFO("Drawer created: Video mode = " << mode.width << "x" << mode.height <<
             ", Map size = " << map_size.x << "x" << map_size.y);
}

Drawer::~Drawer() {

}

void Drawer::DrawMap() {
    window_.setView(view_);
    window_.draw(sf::Sprite(map_.getTexture()));
}

void Drawer::ResizeWindow(int width, int height) {
    view_.reset(sf::FloatRect(0, 0, width, height));
    default_view_.reset(sf::FloatRect(0, 0, width, height));
}

void Drawer::DrawText(Text txt) {
    sf::Text text(txt.text, font_, txt.size);
    if (txt.origin_centering) {
        auto bounds = text.getGlobalBounds();
        text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }
    text.setPosition(txt.pos.x, txt.pos.y);
    text.setFillColor(txt.color);
    if (txt.draw_to_map) {
        map_.draw(text);
    } else {
        sf::View prev_view = window_.getView();
        window_.setView(default_view_);
        window_.draw(text);
        window_.setView(prev_view);
    }
}

void Drawer::VisualizeQuadTree(QuadTree &tree, sf::Color color) {
    if (tree.IsLeaf()) {
        int line_thickness = 5;
        sf::FloatRect boundary = tree.GetBoundary();
        sf::RectangleShape box;
        box.setSize(sf::Vector2f(boundary.width, boundary.height));
        box.setPosition(sf::Vector2f(boundary.left, boundary.top));
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(color);
        box.setOutlineThickness(-line_thickness);
        map_.draw(box);
        std::string objects_count = std::to_string(tree.GetObjectsCount());
        sf::Vector2f pos(boundary.left + line_thickness * 2,
                         boundary.top + line_thickness * 2);
        DrawText(Drawer::Text(objects_count, 50, pos, color, false, true));
    } else {
        auto children = tree.GetChildren();
        for (auto& child : children) {
            if (child != nullptr) {
                VisualizeQuadTree(*child);
            }
    }
    }
}

}
