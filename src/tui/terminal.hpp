/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef TUI_TERMINAL_HPP
#define TUI_TERMINAL_HPP

#include "color.hpp"
#include "window.hpp"
#include <atomic>
#include <memory>

namespace taskpp
{

/**
 * @brief All-encompassing ncurses terminal
 *
 * This class represents a root ncurses window and provides methods
 * for manipulating the ncurses environment. Only one Terminal can
 * live at any one time, guarded by the static Terminal::constructed
 * boolean.
 *
 * Internally, std::optional<T>s are used to refer to Window-like classes
 * derivatives.
 *
 * If a second Terminal is constructed within the same scope, a
 * std::domain_error is thrown.
 **/
class Terminal
{
private:
    //! Internal color flag
    bool has_colors = false;

    //! Root ncurses window
    WINDOW *stdscr = nullptr;

    //! First child window
    Window window;

public:
    //! Construct a Terminal
    Terminal(void);

    //! Deconstruct a Terminal
    ~Terminal(void);

    //! Refresh the child Window
    void refresh(void);

    //! Return global COLS macro
    static int columns(void);

    //! Return global LINES macro
    static int rows(void);
};

}; // namespace taskpp

#endif /* TUI_TERMINAL_HPP */
