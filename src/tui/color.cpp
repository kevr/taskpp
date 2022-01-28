/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "color.hpp"
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

void Color::clear(void)
{
    map.clear();
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
    auto retval = Color::instance().get(id);
    if (retval == -1)
        return retval;
    return COLOR_PAIR(Color::instance().get(id));
}

void clear_colors(void)
{
    return Color::instance().clear();
}
}; // namespace taskpp
