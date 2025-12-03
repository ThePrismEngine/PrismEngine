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

// Функция для расчета затухания
float calculateAttenuation(float distance, float radius) {
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);
    float maxDistance = radius;
    attenuation *= 1.0 - smoothstep(maxDistance * 0.75, maxDistance, distance);
    return attenuation;
}

// Функция расчета освещения
vec3 calculateLighting(vec3 normal, vec3 viewDir, vec3 diffuseColor) {
    vec3 result = vec3(0.0);

    // Ambient lighting
    result += camera.ambientColor * camera.ambientIntensity * diffuseColor;

    // Directional lights
    for (uint i = 0; i < camera.directionalLightCount; i++) {
        DirectionalLight light = directionalLights.lights[i];

        vec3 lightDir = normalize(-light.direction);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = light.color * diff * light.intensity;

        result += diffuse * diffuseColor;
    }

    // Point lights
    for (uint i = 0; i < camera.pointLightCount; i++) {
        PointLight light = pointLights.lights[i];

        vec3 lightDir = normalize(light.position - fragPos);
        float distance = length(light.position - fragPos);
        float attenuation = calculateAttenuation(distance, light.radius);

        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = light.color * diff * light.intensity * attenuation;

        result += diffuse * diffuseColor;
    }

    return result;
}


void main() {
    vec4 texColor;
    if (fragTextureIndex == 0) {
        texColor = vec4(fragColor, 1.0);
    } else {
        texColor = texture(textures[nonuniformEXT(fragTextureIndex)], fragTexCoord);
    }

	// Нормализуем нормаль (интерполяция может сделать ее неединичной)
    vec3 normal = normalize(fragNormal);

    // Вектор направления взгляда
    vec3 viewDir = normalize(camera.cameraPos - fragPos);

    // Расчет освещения
    vec3 diffuseColor = texColor.rgb;
    vec3 finalColor = calculateLighting(normal, viewDir, diffuseColor);

    outColor = vec4(finalColor, texColor.a);
}
