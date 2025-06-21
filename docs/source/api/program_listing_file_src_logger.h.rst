
.. _program_listing_file_src_logger.h:

Program Listing for File logger.h
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_logger.h>` (``src\logger.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include <SDL2/SDL_log.h>
   #include <string>
   #include <memory>
   #include <fstream>
   #include <unordered_map>
   
   namespace prism::logger {
       enum class Error {
           TEST_ERROR 
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
   }
