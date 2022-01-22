/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "window.hpp"
#include "../library.hpp"
#include <stdexcept>
using namespace taskpp;

Window::Window(int x, int y, int w, int h)
    : ptr(ncurses().newwin(h, w, y, x))
{
    if (ptr == nullptr) {
        throw std::runtime_error(
            "newwin(h, w, y, x) is unable to create a new window.");
    }
}

Window::~Window(void)
{
    ncurses().delwin(ptr);
}

WINDOW *Window::pointer(void) const
{
    return ptr;
}

int Window::refresh(void) const
{
    return ncurses().wrefresh(ptr);
}
