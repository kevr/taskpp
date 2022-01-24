/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "color.hpp"
#include "ncurses.h"
#include <gtest/gtest.h>
using namespace taskpp;

TEST(Color, get_set_color)
{
    auto pair = set_pair(COLOR_NORM, COLOR_GREEN, COLOR_GREEN);
    ASSERT_EQ(get_color(COLOR_NORM), pair);
}

TEST(Color, set_twice_fails)
{
    set_pair(COLOR_NORM, COLOR_GREEN, COLOR_GREEN);
    ASSERT_THROW(set_pair(COLOR_NORM, COLOR_WHITE, COLOR_BLACK),
                 std::logic_error);
}
