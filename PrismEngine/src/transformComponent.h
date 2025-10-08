#pragma once

namespace prism {
	namespace scene {
		struct Position {
			float x=0, y=0, z=0;
		};

		struct Rotation {
			float x=0, y=0, z=0;
		};

		struct Scale {
			float x=1, y=1, z=1;
		};

		struct TransformComponent
		{
			Position pos;
			Rotation rot;
			Scale scale;
		};
	}
}