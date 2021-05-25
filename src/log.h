/**
 * logger utility with multi-level
 */

#pragma once

#include <cstdio>
#include <mutex>

enum LogType { DEBUG, INFO, WARNING, ERROR };
static const std::string LogTypeStrings[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
static std::mutex log_mutex;

extern LogType LOG_LEVEL;

/**
 * Print a debug message, accepting printf-style arguments.
 *
 * @param format C string that contains the text to be written.
 * @param ... (additional arguments)
 */
template<typename... Args>
void debug(const char* format, Args... args) {
    log(DEBUG, format, args...);
}

/**
 * Print an informational message, accepting printf-style arguments.
 *
 * @param format C string that contains the text to be written.
 * @param ... (additional arguments)
 */
template<typename... Args>
void info(const char* format, Args... args) {
    log(INFO, format, args...);
}

/**
 * Print an informational message, accepting printf-style arguments.
 *
 * @param format C string that contains the text to be written.
 * @param ... (additional arguments)
 */
template<typename... Args>
void warning(const char* format, Args... args) {
    log(WARNING, format, args...);
}

/**
 * Print an informational message, accepting printf-style arguments.
 *
 * @param format C string that contains the text to be written.
 * @param ... (additional arguments)
 */
template<typename... Args>
void error(const char* format, Args... args) {
    log(ERROR, format, args...);
}

/**
 * Internal function. Print to stdout using the given log level, in a
 * thread-safe manner.
 */
template<typename... Args>
static void log(LogType level, const char* format, Args... args) {
    std::lock_guard<std::mutex> lock(log_mutex);
    if (level < LOG_LEVEL) return;
    printf("[%s] ", LogTypeStrings[level].c_str());
    printf(format, args...);
    printf("\n");
}