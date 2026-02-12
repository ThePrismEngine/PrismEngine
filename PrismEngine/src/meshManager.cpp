#include "meshManager.h"
#include "meshLoader.h"
#include "bufferWrapper.h"

void prism::PGC::L1::MeshManager::createImpl()
{
    meshLoader = new PGC::L2::MeshLoader(context, settings);
}

prism::Mesh prism::PGC::L1::MeshManager::addMesh(std::string texturePath)
{
    prism::PGC::MeshData mesh = meshLoader->load(texturePath);

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

    prism::Mesh id = getNextAvailableIndex();
    if (id >= context->meshes.size()) {
        context->meshes.push_back(info);
    }
    else {
        context->meshes[id] = info;
    }

    context->meshBuffersDirty = true;
    return id;
}

void prism::PGC::L1::MeshManager::update()
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

void prism::PGC::L1::MeshManager::clear()
{
    context->meshes.clear();
    context->allVertices.clear();
    context->allIndices.clear();
    context->freeMeshIndices.clear();

    context->meshBuffersDirty = true;
}

void prism::PGC::L1::MeshManager::cleanupImpl()
{
    clear();
    delete meshLoader;
}

prism::PGC::Mesh& prism::PGC::L1::MeshManager::getMeshInfo(prism::Mesh id)
{
    static Mesh emptyInfo = { 0, 0, 0, 0 };

    if (id < context->meshes.size()) {
        return context->meshes[id];
    }

    return emptyInfo;
}

uint32_t prism::PGC::L1::MeshManager::getNextAvailableIndex()
{
    if (!context->freeMeshIndices.empty()) {
        uint32_t index = context->freeMeshIndices.back();
        context->freeMeshIndices.pop_back();
        return index;
    }

    return static_cast<uint32_t>(context->meshes.size());
}

