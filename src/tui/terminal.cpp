/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "terminal.hpp"
#include "../exceptions.hpp"
#include "../library.hpp"
#include "../logging.hpp"
#include "color.hpp"
#include <functional>
#include <stdexcept>
using namespace taskpp;

static std::atomic<bool> constructed;
static Logger logger(__FILENAME__);

void Terminal::start(void)
{
    // This class can only be constructed once at any time. `constructed`
    // is a static std::atomic<bool> used to detect this.
    if (constructed) {
        throw std::logic_error(
            "Only one Terminal can be constructed at any time.");
    }
    constructed = true;

    auto &ncurses = ncurses();

    // Initialize the screen.
    auto *scr = ncurses.initscr();
    ASSERT_NOT_NULL(scr);

    // Produce a Window out of the screen.
    _stdscr = std::make_shared<Window>(scr);
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

    // Create a child window of _stdscr.
    _root = std::make_shared<Window>();
    _root->set_parent(*_stdscr).init(0, 0, 0, 0);
}

Terminal::~Terminal(void)
{
    if (_root)
        _root->teardown();
    constructed = false;
}

void Terminal::refresh(void)
{
    _root->refresh();
}

std::shared_ptr<Window> Terminal::stdscr(void) const
{
    return _stdscr;
}

std::shared_ptr<Window> Terminal::root(void) const
{
    return _root;
}

int Terminal::columns(void)
{
    return ncurses().columns();
}

int Terminal::rows(void)
{
    return ncurses().rows();
}
