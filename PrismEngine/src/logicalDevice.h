#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"

DECLARE_PGC_LAYER_INSTANCE(L1)

class LogicalDevice : public L1_Object<LogicalDevice> {
public:
	void createImpl();
	void cleanupImpl();

private:
};

END_NAMESPACE_DECLARATION