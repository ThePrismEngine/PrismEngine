#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"

DECLARE_PGC_LAYER_INSTANCE(L1)

class Surface : public L1_Object<Surface> {
public:
	void createImpl();
	void cleanupImpl();

private:
	
};

END_NAMESPACE_DECLARATION