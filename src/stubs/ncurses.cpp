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
#define wrefresh _wrefresh
#define delwin _delwin
#define endwin _endwin
#include <ncurses.h>
#undef initscr
#undef wrefresh
#undef delwin
#undef endwin

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
};
// LCOV_EXCL_STOP
