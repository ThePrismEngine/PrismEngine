#include "memory"
#include "textureStorage.h"
#include "textureLoader.h"

void prism::PGC::L1::TextureStorage::createImpl() {
    textureLoader = new PGC::L2::TextureLoader(context, settings);
    textures.push_back(PGC::Texture{});
}

prism::TextureId prism::PGC::L1::TextureStorage::load(std::string texturePath) {
    Texture texture = textureLoader->load(texturePath);

    if (texture.image == VK_NULL_HANDLE) {
        return INVALID_TEXTURE_ID;
    }

    uint32_t index = getNextAvailableIndex(context);
    texture.bindlessIndex = index;

    if (index >= textures.size()) {
        textures.push_back(texture);
    }
    else {
        textures[index] = texture;
    }

    updateDescriptors();

    return index;
}

std::shared_ptr<prism::PGC::Texture> prism::PGC::L1::TextureStorage::get(TextureId textureId)
{
    return std::make_shared<prism::PGC::Texture>(textures[textureId]);
}

bool prism::PGC::L1::TextureStorage::remove(TextureId textureId)
{
    if (textureId == INVALID_TEXTURE_ID || textureId >= textures.size()) {
        return false;
    }

    textureLoader->cleanup(&textures[textureId]);

    freeTextureIndices.push_back(textureId);

    updateDescriptors();
}

void prism::PGC::L1::TextureStorage::cleanupImpl()
{
    for (uint32_t i = INVALID_TEXTURE_ID + 1; i < textures.size(); i++) {
        auto& texture = textures[i];
        if (texture.image != VK_NULL_HANDLE) {
            textureLoader->cleanup(&texture);
        }
    }

    textures.clear();
    freeTextureIndices.clear();

    if (context->textureDescriptorSetLayout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(context->device, context->textureDescriptorSetLayout, nullptr);
        context->textureDescriptorSetLayout = VK_NULL_HANDLE;
    }

    delete textureLoader;
}

void prism::PGC::L1::TextureStorage::updateDescriptors()
{
    if (context->textureDescriptorSet == VK_NULL_HANDLE) {
        return;
    }

    std::vector<std::pair<uint32_t, VkDescriptorImageInfo>> validTextures;
    for (uint32_t i = INVALID_TEXTURE_ID + 1; i < textures.size(); i++) {
        if (textures[i].image != VK_NULL_HANDLE) {
            VkDescriptorImageInfo imageInfo{};
            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageInfo.imageView = textures[i].imageView;
            imageInfo.sampler = textures[i].sampler;
            validTextures.emplace_back(i, imageInfo);
        }
    }

    if (validTextures.empty()) {
        return;
    }

    std::vector<VkWriteDescriptorSet> descriptorWrites;
    descriptorWrites.reserve(validTextures.size());

    for (const auto& [index, imageInfo] : validTextures) {
        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = context->textureDescriptorSet;
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = index;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pImageInfo = &imageInfo;

        descriptorWrites.push_back(descriptorWrite);
    }


    vkUpdateDescriptorSets(context->device,
        static_cast<uint32_t>(descriptorWrites.size()),
        descriptorWrites.data(), 0, nullptr);
}

uint32_t prism::PGC::L1::TextureStorage::getNextAvailableIndex(utils::Context* context) {
    if (!freeTextureIndices.empty()) {
        uint32_t index = freeTextureIndices.back();
        freeTextureIndices.pop_back();
        return index >= INVALID_TEXTURE_ID + 1 ? index : getNextAvailableIndex(context);
    }

    return static_cast<uint32_t>(textures.size() > 0 ? textures.size() : INVALID_TEXTURE_ID + 1);
}