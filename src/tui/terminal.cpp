/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "terminal.hpp"
#include <stdexcept>
using namespace taskpp;

std::atomic<bool> Terminal::constructed(false);

Terminal::Terminal(void)
{
    if (constructed) {
        throw std::domain_error(
            "Only one Terminal can be constructed at any time.");
    }

    constructed = true;
    window = std::make_unique<Window>(initscr());
    refresh();
}

Terminal::~Terminal(void)
{
    window.reset();
    endwin();
    constructed = false;
}

void Terminal::refresh(void)
{
    wrefresh(window.get()->pointer());
}
