/*!
    @file Utility.h
    @brief Служебные функции
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <cmath>

namespace thirtythree {

//! Шаблон функции, возвращающей длину вектора
template <typename T>
float length(const sf::Vector2<T> &v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

//! Шаблон функции, возвращающей нормированный на единицу вектор
template <typename T>
sf::Vector2<T> normalize(const sf::Vector2<T> &v) {
    float len = length(v);
    if (len != 0) {
        return sf::Vector2<T>(v.x / len, v.y / len);
    } else {
        return v;
    }
}

}

#endif // UTILITY_H_INCLUDED
