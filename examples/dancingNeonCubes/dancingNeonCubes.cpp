#include "PrismEngine.h"
#include <timeResource.h>
#include <inputSystem.h>
#include "../examples.h"

namespace dancingNeonCubes {
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
        DancingNeonCubesSystem(Scene* scene) : scene(scene) {}

        void update() override {
            double_t time = scene->getResource<TimeResource>()->time;
            double_t deltaTime = scene->getResource<TimeResource>()->deltaTime;


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
    };

    /**
     * Создает круг из кубов
     */
    void createNeonCubeCircle(Scene& scene, const MeshComponent& mesh,
        const MaterialComponent& material, int count, float radius) {
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
            scene.addComponent<MaterialComponent>(cube, material);
            scene.addComponent(cube, NeonCybe{}); // Для идентификации
        }
    }

    void createBackground(Scene& scene, prism::render::Renderer& renderer, MeshComponent mesh, MaterialComponent material) {
        Entity back = scene.createEntity();

        scene.addComponent(back, mesh);
        scene.addComponent(back, material);
        scene.addComponent(back, TransformComponent{ {0, -4, 5}, {0, 90, 0}, {29, 1, 31} });
    }

    int dancingNeonCubesDemo() {
        prism::init();

        Scene scene;
        WindowResource window = WindowResource::CreateCentered("Dancing NeonCubes - Geometric Ballet", WINDOW_WIDTH, WINDOW_HEIGHT);
        window.setResizable(true);
        scene.setResource<WindowResource>(window);
        prism::render::Renderer renderer;

        // Настройка рендерера
        renderer.linkWindow(scene.getResource<WindowResource>());
        renderer.setDefaultSettings();
        //renderer.settings.
        renderer.settings.pipeline.shaders = { "vert.spv", "frag.spv", EXAMPLE_NAME + "/shaders/" };
        renderer.init();

        // Загрузка ресурсов
        MeshComponent cubeMesh = renderer.addMesh(EXAMPLE_NAME + "/models/neoncube.obj");
        MeshComponent planeMesh = renderer.addMesh(EXAMPLE_NAME + "/models/plane.obj");
        renderer.updateMeshes();
        MaterialComponent cubeMaterial = { renderer.addTexture(EXAMPLE_NAME + "/textures/neoncube.png") };
        MaterialComponent backMaterial = { renderer.addTexture(EXAMPLE_NAME + "/textures/back.jpeg") };

        // Добавляем ресурс времени
        scene.setResource<TimeResource>(TimeResource{});
        scene.setResource<InputResource>(InputResource{});

        // Системы
        scene.registerSystem<TimeSystem>(&scene);  // система обновления времени
        scene.registerSystem<InputSystem>(&scene);
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
        createNeonCubeCircle(scene, cubeMesh, cubeMaterial, 12, 4.0f);

        // Создаем скайбокс
        createBackground(scene, renderer, planeMesh, backMaterial);

        std::cout << "=== Dancing Neon Cubes - Geometric Ballet ===" << std::endl;
        std::cout << "Watch the cubes dance in harmonic patterns!" << std::endl;
        std::cout << "Each cube has its own unique movement and rotation" << std::endl;

        while (!scene.getResource<WindowResource>()->isClose()) {
            scene.update();

            SDL_Delay(16);
        }

        renderer.destroy();
        return 0;
    }
}