
.. _program_listing_file_PrismEngine_src_shaderStagesLoader.cpp:

Program Listing for File shaderStagesLoader.cpp
===============================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_shaderStagesLoader.cpp>` (``PrismEngine\src\shaderStagesLoader.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "shaderStagesLoader.h"
   #include <stdexcept>
   #include <iostream>
   #include <fstream>
   #include "logger.h"
   #include <array>
   
   
   std::array<VkPipelineShaderStageCreateInfo, 2> prism::PGC::ShaderStagesLoader::load(PGC::utils::Context* context, PGC::utils::Settings* settings)
   {
       auto vertShaderCode = readShaderFile(settings->pipeline.shaders.shadersDirectory + settings->pipeline.shaders.vertexShaderFilename);
       auto fragShaderCode = readShaderFile(settings->pipeline.shaders.shadersDirectory + settings->pipeline.shaders.fragmentShaderFilename);
       
       VkShaderModule vertShaderModule = createShaderModule(context->device, vertShaderCode);
       VkShaderModule fragShaderModule = createShaderModule(context->device, fragShaderCode);
   
       VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
       vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
       vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
       vertShaderStageInfo.module = vertShaderModule;
       vertShaderStageInfo.pName = "main";
   
       VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
       fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
       fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
       fragShaderStageInfo.module = fragShaderModule;
       fragShaderStageInfo.pName = "main";
   
       return { vertShaderStageInfo, fragShaderStageInfo };
   }
   
   std::vector<char> prism::PGC::ShaderStagesLoader::readShaderFile(const std::string& filename)
   {
       // Открываем файл в режиме бинарного чтения с курсором в конце
       std::ifstream file(filename, std::ios::binary | std::ios::ate);
       if (!file.is_open()) {
           logger::logError(logger::Error::FAILED_TO_OPEN_FILE, "An error occurred in the Prism graphic core during the stage of loading shaders to create a pipeline. FILENAME: " + filename);
       }
   
       // Получаем размер файла
       const auto fileSize = file.tellg();
       if (fileSize == -1) {
           logger::logError(logger::Error::FAILED_TO_DETERMINE_FILE_SIZE, "An error occurred in the Prism graphic core during the stage of loading shaders to create a pipeline. FILENAME: " + filename);
       }
   
       // Перемещаем курсор в начало
       file.seekg(0);
   
       // Создаем вектор размером fileSize и читаем данные напрямую
       std::vector<char> buffer(static_cast<size_t>(fileSize));
       if (!file.read(buffer.data(), fileSize)) {
           logger::logError(logger::Error::FAILED_TO_READ_FILE, "An error occurred in the Prism graphic core during the stage of loading shaders to create a pipeline. FILENAME: " + filename);
       }
   
       return buffer;
   }
   
   VkShaderModule prism::PGC::ShaderStagesLoader::createShaderModule(VkDevice device, const std::vector<char>& code)
   {
       VkShaderModuleCreateInfo createInfo{};
       createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
       createInfo.codeSize = code.size();
       createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
   
       VkShaderModule shaderModule;
       if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
           throw std::runtime_error("failed to create shader module!");
       }
   
       return shaderModule;
   }
