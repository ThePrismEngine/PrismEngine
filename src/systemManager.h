#pragma once
#include <vector>
#include <memory>
#include "system.h"


namespace prism {
	namespace scene {
        class SystemManager
        {
        public:
            SystemManager() = default;

            template<typename T, typename... Args>
            SystemId registerSystem(Args&&... args) {
                systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
                return systems.size() - 1;
            };

            void enableSystem(SystemId systemId);
            void disableSystem(SystemId systemId);

            void update(float deltaTime);

        private:
            std::vector<std::unique_ptr<ISystem>> systems;
        };
	}
}