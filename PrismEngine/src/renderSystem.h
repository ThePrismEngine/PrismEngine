#pragma once
#include "scene.h"
#include "renderer.h"


namespace prism {
	namespace scene {
        class RenderSystem : public ISystem {
        public:
            RenderSystem(Scene* scene, render::Renderer* renderer) : scene(scene), renderer(renderer) {}
            void update() override;

        private:
            prism::scene::Scene* scene;
            prism::render::Renderer* renderer;
        };
	}
}