#include "fmath.h"

namespace prism {
	namespace math {
		float degToRad(float degrees) {
			return degrees * (float)M_PI / 180.0f;
		}
	}
}