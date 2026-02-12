#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"

DECLARE_PGC_LAYER_INSTANCE(L1)

class Debug : public L1_Object<Debug> {
public:
	void createImpl();
	void cleanupImpl();

private:
	VkDebugUtilsMessengerEXT debugMessenger;
};

END_NAMESPACE_DECLARATION