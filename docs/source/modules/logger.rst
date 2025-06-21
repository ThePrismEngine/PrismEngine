Модуль логирования
=============

Модуль логирования предоставляет систему для записи сообщений различного уровня важности с возможностью вывода в консоль или файл.

Перечисления
-----

.. doxygenenum:: prism::logger::Error

.. doxygenenum:: prism::logger::Level

Функции
---------

Основные функции управления логированием:

.. doxygenfunction:: prism::logger::setLevel

.. doxygenfunction:: prism::logger::setOutputFile

.. doxygenfunction:: prism::logger::setOutputConsole

.. doxygenfunction:: prism::logger::log

.. doxygenfunction:: prism::logger::logError

Удобные функции для разных уровней логирования:

.. doxygenfunction:: prism::logger::verbose

.. doxygenfunction:: prism::logger::debug

.. doxygenfunction:: prism::logger::info

.. doxygenfunction:: prism::logger::warning

.. doxygenfunction:: prism::logger::error

.. doxygenfunction:: prism::logger::critical
