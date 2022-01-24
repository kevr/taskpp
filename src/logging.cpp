/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "logging.hpp"
using namespace taskpp;

std::atomic<uint8_t> Logger::level(INFO);

Logger::Logger(std::string name, std::ostream &cout, std::ostream &cerr)
    : name(std::move(name))
    , cout(&cout)
    , cerr(&cerr)
{
}

Logger::Logger(Logger &&other)
{
    *this = std::forward<Logger>(other);
}

Logger &Logger::operator=(Logger &&other)
{
    cout = other.cout;
    cerr = other.cerr;
    other.level = INFO;
    other.cout = &std::cout;
    other.cerr = &std::cerr;
    return *this;
}

LogLevel Logger::set_level(LogLevel new_level)
{
    level = new_level;
    return new_level;
}

std::ostream &Logger::output_stream(std::ostream &os)
{
    cout = &os;
    return os;
}

std::ostream &Logger::error_stream(std::ostream &os)
{
    cerr = &os;
    return os;
}

std::string taskpp::get_filename(std::string path)
{
    path.erase(0, PROJECT_ROOT_LEN);
    return path;
}
