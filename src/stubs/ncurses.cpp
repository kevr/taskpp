/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
extern "C" {
// Use some preprocessor hackery to avoid bringing in
// the stub's real functions. We include ncurses.h here
// to gain access to WINDOW for the stub functions.
#define wrefresh _wrefresh
#define endwin _endwin
#define delwin _delwin
#include <ncurses.h>
#undef wrefresh
#undef endwin
#undef delwin

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
