/*!
    @file Randomizer.h
    @brief Класс, предоставляющий методы для генерации случайных величин
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef RANDOMIZER_H_INCLUDED
#define RANDOMIZER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include "Logger.h"
#include <random>
#include <chrono>
#include <cmath>

namespace thirtythree {

class Randomizer {
public:

    //! Инициализация генератора случайных чисел
    Randomizer();
    ~Randomizer();

    //! Возвращает случайное вещественное число в диапазоне от min(a,b) до max(a,b)
    //! @param b,a Границы диапазона, по умолчанию 1 и 0
    //! @return Случайное вещественное число
    float Uniform(float b = 1, float a = 0);

    //! Возвращает случайное целое число в диапазоне от min(a,b) до max(a,b)
    //! @param b,a Границы диапазона, по умолчанию 1 и 0
    //! @return Случайное целое число
    int UniformInt(int b = 1, int a = 0);

    //! Возвращает вектор случайного направления в 2D пространстве
    //! @return Нормированный вектор случайного направления
    sf::Vector2f Direction();

    //! Возвращает случайную точку в прямоугольнике, заключенном между двумя точками
    //! @param b,a Точки, между которыми заключен прямоугольник, по умолчанию (1,1) и (0,0)
    //! @return Случайная точка
    template <typename T>
    sf::Vector2<T> UniformRect(sf::Vector2<T> b = {1, 1}, sf::Vector2<T> a = {0, 0}) {
        return {Uniform(a.x, b.x), Uniform(a.y, b.y)};
    }

    //! Возвращает случайный цвет со случайной прозрачностью
    //! @return Цвет
    sf::Color Color();

    //! Возвращает непрозрачный случайный цвет
    //! @return Цвет
    sf::Color ColorOpaque();

private:

    //! Генератор случайных чисел
    std::default_random_engine rand_engine_;

    //! Равномерное распределение вещественных чисел на (0, 1)
    std::uniform_real_distribution<float> distribution_;
};

}
#endif // RANDOMIZER_H_INCLUDED
