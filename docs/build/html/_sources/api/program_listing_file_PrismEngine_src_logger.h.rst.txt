
.. _program_listing_file_PrismEngine_src_logger.h:

Program Listing for File logger.h
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_PrismEngine_src_logger.h>` (``PrismEngine\src\logger.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <SDL2/SDL_log.h>
   #include <string>
   #include <memory>
   #include <fstream>
   #include <unordered_map>
   #include <optional>
   
   namespace prism::logger {
       enum class Error {
           TEST_ERROR, 
           FAILED_TO_CREATE_VK_INSTANCE,
           FAILED_TO_CREATE_WINDOW_SURFACE,
           PRISM_ENGINE_NOT_INITIALIZE,
           WINDOW_INSTANCE_CREATE_ERROR,
           NOT_CALL_CLEANUP_IN_PGC_CORE,
           SDL_VULKAN_EXTENSIONS_COUNT_FAILED,
           VULKAN_VALIDATION_LAYERS_UNAVAILABLE,
           VULKAN_DEBUG_MESSENGER_SETUP_FAILED,
           VULKAN_NO_GPU_SUPPORT,
           VULKAN_NO_SUITABLE_GPU,
           VULKAN_LOGICAL_DEVICE_CREATION_FAILED,
           VULKAN_SWAP_CHAIN_FAILED,
           FAILED_TO_OPEN_FILE,
           FAILED_TO_DETERMINE_FILE_SIZE,
           FAILED_TO_READ_FILE,
       };
   
       enum class Level {
           VERBOSE = SDL_LOG_PRIORITY_VERBOSE,  
           DEBUG = SDL_LOG_PRIORITY_DEBUG,      
           INFO = SDL_LOG_PRIORITY_INFO,        
           WARNING = SDL_LOG_PRIORITY_WARN,     
           ERROR = SDL_LOG_PRIORITY_ERROR,      
           CRITICAL = SDL_LOG_PRIORITY_CRITICAL 
       };
   
       void setLevel(Level level);
   
       bool setOutputFile(const std::string& filename);
   
       void setOutputConsole();
   
       void log(Level level, const std::string& message);
   
       void logError(Error err, const std::string& details = "");
   
       void verbose(const std::string& message);
   
       void debug(const std::string& message);
   
       void info(const std::string& message);
   
       void warning(const std::string& message);
   
       void error(const std::string& message);
   
       void critical(const std::string& message);
   
       std::optional<Error> getLastError();
   
       bool hasLastError();
   
       bool checkLastErrorType(Error errorType);
   
       void clearLastError();
   }
