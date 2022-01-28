/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef TUI_SCREEN_HPP
#define TUI_SCREEN_HPP

#include "window.hpp"
#include <map>
#include <string>

namespace taskpp
{

enum Widget : int { SCREEN, ROOT, HEADER_BAR, BOARD, LIST, FOOTER_BAR };

class Screen
{
private:
    std::shared_ptr<Window> stdscr;
    std::shared_ptr<Window> root;
    std::map<int, std::shared_ptr<Window>> map;

public:
    Screen(void) = default;
    void init(std::shared_ptr<Window> stdscr, std::shared_ptr<Window> root);
    void emplace(Widget w, std::shared_ptr<Window> window);
    void emplace(Widget parent, Widget w, std::shared_ptr<Window> window);
    std::shared_ptr<Window> window(Widget w) const;
};

}; // namespace taskpp

#endif /* TUI_SCREEN_HPP */
