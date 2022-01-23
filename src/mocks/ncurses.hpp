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
};

}; // namespace taskpp

#endif /* MOCKS_NCURSES_HPP */