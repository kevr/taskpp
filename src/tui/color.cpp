/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "tui/color.hpp"
#include "../iface/ncurses.hpp"
#include "../library.hpp"
#include <fmt/format.h>
using namespace taskpp;

Color &Color::instance(void)
{
    static Color instance;
    return instance;
}

void Color::set(TermColor id, int pair)
{
    if (map.find(id) != map.end())
        throw std::logic_error(
            fmt::format("TermColor '{}' already registered", id));
    map[id] = pair;
}

int Color::get(TermColor id) const
{
    if (map.find(id) == map.end())
        return -1;
    return map.at(id);
}

namespace taskpp
{

int set_pair(TermColor id, int fg, int bg)
{
    int pair = ncurses().alloc_pair(fg, bg);
    Color::instance().set(id, pair);
    return pair;
}

int get_color(TermColor id)
{
    return COLOR_PAIR(Color::instance().get(id));
}

}; // namespace taskpp
