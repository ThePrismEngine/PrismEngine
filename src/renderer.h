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

			bool isRenderingActive();
			void beginFrame();
			void beginRender();
			void endRender();
			void endFrame();
			void updateCamera(prism::scene::TransformComponent* transform, prism::scene::CameraComponent* camera);
			void updateObjectTransform(prism::scene::TransformComponent* transform, uint32_t transformId);
			void bindDefault();
			void bindTransform(uint32_t transformId);
			void pushTextureId(uint32_t textureId);
			void drawMesh(uint32_t meshId);
			void awaitRenderingCompletion();
			void destroy();

			PGC::utils::Settings settings;
		private:

			PGC::PrismGraphicCore pgc;
			Window* window;
		};
	}
}
