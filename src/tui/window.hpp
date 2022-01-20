/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef TUI_WINDOW_HPP
#define TUI_WINDOW_HPP

#include <ncurses.h>

namespace taskpp
{

class Window
{
private:
    WINDOW *ptr = nullptr;

public:
    //! Construct a Window
    Window(WINDOW *window);

    //! Deconstruct a Window
    ~Window(void);

    //! Return Window's internal pointer
    WINDOW *pointer(void) const;
};

}; // namespace taskpp

#endif /* TUI_WINDOW_HPP */
