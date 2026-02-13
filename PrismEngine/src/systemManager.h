#pragma once
#include <vector>
#include <memory>
#include "system.h"


namespace prism {
    namespace scene {
        /// @brief Менеджер систем для регистрации, включения/выключения и обновления систем.
        /// @details Управляет коллекцией систем, обновляя их в порядке регистрации.
        class SystemManager
        {
        public:
            SystemManager() = default;

            /// @brief Регистрирует новую систему в менеджере.
            /// @tparam T Тип системы (должен быть производным от ISystem).
            /// @tparam Args Типы аргументов для конструктора системы.
            /// @param args Аргументы для передачи конструктору системы.
            /// @return Идентификатор зарегистрированной системы.
            /// @details Создает экземпляр системы и добавляет его в список управления
            template<typename T, typename... Args>
            SystemId registerSystem(Args&&... args) {
                static_assert(std::is_base_of_v<ISystem, T>, "T must derive from ISystem");
                systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
                auto* sys = systems.back().get();
				if (sys->isEnabled()) activeSystems.push_back(sys);
                return systems.size() - 1;
            };

            /// @brief Включает систему по идентификатору.
            /// @param systemId Идентификатор системы, которую нужно включить.
            void enableSystem(SystemId systemId);

            /// @brief Выключает систему по идентификатору.
            /// @param systemId Идентификатор системы, которую нужно выключить.
            void disableSystem(SystemId systemId);

            /// @brief Обновляет все активные системы, при первом бызове еще и вызывает start()
            /// @details Вызывает: 
            /// 1) start() в системах с неактивным started.
            /// 2) update() каждый вызыв. 
            /// для всех включенных систем в порядке регистрации
            /// @see prism::scene::ISystem::update
            void update();

        private:
            /// @brief Массив зарегистрированных систем
            std::vector<std::unique_ptr<ISystem>> systems;

			/// @brief Кэш активных систем для оптимизации обновления
            std::vector<ISystem*> activeSystems;
        };
    }
}