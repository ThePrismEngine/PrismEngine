<div align="center">
  <a href="https://github.com/Aleksei-Kutuzov/PrismEngine">
    <img src="https://github.com/Aleksei-Kutuzov/PrismEngine/blob/master/docs/source/_static/logo.png?raw=true" alt="Repo Logo" height="100">
  </a>
</div>

<h3 align="center">PrismEngine</h3>

<div align="center">Современный, производительный, кроссплатформенный 3d движок.PrismEngine имеет ECS (Entity-Component-System) API. Написан на c++, а рендер испльзует графическое API Vulkan</div>

<div align="center">
  <img alt="GitHub top language" src="https://shields.foxteam.ru/github/languages/top/Aleksei-Kutuzov/PrismEngine?style=plastic">
  <img alt="GitHub License" src="https://shields.foxteam.ru/github/license/Aleksei-Kutuzov/PrismEngine">
  <img alt="GitHub Release" src="https://shields.foxteam.ru/github/v/release/Aleksei-Kutuzov/PrismEngine">
  <img src="https://img.shields.io/github/stars/Aleksei-Kutuzov/PrismEngine.svg?labelColor=003694&color=ffffff" alt="Stars">
  <img src="https://img.shields.io/github/issues/Aleksei-Kutuzov/PrismEngine.svg?labelColor=003694&color=ffffff" alt="Issues">

  <img alt="Platform" src="https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-blue">
  <img alt="Vulkan" src="https://img.shields.io/badge/Vulkan-1.3-AC162C?logo=vulkan">
</div>

<br>

<details>
<summary><strong>Table of Contents 📜</strong></summary>

