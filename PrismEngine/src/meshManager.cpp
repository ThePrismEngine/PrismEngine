#include "meshManager.h"
#include "meshLoader.h"
#include "bufferWrapper.h"

prism::Mesh prism::PGC::MeshManager::addMesh(utils::Context* context, std::string texturePath)
{
    prism::PGC::MeshData mesh = MeshLoader::load(texturePath);

  //if (vertices.empty() || indices.empty()) {
  //    return INVALID_MESH_ID;
  //}

    Mesh info;
    info.vertexOffset = static_cast<uint32_t>(context->allVertices.size());
    info.vertexCount = static_cast<uint32_t>(mesh.vertices.size());
    info.indexOffset = static_cast<uint32_t>(context->allIndices.size());
    info.indexCount = static_cast<uint32_t>(mesh.indices.size());

    context->allVertices.insert(context->allVertices.end(), mesh.vertices.begin(), mesh.vertices.end());
    context->allIndices.insert(context->allIndices.end(), mesh.indices.begin(), mesh.indices.end());

    prism::Mesh id = getNextAvailableIndex(context);
    if (id >= context->meshes.size()) {
        context->meshes.push_back(info);
    }
    else {
        context->meshes[id] = info;
    }

    context->meshBuffersDirty = true;
    return id;
}

void prism::PGC::MeshManager::update(utils::Context* context)
{
    if (!context->meshBuffersDirty) return;

    // Освобождаем старые буферы если они существуют
    if (context->vertexBuffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(context->device, context->vertexBuffer, nullptr);
        context->vertexBuffer = VK_NULL_HANDLE;
    }

    if (context->vertexBufferMemory != VK_NULL_HANDLE) {
        vkFreeMemory(context->device, context->vertexBufferMemory, nullptr);
        context->vertexBufferMemory = VK_NULL_HANDLE;
    }

    if (context->indexBuffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(context->device, context->indexBuffer, nullptr);
        context->indexBuffer = VK_NULL_HANDLE;
    }
    if (context->indexBufferMemory != VK_NULL_HANDLE) {
        vkFreeMemory(context->device, context->indexBufferMemory, nullptr);
        context->indexBufferMemory = VK_NULL_HANDLE;
    }
    
    // Создаем новые буферы с актуальными данными
    if (!context->allVertices.empty()) {
        PGC::L3::BufferWrapper::createVertexBuffer(context);
    }
    if (!context->allIndices.empty()) {
        PGC::L3::BufferWrapper::createIndexBuffer(context);
    }

    context->meshBuffersDirty = false;
}

void prism::PGC::MeshManager::clear(utils::Context* context)
{
    context->meshes.clear();
    context->allVertices.clear();
    context->allIndices.clear();
    context->freeMeshIndices.clear();

    context->meshBuffersDirty = true;
}

prism::PGC::Mesh& prism::PGC::MeshManager::getMeshInfo(utils::Context* context, prism::Mesh id)
{
    static Mesh emptyInfo = { 0, 0, 0, 0 };

    if (id < context->meshes.size()) {
        return context->meshes[id];
    }

    return emptyInfo;
}

uint32_t prism::PGC::MeshManager::getNextAvailableIndex(utils::Context* context)
{
    if (!context->freeMeshIndices.empty()) {
        uint32_t index = context->freeMeshIndices.back();
        context->freeMeshIndices.pop_back();
        return index;
    }

    return static_cast<uint32_t>(context->meshes.size());
}
