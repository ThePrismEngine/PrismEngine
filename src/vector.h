#pragma once


#include <stdexcept>
#include "SDL.h"


namespace prism {

	namespace math {
		/// <summary>
	/// Структура PRISM_Vector3d предназначена для представления 
	/// трёхмерного вектора с дополнительным четвёртым компонентом (w).
	/// Четвёртая компонента используется для различных операций, 
	/// таких как преобразования в однородных координатах 
	/// </summary>
	/// <remarks>
	/// Поля структуры:
	/// - x: координата по оси X.
	/// - y: координата по оси Y.
	/// - z: координата по оси Z.
	/// - w: четвёртая координата, используемая, например, для представления 
	/// веса точки в проекционных преобразованиях или для перехода 
	/// от однородных координат к обычным. По умолчанию равна 1.
	/// </remarks>
		struct Vector3d
		{
			/// <summary>
			/// Координата вектора по оси X.
			/// </summary>
			float x;


			/// <summary>
			/// Координата вектора по оси Y.
			/// </summary>
			float y;


			/// <summary>
			/// Координата вектора по оси Z.
			/// </summary>
			float z;


			/// <summary>
			/// Четвёртая координата (w). 
			/// Используется для преобразований в однородных координатах 
			/// или для работы с весами точек. По умолчанию равна 1.0.
			/// </summary>
			float w = 1.0;


			/// <summary>
			/// Конструктор по умолчанию. Инициализирует все координаты нулями, 
			/// а w — единицей.
			/// </summary>
			Vector3d() : x(0), y(0), z(0), w(1) {}

			/// <summary>
			/// Конструктор для инициализации всех координат.
			/// </summary>
			/// <param name="x">Значение координаты X.</param>
			/// <param name="y">Значение координаты Y.</param>
			/// <param name="z">Значение координаты Z.</param>
			/// <param name="w">Значение четвёртой координаты (w). По умолчанию равно 1.0.</param>
			Vector3d(float x, float y, float z, float w = 1.0f) : x(x), y(y), z(z), w(w) {}

			/// <summary>
			/// Выводит значения координат вектора в консоль.
			/// </summary>
			void print();

			/// <summary>
			/// Оператор сложения двух векторов.
			/// </summary>
			/// <param name="other">Другой вектор для сложения.</param>
			/// <returns>Результат сложения как новый вектор.</returns>
			Vector3d operator+(Vector3d& other);

			/// <summary>
			/// Оператор вычитания двух векторов.
			/// </summary>
			/// <param name="other">Другой вектор для вычитания.</param>
			/// <returns>Результат вычитания как новый вектор.</returns>
			Vector3d operator-(Vector3d& other);

			/// <summary>
			/// Оператор умножения вектора на скаляр.
			/// </summary>
			/// <param name="k">Скалярное значение для умножения.</param>
			/// <returns>Результат умножения как новый вектор.</returns>
			Vector3d operator*(float k);

			/// <summary>
			/// Оператор деления вектора на скаляр.
			/// </summary>
			/// <param name="k">Скалярное значение для деления.</param>
			/// <returns>Результат деления как новый вектор.</returns>
			/// <exception cref="std::invalid_argument">Бросает исключение, если k = 0.</exception>
			Vector3d operator/(float k);

			/// <summary>
				/// Оператор доступа к координатам по индексу.
				/// </summary>
				/// <param name="index">Индекс координаты (0 для X, 1 для Y, 2 для Z, 3 для W).</param>
				/// <returns>Значение координаты по индексу.</returns>
				/// <exception cref="std::out_of_range">Бросает исключение, если индекс выходит за пределы [0, 3].</exception>
			float operator[](int index);

			/// <summary>
			/// Оператор сравнения двух векторов на равенство.
			/// </summary>
			/// <param name="other">Другой вектор для сравнения.</param>
			/// <returns>True, если все координаты совпадают (кроме w); иначе False.</returns>
			bool operator==(Vector3d& other);


			float length();
			Vector3d normalise();
		};
		float Vector_DotProduct(Vector3d& v1, Vector3d& v2);
		Vector3d Vector_CrossProduct(Vector3d& v1, Vector3d& v2);
		Vector3d Vector_IntersectPlane(Vector3d& plane_p, Vector3d& plane_n, Vector3d& lineStart, Vector3d& lineEnd);
	}
}
