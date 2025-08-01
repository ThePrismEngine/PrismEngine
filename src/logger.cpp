#include "logger.h"

namespace prism::logger {
    namespace {
        Level logLevel = Level::INFO;
        std::unique_ptr<std::ofstream> logFileStream;
        bool useCustomOutput = false;

        // Стандартная функция вывода SDL
        static SDL_LogOutputFunction defaultOutputFunction = nullptr;
        static void* defaultUserdata = nullptr;

        std::optional<Error> lastError;

        // функция вывода
        void CustomOutputFunction(void* userdata, int category,
            SDL_LogPriority priority, const char* message) {
            if (logFileStream && logFileStream->is_open()) {
                *logFileStream << message << std::endl;
            }

            // Всегда выводим в стандартный вывод SDL
            if (defaultOutputFunction) {
                defaultOutputFunction(defaultUserdata, category, priority, message);
            }
        }

        const std::unordered_map<Error, std::string> errorMessages = {
            {Error::TEST_ERROR, "It is test error"},
            {Error::FAILED_TO_CREATE_VK_INSTANCE, "failed to create Vulkan instance!"},
            {Error::FAILED_TO_CREATE_WINDOW_SURFACE, "failed to create window surface!"},
            {Error::PRISM_ENGINE_NOT_INITIALIZE, "the part of PrismEngine that requires initialization has been called, please call prism::init() at the beginning of your program" },
            {Error::WINDOW_INSTANCE_CREATE_ERROR, "Window instance creation failed for unspecified reasons"},
            {Error::NOT_CALL_CLEANUP_IN_PGC_CORE, "Cleanup was not called for an instance of the PGC::core::Core class"},
            {Error::SDL_VULKAN_EXTENSIONS_COUNT_FAILED, "Failed to get SDL Vulkan instance extensions count"},
            {Error::VULKAN_VALIDATION_LAYERS_UNAVAILABLE, "Vulkan validation layers requested, but not available!"},
            {Error::VULKAN_DEBUG_MESSENGER_SETUP_FAILED, "Failed to set up debug messenger!"},
            {Error::VULKAN_NO_GPU_SUPPORT, "Failed to find GPUs with Vulkan support!"},
            {Error::VULKAN_NO_SUITABLE_GPU, "Failed to find a suitable GPU!"},
            {Error::VULKAN_LOGICAL_DEVICE_CREATION_FAILED, "Failed to create logical device!"},
            {Error::VULKAN_SWAP_CHAIN_FAILED, "Failed to create swap chain!"}
        };
    }

    void setLevel(Level level) {
        logLevel = level;
        SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION,
            static_cast<SDL_LogPriority>(level));
    }

    bool setOutputFile(const std::string& filename) {
        try {
            // Сохраняем стандартный вывод, если ещё не сделали этого
            if (!defaultOutputFunction) {
                SDL_LogGetOutputFunction(&defaultOutputFunction, &defaultUserdata);
            }

            logFileStream = std::make_unique<std::ofstream>();
            logFileStream->open(filename, std::ios::app);

            if (!logFileStream->is_open()) {
                logFileStream.reset();
                return false;
            }

            SDL_LogSetOutputFunction(CustomOutputFunction, nullptr);
            useCustomOutput = true;
            return true;
        }
        catch (...) {
            logFileStream.reset();
            return false;
        }
    }

    void setOutputConsole() {
        if (logFileStream) {
            logFileStream->close();
            logFileStream.reset();
        }

        if (useCustomOutput && defaultOutputFunction) {
            SDL_LogSetOutputFunction(defaultOutputFunction, defaultUserdata);
        }
        useCustomOutput = false;
    }

    void log(Level level, const std::string& message) {
        if (static_cast<int>(level) < static_cast<int>(logLevel)) return;
        SDL_LogPriority priority = static_cast<SDL_LogPriority>(level);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, "%s", message.c_str());
    }

    void logError(Error err, const std::string& details) {
        std::string fullMsg = "[ENGINE ERROR] " + errorMessages.at(err);
        if (!details.empty()) {
            fullMsg += " | Details: " + details;
        }

        // Сохраняем ошибку
        lastError = err;

        log(Level::ERROR, fullMsg);
    }

    void verbose(const std::string& message) { log(Level::VERBOSE, message); }
    void debug(const std::string& message) { log(Level::DEBUG, message); }
    void info(const std::string& message) { log(Level::INFO, message); }
    void warning(const std::string& message) { log(Level::WARNING, message); }
    void error(const std::string& message) { log(Level::ERROR, message); }
    void critical(const std::string& message) { log(Level::CRITICAL, message); }
    std::optional<Error> getLastError()
    {
        return lastError;
    }

    bool hasLastError() {
        return lastError.has_value();
    }

    bool checkLastErrorType(Error errorType) {
        return lastError.has_value() && lastError == errorType;
    }

    void clearLastError() {
        lastError.reset();
    }
}