#pragma once
#include <vector>
#include "vertex.h"

namespace prism {
	namespace PGC {
		struct MeshData {
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
		};

		class MeshLoader
		{
		public:
			static MeshData load(std::string texturePath);
		private:

		};
	}
}