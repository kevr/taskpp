/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef APP_HPP
#define APP_HPP

#include "config.hpp"
#include "tui/terminal.hpp"

namespace taskpp
{

class App
{
private:
    Config config;
    Terminal *term = nullptr;

public:
    //! Initialize the application
    int init(int argc, char **argv);

    //! Run the application
    int run(void);
};

}; // namespace taskpp

#endif /* APP_HPP */
