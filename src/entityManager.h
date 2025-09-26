#pragma once
#include "entity.h"
#include <queue>

namespace prism {
	namespace scene {
        /// @brief Менеджер для создания и управления сущностями
        /// @details Обеспечивает создание, удаление и валидацию сущностей с использованием пула идентификаторов
        class EntityManager
        {
        public:
            EntityManager() : nextEntityId(1) {}

            /// @brief Создает новую сущность
            /// @return Идентификатор созданной сущности
            /// @details Использует свободные ID из пула при наличии, иначе генерирует новый
            Entity createEntity();

            /// @brief Удаляет сущность и освобождает ее ID
            /// @param entityId Идентификатор сущности для удаления
            /// @return true если сущность успешно удалена, false если ID невалиден
            /// @details Освобожденный ID помещается в пул для повторного использования
            bool destroyEntity(Entity entityId);

            /// @brief Проверяет валидность идентификатора сущности
            /// @param entityId Идентификатор сущности для проверки
            /// @return true если сущность существует и валидна, false в противном случае
            bool isEntityValid(Entity entityId) const;

        private:
            /// @brief Следующий доступный идентификатор сущности
            Entity nextEntityId;

            /// @brief Очередь свободных идентификаторов для повторного использования
            std::queue<Entity> freeList;
        };
	}
}