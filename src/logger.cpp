#include "logger.h"

namespace prism::logger {
    namespace {
        Level logLevel = Level::INFO;
        std::unique_ptr<std::ofstream> logFileStream;
        bool useCustomOutput = false;

        // Стандартная функция вывода SDL
        static SDL_LogOutputFunction defaultOutputFunction = nullptr;
        static void* defaultUserdata = nullptr;

        // Наша функция вывода
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
            {Error::TEST_ERROR, "It is test error"}
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
        log(Level::ERROR, fullMsg);
    }

    void verbose(const std::string& message) { log(Level::VERBOSE, message); }
    void debug(const std::string& message) { log(Level::DEBUG, message); }
    void info(const std::string& message) { log(Level::INFO, message); }
    void warning(const std::string& message) { log(Level::WARNING, message); }
    void error(const std::string& message) { log(Level::ERROR, message); }
    void critical(const std::string& message) { log(Level::CRITICAL, message); }
}