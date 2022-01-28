/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "screen.hpp"
#include "window.hpp"
#include <logging.hpp>
using namespace taskpp;

static Logger logger(__FILENAME__);

void Screen::init(std::shared_ptr<Window> stdscr, std::shared_ptr<Window> root)
{
    this->stdscr = std::move(stdscr);
    this->root = std::move(root);
    emplace(TERM, this->stdscr);
    emplace(TERM, ROOT, this->root);
}

void Screen::emplace(Widget w, std::shared_ptr<Window> window)
{
    map.emplace(w, std::move(window));
}

void Screen::emplace(Widget parent, Widget w, std::shared_ptr<Window> window)
{
    auto &parent_ptr = map.at(parent);
    window->set_parent(*parent_ptr);
    parent_ptr->add_child(window);
    emplace(w, window);
}

std::shared_ptr<Window> Screen::window(Widget w) const
{
    return map.at(w);
}
