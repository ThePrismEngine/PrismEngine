#version 450
#extension GL_EXT_nonuniform_qualifier : enable

// Bindless текстуры (set = 1, binding = 0)
layout(set = 1, binding = 0) uniform sampler2D textures[];

layout(binding = 0) uniform CameraUBO {
    mat4 view;
    mat4 proj;
    mat4 viewProj;
    vec3 cameraPos;
    vec3 ambientColor;
    float ambientIntensity;
    uint pointLightCount;
    uint directionalLightCount;
} camera;

// Point lights SSBO
struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float radius;
};

layout(std430, binding = 2) readonly buffer PointLightsSSBO {
    PointLight lights[];
} pointLights;

// Directional lights SSBO
struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

layout(std430, binding = 3) readonly buffer DirectionalLightsSSBO {
    DirectionalLight lights[];
} directionalLights;

// Входные данные от вершинного шейдера
layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in flat uint fragTextureIndex;
layout(location = 3) in vec3 fragNormal;
layout(location = 4) in vec3 fragPos;

layout(location = 0) out vec4 outColor;

void main() {
    // Простой диагностический вывод - используем разные цвета для разных атрибутов

    // Вариант 1: Цвет вершины
    // outColor = vec4(fragColor, 1.0);

    // Вариант 2: UV координаты (должны быть плавными)
    // outColor = vec4(fragTexCoord, 0.0, 1.0);

    // Вариант 3: Нормали (должны быть в диапазоне [-1,1], преобразуем в [0,1])
    // outColor = vec4(normalize(fragNormal) * 0.6 + 0.4, 1.0);

    // Вариант 4: Позиция в мире
    outColor = vec4(fract(fragPos * 0.1), 1.0);

    // Вариант 5: Индекс текстуры по инстансу (разные цвета для разных инстансов)
    //if (fragTextureIndex == 0) {
    //    outColor = vec4(1.0, 0.0, 0.0, 1.0); // Красный
    //} else if (fragTextureIndex == 1) {
    //    outColor = vec4(0.0, 1.0, 0.0, 1.0); // Зеленый
    //} else if (fragTextureIndex == 2) {
    //    outColor = vec4(0.0, 0.0, 1.0, 1.0); // Синий
    //} else {
    //    outColor = vec4(1.0, 1.0, 0.0, 1.0); // Желтый для остальных
    //}

    // Вариант 6: Простая проверка - если видим черный экран, значит проблема в данных
    // outColor = vec4(0.0, 0.5, 0.5, 1.0); // Тестовый цвет
}
