#pragma once
#include <vector>
#include "layersMacroses.h"
#include "utils.h"
#include "vertex.h"
#include "meshData.h"


DECLARE_PGC_LAYER_INSTANCE(L2)
class MeshLoader {
public:
	MeshLoader(utils::Context* context, utils::Settings* settings) : context(context), settings(settings) {};
	static MeshData load(std::string texturePath);
private:
	utils::Context* context;
	utils::Settings* settings;
};
END_NAMESPACE_DECLARATION