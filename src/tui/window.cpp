/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "window.hpp"
using namespace taskpp;

Window::Window(WINDOW *window)
    : ptr(window)
{
}

Window::~Window(void)
{
    delwin(ptr);
}

WINDOW *Window::pointer(void) const
{
    return ptr;
}
