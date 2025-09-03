#pragma once
#include "prismGraphicCore.h"
#include "Window.h"

namespace prism {
	namespace render {
		class Renderer
		{
		public:

			Renderer(Window* window);
			~Renderer();
			void init();
			void drawFrame();
			void awaitRenderingCompletion();
			void destroy();

			PGC::utils::Settings settings;
		private:
			void setDefaultSettings();

			PGC::PrismGraphicCore pgc;
			Window* window;
		};
	}
}