- [Демо 🎮](#демо-)
- [Особенности ✨](#особенности-)
- [Быстрый старт 🚀](#быстрый-старт-)
  - [Предварительные требования 📋](#предварительные-требования-)
  - [Установка 📥](#установка-)
    - [Windows 🪟](#windows-)
    - [Linux 🐧](#linux-)
    - [macOS 🍎](#macos-)
- [Использование 🛠️](#использование-️)
  - [Базовый пример 📝](#базовый-пример-)
  - [Продвинутое использование 🦾](#продвинутое-использование-)
- [Сборка проекта 🔧](#сборка-проекта-)
- [Документация 📖](#документация-)
- [Планы развития 🗺️](#планы-развития-️)
- [Технологии 🛠️](#технологии-️)
- [Разработчики 🧙‍♂️](#разработчики-️)
- [Благодарности 💝](#благодарности-)
- [Лицензия 📄](#лицензия-)

</details>

## Демо 🎮
[//]: # (Здесь добавьте GIF/видео/скриншоты вашего движка в действии)
![Demo Scene](https://via.placeholder.com/800x450.png?text=PrismEngine+Demo)
*Пример работы движка: PBR рендеринг, динамическое освещение, пост-обработка*


## Особенности ✨
- **🚀 Vulkan рендерер**: Современный графический конвейер с поддержкой самых разных графических ускорителей
- **🏗️ ECS архитектура**: Высокопроизводительная система Entity-Component-System
- **🌍 Кроссплатформенность**: Поддержка Windows, Linux, macOS
- **📘 Документация**: Содержит описание и внешнего API и вутреннего
- **⚡ Оптимизация**: Современные тенденции оптимизации рендеринга
- **🎮 VR поддержка**: Совместимость с OpenXR за счет SDL
- **🔧 Hot-reload**: Перекомпиляция шейдеров, пересоздание рендера на лету
- **⚙️ Настройка рендера** Возможность широкой настройки (от шейдеров до выбора предпочтительного GPU)


### Предварительные требования 📋
- Microsoft Visual Studio (желательно v2022)
- C++17 компилятор
- Vulkan SDK 1.3+

### Установка 📥 **//TODO CMAKE**

#### Windows 🪟

1. Navigate to the latest release of the repo
2. Under assets, download the `release_for_windows.zip`

#### MacOS 🍎

1. Navigate to the latest release of the repo
2. Under assets, download the `release_for_mac.zip`

#### Linux 🐧

1. Navigate to the latest release of the repo
2. Under assets, download the `release_for_linux.zip`


## Использование 🛠️

### Базовый пример 📝
```cpp
#include <prism/scene.h>

// 1. Создаем сцену
prism::scene::Scene scene;

// 2. Создаем сущность игрока
auto player = scene.createEntity();

// 3. Добавляем компоненты
scene.addComponent<Transform>(player, Transform{0, 0, 0});
scene.addComponent<Velocity>(player, Velocity{0.2, 0.4, 0});
scene.addComponent<Health>(player, Health{100});

class MovementSystem : public prism::scene::ISystem {
public:
    void update(float deltaTime) override {
        auto entities = scene->getEntitiesWith<Transform, Velocity>();
        for (auto entity : entities) {
            auto* transform = scene->getComponent<Transform>(entity);
            auto* velocity = scene->getComponent<Velocity>(entity);
            transform->position.x += velocity->x * deltaTime;
        }
    }
};

// 4. Регистрируем систему
scene.registerSystem<MovementSystem>();

// 5. Обновление
void gameLoop() {
    while (running) {
        float deltaTime = getDeltaTime();
        scene.update(deltaTime);
    }
}
```

### Продвинутое использование 🦾
<details>


```cpp
#include "PrismEngine.h"
#include <iostream>
#include <chrono>
#include <scene.h>
#include <renderSystem.h>
#include <meshComponent.h>
#include <textureComponent.h>

#undef main
using namespace prism::scene;

class FlyCameraSystem : public ISystem {
public:
    FlyCameraSystem(Scene* scene) : scene(scene) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }

    void update(float deltaTime) override {
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
            float speed = 5.0f * deltaTime;
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
    ObjectRotationSystem(Scene* scene) : scene(scene) {}

    void update(float deltaTime) override {
        auto entities = scene->getEntitiesWithAll<TransformComponent, MeshComponent>();
        for (auto entity : entities) {
            TransformComponent* transform = scene->getComponent<TransformComponent>(entity);
            transform->rot.y += 30.0f * deltaTime;
        }
    }

private:
    Scene* scene;
};

int main() {
    prism::init();

    Scene scene;
    prism::render::Window w = prism::render::Window("Fly Camera Demo", 1200, 800);
    w.setResizable(true);

    prism::render::Renderer r = prism::render::Renderer();
    r.linkWindow(&w);
    r.setDefaultSettings();
    r.settings.pipeline.rasterization.polygonMode = VK_POLYGON_MODE_FILL;

    const std::string MODEL_PATH = "models/t1/SovietBall.obj";
    const std::string TEXTURE_PATH = "models/t1/SovietBall_BaseColor.png";

    r.init();

    MeshComponent mainMesh = r.addMesh(MODEL_PATH);
    r.updateMeshes();
    TextureComponent mainTexture = r.addTexture(TEXTURE_PATH);

    scene.registerSystem<RenderSystem>(&scene, &r);
    scene.registerSystem<FlyCameraSystem>(&scene);
    scene.registerSystem<ObjectRotationSystem>(&scene);

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
    for (int x = -2; x <= 2; x++) {
        for (int z = -2; z <= 2; z++) {
            Entity obj = scene.createEntity();
            scene.addComponent<TransformComponent>(obj, {
                {(float)x * 4.f, 0.f, (float)z * 4.f},
                {-90.f, 0.f, 0.f},
                {0.3f, 0.3f, 0.3f}
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

        scene.update(deltaTime);
    }

    r.awaitRenderingCompletion();
    r.destroy();

    return 0;
}
```

</details>

## Документация 📖
- [📚 Полная документация](https://prismengine.readthedocs.io/ru/latest)
- [🎓 Примеры кода](/examples) **//TODO**
- [📖 API Reference](https://prismengine.readthedocs.io/ru/latest/modules/ecs/public/api_reference.html) **//TODO**

## Планы развития 🗺️
- [ ] Физически корректный рендеринг
- [ ] Расширение ESC и архитектуры
- [ ] Полная портация на android
- [ ] Физическое ядро
- [ ] Вычислительное ядро
- [ ] Поддержка трассировки путей (Path Tracing)
- [ ] Расширение форматов моделей
- [ ] Сериализация и взаимодействие но интернету

## Технологии 🛠️
- **Графика**: Vulkan, SPIR-V, GLSL
- **Математика**: GLM
- **Окна и взаимодействие**: SDL
- **Ассеты**: tiny_obj_loader, stb_image

## Разработчики 🧙‍♂️
- **Алексей Кутузов** - [@Aleksei-Kutuzov](https://github.com/Aleksei-Kutuzov) - Lead Developer

## Благодарности 💝
- [Vulkan Community](https://www.vulkan.org/)
- [Khronos Group](https://www.khronos.org/)

## Лицензия 📄
Этот проект лицензирован под MIT License - смотрите [LICENSE](LICENSE) файл для деталей.
