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
#include <ncurses.h>
#undef initscr
#undef subwin
#undef wrefresh
#undef delwin
#undef endwin
#undef noecho
#undef curs_set
#undef wborder

int COLS = 0;
int LINES = 0;

//! noop
WINDOW *initscr(void)
{
    return nullptr;
}

//! noop
WINDOW *newwin(int, int, int, int)
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
};
// LCOV_EXCL_STOP
