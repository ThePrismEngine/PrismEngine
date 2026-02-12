#pragma once
#include <vector>
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"
#include "utils.h"
#include "vertex.h"
#include "meshData.h"


DECLARE_PGC_LAYER_INSTANCE(L2)
class MeshLoader : public L2_Object<MeshLoader> {
public:
	MeshLoader(PGC::utils::Context* context, PGC::utils::Settings* settings) : L2_Object(context, settings) {};
	static MeshData load(std::string texturePath);
};
END_NAMESPACE_DECLARATION