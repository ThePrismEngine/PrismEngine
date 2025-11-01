#pragma once
#include "prismGraphicCore.h"
#include "transformComponent.h"
#include "cameraComponent.h"
#include "textureComponent.h"
#include "meshComponent.h"
#include "windowResource.h"

namespace prism {
	namespace render {
	   class Renderer
	    {
		public:
			Renderer() : window(nullptr) {};
			void linkWindow(prism::scene::WindowResource* window);
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
			scene::TextureComponent addTexture(const std::string& texturePath);
			void removeTexture(scene::TextureComponent texture);

			scene::MeshComponent addMesh(std::string texturePath);
			void updateMeshes();
			void clearMeshes();

			void awaitRenderingCompletion();
			void destroy();

			PGC::utils::Settings settings;
		private:

			PGC::PrismGraphicCore pgc;
			prism::scene::WindowResource* window;
		};
	}
}
