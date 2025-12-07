#include "renderer.h"
#include "meshManager.h"
#include <gtc/quaternion.hpp>


void prism::render::Renderer::linkWindow(prism::scene::WindowResource* window)
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

bool prism::render::Renderer::isRenderingActive()
{
	if (!pgc.isWindowReadyForRendering(this->window->getSDLWindow())) {
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

	// Правильное преобразование координат: X→X, Y→Z, Z→-Y (для Vulkan)
	cameraData->pos = { transform->pos.x, transform->pos.y, transform->pos.z };
	cameraData->look = { camera->look.x, camera->look.y, camera->look.z };
	cameraData->fovy = camera->fovy;
	cameraData->aspect = camera->aspect;
	cameraData->zFar = camera->zFar;
	cameraData->zNear = camera->zNear;
	cameraData->useСurrentWindowAspect = camera->useCurrentWindowAspect;

	prism::PGC::CameraUBO cameraUbo{};

	// Вычисляем точку, куда смотрит камера, на основе углов
	glm::vec3 direction;
	direction.x = cos(glm::radians(camera->look.x)) * cos(glm::radians(camera->look.y));
	direction.y = sin(glm::radians(camera->look.y));
	direction.z = sin(glm::radians(camera->look.x)) * cos(glm::radians(camera->look.y));
	direction = glm::normalize(direction);

	glm::vec3 cameraPos = { transform->pos.x, transform->pos.y, transform->pos.z };
	glm::vec3 cameraTarget = cameraPos + direction;

	cameraUbo.view = glm::lookAt(
		cameraPos,
		cameraTarget,
		glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector (Y вверх)
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

	cameraUbo.proj[1][1] *= -1;
	cameraUbo.viewProj = cameraUbo.proj * cameraUbo.view;
	cameraUbo.cameraPos = cameraPos;
	cameraUbo.ambientColor = camera->ambientColor;
	cameraUbo.ambientIntensity = camera->ambientIntensity;

	memcpy(pgc.context.uniformBuffers[pgc.context.currentFrame].cameraMapped, &cameraUbo, sizeof(cameraUbo));
}

void prism::render::Renderer::updateInstances(std::vector<InstanceData> renderData)
{
	std::vector<prism::PGC::ObjectSSBO> allObjectsData;
	for (auto& obj : renderData) {
		prism::PGC::ObjectSSBO data;
		data.model = glm::mat4(1.0f);
		data.model = glm::translate(data.model, glm::vec3(obj.transform->pos.x, obj.transform->pos.y, obj.transform->pos.z));
		data.model = data.model * glm::mat4_cast(glm::quat(glm::radians(glm::vec3{ obj.transform->rot.x, obj.transform->rot.y, obj.transform->rot.z })));
		data.model = glm::scale(data.model, glm::vec3(obj.transform->scale.x, obj.transform->scale.y, obj.transform->scale.z));

		data.normals = glm::transpose(glm::inverse(data.model));

		data.texture = obj.texture->texture;
		allObjectsData.push_back(data);
	}

	memcpy((char*)pgc.context.storageBuffers[pgc.context.currentFrame].objectMapped,
		allObjectsData.data(),
		allObjectsData.size() * sizeof(prism::PGC::ObjectSSBO));
}

void prism::render::Renderer::updateLights(LightData* lightData)
{
	prism::PGC::CameraUBO* cameraUBO = static_cast<prism::PGC::CameraUBO*>(pgc.context.uniformBuffers[pgc.context.currentFrame].cameraMapped);
	cameraUBO->pointLightCount = static_cast<uint32_t>(lightData->pointLights.size());
	cameraUBO->directionalLightCount = static_cast<uint32_t>(lightData->directionalLights.size());

	if (!lightData->pointLights.empty()) {
		memcpy(pgc.context.storageBuffers[pgc.context.currentFrame].pointLightsMapped,
			lightData->pointLights.data(),
			lightData->pointLights.size() * sizeof(prism::scene::PointLightComponent));
	}

	if (!lightData->directionalLights.empty()) {
		memcpy(pgc.context.storageBuffers[pgc.context.currentFrame].directionalLightsMapped,
			lightData->directionalLights.data(),
			lightData->directionalLights.size() * sizeof(prism::scene::DirectionalLightComponents));
	}
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

void prism::render::Renderer::bindObjectsData()
{
	vkCmdBindDescriptorSets(pgc.context.commandBuffers[pgc.context.currentFrame],
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		pgc.context.pipelineLayout,
		0,
		1,
		&pgc.context.descriptorSets[pgc.context.currentFrame],
		0, nullptr);
}

void prism::render::Renderer::drawMesh(uint32_t meshId, uint32_t instanceCount, uint32_t firstIndex)
{
	const PGC::Mesh& info = prism::PGC::MeshManager::getMeshInfo(&pgc.context, meshId);
	vkCmdDrawIndexed(pgc.context.commandBuffers[pgc.context.currentFrame], info.indexCount, instanceCount, info.indexOffset, info.vertexOffset, firstIndex);

}

prism::TextureId prism::render::Renderer::addTexture(const std::string& texturePath)
{
	return pgc.textureStorage.load(texturePath);
}

bool prism::render::Renderer::removeTexture(TextureId texture)
{
	return pgc.textureStorage.remove(texture);
}

void prism::render::Renderer::remodeMaterial(scene::MaterialComponent material)
{
	if (!material.texture)
	{
		pgc.textureStorage.remove(material.texture);
	}
}

void prism::render::Renderer::clearTextures()
{
	pgc.textureStorage.cleanup();
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
	settings.app.applicationName = SDL_GetWindowTitle(window->getSDLWindow());
	settings.app.applicationVersion = { 1, 0, 0 };
	settings.window = window->getSDLWindow();

	settings.descriptorSetLayout = {
	{
			// Camera UBO
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT},

			// Objects SSBO
			{1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT },
			// PointLightsSSBO
			{2, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_FRAGMENT_BIT},
			// DirectionalLightsSSBO
			{3, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_FRAGMENT_BIT},
			
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
