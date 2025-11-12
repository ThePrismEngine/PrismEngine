#pragma once
#include "prismGraphicCore.h"
#include "cameraComponent.h"
#include "textureComponent.h"
#include "meshComponent.h"
#include "windowResource.h"
#include "transformComponent.h"

namespace prism {
	namespace render {
		struct RenderData
		{
			prism::scene::TransformComponent* transform;
			prism::scene::MaterialComponent* texture;
		};

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
			void updateObjects(std::vector<RenderData> renderData);
			void bindDefault();
			void bindObjectsData();
			void drawMesh(uint32_t meshId, uint32_t instanceCount, uint32_t firstIndex);

			TextureId addTexture(const std::string& texturePath);
			bool removeTexture(TextureId texture);
			void remodeMaterial(scene::MaterialComponent material);
			void clearTextures();


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
