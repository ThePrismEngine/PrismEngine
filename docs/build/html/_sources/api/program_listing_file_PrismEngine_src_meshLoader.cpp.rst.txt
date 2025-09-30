
.. _program_listing_file_PrismEngine_src_meshLoader.cpp:

Program Listing for File meshLoader.cpp
=======================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_meshLoader.cpp>` (``PrismEngine\src\meshLoader.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "meshLoader.h"
   #include <unordered_map>
   #include <tiny_obj_loader.h>
   
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
   
               vertex.texCoord = {
                   attrib.texcoords[2 * index.texcoord_index + 0],
                   1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
               };
   
               vertex.color = { attrib.colors[3 * index.vertex_index + 0],
                                attrib.colors[3 * index.vertex_index + 1],
                                attrib.colors[3 * index.vertex_index + 2]};
   
               if (uniqueVertices.count(vertex) == 0) {
                   uniqueVertices[vertex] = static_cast<uint32_t>(meshData.vertices.size());
                   meshData.vertices.push_back(vertex);
               }
   
               meshData.indices.push_back(uniqueVertices[vertex]);
           }
       }
   
       return meshData;
   }
