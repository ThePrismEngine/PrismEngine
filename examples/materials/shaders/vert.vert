#version 450

layout(binding = 0) uniform CameraUBO {
    mat4 view;
    mat4 proj;
    mat4 viewProj;
    vec3 cameraPos;
} camera;

struct ObjectData {
    mat4 model;
    mat4 normals;
    uint textureIndex;
};

// Runtime-sized array - должен быть последним полем
layout(std430, binding = 1) readonly buffer ObjectSSBO {
    ObjectData objects[];
} ssbo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out flat uint fragTextureIndex;

void main() {
    // Индексируем runtime-sized array через gl_InstanceIndex
    ObjectData object = ssbo.objects[gl_InstanceIndex];
    
    gl_Position = camera.proj * camera.view * object.model * vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
    fragTextureIndex = object.textureIndex;
}