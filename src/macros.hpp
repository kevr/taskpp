/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef MACROS_HPP
#define MACROS_HPP

#ifndef BUILD_TEST
// Macros defined for executable.
// LCOV_EXCL_START
#include "ncurses.h"
#define VLINE ACS_VLINE
#define HLINE ACS_HLINE
#define ULCORNER ACS_ULCORNER
#define URCORNER ACS_URCORNER
#define LLCORNER ACS_LLCORNER
#define LRCORNER ACS_LRCORNER
// LCOV_EXCL_STOP
#else
// Macros defined for testing.
#define VLINE '|'
#define HLINE '-'
#define ULCORNER '+'
#define URCORNER '+'
#define LLCORNER '+'
#define LRCORNER '+'
#endif

#endif /* MACROS_HPP */
