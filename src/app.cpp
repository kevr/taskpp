/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "app.hpp"
#include "logging.hpp"
#include <iostream>
#include <stdexcept>
using namespace taskpp;

static Logger logger(__FILENAME__);

int App::init(int argc, char **argv)
{
    auto parse_error = config.parse_args(argc, argv);
    if (parse_error)
        return parse_error;

    if (config.has("help")) {
        return config.help(std::cout, RETURN_HELP);
    } else if (config.has("config-help")) {
        return config.config_help(std::cout, RETURN_HELP);
    } else if (config.has("version")) {
        return !(std::cout << VERSION << std::endl);
    } else if (config.get<bool>("verbose")) {
        logger.set_level(DEBUG);
        log_debug("Debug logging enabled.");
    }

    return 0;
}

int App::run(void)
{
    static Terminal term_;
    term = &term_;
    return 0;
}
