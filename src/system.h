#pragma once
#include <cstdint>

namespace prism {
	namespace world {
		typedef uint32_t SystemId;

		const SystemId INVALID_SYSTEM_ID = 0;

		class ISystem {
		public:
			virtual ~ISystem() = default;
			virtual void update(float deltaTime) = 0;
			bool enabled = true;
		};
	}
}