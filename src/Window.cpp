#include "Window.h"
#include <map>
#include <iostream>

namespace prism {
    namespace view {

        Window::Window(const char* title, int width, int height)
            : Window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN) {
        }

        Window::Window(const char* title, int width, int height, Uint32 sdlFlags)
            : Window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, sdlFlags) {
        }

        Window::Window(const char* title, int x, int y, int width, int height)
            : Window(title, x, y, width, height, SDL_WINDOW_SHOWN) {
        }

        Window::Window(const char* title, int width, int height, const std::string& iconPath)
            : Window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN) {
            SDL_Surface* icon = SDL_LoadBMP(iconPath.c_str());
            if (icon) {
                SDL_SetWindowIcon(m_sdlWindow, icon);
                SDL_FreeSurface(icon);
            }
        }

        Window Window::CreateCentered(const char* title, int width, int height) {
            return Window(title, width, height);
        }

        Window::Window(const char* title, int width, int height,
            int minWidth, int minHeight, int maxWidth, int maxHeight)
            : Window(title, width, height) {
            SDL_SetWindowMinimumSize(m_sdlWindow, minWidth, minHeight);
            SDL_SetWindowMaximumSize(m_sdlWindow, maxWidth, maxHeight);
        }

        Window::Window(const char* title, int x, int y, int width, int height, Uint32 sdlFlags)
            : m_isDestroyed(false), instance(VK_NULL_HANDLE), physicalDevice(VK_NULL_HANDLE),
            device(VK_NULL_HANDLE), surface(VK_NULL_HANDLE) {
            if (!s_sdlInitialized) {
                if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                    throw std::runtime_error("SDL could not initialize!");
                }
                s_sdlInitialized = true;
            }

            m_sdlWindow = SDL_CreateWindow(title, x, y, width, height, sdlFlags | SDL_WINDOW_VULKAN);
            if (!m_sdlWindow) {
                throw std::runtime_error("Window could not be created!");
            }

            vulkanInut();
        }

        Window::~Window() {
            destroy();
        }

        const char* Window::getTitle() const {
            return SDL_GetWindowTitle(m_sdlWindow);
        }

        void Window::setTitle(const char* title) {
            SDL_SetWindowTitle(m_sdlWindow, title);
        }

        int Window::getWidth() {
            int width;
            SDL_GetWindowSize(m_sdlWindow, &width, nullptr);
            return width;
        }

        int Window::getHeight() {
            int height;
            SDL_GetWindowSize(m_sdlWindow, nullptr, &height);
            return height;
        }

        void Window::getSize(int* width, int* height) {
            SDL_GetWindowSize(m_sdlWindow, width, height);
        }

        void Window::setWidth(int width) {
            int height;
            SDL_GetWindowSize(m_sdlWindow, nullptr, &height);
            SDL_SetWindowSize(m_sdlWindow, width, height);
        }

        void Window::setHeight(int height) {
            int width;
            SDL_GetWindowSize(m_sdlWindow, &width, nullptr);
            SDL_SetWindowSize(m_sdlWindow, width, height);
        }

        void Window::setSize(int width, int height) {
            SDL_SetWindowSize(m_sdlWindow, width, height);
        }

        void Window::setFullscreen(bool enabled) {
            SDL_SetWindowFullscreen(m_sdlWindow, enabled ? SDL_WINDOW_FULLSCREEN : 0);
        }

        void Window::setBorderless(bool enabled) {
            SDL_SetWindowBordered(m_sdlWindow, enabled ? SDL_FALSE : SDL_TRUE);
        }

        void Window::setResizable(bool enabled) {
            SDL_SetWindowResizable(m_sdlWindow, enabled ? SDL_TRUE : SDL_FALSE);
        }

        void Window::setGrabMouse(bool enabled) {
            SDL_SetWindowGrab(m_sdlWindow, enabled ? SDL_TRUE : SDL_FALSE);
        }

        bool Window::isFullscreen() const {
            return (SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_FULLSCREEN) != 0;
        }

        bool Window::isBorderless() const {
            return (SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_BORDERLESS) != 0;
        }

        bool Window::isResizable() const {
            return (SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_RESIZABLE) != 0;
        }

        bool Window::isGrabMouse() const {
            return SDL_GetWindowGrab(m_sdlWindow) == SDL_TRUE;
        }

        void Window::setPosition(int x, int y) {
            SDL_SetWindowPosition(m_sdlWindow, x, y);
        }

        std::pair<int, int> Window::getPosition() const {
            int x, y;
            SDL_GetWindowPosition(m_sdlWindow, &x, &y);
            return { x, y };
        }

        void Window::centerWindow() {
            SDL_SetWindowPosition(m_sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        }

        void Window::setMinSize(int minWidth, int minHeight) {
            SDL_SetWindowMinimumSize(m_sdlWindow, minWidth, minHeight);
        }

        void Window::setMaxSize(int maxWidth, int maxHeight) {
            SDL_SetWindowMaximumSize(m_sdlWindow, maxWidth, maxHeight);
        }

        bool Window::shouldClose() const {
            return m_isDestroyed;
        }

        void Window::setCloseRequested(bool value) {
            m_isDestroyed = value;
        }

        void Window::handleEvents() {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    m_isDestroyed = true;
                }
                else if (event.type == SDL_WINDOWEVENT) {
                    if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                        m_windowMinimized = true;
                    }
                    else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
                        m_windowMinimized = false;
                    }
                }
            }
        }

        void Window::clear() {
            // Реализация очистки окна будет зависеть от используемого API рендеринга
        }

        void Window::update() {
            // Реализация обновления окна будет зависеть от используемого API рендеринга
        }

        void Window::destroy() {
            if (m_sdlWindow) {
                if (device != VK_NULL_HANDLE) {
                    vkDestroyDevice(device, nullptr);
                    device = VK_NULL_HANDLE;
                }
                if (surface != VK_NULL_HANDLE) {
                    vkDestroySurfaceKHR(instance, surface, nullptr);
                    surface = VK_NULL_HANDLE;
                }
                if (instance != VK_NULL_HANDLE) {
                    vkDestroyInstance(instance, nullptr);
                    instance = VK_NULL_HANDLE;
                }
                SDL_DestroyWindow(m_sdlWindow);
                m_sdlWindow = nullptr;
                m_isDestroyed = true;
            }
        }

        void Window::vulkanInut()
        {
            createInstance();
            createSurface();
            pickPhysicalDevice();
            createLogicalDevice();
        }

        void Window::createInstance() {
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = SDL_GetWindowTitle(m_sdlWindow);
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "No Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;

            uint32_t extensionCount = 0;
            SDL_Vulkan_GetInstanceExtensions(m_sdlWindow, &extensionCount, nullptr);
            std::vector<const char*> extensions(extensionCount);
            SDL_Vulkan_GetInstanceExtensions(m_sdlWindow, &extensionCount, extensions.data());

            createInfo.enabledExtensionCount = extensionCount;
            createInfo.ppEnabledExtensionNames = extensions.data();
            createInfo.enabledLayerCount = 0;

            if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
                throw std::runtime_error("failed to create Vulkan instance!");
            }
        }

        void Window::pickPhysicalDevice() {
            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

            if (deviceCount == 0) {
                throw std::runtime_error("failed to find GPUs with Vulkan support!");
            }

            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

            // Вывод информации о всех доступных устройствах
            std::cout << "Available Vulkan devices:\n";
            for (const auto& device : devices) {
                VkPhysicalDeviceProperties deviceProps;
                vkGetPhysicalDeviceProperties(device, &deviceProps);

                std::cout << "  - " << deviceProps.deviceName
                    << " (API: " << VK_VERSION_MAJOR(deviceProps.apiVersion) << "."
                    << VK_VERSION_MINOR(deviceProps.apiVersion) << "."
                    << VK_VERSION_PATCH(deviceProps.apiVersion) << ")\n";
            }

            // Выбор устройства с максимальным рейтингом
            std::multimap<int, VkPhysicalDevice> candidates;
            for (const auto& device : devices) {
                int score = rateDeviceSuitability(device);
                candidates.insert(std::make_pair(score, device));
            }

            // Проверка, что лучшее устройство подходит
            if (candidates.rbegin()->first > 0) {
                physicalDevice = candidates.rbegin()->second;
            }
            else {
                throw std::runtime_error("failed to find a suitable GPU!");
            }

            // Вывод информации о выбранном устройстве
            VkPhysicalDeviceProperties deviceProps;
            vkGetPhysicalDeviceProperties(physicalDevice, &deviceProps);
            std::cout << "\nSelected Vulkan device:\n";
            std::cout << "  - Name: " << deviceProps.deviceName << "\n";
            std::cout << "  - Type: ";
            switch (deviceProps.deviceType) {
            case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: std::cout << "Integrated GPU"; break;
            case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: std::cout << "Discrete GPU"; break;
            case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: std::cout << "Virtual GPU"; break;
            case VK_PHYSICAL_DEVICE_TYPE_CPU: std::cout << "CPU"; break;
            default: std::cout << "Other"; break;
            }
            std::cout << "\n";
            std::cout << "  - API Version: " << VK_VERSION_MAJOR(deviceProps.apiVersion) << "."
                << VK_VERSION_MINOR(deviceProps.apiVersion) << "."
                << VK_VERSION_PATCH(deviceProps.apiVersion) << "\n";
            std::cout << "  - Driver Version: " << deviceProps.driverVersion << "\n";
            std::cout << "  - Vendor ID: " << deviceProps.vendorID << "\n";
            std::cout << "  - Device ID: " << deviceProps.deviceID << "\n";
            std::cout << "  - Score: " << candidates.rbegin()->first << "\n\n";
        }

        int Window::rateDeviceSuitability(VkPhysicalDevice device) {
            VkPhysicalDeviceProperties deviceProps;
            VkPhysicalDeviceFeatures deviceFeatures;
            vkGetPhysicalDeviceProperties(device, &deviceProps);
            vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

            int score = 0;

            // Вывод дополнительной информации при оценке
            std::cout << "\nEvaluating device: " << deviceProps.deviceName << "\n";
            std::cout << "  - Device type: ";
            switch (deviceProps.deviceType) {
            case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: std::cout << "Integrated GPU"; break;
            case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: std::cout << "Discrete GPU"; break;
            case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: std::cout << "Virtual GPU"; break;
            case VK_PHYSICAL_DEVICE_TYPE_CPU: std::cout << "CPU"; break;
            default: std::cout << "Other"; break;
            }
            std::cout << "\n";

            // Дискретные GPU имеют преимущество в производительности
            if (deviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                score += 1000;
                std::cout << "  + 1000 points for discrete GPU\n";
            }

            // Максимальный размер текстур влияет на качество графики
            score += deviceProps.limits.maxImageDimension2D;
            std::cout << "  + " << deviceProps.limits.maxImageDimension2D
                << " points for max image dimension ("
                << deviceProps.limits.maxImageDimension2D << ")\n";

            // Приложение не может работать без geometry shader
            if (!deviceFeatures.geometryShader) {
                std::cout << "  - Device rejected (no geometry shader support)\n";
                return 0;
            }

            // Проверка поддержки необходимых очередей
            if (!isDeviceSuitable(device)) {
                std::cout << "  - Device rejected (missing required queue families)\n";
                return 0;
            }

            std::cout << "  - Total score: " << score << "\n";

            return score;
        }

        QueueFamilyIndices Window::findQueueFamilies(VkPhysicalDevice device) {
            QueueFamilyIndices indices;

            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

            std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

            int i = 0;
            for (const auto& queueFamily : queueFamilies) {
                if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                    indices.graphicsFamily = i;
                }

                VkBool32 presentSupport = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
                if (presentSupport) {
                    indices.presentFamily = i;
                }

                if (indices.isComplete()) {
                    break;
                }

                i++;
            }

            return indices;
        }

        void Window::createLogicalDevice() {
            if (!isDeviceSuitable(physicalDevice)) {
                throw std::runtime_error("queue families not complete!");
            }

            QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
            std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
            std::set<uint32_t> uniqueQueueFamilies = {
                indices.graphicsFamily.value(),
                indices.presentFamily.value()
            };

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

            VkDeviceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
            createInfo.pQueueCreateInfos = queueCreateInfos.data();
            createInfo.pEnabledFeatures = &deviceFeatures;
            createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
            createInfo.ppEnabledExtensionNames = deviceExtensions.data();
            createInfo.enabledLayerCount = 0;

            if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
                throw std::runtime_error("failed to create logical device!");
            }

            vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
            vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
        }

        void Window::createSurface() {
            if (!SDL_Vulkan_CreateSurface(m_sdlWindow, instance, &surface)) {
                throw std::runtime_error("failed to create window surface!");
            }
        }

        bool Window::isDeviceSuitable(VkPhysicalDevice device) {
            QueueFamilyIndices indices = findQueueFamilies(device);

            bool extensionsSupported = checkDeviceExtensionSupport(device);

            return indices.isComplete() && extensionsSupported;
        }

        bool Window::checkDeviceExtensionSupport(VkPhysicalDevice device) {
            uint32_t extensionCount;
            vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

            std::vector<VkExtensionProperties> availableExtensions(extensionCount);
            vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

            std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

            for (const auto& extension : availableExtensions) {
                requiredExtensions.erase(extension.extensionName);
            }

            return requiredExtensions.empty();
        }

    } // namespace view
} // namespace prism