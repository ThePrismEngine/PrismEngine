#include "PrismEngine.h"

const std::string EXAMPLE_NAME = "solarSystem";
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

std::vector<std::string> CelestialObjectRes
{
    "Sun",
    "Mercury",
    "Venus",
    "Earth",
    "Mars",
    "Jupiter",
    "Saturn",
    "Uranus",
    "Neptune",
};

using namespace prism::scene;

struct PlanetaryBodyComponent {
    Position* center;        // Центр орбиты
    float orbitRadius=0;      // Радиус орбиты
    float orbitalSpeed=0;     // Скорость движения по орбите (градусов/секунду)
    float orbitAngle=0;       // Текущий угол на орбите
    float rotationSpeed=0;    // Скорость вращения вокруг своей оси (градусов/секунду)
};

class PlanetarySystem : public ISystem {
public:
    PlanetarySystem(Scene* scene) : scene(scene) {}

    void update(float deltaTime) override {
        auto entities = scene->getEntitiesWithAll<TransformComponent, PlanetaryBodyComponent>();

        for (auto entity : entities) {
            TransformComponent* transform = scene->getComponent<TransformComponent>(entity);
            PlanetaryBodyComponent* planetary = scene->getComponent<PlanetaryBodyComponent>(entity);

            // Вращение вокруг собственной оси
            transform->rot.y += planetary->rotationSpeed * deltaTime;

            // Движение по орбите
            planetary->orbitAngle += planetary->orbitalSpeed * deltaTime;

                // Вычисляем позицию на круговой орбите
            float rad = glm::radians(planetary->orbitAngle);
            transform->pos.x = planetary->center->x + planetary->orbitRadius * cos(rad);
            transform->pos.z = planetary->center->z + planetary->orbitRadius * sin(rad);
        }
    }

private:
    Scene* scene;
};

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

void createSkybox(Scene& scene, MeshComponent mesh, TextureComponent texture) {
    Entity skybox = scene.createEntity();

    scene.addComponent(skybox, mesh);
    scene.addComponent(skybox, texture);
    scene.addComponent(skybox, TransformComponent{ {0, 0, 0}, {0, 0, 0}, {120, 120, 120}});
}

void createCamera(Scene& scene, TransformComponent transform, CameraComponent cameraConfig) {
    Entity camera = scene.createEntity();
    scene.addComponent<TransformComponent>(camera, transform);
    scene.addComponent<CameraComponent>(camera, cameraConfig);
}

Entity createPlanet(Scene& scene, prism::render::Renderer& renderer, std::string name,
    float orbitRadius, float orbitalSpeed, float rotationSpeed, Position& center) {
    Entity planet = scene.createEntity();

    scene.addComponent(planet, renderer.addMesh(EXAMPLE_NAME + "/models/" + name + ".obj"));
    scene.addComponent(planet, renderer.addTexture(EXAMPLE_NAME + "/textures/" + name + ".png"));

    scene.addComponent(planet, TransformComponent{ {}, {90, 0, 0}, { 300, 300, 300 } });
    scene.addComponent(planet, PlanetaryBodyComponent{ &center, orbitRadius, orbitalSpeed, 0, rotationSpeed });

    return planet;
}


int solarSystem() {
    prism::init();

    Scene scene;
    prism::render::Window window("The solar system model", WINDOW_WIDTH, WINDOW_HEIGHT);
    prism::render::Renderer renderer;

    // Настройка рендерера
    renderer.linkWindow(&window);
    renderer.setDefaultSettings();
    renderer.settings.pipeline.shaders = { "vert.spv", "frag.spv", EXAMPLE_NAME + "/shaders/" };
    renderer.init();

    // Загрузка ресурсов
    MeshComponent skyboxMesh = renderer.addMesh(EXAMPLE_NAME + "/models/skybox2.obj");
    TextureComponent skyboxTexture = renderer.addTexture(EXAMPLE_NAME + "/textures/lambert1_emissive.jpeg");

    Position center = {0, 0, 0};

    createPlanet(scene, renderer, "Sun", 0.0f, 0.0f, 0.0f, center);
    createPlanet(scene, renderer, "Mercury", 100.0f, 15.0f, 8.0f, center);
    createPlanet(scene, renderer, "Venus", 150.0f, 12.0f, 6.0f, center);
    Entity earth = createPlanet(scene, renderer, "Earth", 200.0f, 10.0f, 10.0f, center);
    createPlanet(scene, renderer, "Moon", 15.0f, 30.0f, 5.0f, scene.getComponent<TransformComponent>(earth)->pos);
    createPlanet(scene, renderer, "Mars", 250.0f, 8.0f, 9.0f, center);
    createPlanet(scene, renderer, "Jupiter", 350.0f, 5.0f, 15.0f, center);
    Entity saturn = createPlanet(scene, renderer, "Saturn", 450.0f, 4.0f, 12.0f, center);
    createPlanet(scene, renderer, "SaturnRing", 0.0f, 0.0f, 8.0f, scene.getComponent<TransformComponent>(saturn)->pos);
    Entity uranus = createPlanet(scene, renderer, "Uranus", 550.0f, 3.0f, 10.0f, center);
    createPlanet(scene, renderer, "UranusRing", 0.0f, 0.0f, 6.0f, scene.getComponent<TransformComponent>(uranus)->pos);

    renderer.updateMeshes();

    // Системы
    scene.registerSystem<RenderSystem>(&scene, &renderer);
    scene.registerSystem<FlyCameraSystem>(&scene);
    scene.registerSystem<PlanetarySystem>(&scene);

    // Камера
    CameraComponent cameraConfig{};
    cameraConfig.isActive = true;
    cameraConfig.fovy = 60.0f;
    cameraConfig.zNear = 0.1f;
    cameraConfig.zFar = 1200.0f;
    cameraConfig.look.y = -90;

    createCamera(scene, { 0, 150, 5 }, cameraConfig);

    // Создаем скайбокс
    createSkybox(scene, skyboxMesh, skyboxTexture);

    auto lastTime = std::chrono::high_resolution_clock::now();
    while (!window.shouldClose()) {
        window.handleEvents();

        float deltaTime = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - lastTime).count();
        lastTime = std::chrono::high_resolution_clock::now();

        scene.update(deltaTime);
        SDL_Delay(16);
    }

    renderer.destroy();
    return 0;
}
