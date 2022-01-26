/**
 * @brief Main entry point for the taskpp application.
 *
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "app.hpp"
#include "config.hpp"
#include "tui/terminal.hpp"
#include <iostream>
using namespace taskpp;

int main(int argc, char **argv)
{
    App app;
    if (auto error_code = app.init(argc, argv)) {
        // If the error_code returned was HELP_CODE, we return
        // successfully; --[config-]help was given.
        if (error_code == RETURN_HELP)
            return 0;
        return error_code;
    }
    return app.run();
}
