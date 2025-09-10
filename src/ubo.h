#pragma once
#include "glm.hpp"
#include <vulkan/vulkan_core.h>


namespace prism {
	namespace PGC {
		struct ObjectUBO {
			alignas(16) glm::mat4 model;
			alignas(16) glm::mat4 normals;
		};

		struct CameraUBO {
			alignas(16) glm::mat4 view;
			alignas(16) glm::mat4 proj;
			alignas(16) glm::mat4 viewProj;
			alignas(16) glm::vec3 cameraPos;
		};

		struct UniformBuffers {
			VkBuffer camera;
			VkDeviceMemory cameraMemory;
			void* cameraMapped;

			VkBuffer object;
			VkDeviceMemory objectMemory;
			void* objectMapped;
		};
	}
}