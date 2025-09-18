#pragma once
#include "mesh.h"
#include "utils.h"
#include <string>

namespace prism {
	namespace PGC {
		class MeshManager
		{
		public:
			static prism::Mesh addMesh(utils::Context* context, std::string texturePath);
			static void update(utils::Context* context);
			static void clear(utils::Context* context);
			static prism::PGC::Mesh& getMeshInfo(utils::Context* context, prism::Mesh id);
		private:
			static uint32_t getNextAvailableIndex(utils::Context* context);
		};
	}
}
