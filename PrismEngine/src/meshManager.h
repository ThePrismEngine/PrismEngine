#pragma once
#include <string>
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"
#include "mesh.h"
#include "meshLoader.h"

DECLARE_PGC_LAYER_INSTANCE(L1)
class MeshManager : public L1_Object<MeshManager> {
public:
	void createImpl();
	prism::Mesh addMesh(std::string texturePath);
	void update();
	void clear();
	void cleanupImpl();
	prism::PGC::Mesh& getMeshInfo(prism::Mesh id);
private:
	uint32_t getNextAvailableIndex();
	PGC::L2::MeshLoader* meshLoader;
};
END_NAMESPACE_DECLARATION