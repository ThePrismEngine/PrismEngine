#include "PrismEngine.h"
#include <timeResource.h>
#include <inputSystem.h>
#include <windowResource.h>
#include "../examples.h"

namespace spinningPrism {
    // Константы для удобства изменения параметров
    const std::string EXAMPLE_NAME = "spinningPrism";
    const float ROTATION_SPEED = 45.0f; // градусов в секунду
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    using namespace prism::scene;

    /**
     * Система вращения - автоматически вращает все объекты с компонентом Transform
     * Демонстрирует принцип работы систем в ECS архитектуре
     */
    class RotationSystem : public ISystem {
    public:
        RotationSystem(Scene* scene) : scene(scene) {}

        void update() override {
            // Получаем все сущности, которые имеют и Transform и Mesh компоненты
            auto rotatingObjects = scene->getEntitiesWithAll<TransformComponent, MeshComponent>();

            // Для каждого объекта добавляем вращение вокруг оси Y
            for (auto entity : rotatingObjects) {
                TransformComponent* transform = scene->getComponent<TransformComponent>(entity);
                transform->rot.y += ROTATION_SPEED * scene->getResource<TimeResource>()->deltaTime;
            }
        }

    private:
        Scene* scene;
    };

    /**
     * Создает 3D объект с заданными параметрами
     * Демонстрирует композиционный подход - объект собирается из компонентов
     */
    Entity create3DObject(Scene& scene,
        const MeshComponent& mesh,
        const MaterialComponent& material,
        Position position = { 0, 0, 0 },
        Scale scale = { 1, 1, 1 }) {
        // Создаем новую сущность в сцене
        Entity entity = scene.createEntity();

        // Добавляем компонент трансформации (позиция, вращение, масштаб)
        scene.addComponent<TransformComponent>(entity, {
            position,           // Позиция в мире
            {0, 0, 0},          // Начальное вращение (в градусах)
            scale               // Масштаб
            });

        // Добавляем компонент меша (геометрия объекта)
        scene.addComponent<MeshComponent>(entity, mesh);

        // Добавляем компонент текстуры (внешний вид)
        scene.addComponent<MaterialComponent>(entity, material);

        return entity;
    }

    /**
     * Демонстрация вращающейся призмы - первый пример для движка PrismEngine
     *
     * Этот пример показывает:
     * 1. Как инициализировать движок и создать окно
     * 2. Как работать с ECS (Entity-Component-System) архитектурой
     * 3. Как создавать и настраивать 3D объекты
     * 4. Как использовать системы для добавления поведения
     */
    int spinningPrismDemo() {
        // ========== ШАГ 1: ИНИЦИАЛИЗАЦИЯ ДВИЖКА ==========
        prism::init();

        // Создаем сцену для хранения всех объектов
        Scene scene;

        // Создаем ресурс окна для отображения 3D графики
        WindowResource window = WindowResource::CreateCentered("The solar system model", WINDOW_WIDTH, WINDOW_HEIGHT);
        scene.setResource<WindowResource>(window);

        // Создаем и настраиваем рендерер
        prism::render::Renderer renderer;
        renderer.linkWindow(scene.getResource<WindowResource>());
        renderer.setDefaultSettings();

        // Указываем пути к шейдерам (программы для видеокарты)
        renderer.settings.defaultPipeline.shaders = {
            "vert.spv",
            "frag.spv",
            EXAMPLE_NAME + "/shaders/"
        };
        renderer.init();

        // ========== ШАГ 2: ЗАГРУЗКА РЕСУРСОВ ==========

        // Загружаем 3D модель призмы из файла
        MeshComponent prismMesh = renderer.addMesh(EXAMPLE_NAME + "/models/prism.obj");

        // Загружаем материал для призмы
        MaterialComponent prismMaterial = { renderer.addTexture(EXAMPLE_NAME + "/textures/prismfasetexturex.png") };

        // Обновляем меши в рендерере (применяем загруженные ресурсы)
        renderer.updateMeshes();

        // ========== ШАГ 3: НАСТРОЙКА СИСТЕМ И РЕСУРСОВ ==========

        // Добавляем ресурс времени
        scene.setResource<TimeResource>(TimeResource{});

        scene.setResource<InputResource>(InputResource{});
        scene.registerSystem<InputSystem>(&scene); // Нужна для обновления состояний окна и ввода

        // Добавляем систему обновления времени
        scene.registerSystem<TimeSystem>(&scene);

        // Регистрируем систему рендеринга (отвечает за отрисовку)
        scene.registerSystem<RenderSystem>(&scene, &renderer);

        // Регистрируем нашу кастомную систему вращения
        scene.registerSystem<RotationSystem>(&scene);

        // ========== ШАГ 4: СОЗДАНИЕ КАМЕРЫ ==========

        // Камера - глаза пользователя в 3D мире
        Entity camera = scene.createEntity();

        // Позиционируем камеру так, чтобы хорошо видеть сцену
        scene.addComponent<TransformComponent>(camera, {
            {0, 2, 10},     // Камера смотрит на сцену сверху и сзади
            {0, 0, 0},
            {1, 1, 1}
            });

        // Настраиваем параметры камеры
        CameraComponent cameraConfig{};
        cameraConfig.isActive = true;    // Делаем эту камеру активной
        cameraConfig.fovy = 45.0f;       // Угол обзора (поле зрения)
        cameraConfig.zNear = 0.1f;       // Ближняя плоскость отсечения
        cameraConfig.zFar = 100.0f;      // Дальняя плоскость отсечения
        cameraConfig.look = { -90.f, -15.f, 0.0f };

        scene.addComponent<CameraComponent>(camera, cameraConfig);

        // ========== ШАГ 5: СОЗДАНИЕ ОБЪЕКТОВ СЦЕНЫ ==========

        // Создаем центральную призму
        create3DObject(scene, prismMesh, prismMaterial,
            { 0, 0, 0 },     // Позиция в центре
            { 1, 1, 1 });    // Полный размер

        // Создаем меньшую призму справа
        create3DObject(scene, prismMesh, prismMaterial,
            { 3, 0, 0 },     // Смещена вправо
            { 0.5, 0.5, 0.5 }); // Вдвое меньше

        // Создаем меньшую призму слева  
        create3DObject(scene, prismMesh, prismMaterial,
            { -3, 0, 0 },    // Смещена влево
            { 0.5, 0.5, 0.5 }); // Вдвое меньше

        // ========== ШАГ 6: ИНФОРМАЦИЯ ДЛЯ ПОЛЬЗОВАТЕЛЯ ==========

        std::cout << "=== PrismEngine: Spinning Prism Demo ===" << std::endl;
        std::cout << "All prisms automatically rotate at a speed of "
            << ROTATION_SPEED << " degrees per second" << std::endl;
        std::cout << "Close the exit window" << std::endl;



        // ========== ШАГ 7: ГЛАВНЫЙ ЦИКЛ ПРИЛОЖЕНИЯ ==========
        // Главный цикл - выполняется пока окно не закрыто
        while (!scene.getResource<WindowResource>()->isClose()) {
            // Обновляем сцену (вызываем все системы)
            scene.update();

            // Небольшая задержка для снижения нагрузки на CPU
            SDL_Delay(15); // ~60 кадров в секунду
        }

        // ========== ШАГ 8: КОРРЕКТНОЕ ЗАВЕРШЕНИЕ ==========

        // Очищаем ресурсы рендерера
        renderer.destroy();

        return 0;
    }
}