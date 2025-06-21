#pragma once
#include <SDL2/SDL_log.h>
#include <string>
#include <memory>
#include <fstream>
#include <unordered_map>

namespace prism::logger {
    /**
     * @brief Перечисление ошибок движка
     * @details Содержит коды ошибок, которые могут быть залогированы через logError()
     */
    enum class Error {
        TEST_ERROR ///< Тестовая ошибка (пример)
    };

    /**
     * @brief Уровни логирования
     * @details Совместимы с уровнями логирования SDL (используют соответствующие приоритеты)
     */
    enum class Level {
        VERBOSE = SDL_LOG_PRIORITY_VERBOSE,  ///< Подробные сообщения (наибольшая детализация)
        DEBUG = SDL_LOG_PRIORITY_DEBUG,      ///< Отладочные сообщения
        INFO = SDL_LOG_PRIORITY_INFO,        ///< Информационные сообщения
        WARNING = SDL_LOG_PRIORITY_WARN,     ///< Предупреждения
        ERROR = SDL_LOG_PRIORITY_ERROR,      ///< Ошибки
        CRITICAL = SDL_LOG_PRIORITY_CRITICAL ///< Критические ошибки
    };

    /**
     * @brief Устанавливает уровень логирования
     * @param level Минимальный уровень логирования (сообщения ниже этого уровня игнорируются)
     */
    void setLevel(Level level);

    /**
     * @brief Настраивает вывод логов в файл
     * @param filename Имя файла для записи логов
     * @return true если файл успешно открыт для записи, false в случае ошибки
     */
    bool setOutputFile(const std::string& filename);

    /**
     * @brief Настраивает вывод логов в консоль
     * @details Это режим по умолчанию для системы логирования
     */
    void setOutputConsole();

    /**
     * @brief Основная функция логирования
     * @param level Уровень важности сообщения
     * @param message Текст сообщения для логирования
     */
    void log(Level level, const std::string& message);

    /**
     * @brief Логирует ошибку движка с дополнительными деталями
     * @param err Код ошибки из перечисления Error
     * @param details Дополнительная информация об ошибке (по умолчанию пустая строка)
     */
    void logError(Error err, const std::string& details = "");

    /**
     * @brief Логирует сообщение с уровнем VERBOSE
     * @param message Текст сообщения
     */
    void verbose(const std::string& message);

    /**
     * @brief Логирует сообщение с уровнем DEBUG
     * @param message Текст сообщения
     */
    void debug(const std::string& message);

    /**
     * @brief Логирует сообщение с уровнем INFO
     * @param message Текст сообщения
     */
    void info(const std::string& message);

    /**
     * @brief Логирует сообщение с уровнем WARNING
     * @param message Текст сообщения
     */
    void warning(const std::string& message);

    /**
     * @brief Логирует сообщение с уровнем ERROR
     * @param message Текст сообщения
     */
    void error(const std::string& message);

    /**
     * @brief Логирует сообщение с уровнем CRITICAL
     * @param message Текст сообщения
     */
    void critical(const std::string& message);
}