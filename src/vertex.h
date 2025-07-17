#pragma once
#include <vulkan/vulkan_core.h>
#include <array>
#include "matrix.h"
#include "glm.hpp"



namespace prism {
	namespace render {
		struct VertexPosVector2d
		{
			float x, y;
		};
		struct Color
		{
			float r, g, b;
		};
		struct Vertex
		{
			glm::vec3 pos;
			glm::vec3 color;
			glm::vec2 texCoord;

			static VkVertexInputBindingDescription getBindingDescription();

			static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();

			bool operator==(const Vertex& other) const;
		};

		// Отдельный функтор для хеширования
		struct VertexHasher {
			size_t operator()(const Vertex& v) const noexcept;
		};

		struct UniformBufferObject {
			///prism::math::Matrix4X4 model;
			///prism::math::Matrix4X4 view;
			///prism::math::Matrix4X4 proj;
			alignas(16) glm::mat4 model;
			alignas(16) glm::mat4 view;
			alignas(16) glm::mat4 proj;
		};
	}
}