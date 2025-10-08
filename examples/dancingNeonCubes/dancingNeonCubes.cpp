#include "PrismEngine.h"

const std::string EXAMPLE_NAME = "dancingNeonCubes";
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

using namespace prism::scene;

typedef bool NeonCybe;

/**
 * Система сложного вращения - создает красивый геометрический танец
 */
class DancingNeonCubesSystem : public ISystem {
public:
    DancingNeonCubesSystem(Scene* scene) : scene(scene), time(0.0f) {}

    void update(float deltaTime) override {
        time += deltaTime;

        auto entities = scene->getEntitiesWithAll<NeonCybe, TransformComponent, MeshComponent>();
        int entityCount = entities.size();
        int i = 0;
        for (auto entity : entities) {
            TransformComponent* transform = scene->getComponent<TransformComponent>(entity);

            // Каждый обьект получает уникальное поведение на основе индекса
            float phase = (float)i / entityCount * 2.0f * M_PI;

            // Сложное движение по орбите
            float orbitRadius = 30.0f + sin(time * 0.5f + phase) * 1.0f;
            transform->pos.x = orbitRadius * cos(time + phase);
            transform->pos.z = orbitRadius * sin(time * 1.5f + phase);
            transform->pos.y = sin(time * 2.0f + phase) * 1.5f;

            // Многоосевое вращение
            transform->rot.x += 45.0f * deltaTime * sin(phase);
            transform->rot.y += 60.0f * deltaTime * cos(phase * 1.3f);
            transform->rot.z += 30.0f * deltaTime * sin(phase * 0.7f);

            // Пульсирующий масштаб
            float pulse = 0.7f + sin(time * 3.0f + phase) * 0.3f;
            transform->scale = { pulse, pulse, pulse };
            i++;
        }
    }

private:
    Scene* scene;
    float time;
};

/**
 * Создает круг из кубов
 */
void createNeonCubeCircle(Scene& scene, const MeshComponent& mesh,
    const TextureComponent& texture, int count, float radius) {
    for (int i = 0; i < count; ++i) {
        float angle = (float)i / count * 2.0f * M_PI;
        Position position = {
            cos(angle) * radius,
            0,
            sin(angle) * radius
        };

        Entity cube = scene.createEntity();
        scene.addComponent<TransformComponent>(cube, {
            position,
            {0, 0, 0},
            {0.1f, .1f, .1f}
            });
        scene.addComponent<MeshComponent>(cube, mesh);
        scene.addComponent<TextureComponent>(cube, texture);
        scene.addComponent(cube, NeonCybe{}); // Для идентификации
    }
}

void createBackground(Scene& scene, prism::render::Renderer& renderer, MeshComponent mesh, TextureComponent texture) {
    Entity back = scene.createEntity();

    scene.addComponent(back, mesh);
    scene.addComponent(back, texture);
    scene.addComponent(back, TransformComponent{ {0, -50, 0}, {0, 90, 0}, {75, 1, 65} });
}

int dancingNeonCubesDemo() {
    prism::init();

    Scene scene;
    prism::render::Window window("Dancing NeonCubes - Geometric Ballet", WINDOW_WIDTH, WINDOW_HEIGHT);
    window.setResizable(true);
    prism::render::Renderer renderer;

    // Настройка рендерера
    renderer.linkWindow(&window);
    renderer.setDefaultSettings();
    renderer.settings.pipeline.shaders = { "vert.spv", "frag.spv", EXAMPLE_NAME + "/shaders/" };
    renderer.init();
    
    // Загрузка ресурсов
    MeshComponent cubeMesh = renderer.addMesh(EXAMPLE_NAME + "/models/neoncube.obj");
    MeshComponent planeMesh = renderer.addMesh(EXAMPLE_NAME + "/models/plane.obj");
    renderer.updateMeshes();
    TextureComponent cubeTexture = renderer.addTexture(EXAMPLE_NAME + "/textures/neoncube.png");
    TextureComponent backTexture = renderer.addTexture(EXAMPLE_NAME + "/textures/back.jpeg");

    // Системы
    scene.registerSystem<RenderSystem>(&scene, &renderer);
    scene.registerSystem<DancingNeonCubesSystem>(&scene);

    // Камера
    Entity camera = scene.createEntity();
    scene.addComponent<TransformComponent>(camera, { {0, 50, 5} });
    
    CameraComponent cameraConfig{};
    cameraConfig.isActive = true;
    cameraConfig.fovy = 60.0f;
    cameraConfig.zNear = 0.1f;
    cameraConfig.zFar = 300.0f;
    cameraConfig.look.y = -90;
    scene.addComponent<CameraComponent>(camera, cameraConfig);

    // Создаем 12 кубов по кругу
    createNeonCubeCircle(scene, cubeMesh, cubeTexture, 12, 4.0f);

    // Создаем скайбокс
    createBackground(scene, renderer, planeMesh, backTexture);

    std::cout << "=== Dancing Neon Cubes - Geometric Ballet ===" << std::endl;
    std::cout << "Watch the cubes dance in harmonic patterns!" << std::endl;
    std::cout << "Each cube has its own unique movement and rotation" << std::endl;

    auto lastTime = std::chrono::high_resolution_clock::now();
    while (!window.shouldClose()) {
        window.handleEvents();

        float deltaTime = std::chrono::duration<float>(
            std::chrono::high_resolution_clock::now() - lastTime).count();
        lastTime = std::chrono::high_resolution_clock::now();

        scene.update(deltaTime);
        SDL_Delay(16);
    }

    renderer.destroy();
    return 0;
}