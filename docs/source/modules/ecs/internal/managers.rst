Внутренние менеджеры ECS
=========================

.. _ecs-internal-managers:

EntityManager
-------------

.. doxygenclass:: prism::scene::EntityManager
   :members:
   :private-members:

ComponentManager
----------------

.. doxygenclass:: prism::scene::ComponentManager  
   :members:
   :private-members:

SystemManager
-------------

.. doxygenclass:: prism::scene::SystemManager
   :members:
   :private-members:

ResourceManager
---------------

.. doxygenclass:: prism::scene::ResourceManager
   :members:
   :private-members:


Оптимизации
-----------

- **Пул сущностей** - переиспользование ID
- **Раздельное хранение** - компоненты по типам
- **Быстрый поиск** - индексация сущностей по компонентам