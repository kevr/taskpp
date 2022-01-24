/**
 * @brief Main entry point for the taskpp application.
 *
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "config.hpp"
#include "logging.hpp"
#include "tui/terminal.hpp"
#include <iostream>
using namespace taskpp;

static Logger logger(__FILENAME__);

int main(int argc, char **argv)
{
    Config config(argv[0]);
    auto err = config.parse_args(argc, argv);
    if (err)
        return err;

    if (config.has("help")) {
        return config.help(std::cout, 0);
    } else if (config.has("config-help")) {
        return config.config_help(std::cout, 0);
    } else if (config.get<bool>("verbose")) {
        logger.set_level(DEBUG);
        log_debug("Debug logging enabled.");
    }

    log_info("This is project {}.", PROJECT_NAME);

    Terminal term;
    return 0;
}
