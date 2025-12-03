#version 450

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

struct ObjectData {
    mat4 model;
    mat4 normals;
    uint textureIndex;
};

layout(std430, binding = 1) readonly buffer ObjectSSBO {
    ObjectData objects[];
} ssbo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out flat uint fragTextureIndex;
layout(location = 3) out vec3 fragNormal;
layout(location = 4) out vec3 fragPos;

void main() {
    ObjectData object = ssbo.objects[gl_InstanceIndex];

    vec4 worldPos = object.model * vec4(inPosition, 1.0);
    gl_Position = camera.proj * camera.view * object.model * vec4(inPosition, 1.0);

	fragColor = inColor;
  fragTexCoord = inTexCoord;
  fragTextureIndex = object.textureIndex;
	fragNormal = mat3(object.normals) * inNormal;
  fragPos = worldPos.xyz;
}
