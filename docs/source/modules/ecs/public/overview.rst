Публичное API ECS модуля
=========================

.. _ecs-public-overview:

Обзор
-----

Публичное API предназначено для разработчиков игр и приложений. Оно предоставляет простой интерфейс для работы с ECS.

Основные классы:

- **Scene** - основная точка входа для работы с ECS
- **ISystem** - базовый интерфейс для всех систем

Пример использования:

.. code-block:: cpp

   #include <prism/scene.h>
   
   prism::scene::Scene scene;
   auto entity = scene.createEntity();
   scene.addComponent<Transform>(entity, Transform{0, 0, 0});

Смотрите также:
   * :doc:`../public/quickstart` - руководство по началу работы
   * :doc:`../public/api_reference` - полный справочник API