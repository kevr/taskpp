/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "terminal.hpp"
#include "../exceptions.hpp"
#include "../library.hpp"
#include "../mocks/ncurses.hpp"
#include <gtest/gtest.h>
#include <memory>
using namespace taskpp;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;

class TerminalTest : public ::testing::Test
{
protected:
    NiceMock<MockNcurses> mock_ncurses;
    std::unique_ptr<Terminal> term;

public:
    void SetUp(void)
    {
        set_library("ncurses", mock_ncurses);

        WINDOW *root = reinterpret_cast<WINDOW *>(1);
        WINDOW *win = reinterpret_cast<WINDOW *>(2);
        EXPECT_CALL(mock_ncurses, initscr())
            .Times(AtLeast(1))
            .WillRepeatedly(Return(root));
        EXPECT_CALL(mock_ncurses, subwin(_, _, _, _, _))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(win));
        EXPECT_CALL(mock_ncurses, endwin())
            .Times(AtLeast(0))
            .WillRepeatedly(Return(OK));

        term = std::make_unique<Terminal>();
        term->start();
    }

    void TearDown(void)
    {
        restore_library();
        clear_colors();
    }
};

TEST(Terminal, initscr_failure_throws)
{
    NiceMock<MockNcurses> mock_ncurses;
    set_library("ncurses", mock_ncurses);
    EXPECT_CALL(mock_ncurses, initscr())
        .Times(AtLeast(0))
        .WillOnce(Return(nullptr));
    ASSERT_THROW(Terminal().start(), ResourceError);
    restore_library();
}

TEST_F(TerminalTest, fails_second_start)
{
    ASSERT_THROW(Terminal().start(), std::logic_error);
}

TEST_F(TerminalTest, refreshes)
{
    term->refresh();
}

TEST_F(TerminalTest, dimensions)
{
    ASSERT_EQ(term->columns(), 0);
    ASSERT_EQ(term->rows(), 0);
}

TEST_F(TerminalTest, colored_terminal)
{
    term.reset();
    EXPECT_CALL(mock_ncurses, has_colors()).Times(1).WillOnce(Return(true));
    ASSERT_NO_THROW(Terminal().start());
}

TEST(Terminal, null_stdscr)
{
    ASSERT_THROW(Terminal().start(), ResourceError);
    clear_colors();
}
