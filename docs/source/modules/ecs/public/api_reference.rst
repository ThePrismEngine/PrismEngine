Справочник публичного API
==========================

.. _ecs-public-api:

Класс Scene
-----------

.. doxygenclass:: prism::scene::Scene
   :members:
   :undoc-members:

Стандартные ресурсы:
-----------------------
..  doxygenstruct:: prism::scene::InputResource
    :members:
	
..  doxygenstruct:: prism::scene::TimeResource
    :members:

Стандартные компоненты:
-----------------------

.. doxygenstruct:: prism::scene::TransformComponent  
   :members:

.. doxygenstruct:: prism::scene::CameraComponent  
   :members:
   
.. doxygenstruct:: prism::scene::MeshComponent  
   :members:
   
.. doxygenstruct:: prism::scene::TextureComponent  
   :members:

Системы
-------

.. doxygenclass:: prism::scene::ISystem
   :members:
   
Стандартные системы:

.. doxygenclass:: prism::scene::RenderSystem
   :members:
   
.. doxygenclass:: prism::scene::InputSystem
   :members:
   
.. doxygenclass:: prism::scene::TimeSystem
   :members: