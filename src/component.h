#pragma once
#include <cstdint>

namespace prism {
	namespace world {
		typedef uint32_t ComponentType;
		const ComponentType INVALID_COMPONENT_TYPE = 0;

		struct IComponent {
			virtual ~IComponent() = default;
		};
	}
}