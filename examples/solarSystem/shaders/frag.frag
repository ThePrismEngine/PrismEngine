#version 450
#extension GL_EXT_nonuniform_qualifier : enable

// Bindless текстуры (set = 1, binding = 0)
layout(set = 1, binding = 0) uniform sampler2D textures[];

// Push-константы для индекса текстуры
layout(push_constant) uniform PushConstants {
    int textureIndex;
} push;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    // Используем nonuniformEXT для безопасного доступа к текстуре по индексу
    vec4 texColor = texture(textures[nonuniformEXT(push.textureIndex)], fragTexCoord);
    // Комбинированная проверка на нулевой индекс
    float useVertexColor = float(push.textureIndex == 0);

    outColor = mix(texColor, vec4(fragColor, 1.0), useVertexColor);
}
