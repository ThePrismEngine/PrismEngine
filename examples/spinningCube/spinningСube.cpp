#include "PrismEngine.h"
#include <iostream>
#include <chrono>
#include <scene.h>
#include <renderSystem.h>
#include <meshComponent.h>
#include <textureComponent.h>
#include "../examples.h"
#include <timeResource.h>

#undef main

const std::string exampleName = "spinningCube";
using namespace prism::scene;

class FlyCameraSystem : public ISystem {
public:
    FlyCameraSystem(Scene* scene) : scene(scene) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }

    void update() override {
        const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
        auto entities = scene->getEntitiesWithAll<TransformComponent, CameraComponent>();

        for (auto entity : entities) {
            TransformComponent* transform = scene->getComponent<TransformComponent>(entity);
            CameraComponent* camera = scene->getComponent<CameraComponent>(entity);

            if (!camera->isActive) continue;

            // Обработка мыши
            int mouseX, mouseY;
            SDL_GetRelativeMouseState(&mouseX, &mouseY);

            float sensitivity = 0.1f;
            camera->look.x += mouseX * sensitivity;
            camera->look.y -= mouseY * sensitivity;

            if (camera->look.y > 89.0f) camera->look.y = 89.0f;
            if (camera->look.y < -89.0f) camera->look.y = -89.0f;

            // Движение относительно камеры
            float speed = 5.0f * scene->getResource<TimeResource>()->deltaTime;
            if (keyboardState[SDL_SCANCODE_LCTRL]) speed *= 3.0f;

            // Вычисляем направление камеры
            glm::vec3 front;
            front.x = cos(glm::radians(camera->look.x)) * cos(glm::radians(camera->look.y));
            front.y = sin(glm::radians(camera->look.y));
            front.z = sin(glm::radians(camera->look.x)) * cos(glm::radians(camera->look.y));
            front = glm::normalize(front);

            glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

            // Движение - применяем к правильным координатам
            if (keyboardState[SDL_SCANCODE_W]) {
                transform->pos.x += front.x * speed;
                transform->pos.y += front.y * speed;
                transform->pos.z += front.z * speed;
            }
            if (keyboardState[SDL_SCANCODE_S]) {
                transform->pos.x -= front.x * speed;
                transform->pos.y -= front.y * speed;
                transform->pos.z -= front.z * speed;
            }
            if (keyboardState[SDL_SCANCODE_A]) {
                transform->pos.x -= right.x * speed;
                transform->pos.z -= right.z * speed;
            }
            if (keyboardState[SDL_SCANCODE_D]) {
                transform->pos.x += right.x * speed;
                transform->pos.z += right.z * speed;
            }
            if (keyboardState[SDL_SCANCODE_SPACE]) transform->pos.y += speed;
            if (keyboardState[SDL_SCANCODE_LSHIFT]) transform->pos.y -= speed;
        }
    }

private:
    Scene* scene;
};

class ObjectRotationSystem : public ISystem {
public:
    ObjectRotationSystem(Scene* scene, float* time) : scene(scene), time(time) {}

    void update() override {
        auto entities = scene->getEntitiesWithAll<TransformComponent, MeshComponent>();
        for (auto entity : entities) {
            TransformComponent* transform = scene->getComponent<TransformComponent>(entity);
            transform->pos.y = sin(*time / 20 + (transform->pos.x + transform->pos.z) / 5);
        }
    }

private:
    Scene* scene;
    float* time;
};

int demo1() {
    prism::init();

    Scene scene;
    prism::render::Window w = prism::render::Window("Fly Camera Demo", 1200, 800);
    w.setResizable(true);

    prism::render::Renderer r = prism::render::Renderer();
    r.linkWindow(&w);
    r.setDefaultSettings();
    r.settings.pipeline.rasterization.polygonMode = VK_POLYGON_MODE_FILL;
    r.settings.pipeline.shaders = { "vert.spv", "frag.spv", exampleName + "/shaders/"};

    const std::string MODEL_PATH = exampleName + "/models/cube.obj";
    const std::string TEXTURE_PATH = exampleName + "/textures/grass_texture.png";
    const std::string TEXTURE_PATH2 = exampleName + "/textures/nograss_texture.png";

    r.init();

    MeshComponent mainMesh = r.addMesh(MODEL_PATH);
    r.updateMeshes();
    TextureComponent mainTexture = r.addTexture(TEXTURE_PATH);

    float time = 0.f;

    scene.registerSystem<RenderSystem>(&scene, &r);
    scene.registerSystem<FlyCameraSystem>(&scene);
    scene.registerSystem<ObjectRotationSystem>(&scene, &time);

    // Камера
    Entity camera = scene.createEntity();
    scene.addComponent<TransformComponent>(camera, {
        {0.f, 0.f, 3.f},
        {0.f, 0.f, 0.f},
        {1.f, 1.f, 1.f}
        });

    CameraComponent camComponent{};
    camComponent.isActive = true;
    camComponent.fovy = 45.0f;
    camComponent.zNear = 0.1f;
    camComponent.zFar = 100.0f;
    camComponent.look = { 0.0f, 0.0f, 0.0f };
    scene.addComponent<CameraComponent>(camera, camComponent);


    // Создаем сетку объектов для лучшей ориентации
    for (int x = -10; x <= 11; x++) {
        for (int z = -11; z <= 11; z++) {
            Entity obj = scene.createEntity();
            scene.addComponent<TransformComponent>(obj, {
                {(float)x * 2.f, 0.f, (float)z * 2.f},
                {0.f, 0.f, 90.f},
                {1.f, 1.0f, 1.0f}
                });
            scene.addComponent<MeshComponent>(obj, mainMesh);
            scene.addComponent<TextureComponent>(obj, mainTexture);
        }
    }

    std::cout << "Fly Camera Controls:" << std::endl;
    std::cout << "WASD - Move relative to camera direction" << std::endl;
    std::cout << "Space/Shift - Up/Down" << std::endl;
    std::cout << "Mouse - Rotate camera" << std::endl;
    std::cout << "Ctrl - Speed boost" << std::endl;
    std::cout << "Escape - Release mouse" << std::endl;

    auto lastTime = std::chrono::high_resolution_clock::now();

    while (!w.shouldClose()) {
        w.handleEvents();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        time++;
        scene.update();
        SDL_Delay(10);
    }

    r.awaitRenderingCompletion();
    r.destroy();

    return 0;
}