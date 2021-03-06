/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef IFACE_NCURSES_HPP
#define IFACE_NCURSES_HPP

#include <boost/any.hpp>
#include <ncurses.h>
#include <vector>

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
    virtual int wmove(WINDOW *, int, int) const = 0;

    virtual int mvwprintw(WINDOW *, int, int, const std::string &) const = 0;

    // Coloring
    virtual bool has_colors(void) const = 0;
    virtual int start_color(void) const = 0;
    virtual int use_default_colors(void) const = 0;
    virtual int alloc_pair(int, int) const = 0;
    virtual int wattr_on(WINDOW *, int) const = 0;
    virtual int wattr_off(WINDOW *, int) const = 0;
    virtual int wbkgd(WINDOW *, chtype) const = 0;
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
    int wmove(WINDOW *, int, int) const final override;
    int mvwprintw(WINDOW *, int, int,
                  const std::string &) const final override;

    // Coloring
    bool has_colors(void) const final override;
    int start_color(void) const final override;
    int use_default_colors(void) const final override;
    int alloc_pair(int, int) const final override;
    int wattr_on(WINDOW *, int) const final override;
    int wattr_off(WINDOW *, int) const final override;
    int wbkgd(WINDOW *, chtype) const final override;
};

}; // namespace taskpp

#endif /* IFACE_NCURSES_HPP */
