#pragma once

namespace prism {
	namespace ECS {
		struct Position {
			float x, y, z;
		};

		struct Rotation {
			float x, y, z;
		};

		struct Scale {
			float x, y;
		};

		struct TransformComponent
		{
			Position pos;
			Rotation rot;
			Scale scale;
		};
	}
}