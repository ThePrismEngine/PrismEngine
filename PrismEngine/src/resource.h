#pragma once
#include <cstdint>

namespace prism {
	namespace scene {
		/// @brief Идентификатор ресурса
		/// @details Уникальный числовой идентификатор для обращения к ресурса в системе
		typedef uint32_t Resource;

		/// @brief Неверный идентификатор ресурса
		/// @details Используется для обозначения отсутствующего или невалидного ресурса
		const Resource INVALID_RESOURCE_ID = 0;
	}
}