# ----------------------------------------------------------------------------
# Список исходников ECS (из основной библиотеки PrismEngine)
# ----------------------------------------------------------------------------
set(ECS_SOURCES
    ${CMAKE_SOURCE_DIR}/PrismEngine/src/entityManager.cpp
    ${CMAKE_SOURCE_DIR}/PrismEngine/src/componentManager.cpp
    ${CMAKE_SOURCE_DIR}/PrismEngine/src/systemManager.cpp
    ${CMAKE_SOURCE_DIR}/PrismEngine/src/scene.cpp
)

# ----------------------------------------------------------------------------
# Исполняемый файл бенчмарков (ваш код + ECS)
# ----------------------------------------------------------------------------
add_executable(benchmarks
    benchmarks.cpp
    ${ECS_SOURCES}
)

# ----------------------------------------------------------------------------
# Пути для поиска заголовков
# ----------------------------------------------------------------------------
target_include_directories(benchmarks PRIVATE
    ${CMAKE_SOURCE_DIR}/PrismEngine/src          # заголовки ECS (scene.h и т.д.)
    ${CMAKE_SOURCE_DIR}/libs/benchmark/include   # Google Benchmark
)

# ----------------------------------------------------------------------------
# Пути для библиотек Google Benchmark (предварительно собран)
# ----------------------------------------------------------------------------
target_link_directories(benchmarks PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/benchmark/lib/$<CONFIG>
)

# ----------------------------------------------------------------------------
# Линковка: только benchmark и системные библиотеки
# ----------------------------------------------------------------------------
target_link_libraries(benchmarks PRIVATE
    benchmark        # benchmark.lib
    benchmark_main   # benchmark_main.lib (точка входа)
    shlwapi.lib      # из .vcxproj (Windows)
)

# ----------------------------------------------------------------------------
# Определения препроцессора
# ----------------------------------------------------------------------------
target_compile_definitions(benchmarks PRIVATE
    BENCHMARK_STATIC_DEFINE        # для статической линковки Google Benchmark
    $<$<CONFIG:Debug>:_DEBUG>     # опционально
    $<$<CONFIG:Release>:NDEBUG>
)

# ----------------------------------------------------------------------------
# Настройки компилятора (MSVC)
# ----------------------------------------------------------------------------
if(MSVC)
    target_compile_options(benchmarks PRIVATE
        /W3
        /std:c++17
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Release>:/O2>
    )
endif()

# ----------------------------------------------------------------------------
# Выходная директория (как у examples)
# ----------------------------------------------------------------------------
set_target_properties(benchmarks PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    FOLDER "Benchmarks"
)