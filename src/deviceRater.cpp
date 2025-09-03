#include <unordered_set>
#include <algorithm>
#include "deviceRater.h"
#include "base.h"
#include "deviceWrapper.h"
#include "deviceChecker.h"

int prism::PGC::DeviceRater::rate(VkPhysicalDevice device, PGC::utils::Context* context, utils::Settings* settings)
{
    debugDeviceSelection = settings->debug.debugDeviceSelection;
    // Базовые проверки
    if (!DeviceChecker::check(device, context, settings)) return 0;
    
    DeviceScore deviceScore;
    deviceScore.typeScore     = getDeviceTypeScore(device)     * settings->deviceEvaluationWeights.wType;
    deviceScore.featureScore  = getDeviceFeatureScore(device)  * settings->deviceEvaluationWeights.wFeatures;
    deviceScore.hardwareScore = getDeviceHardwareScore(device) * settings->deviceEvaluationWeights.wHardware;
    deviceScore.apiScore      = getDeviceApiScore(device)      * settings->deviceEvaluationWeights.wApi;

    if (debugDeviceSelection) {
       ScoreWrapper::print(deviceScore);
    }


    return ScoreWrapper::getTotal(deviceScore);
}

int prism::PGC::DeviceRater::getDeviceTypeScore(VkPhysicalDevice device)
{
    switch (prism::PGC::DeviceWrapper::getDeviceProperties(device).deviceType) {
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   return 100;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: return 70;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    return 40;
    case VK_PHYSICAL_DEVICE_TYPE_CPU:            return 10;
    default:                                     return 10;
    }
}

int prism::PGC::DeviceRater::getDeviceFeatureScore(VkPhysicalDevice device)
{
    FeatureScores features = calculateFeatureScore(device);

    // Учитываем вендора для RT и Upscaling
    VkPhysicalDeviceProperties props = DeviceWrapper::getDeviceProperties(device);;

    if (props.vendorID == 0x10DE) { // NVIDIA
        features.raytracing *= 1.5f;
        if (features.upscaling > 0) features.upscaling += 5.0f;
    }

    if (debugDeviceSelection) {
        ScoreWrapper::print(features);
    }

    return static_cast<int>(ScoreWrapper::getTotal(features));
}

int prism::PGC::DeviceRater::getDeviceHardwareScore(VkPhysicalDevice device)
{
    HardwareScore score;
    VkPhysicalDeviceProperties props = DeviceWrapper::getDeviceProperties(device);
    VkPhysicalDeviceMemoryProperties memProps = DeviceWrapper::getDeviceMemoryProperties(device);

    // Константы для преобразования единиц
    constexpr float BYTES_TO_GB = 1.0f / (1024 * 1024 * 1024);
    constexpr float MHZ_TO_GHZ = 1.0f / 1000.0f;
    constexpr float TEXTURE_UNITS_NORMALIZER = 1.0f / 10000.0f;

    // Расчет VRAM
    for (uint32_t i = 0; i < memProps.memoryHeapCount; ++i) {
        if (memProps.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
            score.vramGB += static_cast<float>(memProps.memoryHeaps[i].size) * BYTES_TO_GB;
        }
    }

    // показатели производительности
    score.shaderCores = std::log2(static_cast<float>(props.limits.maxComputeWorkGroupInvocations) + 1.0f);

    if (props.limits.maxComputeWorkGroupSize[0] > 0) {
        score.clockSpeedGHz = static_cast<float>(props.limits.maxComputeWorkGroupSize[0]) * MHZ_TO_GHZ;
    }
    else {
        score.clockSpeedGHz = 1.0f; // Значение по умолчанию
    }

    score.textureUnits = static_cast<float>(props.limits.maxImageDimension2D) * TEXTURE_UNITS_NORMALIZER;

    if (debugDeviceSelection) {
        ScoreWrapper::print(score);
    }

    // Возвращаем нормализованную оценку (0-100)
    return ScoreWrapper::getTotal(score);
}

int prism::PGC::DeviceRater::getDeviceApiScore(VkPhysicalDevice device)
{
    const int BASE_SCORE_V1 = 30;
    const int V1_1_BONUS = 5;
    const int V1_2_BONUS = 15;
    const int V1_3_BONUS = 25;
    const int FEATURE_BONUS = 5;

    VkPhysicalDeviceProperties props = DeviceWrapper::getDeviceProperties(device);

    int score = 0;

    uint32_t api_version = props.apiVersion;
    const int major = VK_VERSION_MAJOR(api_version);
    const int minor = VK_VERSION_MINOR(api_version);


    // Базовые баллы
    if (major >= 1) {
        score += BASE_SCORE_V1; // Vulkan 1.0+

        // Бонусы за минорные версии через switch-case
        switch (minor) {
        case 3: score += V1_3_BONUS; break; // 1.3
        case 2: score += V1_2_BONUS; break; // 1.2
        case 1: score += V1_1_BONUS; break; // 1.1
        case 0: break; // 1.0 - без бонусов
        default:       // Для версий выше 1.3
            if (minor > 3) score += V1_3_BONUS;
            break;
        }

        // Проверка фич Vulkan 1.2+
        if (minor >= 2) {
            VkPhysicalDeviceVulkan12Features features12 = {};
            features12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;

            VkPhysicalDeviceFeatures2 features2 = {};
            features2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
                features2.pNext = &features12;

            vkGetPhysicalDeviceFeatures2(device, &features2);
            if (features12.shaderFloat16) score += 5;
            if (features12.descriptorIndexing) score += 5;
        }
    }

    return score;
}

