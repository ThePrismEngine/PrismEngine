#include "meshLoader.h"
#include <unordered_map>
#include <tiny_obj_loader.h>
#include <iostream>

prism::PGC::MeshData prism::PGC::MeshLoader::load(std::string texturePath)
{
    MeshData meshData;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, nullptr, &err, texturePath.c_str())) {
        throw std::runtime_error(err);
    }

    std::unordered_map<prism::PGC::Vertex, uint32_t, prism::PGC::VertexHasher> uniqueVertices{};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            if (index.texcoord_index >= 0) {
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                };
            } else {
                vertex.texCoord = { 0.f, 0.f };
            }

            if (!attrib.colors.empty()) {
                vertex.color = { attrib.colors[3 * index.vertex_index + 0],
                            attrib.colors[3 * index.vertex_index + 1],
                            attrib.colors[3 * index.vertex_index + 2] };
            } else {
                vertex.color = { 1.f, 1.f, 1.f };
            }

            if (index.normal_index >= 0 && !attrib.normals.empty()) {
                vertex.normal = { attrib.normals[3 * index.normal_index + 0],
                                  attrib.normals[3 * index.normal_index + 1],
                                  attrib.normals[3 * index.normal_index + 2] };
            } else {
                // TODO: вычисление нормалей
                vertex.normal = { 0.0f, 1.0f, 0.0f };
            }

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(meshData.vertices.size());
                meshData.vertices.push_back(vertex);
            }

            meshData.indices.push_back(uniqueVertices[vertex]);
        }
    }

    return meshData;
}
