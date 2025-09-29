#pragma once

namespace prism {
	namespace scene {
		struct Position {
			float x, y, z;
		};

		struct Rotation {
			float x, y, z;
		};

		struct Scale {
			float x, y, z;
		};

		struct TransformComponent
		{
			Position pos;
			Rotation rot;
			Scale scale;
		};
	}
}