#include "renderer.h"

prism::render::Renderer::Renderer(Window* window)
{
	this->window = window;
	setDefaultSettings();
}

prism::render::Renderer::~Renderer()
{
}

void prism::render::Renderer::init()
{
	pgc.windowResized = &window->windowResized;
	pgc.windowMinimized = &window->windowMinimized;
	pgc.init(this->settings);
}

void prism::render::Renderer::drawFrame()
{
	pgc.drawFrame();
}

void prism::render::Renderer::awaitRenderingCompletion()
{
	pgc.awaitRenderingCompletion();
}

void prism::render::Renderer::destroy()
{
	pgc.cleanup();
}

void prism::render::Renderer::setDefaultSettings()
{
	settings.app.applicationName = SDL_GetWindowTitle(window->sdlWindow);
	settings.app.applicationVersion = { 1, 0, 0 };
	settings.window = window->sdlWindow;

	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	settings.pipeline.colorBlend.attachments.push_back(colorBlendAttachment);

	settings.descriptorSetLayout = {
	{
			// Camera UBO (binding = 0, vertex stage)
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT},

			// Texture sampler (binding = 1, fragment stage)  
			{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT},

			// Object UBO (binding = 2, vertex stage)
			//{2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT}
			{2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1, VK_SHADER_STAGE_VERTEX_BIT}
		},
		0
	};
}
