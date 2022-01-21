/**
 * @brief Main entry point for the taskpp application.
 *
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "config.hpp"
#include "logging.hpp"
#include <iostream>
using namespace taskpp;

static Logger logger("main");

int main(int argc, char **argv)
{
    if (argc != 1)
        return raw_error_log("{} takes no arguments.", argv[0]);
    logger.info("This is project {}.", PROJECT_NAME);
    return 0;
}
