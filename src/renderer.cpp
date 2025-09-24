#include "renderer.h"
#include "meshManager.h"
#include "textureManager.h"


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
	pgc.context.textures.push_back(PGC::Texture{});
	pgc.init(this->settings);
}

bool prism::render::Renderer::isRenderingActive()
{
	if (!pgc.isWindowReadyForRendering(this->window->sdlWindow)) {
		if (pgc.context.wasRenderingActive) {
			awaitRenderingCompletion();
			pgc.context.wasRenderingActive = false;
		}
		SDL_PumpEvents();
		SDL_Delay(10);
		return false;
	}
	pgc.context.wasRenderingActive = true;
	return true;
}

void prism::render::Renderer::beginFrame()
{
	vkWaitForFences(pgc.context.device, 1, &pgc.context.inFlightFences[pgc.context.currentFrame], VK_TRUE, UINT64_MAX);
	VkResult result = vkAcquireNextImageKHR(pgc.context.device, pgc.context.vkSwapChain, UINT64_MAX, pgc.context.imageAvailableSemaphores[pgc.context.currentFrame], VK_NULL_HANDLE, &pgc.context.imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		pgc.getSwapChainPtr()->recreate();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}
}

void prism::render::Renderer::endFrame()
{
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { pgc.context.imageAvailableSemaphores[pgc.context.currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &pgc.context.commandBuffers[pgc.context.currentFrame];

	VkSemaphore signalSemaphores[] = { pgc.context.renderFinishedSemaphores[pgc.context.currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(pgc.context.graphicsQueue, 1, &submitInfo, pgc.context.inFlightFences[pgc.context.currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { pgc.context.vkSwapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &pgc.context.imageIndex;

	VkResult result = vkQueuePresentKHR(pgc.context.presentQueue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || *pgc.windowResized) {
		*pgc.windowResized = false;
		pgc.getSwapChainPtr()->recreate();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}
	pgc.context.currentFrame = (pgc.context.currentFrame + 1) % pgc.context.MAX_FRAMES_IN_FLIGHT;
}

void prism::render::Renderer::beginRender()
{
	vkResetFences(pgc.context.device, 1, &pgc.context.inFlightFences[pgc.context.currentFrame]);

	vkResetCommandBuffer(pgc.context.commandBuffers[pgc.context.currentFrame], /*VkCommandBufferResetFlagBits*/ 0);

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0; // Optional
	beginInfo.pInheritanceInfo = nullptr; // Optional

	if (vkBeginCommandBuffer(pgc.context.commandBuffers[pgc.context.currentFrame], &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = pgc.context.renderPass;
	renderPassInfo.framebuffer = pgc.context.swapChainFramebuffers[pgc.context.imageIndex];

	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = pgc.context.swapChainExtent;

	std::array<VkClearValue, 2> clearValues{};
	clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
	clearValues[1].depthStencil = { 1.0f, 0 };

	renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	renderPassInfo.pClearValues = clearValues.data();

	vkCmdBeginRenderPass(pgc.context.commandBuffers[pgc.context.currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void prism::render::Renderer::endRender()
{
	vkCmdEndRenderPass(pgc.context.commandBuffers[pgc.context.currentFrame]);

	if (vkEndCommandBuffer(pgc.context.commandBuffers[pgc.context.currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
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

	prism::PGC::CameraUBO cameraUbo{};

	cameraUbo.view = glm::lookAt(
		pgc.context.cameraData.pos,
		pgc.context.cameraData.look,
		pgc.context.cameraData.up
	);
	if (pgc.context.cameraData.useСurrentWindowAspect) {
		cameraUbo.proj = glm::perspective(
			glm::radians(pgc.context.cameraData.fovy),
			pgc.context.swapChainExtent.width / (float)pgc.context.swapChainExtent.height,
			pgc.context.cameraData.zNear, pgc.context.cameraData.zFar
		);
	}
	else {
		cameraUbo.proj = glm::perspective(
			glm::radians(pgc.context.cameraData.fovy),
			pgc.context.cameraData.aspect,
			pgc.context.cameraData.zNear, pgc.context.cameraData.zFar
		);
	}

	cameraUbo.proj[1][1] *= -1;  // Важно для Vulkan!
	cameraUbo.viewProj = cameraUbo.proj * cameraUbo.view;
	cameraUbo.cameraPos = pgc.context.cameraData.pos;
	
	memcpy(pgc.context.uniformBuffers[pgc.context.currentFrame].cameraMapped, &cameraUbo, sizeof(cameraUbo));
}

void prism::render::Renderer::updateObjectTransform(prism::scene::TransformComponent* transform, uint32_t transformId)
{
	//static auto startTime = std::chrono::high_resolution_clock::now();
	//auto currentTime = std::chrono::high_resolution_clock::now();
	//float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	// Обновление ObjectUBO для каждого объекта
	prism::PGC::ObjectUBO objectUbo{};

	objectUbo.model = glm::mat4(1.0f);
    
	objectUbo.model = glm::translate(objectUbo.model, glm::vec3(transform->pos.x, transform->pos.z, transform->pos.y));
	
	objectUbo.model = glm::scale(objectUbo.model, glm::vec3(transform->scale.x, transform->scale.z, transform->scale.y));

	objectUbo.model = glm::rotate(objectUbo.model, glm::radians(transform->rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	objectUbo.model = glm::rotate(objectUbo.model, glm::radians(transform->rot.y), glm::vec3(0.0f, 0.0f, 1.0f));
	objectUbo.model = glm::rotate(objectUbo.model, glm::radians(transform->rot.z), glm::vec3(0.0f, 1.0f, 0.0f));

	objectUbo.normals = glm::transpose(glm::inverse(objectUbo.model));

	// Копируем данные объекта в правильное место в динамическом буфере
	size_t offset = transformId * pgc.context.dynamicAlignment;
	memcpy((char*)pgc.context.uniformBuffers[pgc.context.currentFrame].objectMapped + offset, &objectUbo, sizeof(objectUbo));
}

void prism::render::Renderer::bindDefault()
{
	vkCmdBindPipeline(pgc.context.commandBuffers[pgc.context.currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, pgc.context.graphicsPipeline);

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(pgc.context.swapChainExtent.width);
	viewport.height = static_cast<float>(pgc.context.swapChainExtent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(pgc.context.commandBuffers[pgc.context.currentFrame], 0, 1, &viewport);

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = pgc.context.swapChainExtent;
	vkCmdSetScissor(pgc.context.commandBuffers[pgc.context.currentFrame], 0, 1, &scissor);

	VkBuffer vertexBuffers[] = { pgc.context.vertexBuffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(pgc.context.commandBuffers[pgc.context.currentFrame], 0, 1, vertexBuffers, offsets);
	vkCmdBindIndexBuffer(pgc.context.commandBuffers[pgc.context.currentFrame], pgc.context.indexBuffer, 0, VK_INDEX_TYPE_UINT32);

	vkCmdBindDescriptorSets(pgc.context.commandBuffers[pgc.context.currentFrame],
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		pgc.context.pipelineLayout,
		1, // set = 1 для текстур
		1,
		&pgc.context.textureDescriptorSet,
		0,
		nullptr);
}

void prism::render::Renderer::bindTransform(uint32_t transformId)
{
	uint32_t dynamicOffset = transformId * static_cast<uint32_t>(pgc.context.dynamicAlignment);

	vkCmdBindDescriptorSets(pgc.context.commandBuffers[pgc.context.currentFrame],
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		pgc.context.pipelineLayout,
		0, // set = 0 для ubo
		1,
		&pgc.context.descriptorSets[pgc.context.currentFrame],
		1, &dynamicOffset);
}

void prism::render::Renderer::pushTextureId(uint32_t textureId)
{
	prism::PGC::PushConstants pushConstants{};
	pushConstants.textureIndex = static_cast<int>(textureId);
	SDL_Log("%d", static_cast<int>(textureId));
	vkCmdPushConstants(
		pgc.context.commandBuffers[pgc.context.currentFrame],
		pgc.context.pipelineLayout,
		VK_SHADER_STAGE_FRAGMENT_BIT, // Указываем, что push-константы используются во фрагментном шейдере
		0,
		sizeof(prism::PGC::PushConstants),
		&pushConstants
	);
}

void prism::render::Renderer::drawMesh(uint32_t meshId)
{
	const PGC::Mesh& info = prism::PGC::MeshManager::getMeshInfo(&pgc.context, meshId);
	vkCmdDrawIndexed(pgc.context.commandBuffers[pgc.context.currentFrame], info.indexCount, 1, info.indexOffset, info.vertexOffset, 0);
}

prism::scene::TextureComponent prism::render::Renderer::addTexture(const std::string& texturePath)
{
	return { PGC::TextureManager::addTexture(&pgc.context, texturePath) };
}

void prism::render::Renderer::removeTexture(scene::TextureComponent texture)
{
	PGC::TextureManager::removeTexture(&pgc.context, texture.texture);
}

prism::scene::MeshComponent prism::render::Renderer::addMesh(std::string texturePath)
{
	return { PGC::MeshManager::addMesh(&pgc.context, texturePath)};
}

void prism::render::Renderer::updateMeshes()
{
	PGC::MeshManager::update(&pgc.context);
}

void prism::render::Renderer::clearMeshes()
{
	PGC::MeshManager::clear(&pgc.context);
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
