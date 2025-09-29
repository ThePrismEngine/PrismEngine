#include "textureManager.h"
#include "textureLoader.h"

namespace prism::PGC {
    uint32_t TextureManager::addTexture(utils::Context* context, const std::string& texturePath) {
        Texture texture = TextureLoader::load(context, texturePath);

        if (texture.image == VK_NULL_HANDLE) {
            return INVALID_TEXTURE;
        }

        uint32_t index = getNextAvailableIndex(context);
        texture.bindlessIndex = index;

        if (index >= context->textures.size()) {
            context->textures.push_back(texture);
        }
        else {
            context->textures[index] = texture;
        }

        updateDescriptors(context);

        return index;
    }

    void TextureManager::removeTexture(utils::Context* context, uint32_t textureId) {
        if (textureId == INVALID_TEXTURE || textureId >= context->textures.size()) {
            return;
        }

        TextureLoader::cleanup(context, &context->textures[textureId]);

        context->freeTextureIndices.push_back(textureId);

        updateDescriptors(context);
    }

    void TextureManager::cleanup(utils::Context* context) {
        for (uint32_t i = INVALID_TEXTURE+1; i < context->textures.size(); i++) {
            auto& texture = context->textures[i];
            if (texture.image != VK_NULL_HANDLE) {
                TextureLoader::cleanup(context, &texture);
            }
        }

        context->textures.clear();
        context->freeTextureIndices.clear();
    }

    void TextureManager::updateDescriptors(utils::Context* context) {
        if (context->textureDescriptorSet == VK_NULL_HANDLE) {
            return;
        }

        std::vector<std::pair<uint32_t, VkDescriptorImageInfo>> validTextures;
        for (uint32_t i = INVALID_TEXTURE+1; i < context->textures.size(); i++) {
            if (context->textures[i].image != VK_NULL_HANDLE) {
                VkDescriptorImageInfo imageInfo{};
                imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                imageInfo.imageView = context->textures[i].imageView;
                imageInfo.sampler = context->textures[i].sampler;
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

    uint32_t TextureManager::getNextAvailableIndex(utils::Context* context) {
        if (!context->freeTextureIndices.empty()) {
            uint32_t index = context->freeTextureIndices.back();
            context->freeTextureIndices.pop_back();
            return index >= INVALID_TEXTURE+1 ? index : getNextAvailableIndex(context);
        }

        return static_cast<uint32_t>(context->textures.size() > 0 ? context->textures.size() : INVALID_TEXTURE+1);
    }
}