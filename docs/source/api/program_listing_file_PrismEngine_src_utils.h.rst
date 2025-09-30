
.. _program_listing_file_PrismEngine_src_utils.h:

Program Listing for File utils.h
================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_utils.h>` (``PrismEngine\src\utils.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <vector>
   #include <optional>
   #include "vulkan/vulkan.h"
   #include "config.h"
   #include "SDL.h"
   #include <string>
   #include "./ubo.h"
   #include "vertex.h"
   #include "texture.h"
   #include "mesh.h"
   
   namespace prism {
       namespace PGC {
           namespace utils {
               struct QueueFamilyIndices {
                   std::optional<uint32_t> graphicsFamily;
                   std::optional<uint32_t> presentFamily;
   
                   bool isComplete() {
                       return graphicsFamily.has_value() && presentFamily.has_value();
                   }
               };
   
               struct SwapChainSupportDetails {
                   VkSurfaceCapabilitiesKHR capabilities;
                   std::vector<VkSurfaceFormatKHR> formats;
                   std::vector<VkPresentModeKHR> presentModes;
               };
   
   
               struct CameraData {
                   glm::vec3 pos = { 2.0f, 2.0f, 2.0f };  // Позиция
                   glm::vec3 look = { 0.0f, 0.0f, 0.0f }; // Взгляд
                   glm::vec3 up = { 0.0f, 0.0f, 1.0f };   // Вектор вверх
   
                   float fovy = 45.0f;        // Угол обзора в градусах
                   float aspect = 16.f / 9.f; // Соотношение сторон
                   float zNear = 0.1f;        // Ближняя плоскость отсечения
                   float zFar = 10.0f;        // Дальняя плоскость отсечения
   
                   bool useСurrentWindowAspect = true; // Если истино то aspect игнорируется и соотношение камеры равно соотношению окна
   
               };
   
               struct Context {
                   VkInstance instance;
                   VkSurfaceKHR surface;
                   VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
                   VkDevice device;
                   VkQueue graphicsQueue;
                   VkQueue presentQueue;
   
                   VkSwapchainKHR vkSwapChain;
                   std::vector<VkImageView> swapChainImageViews;
                   std::vector<VkFramebuffer> swapChainFramebuffers;
                   std::vector<VkImage> swapChainImages;
                   VkFormat swapChainImageFormat;
                   VkExtent2D swapChainExtent;
   
                   VkImage depthImage;
                   VkDeviceMemory depthImageMemory;
                   VkImageView depthImageView;
   
                   VkImage colorImage;
                   VkDeviceMemory colorImageMemory;
                   VkImageView colorImageView;
   
                   VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
                   VkRenderPass renderPass;
   
                   VkBuffer vertexBuffer;
                   VkDeviceMemory vertexBufferMemory;
                   VkBuffer indexBuffer;
                   VkDeviceMemory indexBufferMemory;
   
                   std::vector<Vertex> allVertices;
                   std::vector<uint32_t> allIndices;
                   std::vector<prism::PGC::Mesh> meshes;
                   std::vector<uint32_t> freeMeshIndices;
                   bool meshBuffersDirty = false;
   
                   VkDescriptorSetLayout descriptorSetLayout;
   
                   VkPipelineLayout pipelineLayout;
                   VkPipeline graphicsPipeline;
   
                   VkCommandPool commandPool;
                   std::vector<VkCommandBuffer> commandBuffers;
   
                   std::vector<UniformBuffers> uniformBuffers;
   
                   std::vector<VkSemaphore> imageAvailableSemaphores;
                   std::vector<VkSemaphore> renderFinishedSemaphores;
                   std::vector<VkFence> inFlightFences;
   
                   uint32_t currentFrame = 0;
                   uint32_t imageIndex;
                   bool wasRenderingActive = true;
   
                   VkDescriptorPool descriptorPool;
                   VkDescriptorPool textureDescriptorPool;
   
                   // Текстуры и управление ими
                   std::vector<PGC::Texture> textures;
                   std::vector<uint32_t> freeTextureIndices;
                   VkDescriptorSet textureDescriptorSet = VK_NULL_HANDLE;
                   VkDescriptorSetLayout textureDescriptorSetLayout = VK_NULL_HANDLE;
   
                   CameraData cameraData;
   
                   std::vector<VkDescriptorSet> descriptorSets;
   
                   const int MAX_FRAMES_IN_FLIGHT = 2;
   
                   const std::vector<const char*> validationLayers = {
                       "VK_LAYER_KHRONOS_validation"
                   };
   
                   const std::vector<const char*> deviceExtensions = {
                       VK_KHR_SWAPCHAIN_EXTENSION_NAME,
                       VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME
                   };
   
                   size_t dynamicAlignment=0;      // Выровненный размер ObjectUBO
                   uint32_t MAX_OBJECTS=500;         // Максимальное количество объектов
   
   #ifdef NDEBUG
                   bool enableValidationLayers = false;
   #else
                   bool enableValidationLayers = true;
   #endif
               };
   
               struct AppSettings
               {
                   const char* applicationName = "";
                   prism::Version applicationVersion = { 1, 0, 0 };
               };
   
               struct DebugSettings
               {
                   VkDebugUtilsMessageSeverityFlagsEXT VulkanMessageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
                   VkDebugUtilsMessageTypeFlagsEXT VulkanMessageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
   #ifdef NDEBUG
                   bool debugDeviceSelection = false;
   #else
                   bool debugDeviceSelection = true;
   #endif
               };
   
               struct DeviceEvaluationWeightsSettings {
                   float wType = 0.3;
                   float wFeatures = 0.25;
                   float wHardware = 0.35;
                   float wApi = 0.1;
               };
   
               struct SwapChainSettings
               {
                   bool enableVSync = true;
                   bool enableTripleBuffering = true;
                   VkFormat preferredFormat = VK_FORMAT_B8G8R8A8_SRGB;
               };
   
               // Конфигурация для одного биндинга
               struct BindingConfig {
                   uint32_t binding;
                   VkDescriptorType descriptorType;
                   uint32_t descriptorCount;
                   VkShaderStageFlags stageFlags;
                   const VkSampler* immutableSamplers = nullptr;
               };
   
               struct TextureBindingConfig {
                   uint32_t binding;
                   VkDescriptorType descriptorType;
                   uint32_t descriptorCount;
                   VkShaderStageFlags stageFlags;
                   const VkSampler* immutableSamplers = nullptr;
                   VkDescriptorBindingFlagsEXT bindingFlags;
               };
   
               struct DescriptorSetLayoutSettings {
                   std::vector<BindingConfig> bindings;
                   VkDescriptorSetLayoutCreateFlags flags = 0;
               };
   
               struct TextureDescriptorSetLayoutSettings {
                   std::vector<TextureBindingConfig> bindings;
                   VkDescriptorSetLayoutCreateFlags flags = 0;
               };
   
               struct ShadersSettings
               {
                   std::string vertexShaderFilename;
                   std::string fragmentShaderFilename;
                   std::string shadersDirectory;
               };
   
               struct RasterizationSettings {
                   VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;
                   float lineWidth = 1.0f;
                   VkCullModeFlags cullMode = VK_CULL_MODE_BACK_BIT;
                   VkFrontFace frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
                   VkBool32 depthClampEnable = VK_FALSE;
                   VkBool32 rasterizerDiscardEnable = VK_FALSE;
                   VkBool32 depthBiasEnable = VK_FALSE;
               };
   
               enum MultisampleSelectionStrategy {
                   MINIMAL,  // Минимальный уровень после 1x(обычно 2x)
                   MIDDLE,   // Среднее значение из доступных
                   MAXIMAL,  // Максимальное значение
                   CUSTOM,   // Значение из цели или максимально приближенное
                   //ADAPTIVE, // Оценка по баллам устройства
               };
   
               struct MultisampleSettings {
                   VkBool32 sampleShadingEnable = VK_FALSE;
                   VkSampleCountFlagBits rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
                   MultisampleSelectionStrategy strategy = MultisampleSelectionStrategy::MAXIMAL;
               };
   
               struct ColorBlendAttachmentSettings {
                   VkBool32 blendEnable = VK_FALSE;
                   VkColorComponentFlags colorWriteMask =
                       VK_COLOR_COMPONENT_R_BIT |
                       VK_COLOR_COMPONENT_G_BIT |
                       VK_COLOR_COMPONENT_B_BIT |
                       VK_COLOR_COMPONENT_A_BIT;
               };
   
               struct ColorBlendSettings {
                   std::vector<VkPipelineColorBlendAttachmentState> attachments;
                   VkBool32 logicOpEnable = VK_FALSE;
                   VkLogicOp logicOp = VK_LOGIC_OP_COPY;
                   float blendConstants[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
               };
   
               struct DynamicStateSettings {
                   std::vector<VkDynamicState> dynamicStates = {
                       VK_DYNAMIC_STATE_VIEWPORT,
                       VK_DYNAMIC_STATE_SCISSOR
                   };
               };
   
               struct DepthStencilSettings {
                   VkBool32 depthTestEnable = VK_TRUE;
                   VkBool32 depthWriteEnable = VK_TRUE;
                   VkCompareOp depthCompareOp = VK_COMPARE_OP_LESS;
                   VkBool32 depthBoundsTestEnable = VK_FALSE;
                   float minDepthBounds = 0.0f;
                   float maxDepthBounds = 1.0f;
                   VkBool32 stencilTestEnable = VK_FALSE;
                   VkStencilOpState front = {};
                   VkStencilOpState back = {};
               };
   
               struct InputAssemblySettings {
                   VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
                   VkBool32 primitiveRestartEnable = VK_FALSE;
               };
   
               struct ViewportStateSettings {
                   uint32_t viewportCount = 1;
                   uint32_t scissorCount = 1;
               };
   
               struct PipelineSettings {
                   ShadersSettings shaders = { "vert.spv", "frag.spv", "shaders/" };;
                   InputAssemblySettings inputAssembly;
                   RasterizationSettings rasterization;
                   DepthStencilSettings depthStencil;
                   MultisampleSettings multisample;
                   ColorBlendSettings colorBlend;
                   DynamicStateSettings dynamicState;
                   ViewportStateSettings viewportState;
               };
   
               struct Settings
               {
                   AppSettings app;
                   DeviceEvaluationWeightsSettings deviceEvaluationWeights;
                   DebugSettings debug;
                   SwapChainSettings swapChain;
                   DescriptorSetLayoutSettings descriptorSetLayout;
                   TextureDescriptorSetLayoutSettings textureDescriptorSetLayout;
   
                   uint32_t MAX_TEXTURES = 350;
                   
                   PipelineSettings pipeline;
   
                   SDL_Window* window;
               };
           }
       }
   }
