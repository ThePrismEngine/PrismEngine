#pragma once
#include <cstdint>

namespace prism {
	namespace scene {
		/// @brief Тип компонента
		/// @details Уникальный идентификатор типа компонента в системе
		typedef uint32_t ComponentType;

		/// @brief Неверный тип компонента
		/// @details Используется для обозначения отсутствующего или невалидного типа компонента
		const ComponentType INVALID_COMPONENT_TYPE = 0;
	}
}