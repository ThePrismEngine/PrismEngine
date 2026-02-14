#include "PrismEngine.h"
#include <timeResource.h>
#include <inputResource.h>
#include <inputSystem.h>

namespace materials {
    const std::string EXAMPLE_NAME = "materials";
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;

    using namespace prism::scene;


    class FlyCameraSystem : public ISystem {
    public:
        FlyCameraSystem(Scene* scene) : scene(scene) {}

        // Вызовется при первом кадре 
        void start() override {
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }

        void update() override {
            auto entities = scene->getEntitiesWithAll<TransformComponent, CameraComponent>();
            InputResource* input = scene->getResource<InputResource>();

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
                float speed = 5.0f * scene->getResource<TimeResource>()->unscaledDeltaTime;
                if (input->getKeyState(KeyCode::LeftControl) == HELD) speed *= 3.0f;

                // Вычисляем направление камеры
                glm::vec3 front;
                front.x = cos(glm::radians(camera->look.x)) * cos(glm::radians(camera->look.y));
                front.y = sin(glm::radians(camera->look.y));
                front.z = sin(glm::radians(camera->look.x)) * cos(glm::radians(camera->look.y));
                front = glm::normalize(front);

                glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

                if (scene->hasResource<InputResource>()) {
                    // Движение - применяем к правильным координатам
                    if (input->getKeyState(KeyCode::W) == HELD) {
                        transform->pos.x += front.x * speed;
                        transform->pos.y += front.y * speed;
                        transform->pos.z += front.z * speed;
                    }
                    if (input->getKeyState(KeyCode::S) == HELD) {
                        transform->pos.x -= front.x * speed;
                        transform->pos.y -= front.y * speed;
                        transform->pos.z -= front.z * speed;
                    }
                    if (input->getKeyState(KeyCode::A) == HELD) {
                        transform->pos.x -= right.x * speed;
                        transform->pos.z -= right.z * speed;
                    }
                    if (input->getKeyState(KeyCode::D) == HELD) {
                        transform->pos.x += right.x * speed;
                        transform->pos.z += right.z * speed;
                    }
                    if (input->getKeyState(KeyCode::Space) == HELD) transform->pos.y += speed;
                    if (input->getKeyState(KeyCode::LeftShift) == HELD) transform->pos.y -= speed;
                }
            }
        }

    private:
        Scene* scene;
    };

    void createSkybox(Scene& scene, MeshComponent mesh, MaterialComponent texture) {
        Entity skybox = scene.createEntity();

        scene.addComponent(skybox, mesh);
        scene.addComponent(skybox, texture);
        scene.addComponent(skybox, TransformComponent{ {0, 0, 0}, {0, 0, 0}, {120, 120, 120} });
    }

    void createCamera(Scene& scene, TransformComponent transform, CameraComponent cameraConfig) {
        Entity camera = scene.createEntity();
        scene.addComponent(camera, transform);
        scene.addComponent(camera, cameraConfig);
    }

    Entity create3DObject(Scene& scene,
        const MeshComponent& mesh,
        const MaterialComponent& material,
        Position position = { 0, 0, 0 },
        Scale scale = { 1, 1, 1 }) {
        // Создаем новую сущность в сцене
        Entity entity = scene.createEntity();

        // Добавляем компонент трансформации (позиция, вращение, масштаб)
        scene.addComponent(entity, TransformComponent{
            position,           // Позиция в мире
            {0, 0, 0},          // Начальное вращение (в градусах)
            scale               // Масштаб
            });

        // Добавляем компонент меша (геометрия объекта)
        scene.addComponent(entity, mesh);

        // Добавляем компонент текстуры (внешний вид)
        scene.addComponent(entity, material);

        scene.addComponent(entity, DirectionalLightComponents{ {0.05f, 0.9f, 0.05f}, {0.f, 0.f, 250.f}, 30 });

        return entity;
    }

    int materialsDemo() {
        prism::init();

        Scene scene;
        scene.setResource<WindowResource>(WindowResource::CreateCentered("The solar system model", WINDOW_WIDTH, WINDOW_HEIGHT));
        prism::render::Renderer renderer;

        // Настройка рендерера
        renderer.linkWindow(scene.getResource<WindowResource>());
        renderer.setDefaultSettings();
        renderer.settings.defaultPipeline.shaders = { "vert.spv", "frag.spv", EXAMPLE_NAME + "/shaders/" };
        renderer.init();

        // Загрузка ресурсов
        MeshComponent skyboxMesh = renderer.addMesh(EXAMPLE_NAME + "/models/skybox2.obj");
        MaterialComponent skyboxTexture = { renderer.addTexture(EXAMPLE_NAME + "/textures/lambert1_emissive.jpeg") };

        Position center = { 0, 0, 0 };


        renderer.updateMeshes();

        // ресурсы
        scene.setResource<TimeResource>(TimeResource{});
        scene.setResource<InputResource>(InputResource{});

        // Системы
        scene.registerSystem<TimeSystem>(&scene);
        scene.registerSystem<InputSystem>(&scene);
        scene.registerSystem<RenderSystem>(&scene, &renderer);
        scene.registerSystem<FlyCameraSystem>(&scene);

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

        MeshComponent cubeMesh = renderer.addMesh(EXAMPLE_NAME + "/models/neoncube.obj");

        // Загружаем материал для призмы
        MaterialComponent cubeMaterial = { renderer.addTexture(EXAMPLE_NAME + "/textures/neoncube.png") };

        // Обновляем меши в рендерере (применяем загруженные ресурсы)
        renderer.updateMeshes();

        create3DObject(scene, cubeMesh, cubeMaterial, { 10, 0, 0 }, { 10, 10, 10 });

        while (!scene.getResource<WindowResource>()->isClose()) {
            scene.update();

            SDL_Delay(16);
        }

        renderer.destroy();
        return 0;
    }

}