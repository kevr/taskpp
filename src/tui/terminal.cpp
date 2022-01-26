/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "terminal.hpp"
#include "../library.hpp"
#include "../logging.hpp"
#include "../tui/color.hpp"
#include <functional>
#include <stdexcept>
using namespace taskpp;

static std::atomic<bool> constructed;
static Logger logger(__FILENAME__);

Terminal::Terminal(void)
{
    if (constructed) {
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

    // Initialize colors.
    has_colors = ncurses.has_colors();
    if (has_colors) {
        ncurses.start_color();
        ncurses.use_default_colors();
        set_pair(COLOR_NORM, COLOR_NONE, COLOR_NONE);
        set_pair(COLOR_BAR, COLOR_BLACK, COLOR_BLUE);
        set_pair(COLOR_ACCENT, COLOR_BLUE, COLOR_NONE);
    }

    // Initialize screen attributes.
    ncurses.noecho();
    ncurses.curs_set(FALSE);

    // Create a child window.
    window.set_parent(stdscr)
        .init(0, 0, 0, 0)
        .set_color(get_color(COLOR_BAR))
        .color(get_color(COLOR_BAR),
               [](Window &window) {
                   window.box();
               })
        .refresh();
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
