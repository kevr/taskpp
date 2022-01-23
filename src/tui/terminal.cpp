/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "terminal.hpp"
#include "../library.hpp"
#include "../logging.hpp"
#include <functional>
#include <stdexcept>
using namespace taskpp;

static Logger logger(__LOCATION__);
static std::atomic<bool> constructed;

Terminal::Terminal(void)
{
    if (constructed) {
        logger.error("already constructed");
        throw std::domain_error(
            "Only one Terminal can be constructed at any time.");
    }
    constructed = true;

    auto &ncurses = ncurses();

    // Initialize the root window.
    stdscr = ncurses.initscr();
    if (!stdscr)
        throw std::runtime_error("initscr");
    ncurses.refresh();

    ncurses.noecho();
    ncurses.curs_set(FALSE);

    // Create a child window.
    window.set_parent(stdscr);
    window.init(0, 0, 0, 0).box().refresh();
}

Terminal::~Terminal(void)
{
    window.teardown();
    ncurses().endwin();
    constructed = false;
}

void Terminal::refresh(void)
{
    window.refresh();
}

int Terminal::columns(void)
{
    return ncurses().columns();
}

int Terminal::rows(void)
{
    return ncurses().rows();
}
