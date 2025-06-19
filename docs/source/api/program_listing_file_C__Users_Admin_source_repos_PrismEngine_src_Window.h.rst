
.. _program_listing_file_C__Users_Admin_source_repos_PrismEngine_src_Window.h:

Program Listing for File Window.h
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_C__Users_Admin_source_repos_PrismEngine_src_Window.h>` (``C:\Users\Admin\source\repos\PrismEngine\src\Window.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <vector>
   #include <string>
   #include <SDL.h>
   #include <vulkan/vulkan.h>
   #include <optional>
   #include <stdexcept>
   #include <utility> // для std::pair
   #include <SDL_vulkan.h>
   #include <memory> 
   #include <set>
   
   namespace prism {
       namespace view {
   
           const std::vector<const char*> validationLayers = {
                   "VK_LAYER_KHRONOS_validation"
           };
           const std::vector<const char*> deviceExtensions = {
                   VK_KHR_SWAPCHAIN_EXTENSION_NAME
           };
   
           struct QueueFamilyIndices {
               std::optional<uint32_t> graphicsFamily;
               std::optional<uint32_t> presentFamily;
   
               bool isComplete() {
                   return graphicsFamily.has_value() && presentFamily.has_value();
               }
           };
   
           class Window {
           public:
               // === Конструкторы ===
               Window(const char* title, int width, int height);
               Window(const char* title, int width, int height, Uint32 sdlFlags);
               Window(const char* title, int x, int y, int width, int height);
               Window(const char* title, int width, int height, const std::string& iconPath);
   
               // Специальные конструкторы
               static Window CreateCentered(const char* title, int width, int height);
               Window(const char* title, int width, int height,
                   int minWidth, int minHeight, int maxWidth, int maxHeight);
   
               // === Деструктор ===
               ~Window();
   
               // === Управление окном ===
               const char* getTitle() const;
               void setTitle(const char* title);
               int getWidth();
               int getHeight();
               void getSize(int* width, int* height);
               void setWidth(int width);
               void setHeight(int height);
               void setSize(int width, int height);
   
               // === Режимы окна ===
               void setFullscreen(bool enabled);
               void setBorderless(bool enabled);
               void setResizable(bool enabled);
               void setGrabMouse(bool enabled);
               bool isFullscreen() const;
               bool isBorderless() const;
               bool isResizable() const;
               bool isGrabMouse() const;
   
               // === Позиция и размер ===
               void setPosition(int x, int y);
               std::pair<int, int> getPosition() const;
               void centerWindow();
               void setMinSize(int minWidth, int minHeight);
               void setMaxSize(int maxWidth, int maxHeight);
   
               // === События и рендеринг ===
               bool shouldClose() const;
               void setCloseRequested(bool value);
               void handleEvents();
               void clear();
               void update();
   
   
               // === Дополнительные методы ===
               void destroy();
   
               static void setSDLInitialized(bool initialized) { s_sdlInitialized = initialized; }
   
               // === Vulkan методы ===
               void vulkanInut();
               void createInstance();
               void pickPhysicalDevice();
               bool isDeviceSuitable(VkPhysicalDevice device);
   
               bool checkDeviceExtensionSupport(VkPhysicalDevice device);
   
   
           private:
   #ifdef NDEBUG
               const bool enableValidationLayers = false;
   #else
               const bool enableValidationLayers = true;
   #endif
               static bool s_sdlInitialized;
               SDL_Window* m_sdlWindow;
               bool m_isDestroyed;
   
               bool m_windowMinimized = false; // Флаг минимизации окна
               
               // Внутренний конструктор для делегирования
               Window(const char* title, int x, int y, int width, int height, Uint32 sdlFlags);
   
               VkInstance instance;
               VkPhysicalDevice physicalDevice;
               VkDevice device;
               VkQueue graphicsQueue;
               VkSurfaceKHR surface;
               VkQueue presentQueue;
   
               int rateDeviceSuitability(VkPhysicalDevice device);
   
               QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
               void createLogicalDevice();
               void createSurface();
           };
   
           inline bool Window::s_sdlInitialized = false;
       } // namespace view
   } // namespace prism
