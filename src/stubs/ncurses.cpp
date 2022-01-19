/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
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

//! noop
WINDOW *initscr(void)
{
    return nullptr;
}

//! noop
int wrefresh(WINDOW *)
{
    return 0;
}

//! noop
int delwin(WINDOW *)
{
    return 0;
}

//! noop
int endwin(void)
{
    return 0;
}
};
