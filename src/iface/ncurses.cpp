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

WINDOW *Ncurses::subwin(WINDOW *parent, int h, int w, int y, int x) const
{
    return ::subwin(parent, h, w, y, x);
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

int Ncurses::noecho(void) const
{
    return ::noecho();
}

int Ncurses::curs_set(int visibility) const
{
    return ::curs_set(visibility);
}

int Ncurses::wborder(WINDOW *win, int a, int b, int c, int d, int e, int f,
                     int g, int h) const
{
    return ::wborder(win, a, b, c, d, e, f, g, h);
}

bool Ncurses::has_colors(void) const
{
    return ::has_colors();
}

int Ncurses::start_color(void) const
{
    return ::start_color();
}

int Ncurses::use_default_colors(void) const
{
    return ::use_default_colors();
}

int Ncurses::alloc_pair(int fg, int bg) const
{
    return ::alloc_pair(fg, bg);
}

int Ncurses::wattr_on(WINDOW *win, int attrs) const
{
    return ::wattron(win, attrs);
}

int Ncurses::wattr_off(WINDOW *win, int attrs) const
{
    return ::wattroff(win, attrs);
}
// LCOV_EXCL_STOP