prism::PGC::FeatureScores prism::PGC::DeviceRater::calculateFeatureScore(VkPhysicalDevice device)
{
    FeatureScores scores;

    // Получаем список всех расширений
    std::vector<VkExtensionProperties> extensions;
    DeviceWrapper::getDeviceExtensionProperties(device, &extensions);

    // Создаем множество для быстрого поиска
    std::unordered_set<std::string> availableExtensions;
    for (const auto& ext : extensions) {
        availableExtensions.insert(ext.extensionName);
    }

    // Проверяем базовые расширения
    const std::string swapchainExt = "VK_KHR_swapchain";
    if (availableExtensions.count(swapchainExt)) {
        scores.swapchain = 10.0f;
    }

    // Проверяем Ray Tracing
    const std::vector<std::string> rtExtensions = {
        "VK_KHR_ray_tracing_pipeline",
        "VK_NV_ray_tracing"
    };
    for (const auto& rtExt : rtExtensions) {
        if (availableExtensions.count(rtExt)) {
            scores.raytracing = 25.0f;
            break;
        }
    }

    // Проверяем Upscaling технологии
    const std::vector<std::string> upscalingExtensions = {
        "VK_NV_DLSS",          // NVIDIA DLSS
        "VK_KHR_fragment_shading_rate", // FSR/XeSS
        "VK_EXT_fragment_density_map"   // Альтернативный механизм
    };
    for (const auto& upExt : upscalingExtensions) {
        if (availableExtensions.count(upExt)) {
            scores.upscaling = upExt == "VK_NV_DLSS" ? 20.0f : 15.0f;
            break;
        }

    if (DeviceWrapper::getDeviceProperties(device).apiVersion >= VK_MAKE_VERSION(1, 2, 0)) {
       scores.advancedFeatures += 5.0f;
    }
}

    // Проверяем дополнительные возможности
    VkPhysicalDeviceFeatures2 features2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };
    vkGetPhysicalDeviceFeatures2(device, &features2);

    if (features2.features.tessellationShader) {
        scores.advancedFeatures += 5.0f;
    }
    if (features2.features.multiViewport) {
        scores.advancedFeatures += 3.0f;
    }

    return scores;
}

void prism::PGC::ScoreWrapper::print(DeviceScore score)
{
    logger::info("----------------Score----------------");
    logger::info("Type: " + std::to_string(score.typeScore));
    logger::info("Features: " + std::to_string(score.featureScore));
    logger::info("Hardware: " + std::to_string(score.hardwareScore));
    logger::info("API: " + std::to_string(score.apiScore));
    logger::info("TOTAL: " + std::to_string(getTotal(score)));
}

void prism::PGC::ScoreWrapper::print(FeatureScores score)
{
    logger::info("----------------FeatureScore----------------");
    logger::info("Swapchain: " + std::to_string(score.swapchain));
    logger::info("Ray Tracing: " + std::to_string(score.raytracing));
    logger::info("Upscaling: " + std::to_string(score.upscaling));
    logger::info("Advanced Features: " + std::to_string(score.advancedFeatures));
    logger::info("Total Features: " + std::to_string(getTotal(score)));
}

void prism::PGC::ScoreWrapper::print(HardwareScore score)
{
    logger::info("----------------HardwareScore----------------");
    logger::info("VRAM (GB): " + std::to_string(score.vramGB));
    logger::info("Shader Cores (log2): " + std::to_string(score.shaderCores));
    logger::info("Clock Speed (GHz): " + std::to_string(score.clockSpeedGHz));
    logger::info("Texture Units: " + std::to_string(score.textureUnits));
    logger::info("Normalized Score: " + std::to_string(getTotal(score)));
}

int prism::PGC::ScoreWrapper::getTotal(DeviceScore score)
{
    return score.typeScore + score.featureScore + score.hardwareScore + score.apiScore;
}

int prism::PGC::ScoreWrapper::getTotal(FeatureScores score)
{
    return score.swapchain + score.raytracing + score.upscaling + score.advancedFeatures;
}

int prism::PGC::ScoreWrapper::getTotal(HardwareScore score)
{
    // Нормализованные компоненты(ограничены 1.0 как максимум)
    float normalizedVram = std::min(score.vramGB / score.REFERENCE_VRAM_GB, 1.0f);
    float normalizedShaderCores = std::min(score.shaderCores / score.REFERENCE_SHADER_CORES, 1.0f);
    float normalizedClockSpeed = std::min(score.clockSpeedGHz / score.REFERENCE_CLOCK_SPEED_GHZ, 1.0f);

    float total = normalizedVram        * score.VRAM_WEIGHT +
                  normalizedShaderCores * score.SHADER_CORES_WEIGHT +
                  normalizedClockSpeed  * score.CLOCK_SPEED_WEIGHT;

    // Взвешенная сумма компонентов
    return static_cast<int>(std::clamp(total * 100.0f, 0.0f, 100.0f));
}