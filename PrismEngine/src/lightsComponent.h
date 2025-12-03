#pragma once
#include "transformComponent.h"

namespace prism {
	namespace scene {
		using ColorRGB = Position;

		struct PointLightComponent
		{
			alignas(16) Position pos;
			alignas(16) ColorRGB color;
			alignas(4) float intensity;
			alignas(4) float radius;
		};

		struct DirectionalLightComponents {
			alignas(16) Position direction;
			alignas(16) ColorRGB color;
			alignas(4) float intensity;
		};
	}
}