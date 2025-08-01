#pragma once

namespace prism {
	namespace PGC {
		struct DeviceEvaluationWeightsSettings {
			float wType = 0.3;
			float wFeatures = 0.25;
			float wHardware = 0.35;
			float wApi = 0.1;
		};
	}
}