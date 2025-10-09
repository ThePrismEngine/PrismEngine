cmake_minimum_required(VERSION 3.16)

project(PrismEngine
    VERSION 1.0.0
    DESCRIPTION "Prism Engine - Vulkan Graphics Engine"
    LANGUAGES CXX
)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Конфигурации сборки
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configurations" FORCE)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Включение папок в IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Настройка путей для зависимостей
set(VULKAN_SDK_PATH "$ENV{VULKAN_SDK}")
if(NOT VULKAN_SDK_PATH)
    set(VULKAN_SDK_PATH "C:/VulkanSDK/1.4.309.0")
endif()

set(SDL2_PATH "${CMAKE_SOURCE_DIR}/libs/SDL2-2.30.9")
set(GLM_PATH "${CMAKE_SOURCE_DIR}/libs/glm")
set(STB_IMAGE_PATH "${CMAKE_SOURCE_DIR}/libs/stb_image")
set(TINYOBJLOADER_PATH "${CMAKE_SOURCE_DIR}/libs/tinyobjloader")

# Проверка существования путей
if(NOT EXISTS ${SDL2_PATH})
    message(WARNING "SDL2 not found at: ${SDL2_PATH}")
endif()

if(NOT EXISTS ${VULKAN_SDK_PATH})
    message(WARNING "Vulkan SDK not found at: ${VULKAN_SDK_PATH}")
endif()

# Поддиректории
add_subdirectory(PrismEngine)
add_subdirectory(examples)
