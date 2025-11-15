#pragma once
#include "glm.hpp"
#include <vulkan/vulkan_core.h>
#include "textureComponent.h"


namespace prism {
	namespace PGC {
		struct PointLight {
			alignas(16) glm::vec3 position;
			alignas(16) glm::vec3 color;
			alignas(4) float intensity;
			alignas(4) float radius;
		};

		struct DirectionalLight {
			alignas(16) glm::vec3 direction;
			alignas(16) glm::vec3 color;
			alignas(4) float intensity;
		};

		struct ObjectSSBO {
			alignas(16) glm::mat4 model;
			alignas(16) glm::mat4 normals;
			alignas(4) uint32_t texture;
		};

		struct CameraUBO {
			alignas(16) glm::mat4 view;
			alignas(16) glm::mat4 proj;
			alignas(16) glm::mat4 viewProj;
			alignas(16) glm::vec3 cameraPos;
			alignas(16) glm::vec3 ambientColor;
			alignas(4) float ambientIntensity;
			alignas(4) uint32_t pointLightCount;
			alignas(4) uint32_t directionalLightCount;
		};
		
		struct PointLightsSSBO {
			PointLight lights[];
		};

		struct DirectionalLightsSSBO {
			DirectionalLight lights[];
		};

		struct StorageBuffers {
			VkBuffer object;
			VkDeviceMemory objectMemory;
			void* objectMapped;
			size_t objectBufferSize;
			
			VkBuffer pointLights;
			VkDeviceMemory pointLightsMemory;
			void* pointLightsMapped;
			size_t pointLightsBufferSize;

			VkBuffer directionalLights;
			VkDeviceMemory directionalLightsMemory;
			void* directionalLightsMapped;
			size_t directionalLightsBufferSize;
		};

		struct UniformBuffers {
			VkBuffer camera;
			VkDeviceMemory cameraMemory;
			void* cameraMapped;
		};
	}
}