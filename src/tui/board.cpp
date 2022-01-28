/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "board.hpp"
using namespace taskpp;

Board::Board(std::shared_ptr<Window> parent, int y)
{
    set_parent(*parent);
    auto &ncurses = ncurses();
    auto delta = ncurses.rows() - y * 2;
    init(0, y, ncurses.columns(), ncurses.rows() - delta);
}
