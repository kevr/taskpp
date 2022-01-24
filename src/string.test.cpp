/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "string.hpp"
#include <gtest/gtest.h>
using namespace taskpp;

TEST(string, split)
{
    auto items = split("", ";");
    ASSERT_EQ(items.size(), 1);
    ASSERT_EQ(items.at(0), "");

    items = split("abc;def", ";");
    ASSERT_EQ(items.size(), 2);
    ASSERT_EQ(items.at(0), "abc");
    ASSERT_EQ(items.at(1), "def");
}

TEST(string, join)
{
    std::vector<std::string> v { "abc", "def" };
    ASSERT_EQ(join(",", v), "abc,def");
}

TEST(string, replace)
{
    std::string target("hello");
    ASSERT_EQ(replace(target, "l", "c"), "hecco");

    target = "hello, world!";
    ASSERT_EQ(replace(target, "lo", "^"), "hel^, world!");

    ASSERT_EQ(replace(target, "!", "xxx"), "hello, worldxxx");
    ASSERT_EQ(replace(target, "h", "blah"), "blahello, world!");
}
