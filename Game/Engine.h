/*!
    @file Engine.h
    @brief Класс игрового движка
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <vector>
#include <memory>
#include <string>
#include <limits>

#include <SFML/Graphics.hpp>

#include "GameObjects\GameObject.h"
#include "Drawer.h"
#include "Logger.h"
#include "GameLogic.h"
#include "Randomizer.h"
#include "Utility.h"
#include "Engine/QuadTree.h"

namespace thirtythree {

class Engine {
public:

    //! Инициализация движка
    Engine(Drawer *drawer, GameLogic *logic, QuadTree *tree);

    //! Добавление игрового объекта в движок
    void AddObject(GameObject *object);

    //! Инициализация игрового процесса
    void StartGame();

    //! Возвращает текущее число игровых объектов
    size_t GetObjectsCount() { return objects_.size(); }
    size_t GetObjectsLimit() { return kMaxObjectsCount; }

    //! Возвращает размер карты
    sf::Vector2f GetMapSize() { return drawer_->GetMapSize(); }

    //! Возвращает размер окна
    sf::Vector2f GetWindowSize() { return drawer_->GetWindowSize(); }

    //! Возвращает указатель на окно
    sf::RenderWindow* GetWindow() { return drawer_->GetWindow(); }

private:

    //! Максимальное число объектов, обрабатываемых движком
    static const int kMaxObjectsCount = 1000;
    static const int kObjectInteractionDistance = 800;
    int id_counter_ = 0;

    //! Главный игровой цикл
    void GameLoop();
    void RestartGame();

    void HandleEvents();
    void HandleObject(GameObject &obj);
    void HandleBorderCollisions(GameObject &obj);
    void HandleDeadObjects();

    inline float CalculateDistance(GameObject &obj1, GameObject &obj2) {
        return length(obj2.GetPos() - obj1.GetPos());
    }

    inline bool Collision(GameObject &obj1, GameObject &obj2) {
        auto radius1 = obj1.GetRadius();
        auto radius2 = obj2.GetRadius();
        float distance = CalculateDistance(obj1, obj2);
        if (distance <= std::max(radius1, radius2)) {
            return true;
        }
        return false;
    }

    void DrawUI();
    void DrawDebugInfo();

    //! Хранилище игровых объектов
    std::vector<std::unique_ptr<GameObject>> objects_;

    QuadTree *tree_;

    Drawer *drawer_;

    //! Класс, реализующий игровую логику
    GameLogic *logic_;

    //! Время прохождения одного игрового цикла
    float time_;
    sf::Clock clock_;

    //! Вывод отладочной информации
    bool draw_debug_info_ = true;
    int draw_quadtree_ = 0;
    int draw_obj_id_ = 0;

    bool game_over_ = false;
    bool game_paused_ = false;


};

}

#endif // ENGINE_H_INCLUDED
