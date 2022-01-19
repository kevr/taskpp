/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "terminal.hpp"
#include <gtest/gtest.h>
using namespace taskpp;

class TerminalTest : public ::testing::Test
{
protected:
    Terminal term;
};

TEST(Terminal, constructs)
{
    Terminal term;
}

TEST_F(TerminalTest, refreshes)
{
    term.refresh();
}

TEST_F(TerminalTest, throws_on_second_construct)
{
    ASSERT_THROW(Terminal(), std::domain_error);
}
