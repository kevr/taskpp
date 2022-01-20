/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef TUI_TERMINAL_HPP
#define TUI_TERMINAL_HPP

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
 * If a second Terminal is constructed within the same scope, a
 * std::domain_error is thrown.
 **/
class Terminal
{
private:
    //! Static reference count guard; only one Terminal is allowed
    static std::atomic<bool> constructed;

private:
    //! Internal ncurses window handle
    std::unique_ptr<Window> window;

public:
    //! Construct a Terminal
    Terminal(void);

    //! Deconstruct a Terminal
    ~Terminal(void);

    //! Refresh the root window
    void refresh(void);
};

}; // namespace taskpp

#endif /* TUI_TERMINAL_HPP */
