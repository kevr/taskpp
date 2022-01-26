/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
// LCOV_EXCL_START
extern "C" {
// Use some preprocessor hackery to avoid bringing in
// the stub's real functions. We include ncurses.h here
// to gain access to WINDOW for the stub functions.
#define initscr _initscr
#define subwin _subwin
#define wrefresh _wrefresh
#define delwin _delwin
#define endwin _endwin
#define noecho _noecho
#define curs_set _curs_set
#define wborder _wborder
#define has_colors _has_colors
#define start_color _start_color
#define alloc_pair _alloc_pair
#define wattr_on _wattron
#define wattr_off _wattroff
#define use_default_colors _use_default_colors
#define wbkgd _wbkgd
#include <ncurses.h>
#undef initscr
#undef subwin
#undef wrefresh
#undef delwin
#undef endwin
#undef noecho
#undef curs_set
#undef wborder
#undef has_colors
#undef start_color
#undef alloc_pair
#undef wattr_on
#undef wattr_off
#undef use_default_colors
#undef wbkgd

int COLS = 0;
int LINES = 0;

//! noop
WINDOW *initscr(void)
{
    return nullptr;
}

//! noop
WINDOW *subwin(WINDOW *, int, int, int, int)
{
    return nullptr;
}

//! noop
int refresh(void)
{
    return OK;
}

//! noop
int wrefresh(WINDOW *)
{
    return OK;
}

//! noop
int delwin(WINDOW *)
{
    return OK;
}

//! noop
int endwin(void)
{
    return OK;
}

int noecho(void)
{
    return OK;
}

int curs_set(int)
{
    return OK;
}

int wborder(WINDOW *, int, int, int, int, int, int, int, int)
{
    return OK;
}

bool has_colors(void)
{
    return TRUE;
}

int start_color(void)
{
    return OK;
}

int use_default_colors(void)
{
    return OK;
}

int alloc_pair(int, int)
{
    return 0;
}

int wattr_on(int)
{
    return OK;
}

int wattr_off(int)
{
    return OK;
}

int wbkgd(WINDOW *, chtype)
{
    return OK;
}
};
// LCOV_EXCL_STOP
