/**
 * @file fmath.h
 * @brief Основные математические функции движка
 */

#pragma once

#ifdef _WIN32
#include <corecrt_math_defines.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

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
