Внутренняя архитектура ECS
===========================

.. _ecs-internal-arch:

Обзор
-----

Внутренняя реализация ECS модуля состоит из трех основных менеджеров:

.. graphviz::
   :caption: Архитектура ECS
   
   digraph ecs_architecture {
       rankdir=TB;
       node [shape=box];
       
       Scene -> EntityManager;
       Scene -> ComponentManager;
       Scene -> SystemManager;
       
       EntityManager -> FreeList;
       ComponentManager -> ComponentStorages;
       SystemManager -> SystemList;
   }

Взаимодействие компонентов
--------------------------

.. code-block:: cpp
   :caption: Последовательность операций
   
   scene.createEntity() → EntityManager.createEntity()
   scene.addComponent() → ComponentManager.addComponent()
   scene.update() → SystemManager.update() → ISystem.update()