#pragma once

namespace prism {
	namespace render {
		struct VertexPosVector2d
		{
			float x, y;
		};
		struct Color
		{
			float r, g, b;
		};
		struct Vertex
		{
			VertexPosVector2d pos;
			Color color;
		};
	}
}