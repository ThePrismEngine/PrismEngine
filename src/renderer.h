#pragma once
#include "prismGraphicCore.h"
#include "Window.h"
#include "transformComponent.h"
#include "cameraComponent.h"

namespace prism {
	namespace render {
	   class Renderer
	    {
		public:
			Renderer() : window(nullptr) {};
			void linkWindow(Window* window);
			void setDefaultSettings();
			void init();
			~Renderer();

			void drawFrame();
			void updateCamera(prism::scene::TransformComponent* transform, prism::scene::CameraComponent* camera);
			void awaitRenderingCompletion();
			void destroy();

			PGC::utils::Settings settings;
		private:

			PGC::PrismGraphicCore pgc;
			Window* window;
		};
	}
}
