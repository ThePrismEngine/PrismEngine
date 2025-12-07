#include "base.h"

void prism::PGC::base::Base::create()
{
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
}

void prism::PGC::base::Base::init(PGC::utils::Context* context, PGC::utils::Settings* settings)
{
    this->context = context;
    this->settings = settings;
    create();
}

prism::PGC::base::Base::~Base()
{
    if (!context || !settings) {
        logger::logError(logger::Error::NOT_CALL_CLEANUP_IN_PGC_CORE);
    }
}

void prism::PGC::base::Base::cleanup()
{
    if (context->device != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(context->device);  // Ensure all operations are completed
        vkDestroyDevice(context->device, nullptr);
        context->device = VK_NULL_HANDLE;  // Mark as destroyed
    }

    if (debugMessenger != VK_NULL_HANDLE) {
        DestroyDebugUtilsMessengerEXT(context->instance, debugMessenger, nullptr);
        debugMessenger = VK_NULL_HANDLE;
    }

    if (context->surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(context->instance, context->surface, nullptr);
        context->surface = VK_NULL_HANDLE;
    }
    if (context->instance != VK_NULL_HANDLE) {
        vkDestroyInstance(context->instance, nullptr);
        context->instance = VK_NULL_HANDLE;
    }
    context = nullptr;
    settings = nullptr;
}

bool prism::PGC::base::Base::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : context->validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

