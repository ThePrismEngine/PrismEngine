/**
 * @file vector.h
 * @brief 3D вектор и операции с ним
 */

#pragma once
#include <stdexcept>
#include "SDL.h"

namespace prism {
    namespace math {

        /**
         * @brief 3D вектор с дополнительной компонентой w
         * @details Используется для однородных координат и 3D преобразований
         */
        struct Vector3d {
            float x; ///< Координата X
            float y; ///< Координата Y
            float z; ///< Координата Z
            float w = 1.0f; ///< Однородная координата (по умолчанию 1.0)

            /**
             * @brief Конструктор по умолчанию (нулевой вектор)
             */
            Vector3d() : x(0), y(0), z(0), w(1) {}

            /**
             * @brief Конструктор с параметрами
             * @param x Координата X
             * @param y Координата Y
             * @param z Координата Z
             * @param w Однородная координата (опционально)
             */
            Vector3d(float x, float y, float z, float w = 1.0f) : x(x), y(y), z(z), w(w) {}

            /**
             * @brief Вывод вектора в консоль
             */
            void print();

            /**
             * @brief Сложение векторов
             * @param other Второй вектор
             * @return Результат сложения
             */
            Vector3d operator+(Vector3d& other);

            /**
             * @brief Вычитание векторов
             * @param other Второй вектор
             * @return Результат вычитания
             */
            Vector3d operator-(Vector3d& other);

            /**
             * @brief Умножение на скаляр
             * @param k Скаляр
             * @return Результат умножения
             */
            Vector3d operator*(float k);

            /**
             * @brief Деление на скаляр
             * @param k Скаляр (не должен быть 0)
             * @return Результат деления
             * @throws std::invalid_argument Если k = 0
             */
            Vector3d operator/(float k);

            /**
             * @brief Доступ к компонентам по индексу
             * @param index 0-X, 1-Y, 2-Z, 3-W
             * @return Значение компоненты
             * @throws std::out_of_range При неверном индексе
             */
            float operator[](int index);

            /**
             * @brief Сравнение векторов
             * @param other Второй вектор
             * @return true если векторы равны (w не учитывается)
             */
            bool operator==(Vector3d& other);

            /**
             * @brief Вычисление длины вектора
             * @return Длина вектора
             */
            float length();

            /**
             * @brief Нормализация вектора
             * @return Нормализованный вектор
             */
            Vector3d normalise();
        };

        /**
         * @brief Скалярное произведение векторов
         * @param v1 Первый вектор
         * @param v2 Второй вектор
         * @return Результат скалярного произведения
         */
        float Vector_DotProduct(Vector3d& v1, Vector3d& v2);

        /**
         * @brief Векторное произведение
         * @param v1 Первый вектор
         * @param v2 Второй вектор
         * @return Вектор-результат
         */
        Vector3d Vector_CrossProduct(Vector3d& v1, Vector3d& v2);

        /**
         * @brief Пересечение плоскости и линии
         * @param plane_p Точка на плоскости
         * @param plane_n Нормаль плоскости
         * @param lineStart Начало линии
         * @param lineEnd Конец линии
         * @return Точка пересечения
         */
        Vector3d Vector_IntersectPlane(Vector3d& plane_p, Vector3d& plane_n, Vector3d& lineStart, Vector3d& lineEnd);

    } // namespace math
} // namespace prism