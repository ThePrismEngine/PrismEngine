# Список примеров
set(EXAMPLES_SOURCES
    examples.cpp
    examples.h
    spinningCube/spinningСube.cpp
    spinningPrism/spinningPrism.cpp
    solarSystem/solarSystem.cpp
    dancingNeonCubes/dancingNeonCubes.cpp
)

# Создание исполняемого файла
add_executable(PrismExamples ${EXAMPLES_SOURCES})

# Кросс-платформенная настройка зависимостей
if(WIN32)
    # Windows настройки
    target_include_directories(PrismExamples PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/PrismEngine/src
        ${VULKAN_SDK_PATH}/Include
        ${SDL2_PATH}/include
        ${GLM_PATH}
        ${STB_IMAGE_PATH}
    )

    target_link_libraries(PrismExamples PRIVATE
        PrismEngine
        ${VULKAN_SDK_PATH}/Lib/vulkan-1.lib
        ${SDL2_PATH}/lib/x64/SDL2.lib
        ${SDL2_PATH}/lib/x64/SDL2main.lib
        opengl32.lib
    )
else()
    # Linux настройки
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    find_package(Vulkan REQUIRED)
    find_package(OpenGL REQUIRED)

    target_include_directories(PrismExamples PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/PrismEngine/src
        ${GLM_PATH}
        ${STB_IMAGE_PATH}
        ${SDL2_INCLUDE_DIRS}
        ${Vulkan_INCLUDE_DIRS}
    )

    target_link_libraries(PrismExamples PRIVATE
        PrismEngine
        ${SDL2_LIBRARIES}
        Vulkan::Vulkan
        OpenGL::GL
    )
endif()

# Общие настройки для всех платформ
target_compile_definitions(PrismExamples PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

if(WIN32)
    target_compile_definitions(PrismExamples PRIVATE
        _CONSOLE
        UNICODE
        _UNICODE
    )
endif()

# Настройки компилятора
if(MSVC)
    target_compile_options(PrismExamples PRIVATE
        /W3
        /std:c++17
    )
    target_link_options(PrismExamples PRIVATE /SUBSYSTEM:CONSOLE)
else()
    target_compile_options(PrismExamples PRIVATE
        -Wall
        -Wextra
        -std=c++17
    )
endif()

# Выходные директории
set_target_properties(PrismExamples PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    FOLDER "Examples"
)
