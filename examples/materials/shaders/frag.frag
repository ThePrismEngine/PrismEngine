#version 450
#extension GL_EXT_nonuniform_qualifier : enable

// Bindless текстуры (set = 1, binding = 0)
layout(set = 1, binding = 0) uniform sampler2D textures[];

// Входные данные от вершинного шейдера
layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in flat uint fragTextureIndex; // Добавляем индекс текстуры из вершинного шейдера

layout(location = 0) out vec4 outColor;

void main() {
    // Если текстура невалидна (INVALID_TEXTURE_ID), используем цвет вершины
    if (fragTextureIndex == 0) { // Предполагаем, что 0 = INVALID_TEXTURE_ID
        outColor = vec4(fragColor, 1.0);
    } else {
        // Используем nonuniformEXT для безопасного доступа к текстуре по индексу
        vec4 texColor = texture(textures[nonuniformEXT(fragTextureIndex)], fragTexCoord);
        outColor = texColor;
    }
}