/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef MOCKS_NCURSES_HPP
#define MOCKS_NCURSES_HPP

#include "../iface/ncurses.hpp"
#include <gmock/gmock.h>

namespace taskpp
{

class MockNcurses : public NcursesInterface
{
public:
    MOCK_METHOD(WINDOW *, initscr, (), (const, override));
    MOCK_METHOD(WINDOW *, subwin, (WINDOW *, int, int, int, int),
                (const, override));
    MOCK_METHOD(int, refresh, (), (const, override));
    MOCK_METHOD(int, wrefresh, (WINDOW *), (const, override));
    MOCK_METHOD(int, delwin, (WINDOW *), (const, override));
    MOCK_METHOD(int, endwin, (), (const, override));
    MOCK_METHOD(int, columns, (), (const, override));
    MOCK_METHOD(int, rows, (), (const, override));
    MOCK_METHOD(int, noecho, (), (const, override));
    MOCK_METHOD(int, curs_set, (int), (const, override));
    MOCK_METHOD(int, wborder,
                (WINDOW *, int, int, int, int, int, int, int, int),
                (const, override));
    MOCK_METHOD(bool, has_colors, (), (const, override));
    MOCK_METHOD(int, start_color, (), (const, override));
    MOCK_METHOD(int, use_default_colors, (), (const, override));
    MOCK_METHOD(int, alloc_pair, (int, int), (const, override));
    MOCK_METHOD(int, wattr_on, (WINDOW *, int), (const, override));
    MOCK_METHOD(int, wattr_off, (WINDOW *, int), (const, override));
};

}; // namespace taskpp

#endif /* MOCKS_NCURSES_HPP */
