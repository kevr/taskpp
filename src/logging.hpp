/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <atomic>
#include <fmt/core.h>
#include <fmt/format.h>
#include <iostream>
#include <mutex>
#include <string>

namespace taskpp
{

/**
 * @brief LogLevel values used by the Logger class
 *
 * These values are checked against using a bitmask operation.
 * Each next value must support all previous values in the enum.
 **/
enum LogLevel : uint8_t {
    ERROR = 0b1,
    INFO = 0b11,
    WARN = 0b111,
    DEBUG = 0b1111
};

/**
 * @brief Logger
 *
 * Loggers borrow ownership of externally provided output and
 * error std::ostream objects. This is done to allow the user
 * to do things like log to std::cout or std::cerr, file streams
 * and string streams which comes in useful for testing.
 **/
class Logger
{
private:
    std::string name;

    //! Internal log level
    std::atomic<uint8_t> level { INFO };

    //! Internal pointer to an std::ostream used for normal output
    std::ostream *cout = &std::cout;

    //! Internal pointer to an std::ostream used for error output
    std::ostream *cerr = &std::cerr;

private:
    // Delete copy construction and assignment.
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    /**
     * @brief Output implementation for the class
     *
     * This function is thread-safe. This function depends on fmtlib
     * and logs a line out to the desired std::ostream with fmt::vformat.
     *
     * @param os Output stream
     * @param loglevel Output log level
     * @param prefix Output prefix
     * @param fmt Output format string
     * @param args Optional arguments
     * @return Reference to output stream
     **/
    template <typename... Args>
    std::ostream &output(std::ostream &os, uint8_t loglevel,
                         const char *prefix, const char *fmt,
                         Args &&...args) const
    {
        using namespace std::string_literals;

        // If the bitmask is at _least_ the specified loglevel,
        // emit the message.
        const auto value = loglevel & level;
        if (value >= loglevel) {
            auto view = std::string_view(fmt);
            auto fmtargs = fmt::make_format_args(args...);
            return os << (prefix + " "s + name + ": "s +
                          fmt::vformat(std::move(view), std::move(fmtargs)) +
                          "\n"s);
        }
        return os;
    }

public:
    //! Construct a Logger with optional cout and cerr
    Logger(std::string name, LogLevel level = INFO,
           std::ostream &cout = std::cout, std::ostream &cerr = std::cerr);

    //! Move construct
    Logger(Logger &&other);

    //! Move assignment
    Logger &operator=(Logger &&other);

    //! Set the log level
    Logger &set_level(LogLevel new_level);

    //! Set and return the output stream
    std::ostream &output_stream(std::ostream &os);

    //! Set and return the error stream
    std::ostream &error_stream(std::ostream &os);

    //! Log with the ERROR loglevel
    template <typename... Args>
    std::ostream &error(const char *fmt, Args &&...args) const
    {
        return output(*cerr, ERROR, "[ERROR]", fmt, args...);
    }

    //! Log with the INFO loglevel
    template <typename... Args>
    std::ostream &info(const char *fmt, Args &&...args) const
    {
        return output(*cout, INFO, "[INFO]", fmt, args...);
    }

    //! Log with the WARN loglevel
    template <typename... Args>
    std::ostream &warn(const char *fmt, Args &&...args) const
    {
        return output(*cerr, WARN, "[WARN]", fmt, args...);
    }

    //! Log with the DEBUG loglevel
    template <typename... Args>
    std::ostream &debug(const char *fmt, Args &&...args) const
    {
        return output(*cout, DEBUG, "[DEBUG]", fmt, args...);
    }
};

/**
 * @brief Write raw error log message to stderr and return a code
 *
 * @param return_code Return code
 * @param fmt Format string
 * @param args Optional arguments
 * @return `return_code`
 **/
template <typename... Args>
int rc_raw_error_log(int return_code, const char *const fmt, Args &&...args)
{
    auto view = std::string_view(fmt);
    auto fmtargs = fmt::make_format_args(args...);
    auto error = "error: " + fmt::vformat(view, fmtargs) + "\n";
    std::cerr << error;
    return return_code;
}

/**
 * @brief Write raw error log message to stderr and return 1
 *
 * @param fmt Format string
 * @param args Optional arguments
 * @return 1
 **/
template <typename... Args>
int raw_error_log(const char *const fmt, Args &&...args)
{
    return rc_raw_error_log(1, fmt, args...);
}

std::string get_filename(std::string path);

}; // namespace taskpp

#ifndef PROJECT_ROOT
static_assert(false, "-DPROJECT_ROOT must be defined");
#endif

#define PROJECT_ROOT_LEN (sizeof(PROJECT_ROOT) / sizeof(PROJECT_ROOT[0])) - 1
#define __FILENAME__ taskpp::get_filename(__FILE__)
#define __LOCATION__                                                          \
    __FILENAME__ + std::string("#L") + std::to_string(__LINE__)

#endif /* LOGGING_HPP */
