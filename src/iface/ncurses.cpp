/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
// LCOV_EXCL_START
#include "ncurses.hpp"
using namespace taskpp;

WINDOW *Ncurses::initscr(void) const
{
    return ::initscr();
}

WINDOW *Ncurses::newwin(int y, int x, int h, int w) const
{
    return ::newwin(y, x, h, w);
}

int Ncurses::refresh(void) const
{
    return ::refresh();
}

int Ncurses::wrefresh(WINDOW *window) const
{
    return ::wrefresh(window);
}

int Ncurses::delwin(WINDOW *window) const
{
    return ::delwin(window);
}

int Ncurses::endwin(void) const
{
    return ::endwin();
}

int Ncurses::columns(void) const
{
    return COLS;
}

int Ncurses::rows(void) const
{
    return LINES;
}
// LCOV_EXCL_STOP
