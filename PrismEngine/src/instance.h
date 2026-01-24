#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"

DECLARE_PGC_LAYER_INSTANCE(L1)

class Instance : public L1_Object<Instance> {
public:
	void createImpl();
	void cleanupImpl();
	
private:
	std::vector<const char*> getRequiredExtensions();	
};

END_NAMESPACE_DECLARATION