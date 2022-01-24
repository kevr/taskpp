/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef TUI_WINDOW_HPP
#define TUI_WINDOW_HPP

#include "../iface/ncurses.hpp"
#include "../library.hpp"
#include "color.hpp"
#include <atomic>

namespace taskpp
{

class Window
{
private:
    //! Internal pointer to the parent WINDOW
    WINDOW *parent = nullptr;

    //! Internal pointer to the ncurses WINDOW
    WINDOW *ptr = nullptr;

public:
    //! Construct a Window
    Window(void) = default;

    //! Construct a Window directly with a parent
    Window(WINDOW *parent);

    //! Deconstruct a Window
    virtual ~Window(void);

    //! Set the internal parent pointer
    Window &set_parent(WINDOW *ptr);

    /**
     * @brief Initialize the Window
     *
     * @param x Horizontal start position
     * @param y Vertical start position
     * @param w Horizontal width
     * @param h Vertical height
     **/
    Window &init(int x, int y, int w, int h);

    template <typename Function>
    Window &color(short attr, Function f)
    {
        auto &ncurses = ncurses();
        ncurses.wattr_on(ptr, attr);
        f(*this);
        ncurses.wattr_off(ptr, attr);
        return *this;
    }

    //! State of the Window
    operator bool(void) const;

    //! Return Window's internal pointer
    WINDOW *pointer(void) const;

    //! Refresh the window
    int refresh(void) const;

    //! Draw a border around the window
    const Window &box(void) const;

    //! Teardown internal window
    const Window &teardown(void) const;
};

}; // namespace taskpp

#endif /* TUI_WINDOW_HPP */
