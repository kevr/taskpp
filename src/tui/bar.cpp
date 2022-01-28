/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "bar.hpp"
#include "../config.hpp"
#include "../logging.hpp"
#include "color.hpp"
using namespace taskpp;

static Logger logger(__FILENAME__);

Bar::Bar(std::shared_ptr<Window> parent, int y)
{
    set_parent(*parent);
    init(0, y, ncurses().columns(), BAR_HEIGHT)
        .set_color(get_color(COLOR_BAR));
}

Bar &Bar::content(std::string value)
{
    _content = std::move(value);
    return *this;
}

void Bar::draw(void)
{
    auto &ncurses = ncurses();
    auto spaces =
        std::string(ncurses.columns() - _content.size() - PADDING * 2, ' ');
    ncurses.mvwprintw(pointer(), 0, PADDING, spaces + _content);
}
