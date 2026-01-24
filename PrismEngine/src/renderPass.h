#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"
DECLARE_PGC_LAYER_INSTANCE(L1)
class RenderPass : public L1_Object<RenderPass> {
public:
	void createImpl();
	void cleanupImpl();
private:
	
};
END_NAMESPACE_DECLARATION
