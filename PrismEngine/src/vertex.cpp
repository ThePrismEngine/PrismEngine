#include "vertex.h"
#include <functional>

VkVertexInputBindingDescription prism::PGC::Vertex::getBindingDescription()
{
	VkVertexInputBindingDescription bindingDescription{};

	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(Vertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 3> prism::PGC::Vertex::getAttributeDescriptions()
{
	std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[0].offset = offsetof(Vertex, pos);

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = offsetof(Vertex, color);

	attributeDescriptions[2].binding = 0;
	attributeDescriptions[2].location = 2;
	attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
	attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

	attributeDescriptions[2].binding = 0;
	attributeDescriptions[2].location = 3;
	attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[2].offset = offsetof(Vertex, normal);

	return attributeDescriptions;
}

bool prism::PGC::Vertex::operator==(const Vertex& other)
 const {
	return pos == other.pos && color == other.color && texCoord == other.texCoord;
}

size_t prism::PGC::VertexHasher::operator()(const Vertex& v) const noexcept {
	size_t seed = 0;

	auto hash_combine = [&seed](float value) {
		seed ^= std::hash<float>{}(value)+0x9e3779b9 + (seed << 6) + (seed >> 2);
		};

	hash_combine(v.pos.x);
	hash_combine(v.pos.y);
	hash_combine(v.pos.z);
	hash_combine(v.color.r);
	hash_combine(v.color.g);
	hash_combine(v.color.b);
	hash_combine(v.texCoord.x);
	hash_combine(v.texCoord.y);

	return seed;
}