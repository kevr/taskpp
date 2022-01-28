/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef TUI_BOARD_HPP
#define TUI_BOARD_HPP

#include "window.hpp"

namespace taskpp
{

class Board : public Window
{
public:
    Board(std::shared_ptr<Window> parent, int y);
    ~Board(void) = default;
};

}; // namespace taskpp

#endif /* TUI_BOARD_HPP */
