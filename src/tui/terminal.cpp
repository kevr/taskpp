/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "terminal.hpp"
#include "../library.hpp"
#include "../logging.hpp"
#include <stdexcept>
using namespace taskpp;

static Logger logger("tui.terminal");

static std::atomic<bool> constructed;

Terminal::Terminal(void)
{
    if (constructed.load()) {
        logger.error("already constructed");
        throw std::domain_error(
            "Only one Terminal can be constructed at any time.");
    }

    constructed.store(true);

    // Initialize the root window.
    ncurses().initscr();

    // Create a child window.
    window = Window(0, 0, columns(), rows());
    refresh();
}

Terminal::~Terminal(void)
{
    // Cleanup the child window.
    window.reset();

    // Cleanup the root window.
    ncurses().endwin();

    constructed.store(false);
}

void Terminal::refresh(void)
{
    ncurses().refresh();
    window->refresh();
}

int Terminal::columns(void)
{
    return ncurses().columns();
}

int Terminal::rows(void)
{
    return ncurses().rows();
}
