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

    /**
     * @brief Wrap a function f's call with color application
     *
     * @param color_pair Color pair to apply
     * @param f Function to be wrapped
     * @return Reference to this Window
     **/
    template <typename Function>
    Window &color(int color_pair, Function f)
    {
        auto &ncurses = ncurses();
        ncurses.wattr_on(ptr, color_pair);
        f(*this);
        ncurses.wattr_off(ptr, color_pair);
        return *this;
    }

    //! Apply a color pair to the Window
    Window &set_color(chtype color_pair);

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
