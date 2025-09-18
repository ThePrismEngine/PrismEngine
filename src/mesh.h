#pragma once
#include <cstdint>

namespace prism {
	typedef uint32_t Mesh;

	namespace PGC {
		struct Mesh
		{
			uint32_t vertexOffset;
			uint32_t indexOffset;
			uint32_t vertexCount;
			uint32_t indexCount;
		};
	}
}