#pragma once
#include <cstdint>

namespace prism {
	namespace scene {
		/// @brief Идентификатор сущности
		/// @details Уникальный числовой идентификатор для обращения к сущности в системе
		typedef uint32_t Entity;

		/// @brief Неверный идентификатор сущности
		/// @details Используется для обозначения отсутствующей или невалидной сущности
		const Entity INVALID_ENTITY_ID = 0;
	}
}