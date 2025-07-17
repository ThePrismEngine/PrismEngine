/**
 * @file matrix.h
 * @brief Работа с 4x4 матрицами для 3D преобразований
 */

#pragma once
#include <stdexcept>
#include "SDL.h"
#include "vector.h"

namespace prism {
    namespace math {

        /**
         * @brief 4x4 матрица для линейных преобразований
         * @details Поддерживает операции поворота, масштабирования, переноса, проекции
         */
        struct Matrix4X4 {
            float m[4][4] = { 0 }; ///< Элементы матрицы (строка, столбец)

            /**
             * @brief Выводит матрицу в консоль
             */
            void print();

            /**
             * @brief Доступ к строке матрицы по индексу
             * @param index Индекс строки (0-3)
             * @return Указатель на строку матрицы
             * @throws std::out_of_range При неверном индексе
             */
            float* operator[](int index);

            /**
             * @brief Сравнение матриц на равенство
             * @param other Матрица для сравнения
             * @return true если матрицы равны
             */
            bool operator==(Matrix4X4& other);

            Matrix4X4 getTransposed();

            /**
             * @brief Создает единичную матрицу
             * @return Единичная матрица 4x4
             */
            static Matrix4X4 makeIdentity();

            /**
             * @brief Создает матрицу поворота вокруг оси X
             * @param fAngleRad Угол поворота в радианах
             * @return Матрица поворота вокруг X
             */
            static Matrix4X4 makeRotationX(float fAngleRad);

            /**
             * @brief Создает матрицу поворота вокруг оси Y
             * @param fAngleRad Угол поворота в радианах
             * @return Матрица поворота вокруг Y
             */
            static Matrix4X4 makeRotationY(float fAngleRad);

            /**
             * @brief Создает матрицу поворота вокруг оси Z
             * @param fAngleRad Угол поворота в радианах
             * @return Матрица поворота вокруг Z
             */
            static Matrix4X4 makeRotationZ(float fAngleRad);

            /**
             * @brief Создает матрицу переноса
             * @param x Смещение по X
             * @param y Смещение по Y
             * @param z Смещение по Z
             * @return Матрица переноса
             */
            static Matrix4X4 makeTranslation(float x, float y, float z);

            /**
             * @brief Создает матрицу масштабирования
             * @param x Масштаб по X
             * @param y Масштаб по Y
             * @param z Масштаб по Z
             * @return Матрица масштабирования
             */
            static Matrix4X4 makeScale(float x, float y, float z);

            /**
             * @brief Создает матрицу проекции
             * @param fFovDegrees Угол обзора в градусах
             * @param fAspectRatio Соотношение сторон
             * @param fNear Ближняя плоскость отсечения
             * @param fFar Дальняя плоскость отсечения
             * @return Матрица проекции
             */
            static Matrix4X4 makeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);

            /**
             * @brief Создает матрицу направления "смотрит на"
             * @param pos Позиция наблюдателя
             * @param target Целевая точка
             * @param up Вектор "вверх"
             * @return Матрица направления
             */
            static Matrix4X4 Matrix_PointAt(Vector3d& pos, Vector3d& target, Vector3d& up);
        };

        /**
         * @brief Умножение матриц 4x4
         * @param m1 Первая матрица
         * @param m2 Вторая матрица
         * @return Результат умножения
         */
        static Matrix4X4 Matrix_MultiplyMatrix(Matrix4X4& m1, Matrix4X4& m2);

        /**
         * @brief Быстрое обращение матрицы (специализированное)
         * @param m Матрица для обращения
         * @return Обращенная матрица
         */
        Matrix4X4 Matrix_QuickInverse(Matrix4X4& m);
    } // namespace math
} // namespace prism