/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef TUI_BAR_HPP
#define TUI_BAR_HPP

#include "window.hpp"

namespace taskpp
{

static const int BAR_HEIGHT = 1;

class Bar : public Window
{
private:
    //! Content to be printed to the bar on draw
    std::string _content;

public:
    //! Construct and initialize a Bar at y
    Bar(std::shared_ptr<Window> parent, int y);

    //! Destruct a Bar
    ~Bar(void) = default;

    //! Set bar content
    Bar &content(std::string value);

    //! Draw bar content
    void draw(void) final override;
};

}; // namespace taskpp

#endif /* TUI_BAR_HPP */
