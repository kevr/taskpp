/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#define main _main
#include "main.cpp"
#undef main

#include <gtest/gtest.h>

const char *arg0 = "taskpp";

TEST(main, runs)
{
    auto rc = _main(1, const_cast<char **>(&arg0));
    ASSERT_EQ(rc, 0);
}

TEST(main, invalid_args)
{
    const char *argv[3] = { arg0, "invalid", nullptr };
    auto rc = _main(2, const_cast<char **>(argv));
    ASSERT_EQ(rc, 1);
}
