# Список исходных файлов
file(GLOB PRISM_SOURCES
    "src/*.cpp"
)

file(GLOB PRISM_HEADERS
    "src/*.h"
)

# Создание статической библиотеки
add_library(PrismEngine STATIC ${PRISM_SOURCES} ${PRISM_HEADERS})

# Кросс-платформенная настройка зависимостей
if(WIN32)
    # Windows настройки
    target_include_directories(PrismEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${VULKAN_SDK_PATH}/Include
        ${SDL2_PATH}/include
        ${GLM_PATH}
        ${STB_IMAGE_PATH}
        ${TINYOBJLOADER_PATH}
    )

    target_link_libraries(PrismEngine PRIVATE
        ${VULKAN_SDK_PATH}/Lib/vulkan-1.lib
        ${SDL2_PATH}/lib/x64/SDL2.lib
        ${SDL2_PATH}/lib/x64/SDL2main.lib
        opengl32.lib
    )
else()
    # Linux настройки с pkg-config
    find_package(PkgConfig REQUIRED)

    # Поиск SDL2
    pkg_check_modules(SDL2 REQUIRED sdl2)

    # Поиск Vulkan
    find_package(Vulkan REQUIRED)

    # Поиск OpenGL
    find_package(OpenGL REQUIRED)

    # Включение директорий для Linux
    target_include_directories(PrismEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${GLM_PATH}
        ${STB_IMAGE_PATH}
        ${TINYOBJLOADER_PATH}
    )

    target_include_directories(PrismEngine PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${Vulkan_INCLUDE_DIRS}
    )

    # Линковка для Linux
    target_link_libraries(PrismEngine PRIVATE
        ${SDL2_LIBRARIES}
        Vulkan::Vulkan
        OpenGL::GL
    )
endif()

# Общие настройки для всех платформ
target_compile_definitions(PrismEngine PRIVATE
    PRISM_VULKAN
)

if(WIN32)
    target_compile_definitions(PrismEngine PRIVATE
        UNICODE
        _UNICODE
    )
endif()

# Настройки компилятора
if(MSVC)
    target_compile_options(PrismEngine PRIVATE
        /W3
        /std:c++17
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Release>:/O2>
    )
else()
    target_compile_options(PrismEngine PRIVATE
        -Wall
        -Wextra
        -std=c++17
    )
endif()

# Выходные директории
set_target_properties(PrismEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Группировка в IDE
set_target_properties(PrismEngine PROPERTIES FOLDER "Libraries")