std::vector<const char*> prism::PGC::base::Base::getRequiredExtensions()
{
    std::vector<const char*> extensions;

    unsigned extensionCount = 0;
    if (!SDL_Vulkan_GetInstanceExtensions(settings->window, &extensionCount, nullptr)) {
        logger::logError(logger::Error::SDL_VULKAN_EXTENSIONS_COUNT_FAILED, "prism::PGC::core::Core::getRequiredExtensions()");
    }

    std::vector<const char*> sdlExtensions(extensionCount);
    if (!SDL_Vulkan_GetInstanceExtensions(settings->window, &extensionCount, sdlExtensions.data())) {
        logger::logError(logger::Error::SDL_VULKAN_EXTENSIONS_COUNT_FAILED, "prism::PGC::core::Core::getRequiredExtensions()");
    }

    extensions.insert(extensions.end(), sdlExtensions.begin(), sdlExtensions.end());

    if (context->enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

void prism::PGC::base::Base::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = settings->debug.VulkanMessageSeverity;
    createInfo.messageType = settings->debug.VulkanMessageType;
    createInfo.pfnUserCallback = debugCallback;
}

VKAPI_ATTR VkBool32 VKAPI_CALL prism::PGC::base::Base::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

void prism::PGC::base::Base::createInstance()
{
    if (context->enableValidationLayers && !checkValidationLayerSupport()) {
        logger::logError(logger::Error::VULKAN_VALIDATION_LAYERS_UNAVAILABLE, "prism::PGC::core::Core::createInstance()");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = settings->app.applicationName;
    appInfo.applicationVersion = VK_MAKE_VERSION(settings->app.applicationVersion.MAJOR, settings->app.applicationVersion.MINOR, settings->app.applicationVersion.PATCH);
    appInfo.pEngineName = prism::PrismInfo::NAME;
    appInfo.engineVersion = VK_MAKE_VERSION(prism::PrismVersion::MAJOR, prism::PrismVersion::MINOR, prism::PrismVersion::PATCH);
    appInfo.apiVersion = VK_API_VERSION_1_4;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if (context->enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(context->validationLayers.size());
        createInfo.ppEnabledLayerNames = context->validationLayers.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &context->instance) != VK_SUCCESS) {
        logger::logError(logger::Error::FAILED_TO_CREATE_VK_INSTANCE, "prism::PGC::core::Core::createInstance()");
    }
}

void prism::PGC::base::Base::setupDebugMessenger()
{
    if (!context->enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(context->instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
        logger::logError(logger::Error::VULKAN_DEBUG_MESSENGER_SETUP_FAILED, "prism::PGC::core::Core::setupDebugMessenger()");
    }
}

void prism::PGC::base::Base::pickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(context->instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        logger::logError(logger::Error::VULKAN_NO_GPU_SUPPORT, "prism::PGC::core::Core::pickPhysicalDevice()");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(context->instance, &deviceCount, devices.data());

    std::multimap<int, VkPhysicalDevice> candidates;
    DeviceRater deviceRater;
    for (const auto& device : devices) {
        int score = deviceRater.rate(device, context, settings);
        candidates.insert(std::make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0) {
        context->physicalDevice = candidates.rbegin()->second;
        if (settings->defaultPipeline.multisample.rasterizationSamples)
        context->msaaSamples = getMsaaSamples();
    }
    else {
        logger::logError(logger::Error::VULKAN_NO_SUITABLE_GPU, "prism::PGC::core::Core::pickPhysicalDevice()");
    }

    // Вывод информации о выбранном устройстве
    VkPhysicalDeviceProperties deviceProps = DeviceWrapper::getDeviceProperties(context->physicalDevice);
    logger::info("\n");
    logger::info("Selected Vulkan device:");
    logger::info("  - Name: " + std::string(deviceProps.deviceName));
    std::string type;
    switch (deviceProps.deviceType) {
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: type = "Integrated GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: type = "Discrete GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: type = "Virtual GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_CPU: type = "CPU"; break;
    default: type = "Other"; break;
    }
    logger::info("  - Type: " + type);
    logger::info("  - API Version: "
        + std::to_string(VK_VERSION_MAJOR(deviceProps.apiVersion)) + "."
        + std::to_string(VK_VERSION_MINOR(deviceProps.apiVersion)) + "."
        + std::to_string(VK_VERSION_PATCH(deviceProps.apiVersion)));
    logger::info("  - Driver Version: " + std::to_string(deviceProps.driverVersion));
    logger::info("  - Vendor ID: " + std::to_string(deviceProps.vendorID));
    logger::info("  - Device ID: " + std::to_string(deviceProps.deviceID));
    logger::info("  - Score: " + std::to_string(candidates.rbegin()->first) + "\n");
}

VkSampleCountFlagBits prism::PGC::base::Base::getMsaaSamples() {
    VkSampleCountFlagBits maxCount = getMaxUsableSampleCount();
    std::vector<VkSampleCountFlagBits> possibleCounts = getPossibleCounts(maxCount);


    if (possibleCounts.empty()) {
        return VK_SAMPLE_COUNT_1_BIT;
    }

    switch (settings->defaultPipeline.multisample.strategy) {
    case utils::MultisampleSelectionStrategy::MINIMAL:
        if (possibleCounts.size() >= 2) {
            for (size_t i = 1; i < possibleCounts.size(); ++i) {
                if (possibleCounts[i] != VK_SAMPLE_COUNT_1_BIT) {
                    return possibleCounts[i];
                }
            }
        }
        return possibleCounts[0]; 

    case utils::MultisampleSelectionStrategy::MIDDLE:
        if (possibleCounts.size() == 1) {
            return possibleCounts[0];
        }
        return possibleCounts[possibleCounts.size() / 2];

    case utils::MultisampleSelectionStrategy::MAXIMAL:
        return possibleCounts.back();

    case utils::MultisampleSelectionStrategy::CUSTOM:
        for (VkSampleCountFlagBits possibleCount : possibleCounts) {
            if (possibleCount == settings->defaultPipeline.multisample.rasterizationSamples) {
                return possibleCount;
            }
        }

        VkSampleCountFlagBits closest = possibleCounts[0];
        int minDiff = std::abs(static_cast<int>(closest) - static_cast<int>(settings->defaultPipeline.multisample.rasterizationSamples));

        for (size_t i = 1; i < possibleCounts.size(); ++i) {
            int diff = std::abs(static_cast<int>(possibleCounts[i]) - static_cast<int>(settings->defaultPipeline.multisample.rasterizationSamples));
            if (diff < minDiff) {
                minDiff = diff;
                closest = possibleCounts[i];
            }
        }
        return closest;

    return VK_SAMPLE_COUNT_1_BIT;
    }
}

void prism::PGC::base::Base::createSurface()
{
    if (!SDL_Vulkan_CreateSurface(settings->window, context->instance, &context->surface)) {
        logger::logError(logger::Error::FAILED_TO_CREATE_WINDOW_SURFACE, "WindowVkManager::createSurface");
    }
}

void prism::PGC::base::Base::createLogicalDevice()
{
    PGC::utils::QueueFamilyIndices indices = DeviceWrapper::findQueueFamilies(context->physicalDevice, context->surface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};
    deviceFeatures.samplerAnisotropy = VK_TRUE;
    deviceFeatures.fillModeNonSolid = VK_TRUE;

    VkPhysicalDeviceVulkan12Features vulkan12Features{};
    vulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;

    VkPhysicalDeviceFeatures2 physicalFeatures2{};
    physicalFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    physicalFeatures2.pNext = &vulkan12Features;
    physicalFeatures2.features = deviceFeatures;

    vkGetPhysicalDeviceFeatures2(context->physicalDevice, &physicalFeatures2);

    vulkan12Features.runtimeDescriptorArray = VK_TRUE;
    vulkan12Features.shaderSampledImageArrayNonUniformIndexing = VK_TRUE;
    vulkan12Features.descriptorBindingPartiallyBound = VK_TRUE;
    vulkan12Features.descriptorBindingSampledImageUpdateAfterBind = VK_TRUE;
    vulkan12Features.descriptorBindingUniformBufferUpdateAfterBind = VK_TRUE;


    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pNext = &vulkan12Features;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(context->deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = context->deviceExtensions.data();

    if (context->enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(context->validationLayers.size());
        createInfo.ppEnabledLayerNames = context->validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(context->physicalDevice, &createInfo, nullptr, &context->device) != VK_SUCCESS) {
        logger::logError(logger::Error::VULKAN_LOGICAL_DEVICE_CREATION_FAILED, "prism::PGC::core::Core::createLogicalDevice()");
    }

    vkGetDeviceQueue(context->device, indices.graphicsFamily.value(), 0, &context->graphicsQueue);
    vkGetDeviceQueue(context->device, indices.presentFamily.value(), 0, &context->presentQueue);
}


VkSampleCountFlagBits prism::PGC::base::Base::getMaxUsableSampleCount()
{
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(context->physicalDevice, &physicalDeviceProperties);

    VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
    if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
    if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
    if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
    if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
    if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
    if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

    return VK_SAMPLE_COUNT_1_BIT;
}

std::vector<VkSampleCountFlagBits> prism::PGC::base::Base::getPossibleCounts(VkSampleCountFlagBits maxCount) {

    std::vector<VkSampleCountFlagBits> counts = {
          VK_SAMPLE_COUNT_1_BIT,
          VK_SAMPLE_COUNT_2_BIT,
          VK_SAMPLE_COUNT_4_BIT,
          VK_SAMPLE_COUNT_8_BIT,
          VK_SAMPLE_COUNT_16_BIT,
          VK_SAMPLE_COUNT_32_BIT,
          VK_SAMPLE_COUNT_64_BIT
    };

    std::vector<VkSampleCountFlagBits> possibleCounts;

    for (VkSampleCountFlagBits count : counts)
    {
        if (count <= maxCount) {
            possibleCounts.push_back(count);
        }
        else
        {
            break;
        }
    }
    return possibleCounts;
}