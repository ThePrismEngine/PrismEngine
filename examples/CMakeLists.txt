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

# Включение директорий
target_include_directories(PrismExamples PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/PrismEngine/src
    ${VULKAN_SDK_PATH}/Include
    ${SDL2_PATH}/include
    ${GLM_PATH}
    ${STB_IMAGE_PATH}
)

# Компиляционные определения
target_compile_definitions(PrismExamples PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    _CONSOLE
)

# Настройки компилятора
if(MSVC)
    target_compile_options(PrismExamples PRIVATE
        /W3
        /std:c++17
    )
    target_link_options(PrismExamples PRIVATE /SUBSYSTEM:CONSOLE)
endif()

# Линковка
target_link_libraries(PrismExamples PRIVATE
    PrismEngine
    ${VULKAN_SDK_PATH}/Lib/vulkan-1.lib
    ${SDL2_PATH}/lib/x64/SDL2.lib
    ${SDL2_PATH}/lib/x64/SDL2main.lib
    opengl32.lib
)

# Выходные директории
set_target_properties(PrismExamples PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    FOLDER "Examples"
)
