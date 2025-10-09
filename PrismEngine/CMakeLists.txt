# Список исходных файлов
file(GLOB PRISM_SOURCES
    "src/*.cpp"
)

file(GLOB PRISM_HEADERS
    "src/*.h"
)

# Создание статической библиотеки
add_library(PrismEngine STATIC ${PRISM_SOURCES} ${PRISM_HEADERS})

# Включение директорий
target_include_directories(PrismEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${VULKAN_SDK_PATH}/Include
    ${SDL2_PATH}/include
    ${GLM_PATH}
    ${STB_IMAGE_PATH}
    ${TINYOBJLOADER_PATH}
)

# Компиляционные определения
target_compile_definitions(PrismEngine PRIVATE
    PRISM_VULKAN
    UNICODE
    _UNICODE
)

# Настройки компилятора
if(MSVC)
    target_compile_options(PrismEngine PRIVATE
        /W3
        /std:c++17
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Release>:/O2>
    )
endif()

# Линковка библиотек
target_link_libraries(PrismEngine PRIVATE
    ${VULKAN_SDK_PATH}/Lib/vulkan-1.lib
    ${SDL2_PATH}/lib/x64/SDL2.lib
    ${SDL2_PATH}/lib/x64/SDL2main.lib
    opengl32.lib
)

# Выходные директории
set_target_properties(PrismEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Группировка в IDE
set_target_properties(PrismEngine PROPERTIES FOLDER "Libraries")
