#include "textureManager.h"
#include "textureLoader.h"

namespace prism::PGC {
    uint32_t TextureManager::addTexture(utils::Context* context, const std::string& texturePath) {
        Texture texture = TextureLoader::load(context, texturePath);

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
        if (textureId >= context->textures.size()) {
            return;
        }

        TextureLoader::cleanup(context, &context->textures[textureId]);

        context->freeTextureIndices.push_back(textureId);

        updateDescriptors(context);
    }

    void TextureManager::cleanup(utils::Context* context) {
        for (auto& texture : context->textures) {
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

        std::vector<VkWriteDescriptorSet> descriptorWrites;
        std::vector<VkDescriptorImageInfo> imageInfos;

        for (uint32_t i = 0; i < context->textures.size(); i++) {
            if (context->textures[i].image == VK_NULL_HANDLE) {
                continue;
            }

            VkDescriptorImageInfo imageInfo{};
            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageInfo.imageView = context->textures[i].imageView;
            imageInfo.sampler = context->textures[i].sampler;
            imageInfos.push_back(imageInfo);

            VkWriteDescriptorSet descriptorWrite{};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = context->textureDescriptorSet;
            descriptorWrite.dstBinding = 0;
            descriptorWrite.dstArrayElement = i;
            descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrite.descriptorCount = 1;
            descriptorWrite.pImageInfo = &imageInfos.back();

            descriptorWrites.push_back(descriptorWrite);
        }

        if (!descriptorWrites.empty()) {
            vkUpdateDescriptorSets(context->device,
                static_cast<uint32_t>(descriptorWrites.size()),
                descriptorWrites.data(), 0, nullptr);
        }
    }

    uint32_t TextureManager::getNextAvailableIndex(utils::Context* context) {
        if (!context->freeTextureIndices.empty()) {
            uint32_t index = context->freeTextureIndices.back();
            context->freeTextureIndices.pop_back();
            return index;
        }

        return static_cast<uint32_t>(context->textures.size());
    }
}