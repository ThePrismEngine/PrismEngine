#pragma once
#include <cstdint>

namespace prism {
	namespace scene {
		typedef uint32_t ComponentType;
		const ComponentType INVALID_COMPONENT_TYPE = 0;

		struct IComponent {
			virtual ~IComponent() = default;
		};
	}
}