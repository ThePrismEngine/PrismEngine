#pragma once
#include "utils.h"

namespace prism {
	namespace PGC {
		class SwapChain
		{
		public:
			SwapChain() : context(nullptr), settings(nullptr) {}
			void init(PGC::utils::CoreContext* context, PGC::utils::CoreSettings* settings);
			~SwapChain();
			void cleanup();
			void awaitRenderingCompletion();
			void recreate();

			VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
		private:
			void create();
			void createImageViews();

			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
			uint32_t getImageCount(PGC::utils::SwapChainSupportDetails swapChainSupport);

			utils::CoreContext* context;
			utils::CoreSettings* settings;
		};
	}
}