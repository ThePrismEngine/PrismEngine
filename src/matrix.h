#pragma once


#include <stdexcept>
#include "SDL.h"
#include "vector.h"


namespace prism {
	namespace math {
		/// <summary>
		/// Структура PRISM_Matrix_4X4 представляет 4x4 матрицу, которая может быть 
		/// использована для различных линейных преобразований, таких как масштабирование, 
		/// вращение, перенос, а также для работы с однородными координатами.
		/// </summary>
		struct Matrix_4X4
		{
			/// <summary>
			/// Двумерный массив, представляющий элементы матрицы. 
			/// Индексы: m[row][column].
			/// Инициализируется нулями.
			/// </summary>
			float m[4][4] = { 0 };

			/// <summary>
			/// Выводит содержимое матрицы в консоль.
			/// </summary>
			void print();

			/// <summary>
			/// Оператор доступа к строкам матрицы по индексу.
			/// </summary>
			/// <param name="index">Индекс строки (0-3).</param>
			/// <returns>Указатель на строку матрицы.</returns>
			/// <exception cref="std::out_of_range">Бросает исключение, если индекс выходит за пределы [0, 3].</exception>
			float* operator[](int index);

			/// <summary>
			/// Оператор сравнения двух матриц на равенство.
			/// </summary>
			/// <param name="other">Другая матрица для сравнения.</param>
			/// <returns>True, если все элементы матриц равны; иначе False.</returns>
			bool operator==(Matrix_4X4& other);

			/// <summary>
			/// Создает единичную матрицу 4x4.
			/// </summary>
			/// <returns>Единичная матрица.</returns>
			static Matrix_4X4 makeIdentity();

			/// <summary>
			/// Создает матрицу поворота вокруг оси X.
			/// </summary>
			/// <param name="fAngleRad">Угол поворота в радианах.</param>
			/// <returns>Матрица поворота вокруг оси X.</returns>
			static Matrix_4X4 makeRotationX(float fAngleRad);

			/// <summary>
			/// Создает матрицу поворота вокруг оси Y.
			/// </summary>
			/// <param name="fAngleRad">Угол поворота в радианах.</param>
			/// <returns>Матрица поворота вокруг оси Y.</returns>
			static Matrix_4X4 makeRotationY(float fAngleRad);

			/// <summary>
			/// Создает матрицу поворота вокруг оси Z.
			/// </summary>
			/// <param name="fAngleRad">Угол поворота в радианах.</param>
			/// <returns>Матрица поворота вокруг оси Z.</returns>
			static Matrix_4X4 makeRotationZ(float fAngleRad);

			/// <summary>
			/// Создает матрицу переноса.
			/// </summary>
			/// <param name="x">Смещение по оси X.</param>
			/// <param name="y">Смещение по оси Y.</param>
			/// <param name="z">Смещение по оси Z.</param>
			/// <returns>Матрица переноса.</returns>
			static Matrix_4X4 makeTranslation(float x, float y, float z);

			/// <summary>
			/// Создает матрицу масштабирования.
			/// </summary>
			/// <param name="x">Масштабирование по оси X.</param>
			/// <param name="y">Масштабирование по оси Y.</param>
			/// <param name="z">Масштабирование по оси Z.</param>
			/// <returns>Матрица масштабирования.</returns>
			static Matrix_4X4 makeScale(float x, float y, float z);

			/// <summary>
			/// Создает матрицу проекции.
			/// </summary>
			/// <param name="fFovDegrees">Угол обзора в градусах.</param>
			/// <param name="fAspectRatio">Соотношение сторон экрана.</param>
			/// <param name="fNear">Ближняя плоскость отсечения.</param>
			/// <param name="fFar">Дальняя плоскость отсечения.</param>
			/// <returns>Матрица проекции.</returns>
			static Matrix_4X4 makeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);

			/// <summary>
			/// Создает матрицу, указывающую из одной точки в другую.
			/// </summary>
			/// <param name="pos">Начальная точка.</param>
			/// <param name="target">Целевая точка.</param>
			/// <param name="up">Вектор "вверх".</param>
			/// <returns>Матрица направления.</returns>
			static Matrix_4X4 Matrix_PointAt(Vector3d& pos, Vector3d& target, Vector3d& up);
		};

		/// <summary>
		/// Умножает две матрицы 4x4.
		/// </summary>
		/// <param name="m1">Первая матрица.</param>
		/// <param name="m2">Вторая матрица.</param>
		/// <returns>Результирующая матрица.</returns>
		static Matrix_4X4 Matrix_MultiplyMatrix(Matrix_4X4& m1, Matrix_4X4& m2);
		
		/// <summary>
		/// Быстрое обратное преобразование матрицы 4x4.
		/// </summary>
		/// <param name="m">Матрица для инверсии.</param>
		/// <returns>Инверсированная матрица.</returns>
		static Matrix_4X4 Matrix_QuickInverse(Matrix_4X4& m);

	}
}