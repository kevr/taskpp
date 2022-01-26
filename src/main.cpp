/**
 * @brief Main entry point for the taskpp application.
 *
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "app.hpp"
#include "config.hpp"
#include "logging.hpp"
#include "tui/terminal.hpp"
#include <iostream>
using namespace taskpp;

static Logger logger(__FILENAME__);

int main(int argc, char **argv)
{
    App app;
    if (auto error_code = app.init(argc, argv))
        return error_code;
    return app.run();
}
