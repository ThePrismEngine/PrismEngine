#include "renderer.h"


void prism::render::Renderer::linkWindow(Window* window)
{
	this->window = window;
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

void prism::render::Renderer::updateCamera(prism::scene::TransformComponent* transform, prism::scene::CameraComponent* camera)
{
	prism::PGC::utils::CameraData* cameraData = pgc.getCameraDataPtr();

	cameraData->pos = { transform->pos.x, transform->pos.z, transform->pos.y }; // из пространства сцены в vulkan 
	cameraData->look = { camera->look.x, camera->look.y, camera->look.z };
	cameraData->fovy = camera->fovy;
	cameraData->aspect = camera->aspect;
	cameraData->zFar = camera->zFar;
	cameraData->zNear = camera->zNear;
	cameraData->useСurrentWindowAspect = camera->useСurrentWindowAspect;
}

void prism::render::Renderer::awaitRenderingCompletion()
{
	pgc.awaitRenderingCompletion();
}

void prism::render::Renderer::destroy()
{
	pgc.awaitRenderingCompletion();
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

			// Object UBO (binding = 1, vertex stage)
			{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1, VK_SHADER_STAGE_VERTEX_BIT}
		},
		0
	};

	settings.textureDescriptorSetLayout = {
		{
			{0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, settings.MAX_TEXTURES, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr, VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT | VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT}
		},
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT_EXT
	};
}
