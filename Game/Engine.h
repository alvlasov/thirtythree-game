/*!
    @file Engine.h
    @brief Класс игрового движка
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <vector>
#include <memory>
#include <string>
#include <limits>


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

    typedef std::vector<std::shared_ptr<GameObject>>::iterator obj_iterator;

    //! Инициализация движка
    Engine(Drawer *drawer, GameLogic *logic, QuadTree *tree);

    //! Добавление игрового объекта в движок
    void AddObject(GameObject *object);

    //! Инициализация игрового процесса
    void StartGame();

    //! Возвращает текущее число игровых объектов
    size_t GetObjectsCount() { return objects_.size(); }
    size_t GetObjectsLimit() { return max_object_number_; }

    //! Возвращает размер карты
    sf::Vector2f GetMapSize() { return drawer_->GetMapSize(); }

    //! Возвращает размер окна
    sf::Vector2f GetWindowSize() { return drawer_->GetWindowSize(); }

    //! Возвращает указатель на окно
    sf::RenderWindow* GetWindow() { return drawer_->GetWindow(); }

private:

    //! Максимальное число объектов, обрабатываемых движком
    static const int max_object_number_ = 1000;
    static const int obj_interaction_distance_ = 1300;
    int id_counter = 0;

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

    inline bool Collision(GameObject &obj1, GameObject &obj2, float distance) {
        auto radius1 = obj1.GetRadius();
        auto radius2 = obj2.GetRadius();
        if (distance <= std::max(radius1, radius2)) {
            return true;
        }
        return false;
    }

    void DrawUI();
    void DrawDebugInfo();

    //! Хранилище игровых объектов
    std::vector<std::shared_ptr<GameObject>> objects_;

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

    bool game_over_ = false;

    bool paused_ = false;


};

}

#endif // ENGINE_H_INCLUDED
