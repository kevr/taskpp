/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "window.hpp"
#include "../logging.hpp"
#include "../macros.hpp"
#include <stdexcept>
using namespace taskpp;

Window::Window(WINDOW *parent)
{
    set_parent(parent);
}

Window::~Window(void)
{
    teardown();
}

Window &Window::set_parent(WINDOW *ptr)
{
    parent = ptr;
    return *this;
}

Window &Window::init(int x, int y, int w, int h)
{
    if (!parent)
        throw std::runtime_error("Window::parent cannot be null.");

    if (ptr)
        throw std::runtime_error("Window is already initialized.");

    ptr = ncurses().subwin(parent, h, w, y, x);
    if (!ptr)
        throw std::runtime_error("subwin is unable to create a new window.");

    refresh();
    return *this;
}

Window &Window::set_color(chtype color_pair)
{
    ncurses().wbkgd(ptr, color_pair);
    return *this;
}

Window::operator bool(void) const
{
    return bool(ptr);
}

WINDOW *Window::pointer(void) const
{
    return ptr;
}

int Window::refresh(void) const
{
    return ncurses().wrefresh(ptr);
}

const Window &Window::box(void) const
{
    ncurses().wborder(ptr, VLINE, VLINE, HLINE, HLINE, ULCORNER, URCORNER,
                      LLCORNER, LRCORNER); // LCOV_EXCL_LINE
    return *this;
}

const Window &Window::teardown(void) const
{
    if (ptr)
        ncurses().delwin(ptr);
    return *this;
}
