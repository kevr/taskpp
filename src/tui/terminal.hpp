/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef TUI_TERMINAL_HPP
#define TUI_TERMINAL_HPP

#include <atomic>
#include <memory>

namespace taskpp
{

class Window;

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
    std::shared_ptr<Window> _stdscr;

    //! First child window
    std::shared_ptr<Window> _root;

public:
    //! Construct a Terminal
    Terminal(void) = default;

    //! Deconstruct a Terminal
    ~Terminal(void);

    void start(void);

    //! Refresh the child Window
    void refresh(void);

    //! Return the stdscr Window
    std::shared_ptr<Window> stdscr(void) const;

    //! Return the root Window
    std::shared_ptr<Window> root(void) const;

    //! Return global COLS macro
    static int columns(void);

    //! Return global LINES macro
    static int rows(void);
};

}; // namespace taskpp

#endif /* TUI_TERMINAL_HPP */
