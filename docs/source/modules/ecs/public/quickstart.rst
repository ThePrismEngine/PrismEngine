Быстрое начало работы с ECS
============================

.. _ecs-quickstart:

Создание первой сцены
---------------------

.. code-block:: cpp
   :linenos:
   
   #include <prism/scene.h>
   
   // 1. Создаем сцену
   prism::scene::Scene scene;
   
   // 2. Создаем сущность игрока
   auto player = scene.createEntity();
   
   // 3. Добавляем компоненты
   scene.addComponent<Transform>(player, Transform{0, 0, 0});
   scene.addComponent<Renderable>(player, Renderable{"player.obj"});
   scene.addComponent<Health>(player, Health{100});

Добавляем стандартный ресурс TimeResource и его систему TimeSystem
---------------
.. code-block:: cpp
	scene.setResource<TimeResource>(TimeResource{});
	scene.registerSystem<TimeSystem>(&scene);	    

Создание системы
----------------

.. code-block:: cpp
   
   class MovementSystem : public prism::scene::ISystem {
   public:
       void update() override {
           auto entities = scene->getEntitiesWith<Transform, Velocity>();
           for (auto entity : entities) {
               auto* transform = scene->getComponent<Transform>(entity);
               auto* velocity = scene->getComponent<Velocity>(entity);
               transform->position.x += velocity->x * scene->getResource<TimeResource>()->deltaTime;
           }
       }
   };
   
   // Регистрируем систему
   scene.registerSystem<MovementSystem>();

Обновление сцены
----------------

.. code-block:: cpp
   
   void gameLoop() {
       while (running) {
           scene.update();
       }
   }