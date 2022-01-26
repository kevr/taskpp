/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "color.hpp"
#include "../logging.hpp"
#include <gtest/gtest.h>
#include <ncurses.h>
using namespace taskpp;

static Logger logger(__FILENAME__);

class ColorTest : public ::testing::Test
{
public:
    void TearDown(void)
    {
        clear_colors();
    }
};

TEST_F(ColorTest, get_set_color)
{
    auto pair = set_pair(COLOR_NORM, COLOR_GREEN, COLOR_GREEN);
    ASSERT_EQ(get_color(COLOR_NORM), pair);
}

TEST_F(ColorTest, set_twice_fails)
{
    set_pair(COLOR_NORM, COLOR_GREEN, COLOR_GREEN);
    ASSERT_THROW(set_pair(COLOR_NORM, COLOR_WHITE, COLOR_BLACK),
                 std::logic_error);
}

TEST_F(ColorTest, clear)
{
    // Set the COLOR_NORM color.
    auto pair = set_pair(COLOR_NORM, COLOR_GREEN, COLOR_GREEN);
    ASSERT_EQ(get_color(COLOR_NORM), pair);

    // Clear the colors and expect that COLOR_NORM now returns -1.
    clear_colors();
    ASSERT_EQ(get_color(COLOR_NORM), -1);
}
