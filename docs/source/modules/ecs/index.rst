ECS Module (Entity-Component-System)
====================================

.. toctree::
   :maxdepth: 2
   :caption: Публичное API (для пользователей):
   
   public/overview
   public/quickstart
   public/api_reference
   public/examples

.. toctree::
   :maxdepth: 2
   :caption: Внутренняя реализация (для разработчиков):
   
   internal/architecture
   internal/managers
   internal/performance

Обзор
-----

Модуль ECS предоставляет систему Entity-Component-System для управления игровыми объектами.

Основные концепции:

- **Сущности (Entities)** - идентификаторы игровых объектов
- **Компоненты (Components)** - данные сущностей  
- **Системы (Systems)** - логика обработки компонентов

Быстрые ссылки:

- :ref:`ecs-public-overview` - обзор публичного API
- :ref:`ecs-internal-arch` - внутренняя архитектура
- :ref:`ecs-quickstart` - быстрое начало работы