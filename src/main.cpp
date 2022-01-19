/**
 * @brief Main entry point for the taskpp application.
 *
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "config.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 1) {
        std::cout << argv[0] << "takes no arguments.\n";
        return 1;
    }
    std::cout << "This is project " << PROJECT_NAME << ".\n";
    return 0;
}
