/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef TUI_WINDOW_HPP
#define TUI_WINDOW_HPP

#include "../iface/ncurses.hpp"

namespace taskpp
{

class Window
{
private:
    WINDOW *ptr = nullptr;

public:
    /**
     * @brief Construct a Window
     *
     * @param x Horizontal start position
     * @param y Vertical start position
     * @param w Horizontal width
     * @param h Vertical height
     **/
    Window(int x, int y, int w, int h);

    //! Deconstruct a Window
    virtual ~Window(void);

    //! Return Window's internal pointer
    WINDOW *pointer(void) const;

    //! Refresh the window
    int refresh(void) const;
};

}; // namespace taskpp

#endif /* TUI_WINDOW_HPP */
