Внутренняя архитектура ECS
===========================

.. _ecs-internal-arch:

Обзор
-----

Внутренняя реализация ECS модуля состоит из четырех основных менеджеров:

.. graphviz::
   :caption: Архитектура ECS
   
   digraph ecs_architecture {
       rankdir=TB;
       node [shape=box];
       
       Scene -> EntityManager;
       Scene -> ComponentManager;
       Scene -> SystemManager;
	   Scene -> ResourceManager
       
       EntityManager -> FreeList;
       ComponentManager -> ComponentStorages;
       SystemManager -> SystemList;
	   ResourceManager -> ResourceMap
   }

Взаимодействие компонентов
--------------------------

.. code-block:: cpp
   :caption: Последовательность операций
   
   scene.createEntity() → EntityManager.createEntity()
   scene.addComponent() → ComponentManager.addComponent()
   scene.update() → SystemManager.update() → ISystem.update()
   scene.update() → SystemManager.start() → ISystem.start()
   scene.setResource() → ResourceManager.setResource()