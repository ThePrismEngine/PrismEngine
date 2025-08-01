#pragma once
#include "vulkan/vulkan.h"
#include "configs.h"
#include "utils.h"

namespace prism {
	namespace PGC {
		struct DeviceScore {
			int typeScore = 0;
			int featureScore = 0;
			int hardwareScore = 0;
			int apiScore = 0;
		};

		struct FeatureScores {
			float swapchain = 0.0f;		
			float raytracing = 0.0f;      // RT поддержка
			float upscaling = 0.0f;        // DLSS/FSR
			float advancedFeatures = 0.0f; // Доп. возможности

			
		};

		struct HardwareScore {
			float vramGB = 0.0f;
			float shaderCores = 0.0f;
			float clockSpeedGHz = 0.0f;
			float textureUnits = 0.0f;

			// Весовые коэффициенты для расчета оценки
			const float VRAM_WEIGHT = 0.5f;
			const float SHADER_CORES_WEIGHT = 0.3f;
			const float CLOCK_SPEED_WEIGHT = 0.2f;

			// Референсные значения для нормализации
			const float REFERENCE_VRAM_GB = 16.0f;    // 16GB считается "идеальным" объемом
			const float REFERENCE_SHADER_CORES = 10.0f; // 10 ядер как опорная точка
			const float REFERENCE_CLOCK_SPEED_GHZ = 3.0f; // 3GHz как опорная частота
		};

		class ScoreWrapper {
		public:
			static void print(DeviceScore score);
			static void print(FeatureScores score);
			static void print(HardwareScore score);

			static int getTotal(DeviceScore score);
			static int getTotal(FeatureScores score);
			static int getTotal(HardwareScore score);
		};

		class DeviceRater {
		public:
			int rate(VkPhysicalDevice device, PGC::utils::CoreContext* context, utils::CoreSettings* settings);
		private:
			bool debugDeviceSelection = false;
			int getDeviceTypeScore(VkPhysicalDevice device);
			int getDeviceFeatureScore(VkPhysicalDevice device);
			int getDeviceHardwareScore(VkPhysicalDevice device);
			int getDeviceApiScore(VkPhysicalDevice device);

			static FeatureScores calculateFeatureScore(VkPhysicalDevice device);
		};
	}
}