/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "window.hpp"
#include <gtest/gtest.h>
using namespace taskpp;

TEST(Window, lifecycle)
{
    {
        // Construct window.
        Window window(nullptr);
        // Deconstruct window.
    }
}

TEST(Window, pointer)
{
    auto ptr = reinterpret_cast<WINDOW *>(1);
    Window window(ptr);
    ASSERT_EQ(window.pointer(), ptr);
}
