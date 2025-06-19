/**
 * @file fmath.h
 * @brief Основные математические функции движка
 */

#pragma once
#include <corecrt_math_defines.h>

namespace prism {
	namespace math {

		/**
		 * @brief Преобразует градусы в радианы
		 * @param degrees Угол в градусах
		 * @return Угол в радианах
		 */
		float degToRad(float degrees);

	} // namespace math
} // namespace prism