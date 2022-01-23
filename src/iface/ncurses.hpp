/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef IFACE_NCURSES_HPP
#define IFACE_NCURSES_HPP

#include <ncurses.h>

namespace taskpp
{

class NcursesInterface
{
public:
    virtual ~NcursesInterface(void) = default;

    virtual WINDOW *initscr(void) const = 0;
    virtual WINDOW *subwin(WINDOW *, int, int, int, int) const = 0;
    virtual int refresh(void) const = 0;
    virtual int wrefresh(WINDOW *) const = 0;
    virtual int delwin(WINDOW *) const = 0;
    virtual int endwin(void) const = 0;
    virtual int columns(void) const = 0;
    virtual int rows(void) const = 0;
    virtual int noecho(void) const = 0;
    virtual int curs_set(int) const = 0;
    virtual int wborder(WINDOW *, int, int, int, int, int, int, int,
                        int) const = 0;
};

class Ncurses : public NcursesInterface
{
public:
    ~Ncurses(void) = default;

    WINDOW *initscr(void) const final override;
    WINDOW *subwin(WINDOW *, int, int, int, int) const final override;
    int refresh(void) const final override;
    int wrefresh(WINDOW *) const final override;
    int delwin(WINDOW *) const final override;
    int endwin(void) const final override;
    int columns(void) const final override;
    int rows(void) const final override;
    int noecho(void) const final override;
    int curs_set(int) const final override;
    int wborder(WINDOW *, int, int, int, int, int, int, int,
                int) const final override;
};

}; // namespace taskpp

#endif /* IFACE_NCURSES_HPP */
